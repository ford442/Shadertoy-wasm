#include "../../include/shader/shader_webgpu.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <cstring> // For memcpy
#include <algorithm> // For std::min

// --- Static callback implementations ---

void WebGPUComputePipeline::onAdapterRequestEnded(WGPURequestAdapterStatus status, WGPUAdapter adapter, const char* message, void* userdata) {
    WebGPUComputePipeline* pipeline = static_cast<WebGPUComputePipeline*>(userdata);
    if (pipeline) {
        pipeline->handleAdapterRequestEnded(status, adapter, message);
    }
}

void WebGPUComputePipeline::onDeviceRequestEnded(WGPURequestDeviceStatus status, WGPUDevice device, const char* message, void* userdata) {
    WebGPUComputePipeline* pipeline = static_cast<WebGPUComputePipeline*>(userdata);
    if (pipeline) {
        pipeline->handleDeviceRequestEnded(status, device, message);
    }
}

void WebGPUComputePipeline::onStagingBufferMapCallback(WGPUBufferMapAsyncStatus status, void* userdata) {
    // This callback is part of the runCompute's mapAsync call.
    // It signals the completion of the buffer mapping.
    // The actual data handling is done in runCompute after wgpuDevicePoll.
    if (status != WGPUBufferMapAsyncStatus_Success) {
        std::cerr << "Error: Staging buffer map failed with status: " << status << std::endl;
    }
    // Userdata could be a pointer to a flag or a condition variable to signal completion.
    // For simplicity in this refactor, runCompute will poll or use a simple flag.
    if (userdata) {
        bool* map_success_flag = static_cast<bool*>(userdata);
        *map_success_flag = (status == WGPUBufferMapAsyncStatus_Success);
    }
}

void WebGPUComputePipeline::deviceLostCallback(WGPUDeviceLostReason reason, char const * message, void * userdata) {
    std::cerr << "WebGPU Device Lost: " << message << " (reason: " << reason << ")" << std::endl;
    WebGPUComputePipeline* pipeline = static_cast<WebGPUComputePipeline*>(userdata);
    if (pipeline) {
        pipeline->initialized_ = false;
        pipeline->releaseResources(); // Clean up all resources on device loss
        // TODO: Implement re-initialization logic if desired
    }
}

void WebGPUComputePipeline::uncapturedErrorCallback(WGPUErrorType type, char const * message, void * userdata) {
    std::cerr << "WebGPU Uncaptured Error: " << message << " (type: " << type << ")" << std::endl;
    // Userdata is not used here in this basic setup
}

// --- Constructor & Destructor ---

// Function prototype for rd_fl, assuming it's declared in a header included by shader_webgpu.hpp
// If not, we might need to include its actual header or provide a prototype here.
// For now, assume shader_webgpu.hpp or one of its includes (like emscripten.h or a utility header) makes rd_fl available.
// If rd_fl is static in shader_webgpu.hpp, this won't work directly.
// Let's assume rd_fl is globally accessible for now as per its usage in Run::strt.
extern char * rd_fl(const char * Fnm); // Make sure rd_fl is accessible

WebGPUComputePipeline::WebGPUComputePipeline(const std::string& shader_filepath, const std::string& entry_point, size_t input_size_bytes, size_t result_size_bytes)
    : entry_point_(entry_point), // shader_source_ will be initialized below
      input_buffer_size_bytes_(input_size_bytes),
      result_buffer_size_bytes_(result_size_bytes),
      initialized_(false),
      buffers_created_(false) {

    // Load shader source from file
    char* loaded_shader_c_str = rd_fl(shader_filepath.c_str());
    if (!loaded_shader_c_str) {
        std::cerr << "FATAL: Failed to read shader file: " << shader_filepath << std::endl;
        // shader_source_ remains empty, initialization will likely fail later or should be flagged
        // Consider throwing an exception or setting an error state
    } else {
        shader_source_ = loaded_shader_c_str;
        free(loaded_shader_c_str); // Free memory allocated by rd_fl
    }

    input_data_.resize(input_buffer_size_bytes_, 0); // Initialize with zeros
    if (result_buffer_size_bytes_ % sizeof(uint32_t) != 0) {
        // This could be an error or require padding depending on shader alignment requirements
        std::cerr << "Warning: result_buffer_size_bytes (" << result_buffer_size_bytes_
                  << ") is not a multiple of sizeof(uint32_t) (" << sizeof(uint32_t) << ")." << std::endl;
    }
    result_data_.resize(result_buffer_size_bytes_ / sizeof(uint32_t)); // Result data will be populated by the compute shader.

    WGPUInstanceDescriptor instance_desc = {};
    instance_ = wgpuCreateInstance(&instance_desc);

    if (!instance_) {
        std::cerr << "FATAL: Failed to create WebGPU instance." << std::endl;
        // No recovery possible here, object is not usable.
        return;
    }

    adapter_options_ = {};
    adapter_options_.powerPreference = WGPUPowerPreference_HighPerformance;
    adapter_options_.forceFallbackAdapter = false;

    device_descriptor_ = {};
    device_descriptor_.label = "WebGPUComputePipeline Device";
    device_descriptor_.lostCallback = WebGPUComputePipeline::deviceLostCallback;
    device_descriptor_.lostCallbackUserdata = this;
    // Required limits (can be set to query adapter limits later if needed)
    device_descriptor_.requiredLimits = nullptr; // Use default limits

    shader_module_wgsl_desc_ = {};
    shader_module_wgsl_desc_.chain.sType = WGPUSType_ShaderModuleWGSLDescriptor;
    shader_module_desc_ = {};
    shader_module_desc_.nextInChain = &shader_module_wgsl_desc_.chain;
    shader_module_desc_.label = "Compute Shader Module";
}

WebGPUComputePipeline::~WebGPUComputePipeline() {
    releaseResources();
}

void WebGPUComputePipeline::releaseResources() {
    if (bind_group_) { wgpuBindGroupRelease(bind_group_); bind_group_ = nullptr; }
    if (bind_group_layout_) { wgpuBindGroupLayoutRelease(bind_group_layout_); bind_group_layout_ = nullptr; }
    // Pipeline layout is owned by pipeline, but if created separately and stored:
    // if (pipeline_layout_) { wgpuPipelineLayoutRelease(pipeline_layout_); pipeline_layout_ = nullptr; }
    if (pipeline_) { wgpuComputePipelineRelease(pipeline_); pipeline_ = nullptr; }
    if (compute_module_) { wgpuShaderModuleRelease(compute_module_); compute_module_ = nullptr; }

    if (staging_buffer_) {
        if (wgpuBufferGetMapState(staging_buffer_) != WGPUBufferMapState_Unmapped) {
            wgpuBufferUnmap(staging_buffer_); // Ensure unmapped before release
        }
        wgpuBufferRelease(staging_buffer_); staging_buffer_ = nullptr;
    }
    if (result_buffer_) { wgpuBufferRelease(result_buffer_); result_buffer_ = nullptr; }
    if (input_buffer_) { wgpuBufferRelease(input_buffer_); input_buffer_ = nullptr; }

    // Queue is obtained from device, not released separately by us unless ref/released.
    queue_ = nullptr;

    if (device_) { wgpuDeviceRelease(device_); device_ = nullptr; }
    if (adapter_) { wgpuAdapterRelease(adapter_); adapter_ = nullptr; }
    if (instance_) { wgpuInstanceRelease(instance_); instance_ = nullptr; }

    initialized_ = false;
    buffers_created_ = false;
    std::cout << "WebGPU resources released." << std::endl;
}

// --- Public Methods ---

bool WebGPUComputePipeline::initialize() {
    if (initialized_) {
        std::cout << "WebGPUComputePipeline already initialized." << std::endl;
        return true;
    }
    if (!instance_) {
        std::cerr << "WebGPU instance is null. Cannot initialize." << std::endl;
        return false;
    }
    std::cout << "Requesting WebGPU adapter..." << std::endl;
    wgpuInstanceRequestAdapter(instance_, &adapter_options_, WebGPUComputePipeline::onAdapterRequestEnded, this);
    // Initialization continues asynchronously in callbacks.
    // Consider this method as "startInitialization". isInitialized() reflects true state.
    return true;
}

// --- Instance methods for callbacks ---

void WebGPUComputePipeline::handleAdapterRequestEnded(WGPURequestAdapterStatus status, WGPUAdapter adapter, const char* message) {
    if (status == WGPURequestAdapterStatus_Success && adapter) {
        adapter_ = adapter;
        // Log adapter properties (optional)
        WGPUAdapterProperties properties = {};
        wgpuAdapterGetProperties(adapter_, &properties);
        std::cout << "WebGPU Adapter obtained: " << (properties.name ? properties.name : "N/A")
                  << ", Backend: " << properties.backendType
                  << ", Type: " << properties.adapterType << std::endl;
        wgpuAdapterPropertiesFreeMembers(properties);


        if (!setupDevice()) {
            std::cerr << "Failed to setup WebGPU device after adapter acquisition." << std::endl;
            releaseResources();
        }
    } else {
        std::cerr << "Failed to get WebGPU adapter. Status: " << status << ", Message: " << (message ? message : "N/A") << std::endl;
        adapter_ = nullptr;
        // No recovery path here, initialization failed.
    }
}

void WebGPUComputePipeline::handleDeviceRequestEnded(WGPURequestDeviceStatus status, WGPUDevice device, const char* message) {
    if (status == WGPURequestDeviceStatus_Success && device) {
        device_ = device;
        std::cout << "WebGPU Device obtained successfully." << std::endl;

        wgpuDeviceSetUncapturedErrorCallback(device_, WebGPUComputePipeline::uncapturedErrorCallback, nullptr);
        // It's good practice to also set a device lost callback if not already set in descriptor
        // wgpuDeviceSetDeviceLostCallback(device_, WebGPUComputePipeline::deviceLostCallback, this);


        queue_ = wgpuDeviceGetQueue(device_);
        if (!queue_) {
            std::cerr << "Failed to get WebGPU queue from device." << std::endl;
            releaseResources();
            return;
        }

        if (!createBuffers()) { std::cerr << "Buffer creation failed." << std::endl; releaseResources(); return; }
        if (!createShaderModule()) { std::cerr << "Shader module creation failed." << std::endl; releaseResources(); return; }
        if (!createPipeline()) { std::cerr << "Pipeline creation failed." << std::endl; releaseResources(); return; }

        initialized_ = true;
        std::cout << "WebGPUComputePipeline initialized successfully." << std::endl;

    } else {
        std::cerr << "Failed to get WebGPU device. Status: " << status << ", Message: " << (message ? message : "N/A") << std::endl;
        device_ = nullptr;
        // Adapter might still be valid, but device request failed. Clean up.
        releaseResources();
    }
}

void WebGPUComputePipeline::handleStagingBufferMap(WGPUBufferMapAsyncStatus status) {
    // This is the instance method that would be called if onStagingBufferMapCallback
    // was designed to call an instance method directly.
    // Current runCompute uses a lambda with a boolean flag passed as userdata.
    // This function is kept for potential future refactoring of async handling.
    if (status == WGPUBufferMapAsyncStatus_Success) {
        std::cout << "Staging buffer mapped successfully (instance method)." << std::endl;
        // Data processing would happen here in a fully async model
    } else {
        std::cerr << "Failed to map staging buffer (instance method): Status " << status << std::endl;
    }
}


// --- Internal setup methods ---
bool WebGPUComputePipeline::setupDevice() {
    if (!adapter_) {
        std::cerr << "Cannot setup device, adapter not available." << std::endl;
        return false;
    }
    std::cout << "Requesting WebGPU device..." << std::endl;
    // device_descriptor_ is already configured in the constructor
    wgpuAdapterRequestDevice(adapter_, &device_descriptor_, WebGPUComputePipeline::onDeviceRequestEnded, this);
    return true;
}

bool WebGPUComputePipeline::createBuffers() {
    std::cout << "Creating buffers..." << std::endl;
    if (!device_) { std::cerr << "Device not available for buffer creation." << std::endl; return false; }

    input_buffer_desc_ = {};
    input_buffer_desc_.label = "Input Storage Buffer";
    input_buffer_desc_.usage = WGPUBufferUsage_Storage | WGPUBufferUsage_CopyDst;
    input_buffer_desc_.size = input_buffer_size_bytes_;
    input_buffer_ = wgpuDeviceCreateBuffer(device_, &input_buffer_desc_);
    if (!input_buffer_) { std::cerr << "Failed to create input buffer." << std::endl; return false; }

    result_buffer_desc_ = {};
    result_buffer_desc_.label = "Result Storage Buffer";
    result_buffer_desc_.usage = WGPUBufferUsage_Storage | WGPUBufferUsage_CopySrc;
    result_buffer_desc_.size = result_buffer_size_bytes_;
    result_buffer_ = wgpuDeviceCreateBuffer(device_, &result_buffer_desc_);
    if (!result_buffer_) { std::cerr << "Failed to create result buffer." << std::endl; return false; }

    staging_buffer_desc_ = {};
    staging_buffer_desc_.label = "Staging Buffer (Readback)";
    staging_buffer_desc_.usage = WGPUBufferUsage_MapRead | WGPUBufferUsage_CopyDst;
    staging_buffer_desc_.size = result_buffer_size_bytes_;
    staging_buffer_ = wgpuDeviceCreateBuffer(device_, &staging_buffer_desc_);
    if (!staging_buffer_) { std::cerr << "Failed to create staging buffer." << std::endl; return false; }

    buffers_created_ = true;
    std::cout << "Buffers created successfully." << std::endl;
    return true;
}

bool WebGPUComputePipeline::createShaderModule() {
    std::cout << "Creating shader module..." << std::endl;
    if (!device_ || shader_source_.empty()) {
        std::cerr << "Device or shader source not available for shader module creation." << std::endl;
        return false;
    }
    shader_module_wgsl_desc_.code = shader_source_.c_str();
    compute_module_ = wgpuDeviceCreateShaderModule(device_, &shader_module_desc_);
    if (!compute_module_) { std::cerr << "Failed to create shader module." << std::endl; return false; }
    std::cout << "Shader module created successfully." << std::endl;
    return true;
}

bool WebGPUComputePipeline::createPipeline() {
    std::cout << "Creating compute pipeline..." << std::endl;
    if (!device_ || !compute_module_ || !input_buffer_ || !result_buffer_) {
         std::cerr << "Prerequisites not met for pipeline creation (device, shader, or buffers missing)." << std::endl;
        return false;
    }

    // 1. Bind Group Layout
    std::vector<WGPUBindGroupLayoutEntry> bgl_entries;
    bgl_entries.push_back({nullptr, 0, WGPUShaderStage_Compute, {nullptr, WGPUBufferBindingType_ReadOnlyStorage, false, input_buffer_size_bytes_}}); // Input
    bgl_entries.push_back({nullptr, 1, WGPUShaderStage_Compute, {nullptr, WGPUBufferBindingType_Storage,       false, result_buffer_size_bytes_}}); // Output
    // Add texture entry if used:
    // bgl_entries.push_back({nullptr, 2, WGPUShaderStage_Compute, {}, {}, {nullptr, WGPUStorageTextureAccess_WriteOnly, WGPUTextureFormat_RGBA32Uint, WGPUTextureViewDimension_2D}});


    WGPUBindGroupLayoutDescriptor bgl_desc = {nullptr, "Compute BGL", (uint32_t)bgl_entries.size(), bgl_entries.data()};
    bind_group_layout_ = wgpuDeviceCreateBindGroupLayout(device_, &bgl_desc);
    if (!bind_group_layout_) { std::cerr << "Failed to create bind group layout." << std::endl; return false; }

    // 2. Pipeline Layout
    WGPUPipelineLayoutDescriptor pl_desc = {nullptr, "Compute PL", 1, &bind_group_layout_};
    WGPUPipelineLayout pipeline_layout = wgpuDeviceCreatePipelineLayout(device_, &pl_desc); // Stored temporarily
    if (!pipeline_layout) {
        std::cerr << "Failed to create pipeline layout." << std::endl;
        wgpuBindGroupLayoutRelease(bind_group_layout_); bind_group_layout_ = nullptr;
        return false;
    }

    // 3. Compute Pipeline
    pipeline_desc_ = {}; // zero initialize
    pipeline_desc_.label = "Compute Pipeline";
    pipeline_desc_.layout = pipeline_layout;
    pipeline_desc_.compute.module = compute_module_;
    pipeline_desc_.compute.entryPoint = entry_point_.c_str();

    pipeline_ = wgpuDeviceCreateComputePipeline(device_, &pipeline_desc_);
    wgpuPipelineLayoutRelease(pipeline_layout); // Release local ref, pipeline owns it now.
    if (!pipeline_) {
        std::cerr << "Failed to create compute pipeline." << std::endl;
        // bind_group_layout_ is still valid and needs to be released by releaseResources
        return false;
    }

    // 4. Bind Group
    std::vector<WGPUBindGroupEntry> bg_entries;
    bg_entries.push_back({nullptr, 0, input_buffer_, 0, input_buffer_size_bytes_, nullptr, nullptr});
    bg_entries.push_back({nullptr, 1, result_buffer_, 0, result_buffer_size_bytes_, nullptr, nullptr});
    // Add texture view if used:
    // bg_entries.push_back({nullptr, 2, nullptr, 0, 0, nullptr, texture_view_});


    WGPUBindGroupDescriptor bg_desc = {nullptr, "Compute BG", bind_group_layout_, (uint32_t)bg_entries.size(), bg_entries.data()};
    bind_group_ = wgpuDeviceCreateBindGroup(device_, &bg_desc);
    if (!bind_group_) {
        std::cerr << "Failed to create bind group." << std::endl;
        // pipeline_ and bind_group_layout_ are still valid
        return false;
    }

    std::cout << "Compute pipeline, layout, and bind group created successfully." << std::endl;
    return true;
}

bool WebGPUComputePipeline::runCompute() {
    if (!isInitialized()) {
        std::cerr << "Error: WebGPU pipeline not initialized. Call initialize() first." << std::endl;
        return false;
    }
    if (!pipeline_ || !queue_ || !bind_group_ || !input_buffer_ || !result_buffer_ || !staging_buffer_) {
        std::cerr << "Error: Essential WebGPU resources not available for compute." << std::endl;
        return false;
    }
    //std::cout << "Running compute pass..." << std::endl;

    if (!input_data_.empty()) {
        wgpuQueueWriteBuffer(queue_, input_buffer_, 0, input_data_.data(), input_data_.size());
    }

    WGPUCommandEncoderDescriptor enc_desc = {nullptr, "Compute Command Encoder"};
    WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device_, &enc_desc);
    if (!encoder) { std::cerr << "Failed to create command encoder." << std::endl; return false; }

    WGPUComputePassDescriptor cp_desc = {nullptr, "Main Compute Pass", 0, nullptr};
    WGPUComputePassEncoder pass = wgpuCommandEncoderBeginComputePass(encoder, &cp_desc);
    if (!pass) {
        std::cerr << "Failed to begin compute pass." << std::endl;
        wgpuCommandEncoderRelease(encoder); return false;
    }

    wgpuComputePassEncoderSetPipeline(pass, pipeline_);
    wgpuComputePassEncoderSetBindGroup(pass, 0, bind_group_, 0, nullptr);

    // Determine workgroup counts. This needs to match shader logic.
    // Example: If shader is @workgroup_size(X, Y, Z)
    // And you want to process N total elements.
    // dispatch_x = ceil(N_x / X)
    // dispatch_y = ceil(N_y / Y)
    // dispatch_z = ceil(N_z / Z)
    // The old code used fixed (4,1,64) in dispatch and shader.
    // Assuming InputBufferUnits = 262144, shader workgroup_size(4,1,64)
    // Total invocations per workgroup = 4*1*64 = 256
    // Number of workgroups needed = InputBufferUnits / 256
    // If InputBufferUnits is based on uint32_t elements, and input_buffer_size_bytes_ is its size in bytes:
    // uint32_t total_elements = input_buffer_size_bytes_ / sizeof(uint32_t);
    // uint32_t wg_size_x = 4, wg_size_y = 1, wg_size_z = 64; // From shader
    // uint32_t dispatch_x = (total_elements_x + wg_size_x - 1) / wg_size_x;
    // For now, using the old hardcoded values:
    wgpuComputePassEncoderDispatchWorkgroups(pass, 4, 1, 64);

    wgpuComputePassEncoderEnd(pass);
    wgpuComputePassEncoderRelease(pass);

    wgpuCommandEncoderCopyBufferToBuffer(encoder, result_buffer_, 0, staging_buffer_, 0, result_buffer_size_bytes_);

    WGPUCommandBufferDescriptor cb_desc = {nullptr, "Compute Command Buffer"};
    WGPUCommandBuffer command_buffer = wgpuCommandEncoderFinish(encoder, &cb_desc);
    wgpuCommandEncoderRelease(encoder);
    if (!command_buffer) { std::cerr << "Failed to finish command buffer." << std::endl; return false; }

    wgpuQueueSubmit(queue_, 1, &command_buffer);
    wgpuCommandBufferRelease(command_buffer);

    // Synchronous readback for simplicity in this refactor (matches old wgpu_buffer_map_sync behavior)
    // Note: For production, prefer fully async operations or wgpuDevicePoll with callbacks.
    bool map_success = false;
    wgpuBufferMapAsync(staging_buffer_, WGPUMapMode_Read, 0, result_buffer_size_bytes_, onStagingBufferMapCallback, &map_success);

    // Poll device until map is complete. This is a blocking operation.
    // In a real application, this might be on a separate thread or part of an event loop.
    // For Emscripten, the browser event loop handles polling when control returns to it.
    // For native, wgpuDevicePoll (or wgpuDeviceTick in older APIs) is crucial.
    // This is a simplified busy-wait for native, not ideal.
    #ifndef __EMSCRIPTEN__ // For native builds, poll explicitly
        while (wgpuBufferGetMapState(staging_buffer_) == WGPUBufferMapState_Mapping) { // Or check a flag set by callback
             // wgpuDevicePoll(device_, true, nullptr); // Or wgpuDeviceTick(device) if that's the API
             // The above line is conceptual. The exact polling mechanism depends on wgpu implementation nuances.
             // A common pattern is to poll until the callback sets a flag.
             // For this example, we'll rely on map_success flag set by the callback.
             // This loop needs a proper condition or timeout in real code.
             // For now, we assume the callback will set map_success.
             // A short sleep could prevent pegging CPU but isn't a robust solution.
             // std::this_thread::sleep_for(std::chrono::microseconds(10)); // Example, requires <thread> and <chrono>
             if (map_success || wgpuBufferGetMapState(staging_buffer_) == WGPUBufferMapState_Mapped) break; // Check if callback already ran
             if (wgpuBufferGetMapState(staging_buffer_) == WGPUBufferMapState_Unmapped && !map_success) break; // Error occurred
        }
    #else
        // For Emscripten, mapAsync is truly async. We can't easily make this part synchronous
        // without significant restructuring (e.g. emscripten_sleep or asyncify).
        // The current design will likely lead to issues on web if runCompute expects immediate result.
        // For now, we proceed, but this is a known point of divergence for web.
        // The result_data_ might not be updated when getComputeResult() is called immediately after.
        std::cout << "Warning: On Emscripten, mapAsync is non-blocking. Result may not be immediately available." << std::endl;
    #endif

    if (map_success && wgpuBufferGetMapState(staging_buffer_) == WGPUBufferMapState_Mapped) {
        const void* mapped_range = wgpuBufferGetConstMappedRange(staging_buffer_, 0, result_buffer_size_bytes_);
        if (mapped_range) {
            memcpy(result_data_.data(), mapped_range, result_buffer_size_bytes_);
        } else {
            std::cerr << "Error: Failed to get mapped range even after successful map." << std::endl;
            map_success = false;
        }
        wgpuBufferUnmap(staging_buffer_);
    } else {
        std::cerr << "Error: Staging buffer map failed or was not completed successfully. Map state: " << wgpuBufferGetMapState(staging_buffer_) << std::endl;
        if (wgpuBufferGetMapState(staging_buffer_) != WGPUBufferMapState_Unmapped) {
             wgpuBufferUnmap(staging_buffer_); // Attempt to cleanup
        }
        return false;
    }

    //std::cout << "Compute pass finished." << std::endl;
    return map_success;
}

void WebGPUComputePipeline::setInputDataValue(uint8_t value, size_t index) {
    if (index < input_data_.size()) {
        input_data_[index] = value;
    } else {
        std::cerr << "setInputDataValue: Index " << index << " out of bounds for size " << input_data_.size() << "." << std::endl;
    }
}

void WebGPUComputePipeline::setInputData(const std::vector<uint8_t>& data) {
    if (data.size() != input_buffer_size_bytes_) {
        std::cerr << "setInputData: Provided data size (" << data.size()
                  << ") does not match expected input buffer size (" << input_buffer_size_bytes_
                  << "). Data will be truncated or not fully utilized." << std::endl;
        // Copy what fits
        size_t bytes_to_copy = std::min(data.size(), input_data_.size());
        memcpy(input_data_.data(), data.data(), bytes_to_copy);
        // If provided data is smaller, the rest of input_data_ remains as is (potentially old data or zeros)
    } else {
        input_data_ = data; // Direct copy if sizes match
    }
}

const std::vector<uint32_t>& WebGPUComputePipeline::getComputeResult() const {
    // Ensure runCompute has successfully populated this.
    // For true async, this might return stale data if called too soon.
    return result_data_;
}
