#include "../../include/vanilla/cropcircle.hpp"
#include <vector>
#include <numbers>
#include <cmath>         // For cos, sin, M_PI, round
#include <limits>        // For numeric_limits
#include <algorithm>     // For std::fill (optional, for clearing output buffer)
#include <cstdio>        // For printf (optional error logging)

// Define M_PI if not available (often is in <cmath>)
#ifndef M_PI
// #define M_PI 3.14159265358979323846
#define M_PI std::numbers::pi_v
#endif

EGLConfig eglconfig=NULL;

EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EmscriptenWebGLContextAttributes attr;

float max;
float min;
float sum;
float avgSum;
float minSum;
float maxSum;

EGLDisplay display;
EGLContext contextegl;
EGLSurface surface;
EGLint config_size,major,minor;

double wi,hi;

int Size;
GLfloat S;

static constexpr EGLint anEglCtxAttribs2[]={
// EGL_CONTEXT_MAJOR_VERSION_KHR,2,
// EGL_CONTEXT_MINOR_VERSION_KHR,0,
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_CONTEXT_MAJOR_VERSION_KHR,3,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE
};

static constexpr EGLint attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
  // Google Colab
/*
If BT-2020 is set to linear, it will degrade the fidelity of image representation. 
This is because the BT.2020 color space is a non-linear color space, and when it is set to linear,
the values of the components are directly proportional to the perceived brightness or lightness of the color.
This means that the colors in the image will be misrepresented,
and the image will not be as accurate as it would be if it were in the original BT.2020 color space.
*/
// EGL_GL_COLORSPACE_LINEAR_KHR, 
// EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// / EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_BACK_BUFFER,
EGL_NONE
};

static constexpr EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FIXED_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT|EGL_OPENGL_BIT,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_BIT,
// EGL_CONFORMANT,EGL_NONE,
//  EGL_CONFIG_CAVEAT,EGL_NONE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_TRIPLE_BUFFER_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV, //   available in OpenGL
EGL_SURFACE_TYPE,EGL_SWAP_BEHAVIOR_PRESERVED_BIT|EGL_MULTISAMPLE_RESOLVE_BOX_BIT,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
//  EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE, // "...the context will only support OpenGL ES 3.0 and later features."
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI, //  available in OpenGL
// EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY,EGL_NO_RESET_NOTIFICATION,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_COLOR_BUFFER_TYPE,EGL_RGB_BUFFER,
EGL_LUMINANCE_SIZE,0, // available in OpenGL
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_BUFFER_SIZE,32,
EGL_SAMPLE_BUFFERS,EGL_TRUE,
EGL_COVERAGE_BUFFERS_NV,EGL_TRUE, // available in GLES 3.1
EGL_COVERAGE_SAMPLES_NV,8,
EGL_SAMPLES,4,
EGL_NONE
};

void emsc(int leng,float *ptr){
// eglBindAPI(EGL_OPENGL_ES_API);
glDisable(GL_DITHER);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx,"GL_EXTENSIONS");
emscripten_webgl_enable_extension(ctx,"GL_ALL_EXTENSIONS");
emscripten_webgl_enable_extension(ctx,"KHR_no_error");
emscripten_webgl_enable_extension(ctx,"GL_REGAL_enable");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_client_extensions");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_platform_angle");
emscripten_webgl_enable_extension(ctx,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_sample_shading");
emscripten_webgl_enable_extension(ctx,"ARB_framebuffer_object");
emscripten_webgl_enable_extension(ctx,"ARB_framebuffer_sRGB");
emscripten_webgl_enable_extension(ctx,"NV_half_float");
emscripten_webgl_enable_extension(ctx,"OES_texture_half_float");
emscripten_webgl_enable_extension(ctx,"ARB_fragment_program");
emscripten_webgl_enable_extension(ctx,"NV_fragment_program_option");
emscripten_webgl_enable_extension(ctx,"NV_fragment_program");
emscripten_webgl_enable_extension(ctx,"NV_fragment_program2");
emscripten_webgl_enable_extension(ctx,"NV_float_buffer");
emscripten_webgl_enable_extension(ctx,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx,"EXT_polygon_offset_clamp");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counter_ops");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample_resolve");
emscripten_webgl_enable_extension(ctx,"EGL_NV_quadruple_buffer");
emscripten_webgl_enable_extension(ctx,"NV_depth_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"ARB_texture_float");
emscripten_webgl_enable_extension(ctx,"ARB_texture_half_float");
emscripten_webgl_enable_extension(ctx,"EGL_IMG_context_priority");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_sample_variables");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_create_context");
emscripten_webgl_enable_extension(ctx,"ARB_robustness");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_create_context_robustness");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb_linear");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_pq");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3_linear");
// emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_display_p3_passthrough");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx,"OES_texture_float");
emscripten_webgl_enable_extension(ctx,"NV_gpu_shader4");
emscripten_webgl_enable_extension(ctx,"NV_gpu_shader5");
emscripten_webgl_enable_extension(ctx,"NV_vertex_buffer_unified_memory");
emscripten_webgl_enable_extension(ctx,"NV_gpu_program5");
emscripten_webgl_enable_extension(ctx,"NV_vertex_attrib_integer_64bit");
emscripten_webgl_enable_extension(ctx,"ARB_gpu_shader_fp64");
emscripten_webgl_enable_extension(ctx,"EXT_vertex_attrib_64bit");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB_write_control");
emscripten_webgl_enable_extension(ctx,"OES_sample_shading");
emscripten_webgl_enable_extension(ctx,"EXT_multisample_compatibility");
emscripten_webgl_enable_extension(ctx,"OES_vertex_half_float");
emscripten_webgl_enable_extension(ctx,"NV_framebuffer_multisample");
emscripten_webgl_enable_extension(ctx,"ARB_enhanced_layouts");
emscripten_webgl_enable_extension(ctx,"ARB_shading_language_420pack");
emscripten_webgl_enable_extension(ctx,"ARB_get_program_binary");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(ctx,"EXT_bindable_uniform");
emscripten_webgl_enable_extension(ctx,"EXT_geometry_shader4");
// emscripten_webgl_enable_extension(ctx,"ARB_ES2_compatibility"); // limits to OpenGL ES 2.0
emscripten_webgl_enable_extension(ctx,"ARB_direct_state_access");
emscripten_webgl_enable_extension(ctx,"ARB_multitexture");
emscripten_webgl_enable_extension(ctx,"KHR_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"EXT_texture_norm16");
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_d3d_texture_client_buffer");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_direct3d_display");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_robust_resource_initialization");
emscripten_webgl_enable_extension(ctx,"WEBGL_multi_draw");
// emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"WEBGL_render_shared_exponent");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_device_base");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_device_query");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_output_base");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_platform_base");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_platform_device");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_swap_buffers_with_damage");
emscripten_webgl_enable_extension(ctx,"EGL_NV_cuda_event");
emscripten_webgl_enable_extension(ctx,"EGL_NV_device_cuda");
emscripten_webgl_enable_extension(ctx,"EGL_NV_robustness_video_memory_purge");
emscripten_webgl_enable_extension(ctx,"ARB_texture_view");
emscripten_webgl_enable_extension(ctx,"EXT_float_32_packed_float");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_wait_sync");
emscripten_webgl_enable_extension(ctx,"OES_texture_external");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_image_native_buffer");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_recordable");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_framebuffer_target");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_blob_cache");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_fence_sync");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_native_fence_sync");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_image_base");
emscripten_webgl_enable_extension(ctx,"OES_EGL_image_external");
emscripten_webgl_enable_extension(ctx,"EXT_YUV_target");
emscripten_webgl_enable_extension(ctx,"GL_ARB_texture_rgb10_a2ui");
emscripten_webgl_enable_extension(ctx,"ARB_texture_multisample");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_surface_SMPTE2086_metadata");
emscripten_webgl_enable_extension(ctx,"ARB_texture_storage");
emscripten_webgl_enable_extension(ctx,"ARB_multisample_texture");
emscripten_webgl_enable_extension(ctx,"ARB_texture_cube_map_array");
emscripten_webgl_enable_extension(ctx,"ARB_texture_buffer_object");
emscripten_webgl_enable_extension(ctx,"ARB_texture_view");
emscripten_webgl_enable_extension(ctx,"ARB_shader_storage_buffer_object");
emscripten_webgl_enable_extension(ctx,"ARB_compute_shader");
emscripten_webgl_enable_extension(ctx,"ARB_tessellation_shader");
emscripten_webgl_enable_extension(ctx,"ARB_draw_elements_base_vertex");
emscripten_webgl_enable_extension(ctx,"ARB_provoking_vertex");
emscripten_webgl_enable_extension(ctx,"ARB_seamless_cube_map_per_texture");
emscripten_webgl_enable_extension(ctx,"ARB_texture_compression_rgtc");
emscripten_webgl_enable_extension(ctx,"ARB_texture_compression_bptc");
emscripten_webgl_enable_extension(ctx,"ARB_texture_compression_astc");
emscripten_webgl_enable_extension(ctx,"ARB_texture_filter_minmax");
emscripten_webgl_enable_extension(ctx,"ARB_depth_texture");
emscripten_webgl_enable_extension(ctx,"ARB_multisample");
emscripten_webgl_enable_extension(ctx,"ARB_framebuffer_multisample");
emscripten_webgl_enable_extension(ctx,"ARB_shader_objects");
GLuint buffer,Rbuffer,Fbuffer;
glGenFramebuffers(1,&Fbuffer);
glGenRenderbuffers(1,&Rbuffer);
glGenBuffers(1, &buffer);
glRenderbufferStorage(GL_RENDERBUFFER,GL_RGBA32F,Size,Size);
glBindBuffer(GL_RENDERBUFFER,buffer);
glBufferData(GL_RENDERBUFFER,sizeof(ptr),ptr,GL_DYNAMIC_DRAW);
glBindBuffer(GL_RENDERBUFFER,0);
glViewport(0,0,GLint(Size),GLint(Size));
}

void emscA(){
emscripten_get_element_css_size("zimag",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
// eglBindAPI(0);
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_TRUE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
ctx=emscripten_webgl_create_context("#zimag",&attr);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
emscripten_webgl_make_context_current(ctx);
surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
}


void rotateFrameEmbindVal(int angle, int wid, int hig, emscripten::val FptrVal, emscripten::val NFptrVal)
{
    if (wid <= 0 || hig <= 0) {
        printf("Error (rotateFrameEmbindVal): Invalid dimensions (%d x %d).\n", wid, hig);
        return;
    }

    size_t fptr_byte_offset = 0;
    size_t fptr_length = 0; // length in elements
    size_t nfptr_byte_offset = 0;
    size_t nfptr_length = 0; // length in elements

    try {
        if (!FptrVal["byteOffset"].isUndefined() && FptrVal["byteOffset"].isNumber()) {
            fptr_byte_offset = FptrVal["byteOffset"].as<size_t>();
        } else { throw std::runtime_error("FptrVal.byteOffset missing or not a number"); }

        if (!FptrVal["length"].isUndefined() && FptrVal["length"].isNumber()) {
            fptr_length = FptrVal["length"].as<size_t>();
        } else { throw std::runtime_error("FptrVal.length missing or not a number"); }

        if (!NFptrVal["byteOffset"].isUndefined() && NFptrVal["byteOffset"].isNumber()) {
            nfptr_byte_offset = NFptrVal["byteOffset"].as<size_t>();
        } else { throw std::runtime_error("NFptrVal.byteOffset missing or not a number"); }

        if (!NFptrVal["length"].isUndefined() && NFptrVal["length"].isNumber()) {
            nfptr_length = NFptrVal["length"].as<size_t>();
        } else { throw std::runtime_error("NFptrVal.length missing or not a number"); }
    } catch (const std::exception& e) {
        printf("Error (rotateFrameEmbindVal): Failed to get properties from JS TypedArray val: %s\n", e.what());
        return;
    }

    size_t expected_elements = static_cast<size_t>(wid) * hig * 4; // RGBA

    if (fptr_length < expected_elements) {
        printf("Error (rotateFrameEmbindVal): Input buffer view is too small. Expected elements: %zu, Got: %zu\n",
               expected_elements, fptr_length);
        return;
    }
    if (nfptr_length < expected_elements) {
        printf("Error (rotateFrameEmbindVal): Output buffer view is too small. Expected elements: %zu, Got: %zu\n",
               expected_elements, nfptr_length);
        return;
    }

    // --- Get direct pointers into the Emscripten HEAP ---
    // CRITICAL ASSUMPTION: FptrVal/NFptrVal MUST be views over Module.HEAPF32.buffer.
    float* Fptr = reinterpret_cast<float*>(static_cast<uintptr_t>(fptr_byte_offset));
    float* NFptr = reinterpret_cast<float*>(static_cast<uintptr_t>(nfptr_byte_offset));

    // --- Rotation Logic ---
    double angleRad = angle * M_PI / 180.0;
    double cosAngle = std::cos(angleRad);
    double sinAngle = std::sin(angleRad);

    // Calculate the center of the image
    // Using floating point for precision in center calculation
    double centerX = static_cast<double>(wid) / 2.0;
    double centerY = static_cast<double>(hig) / 2.0;

    // Caller (JavaScript) should ensure NFptr buffer is cleared beforehand.
    // Example: NFptrView.fill(0) in JS.
    // If not cleared, old pixel data might remain in areas not overwritten.

    for (int y = 0; y < hig; ++y) {
        for (int x = 0; x < wid; ++x) {
            size_t source_index = (static_cast<size_t>(y) * wid + x) * 4;

            // Original pixel coordinates (as doubles for precision)
            double currentX_double = static_cast<double>(x);
            double currentY_double = static_cast<double>(y);

            // 1. Translate coordinates so the center of the image is the origin
            double translatedX = currentX_double - centerX;
            double translatedY = currentY_double - centerY;

            // 2. Rotate the translated coordinates
            double rotatedX_at_origin = translatedX * cosAngle - translatedY * sinAngle;
            double rotatedY_at_origin = translatedX * sinAngle + translatedY * cosAngle;

            // 3. Translate the rotated coordinates back to the original system
            double newX_double = rotatedX_at_origin + centerX;
            double newY_double = rotatedY_at_origin + centerY;

            // Round to the nearest integer pixel
            int newX = static_cast<int>(std::round(newX_double));
            int newY = static_cast<int>(std::round(newY_double));

            // Check if the new coordinates are within the bounds of the output image
            if (newX >= 0 && newX < wid && newY >= 0 && newY < hig) {
                size_t target_index = (static_cast<size_t>(newY) * wid + newX) * 4;

                // Copy pixel data (RGBA)
                // Bounds check on source_index is implicitly handled by loop bounds
                // Bounds check on target_index + 3 vs nfptr_length should be fine due to newX/newY check and initial nfptr_length check
                NFptr[target_index]     = Fptr[source_index];
                NFptr[target_index + 1] = Fptr[source_index + 1];
                NFptr[target_index + 2] = Fptr[source_index + 2];
                NFptr[target_index + 3] = Fptr[source_index + 3];
            }
        }
    }
}


void rotateFrameEmbindValFloat(int angle, int wid, int hig, emscripten::val FptrVal, emscripten::val NFptrVal)
{
    if (wid <= 0 || hig <= 0) {
        printf("Error (rotateFrameEmbindVal): Invalid dimensions (%d x %d).\n", wid, hig);
        return;
    }

    size_t fptr_byte_offset = 0;
    size_t fptr_length = 0; // length in elements
    size_t nfptr_byte_offset = 0;
    size_t nfptr_length = 0; // length in elements

    try {
        if (!FptrVal["byteOffset"].isUndefined() && FptrVal["byteOffset"].isNumber()) {
            fptr_byte_offset = FptrVal["byteOffset"].as<size_t>();
        } else { throw std::runtime_error("FptrVal.byteOffset missing or not a number"); }

        if (!FptrVal["length"].isUndefined() && FptrVal["length"].isNumber()) {
            fptr_length = FptrVal["length"].as<size_t>();
        } else { throw std::runtime_error("FptrVal.length missing or not a number"); }

        if (!NFptrVal["byteOffset"].isUndefined() && NFptrVal["byteOffset"].isNumber()) {
            nfptr_byte_offset = NFptrVal["byteOffset"].as<size_t>();
        } else { throw std::runtime_error("NFptrVal.byteOffset missing or not a number"); }

        if (!NFptrVal["length"].isUndefined() && NFptrVal["length"].isNumber()) {
            nfptr_length = NFptrVal["length"].as<size_t>();
        } else { throw std::runtime_error("NFptrVal.length missing or not a number"); }
    } catch (const std::exception& e) {
        printf("Error (rotateFrameEmbindVal): Failed to get properties from JS TypedArray val: %s\n", e.what());
        return;
    }

    size_t expected_elements = static_cast<size_t>(wid) * hig * 4; // RGBA

    if (fptr_length < expected_elements) {
        printf("Error (rotateFrameEmbindVal): Input buffer view is too small. Expected elements: %zu, Got: %zu\n",
               expected_elements, fptr_length);
        return;
    }
    if (nfptr_length < expected_elements) {
        printf("Error (rotateFrameEmbindVal): Output buffer view is too small. Expected elements: %zu, Got: %zu\n",
               expected_elements, nfptr_length);
        return;
    }

    // --- Get direct pointers into the Emscripten HEAP ---
    // CRITICAL ASSUMPTION: FptrVal/NFptrVal MUST be views over Module.HEAPF32.buffer.
    float* Fptr = reinterpret_cast<float*>(static_cast<uintptr_t>(fptr_byte_offset));
    float* NFptr = reinterpret_cast<float*>(static_cast<uintptr_t>(nfptr_byte_offset));

    // --- Rotation Logic ---
    float angleRad = angle * M_PI / 180.0;
    float cosAngle = std::cos(angleRad);
    float sinAngle = std::sin(angleRad);

    // Calculate the center of the image
    // Using floating point for precision in center calculation
    float centerX = static_cast<float>(wid) / 2.0;
    float centerY = static_cast<float>(hig) / 2.0;

    // Caller (JavaScript) should ensure NFptr buffer is cleared beforehand.
    // Example: NFptrView.fill(0) in JS.
    // If not cleared, old pixel data might remain in areas not overwritten.

    for (int y = 0; y < hig; ++y) {
        for (int x = 0; x < wid; ++x) {
            size_t source_index = (static_cast<size_t>(y) * wid + x) * 4;

            // Original pixel coordinates (as floats for precision)
            float currentX_float = static_cast<float>(x);
            float currentY_float = static_cast<float>(y);

            // 1. Translate coordinates so the center of the image is the origin
            float translatedX = currentX_float - centerX;
            float translatedY = currentY_float - centerY;

            // 2. Rotate the translated coordinates
            float rotatedX_at_origin = translatedX * cosAngle - translatedY * sinAngle;
            float rotatedY_at_origin = translatedX * sinAngle + translatedY * cosAngle;

            // 3. Translate the rotated coordinates back to the original system
            float newX_float = rotatedX_at_origin + centerX;
            float newY_float = rotatedY_at_origin + centerY;

            // Round to the nearest integer pixel
            int newX = static_cast<int>(std::round(newX_float));
            int newY = static_cast<int>(std::round(newY_float));

            // Check if the new coordinates are within the bounds of the output image
            if (newX >= 0 && newX < wid && newY >= 0 && newY < hig) {
                size_t target_index = (static_cast<size_t>(newY) * wid + newX) * 4;

                // Copy pixel data (RGBA)
                // Bounds check on source_index is implicitly handled by loop bounds
                // Bounds check on target_index + 3 vs nfptr_length should be fine due to newX/newY check and initial nfptr_length check
                NFptr[target_index]     = Fptr[source_index];
                NFptr[target_index + 1] = Fptr[source_index + 1];
                NFptr[target_index + 2] = Fptr[source_index + 2];
                NFptr[target_index + 3] = Fptr[source_index + 3];
            }
        }
    }
}

boost::function<void(int,float *,float *)>avgFrm=[](int leng,float *ptr,float *aptr){
max=0.0f;
min=255.0f;
sum=0.0f;
avgSum=0.0f;
minSum=0.0f;
maxSum=0.0f;
for (int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];}
}
sum=sum/leng;
aptr[0]=sum;
aptr[1]=min;
aptr[2]=max;
return;
};

emscripten::val processFloatData(emscripten::val js_float32_array_val) {
std::vector<float> cpp_vector = emscripten::vecFromJSArray<float>(js_float32_array_val);
if (cpp_vector.size() == 0) {
return emscripten::val::object();
}
double sum = 0.0;
float min_val = std::numeric_limits<float>::max();
float max_val = std::numeric_limits<float>::lowest();
for(size_t i = 0; i < cpp_vector.size(); ++i) {
float val = cpp_vector[i];
sum += val;
if (val < min_val) min_val = val;
if (val > max_val) max_val = val;
}
double avg = sum / cpp_vector.size();
emscripten::val result = emscripten::val::object();
result.set("average", avg);
result.set("min", min_val);
result.set("max", max_val);
return result;
}

EMSCRIPTEN_BINDINGS(my_module) {
emscripten::function("processFloatData", &processFloatData);
emscripten::function("rotat", &rotateFrameEmbindVal);
emscripten::function("rotatF", &rotateFrameEmbindValFloat);
    // If you needed to return arrays back to JS you could bind std::vector
    // emscripten::register_vector<float>("FloatVector");
}

extern "C" {

void nano(int leng,float *ptr,float *aptr){
avgFrm(leng,ptr,aptr);
}

/*
void rotat(int angle,int wd,int hi,float *Fptr,float *NFptr){
rotateFrame(angle,wd,hi,Fptr,NFptr);
}
*/

void emem(int leng,float *ptr){
emsc(leng,ptr);
}

}

EM_JS(void,ma,(),{
"use strict";
var winSize=parseInt(window.innerHeight,10);
var scanvas=document.createElement('canvas');
var icanvas=document.getElementById('imag2');
var bcanvas=document.getElementById('imag3');
// icanvas.setAttribute("style","opacity:0.422");
scanvas.imageSmoothingEnabled=false;
icanvas.imageSmoothingEnabled=false;
bcanvas.imageSmoothingEnabled=false;
scanvas.id='zimag';
scanvas.imageRendering='pixelated';
icanvas.imageRendering='pixelated';
bcanvas.imageRendering='pixelated';
scanvas.width=winSize;
scanvas.height=winSize;
scanvas.zoom=1;
scanvas.scale=1.0;
scanvas.style.opacity=1;
scanvas.style.pointerEvents='none';
scanvas.style.display='block';
scanvas.style.position='absolute';
scanvas.style.zIndex='999993';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(255,255,255,0.0)';
document.getElementById("cp").appendChild(scanvas);
/*
const zcanvas=document.createElement('canvas');
zcanvas.id='jimag';
zcanvas.imageRendering='pixelated';
zcanvas.width=winSize;
zcanvas.height=winSize;
zcanvas.zoom=1;
zcanvas.scale=1;
zcanvas.style.pointerEvents='none';
zcanvas.style.display='block';
zcanvas.style.position='absolute';
zcanvas.style.zIndex='999994';
zcanvas.style.top='0';
zcanvas.style.height='100vh';
zcanvas.style.width='100vh';
zcanvas.style.backgroundColor='rgba(0,0,0,128)';
// document.getElementById("cpB").appendChild(zcanvas);
  */
var contxVars={
// colorType:'float64',
precision:'highp',
preferLowPowerToHighPerformance:false,
alpha:true,
depth:false,
stencil:false,
preserveDrawingBuffer:true,
premultipliedAlpha:false,
// imageSmoothingEnabled:false,
willReadFrequently:false,
lowLatency:false,
desynchronized:false,
powerPreference:'high-performance',
antialias:true
};
  var contxVarsB={
// colorType:'float32',
precision:'highp',
preferLowPowerToHighPerformance:false,
alpha:true,
depth:true,
stencil:true,
preserveDrawingBuffer:true,
premultipliedAlpha:false,
// imageSmoothingEnabled:true,
willReadFrequently:true,
lowLatency:false,
desynchronized:false,
powerPreference:'high-performance',
antialias:false
};
var ctx=scanvas.getContext('2d',contxVars);
const ctxB=icanvas.getContext('2d',contxVarsB);
const ctxC=bcanvas.getContext('2d',contxVarsB);
const bgPicA=document.getElementById('imgA');
const bgPicB=document.getElementById('imgB');
// const ctxB=zcanvas.getContext('2d',contxVars);
// var gpu=new GPUX({mode:'gpu',canvas:scanvas,webGl:ctx });
// const gpuB=new GPUX({mode:'gpu',canvas:zcanvas,webGl:ctxB });

let dis=set();
if(dis){dis();}
dis=set();

var $,$r,z,w,R,h,ww,o,l,r,m,rotm,rotmb,rottm,kna,knab,knb,knbb,knc,kncb,knd,kndb,rott,rottb,rottc;

// Buffers for rotation - declared outside set to persist if needed, or inside if recreated each time
    var FptrView = null; // Input buffer view
    var NFptrView = null; // Output buffer view
    var la = 0; // length in elements

function set(){

ww=document.getElementById("iwid").innerHTML;
h=document.getElementById("ihig").innerHTML;
console.log('got html size:',ww,' ',h);

let cnP=document.getElementById("cp");
// let cnPB=document.getElementById("cpB");
// let cnPC=document.getElementById("cpC");
let flP=document.getElementById("flip");
let flPB=document.getElementById("flipB");
let vd=document.getElementById("myvideo");

ctx.drawImage(vd,0,0,ww,h);
  
// ctxB.drawImage(vd,0,0,ww,h);
// ctxC.drawImage(vd,0,0,ww,h);
var imgData=ctx.getImageData(0,0,ww,h);
var rgbdat=ctx.createImageData(ww,h);
var rgbdat2=ctxB.createImageData(ww,h);
var rgbdat3=ctxC.createImageData(ww,h);
var rgbd=rgbdat.data;
var rgbd2=rgbdat2.data;
var rgbd3=rgbdat3.data;
var imgg=imgData.data;
var i;
var l=h*ww;
 la=h*ww*4;
var pointa=la*2.0;
var pointb=la*3.0;
var pointc=la*4.0;

var bytes_la = la * Float32Array.BYTES_PER_ELEMENT; // Size in bytes

          // --- Allocate or Re-use Buffers for Rotation ---
        // We need Float32Arrays that C++ can access via typed_memory_view.
        // These should ideally live on the Emscripten HEAP.
        // We need two buffers: one for input (FptrView), one for output (NFptrView).
/*
        // Method 1: Fixed offsets (like original code - careful, layout might change)
        // These offsets seem very large, ensure they are correct byte offsets into HEAPF32
var offset_bytes_a = la * 2.0 * Float32Array.BYTES_PER_ELEMENT; // Example offset for input
var offset_bytes_b = la * 3.0 * Float32Array.BYTES_PER_ELEMENT; // Example offset for output
if (Module.HEAPF32.buffer.byteLength < offset_bytes_b + bytes_la) {
console.error("HEAP buffer too small for specified offsets!");
         // Handle error - perhaps request more memory during compilation? (-sALLOW_MEMORY_GROWTH=1)
return () => {};
}
FptrView = new Float32Array(Module.HEAPF32.buffer, offset_bytes_a, la);
NFptrView = new Float32Array(Module.HEAPF32.buffer, offset_bytes_b, la);
  */

        // Method 2: Dynamic Allocation using _malloc (safer, recommended)
        // Ensure _malloc is exported (usually is by default)
        // Free memory in the cleanup function if using malloc!
var ptr_a1 = Module._malloc(bytes_la);
var ptr_a2 = Module._malloc(bytes_la);
var ptr_a3 = Module._malloc(bytes_la);
var ptr_b = Module._malloc(bytes_la);

FptrViewA = new Float32Array(Module.HEAPF32.buffer, ptr_a1, la);
FptrViewB = new Float32Array(Module.HEAPF32.buffer, ptr_a2, la);
FptrViewC = new Float32Array(Module.HEAPF32.buffer, ptr_a3, la);
NFptrView = new Float32Array(Module.HEAPF32.buffer, ptr_b, la);
console.log(`Allocated buffers via malloc: ptr_a1=${ptr_a1}, ptr_b=${ptr_b}, size=${bytes_la} bytes`);
   
const floatArray = new Float32Array(imgData.data.length);
for(let i = 0; i < imgData.data.length; i++) {
floatArray[i] = imgData.data[i] / 255.0;
}
console.log(`Processing ${floatArray.length} floats`);
const floatResult = Module.processFloatData(floatArray);
if (floatResult && floatResult.average !== undefined) {
console.log("Image Analysis Result (Floats):", floatResult);
console.log(`Average: ${floatResult.average}, Min: ${floatResult.min}, Max: ${floatResult.max}`);
} else {
console.error("processFloatData returned invalid result.");
}
  
// var $H=Module.HEAPF32.buffer;
// var agavF=new Float32Array(Module.HEAPF32.buffer,pointa,la);
// var agavNF=new Float32Array(Module.HEAPF32.buffer,pointb,la);
// agavF.set(imgData.data);
// Module.ccall("nano",null,["Number","Number","Number"],[la,pointa,pointc]);
/* ctx.getExtension('GL_ALL_EXTENSIONS');
ctx.getExtension('GL_KHR_no_error');
ctx.getExtension('GL_REGAL_enable');
ctx.getExtension('GL_ARB_spirv_extensions');
ctx.getExtension('GL_ARB_ES2_compatibility');
ctx.getExtension('GL_ARB_direct_state_access');
 */
// var agav=new Float32Array(Module.HEAPF32.buffer,pointc,1);
// console.log(agav[0]);
for(i=0;i<(ww*h*4);i=i+4){
var rgb=(imgg[i]*0.2126)+(imgg[i+1]*0.7152)+(imgg[i+2]*0.0722);
var lightDark=128+((Math.abs(floatResult.average-128))/2);
rgb=rgb+lightDark/2;
 
 //  but run past a lighter pixel if the avg is darker 
 //  i.e.  pixel is 110/255 or 0.431  ->  avg is 77/255 or 0.302
 //  so the pixel that should be checked would be darker by an amount 0.302 < 0.500
 //  |0|-|64|-|128|-|192|-|255|
 //  
 //  or pixel is 110/255 or 0.431  ->  avg is 177/255 or 0.695
 //  so the pixel that should be checked would be lighter  0.500 < 0.695   
 //
 //  0.302 < 0.500 is 40% of total B->W range
 //  0.302 < 0.500 is 20% of possible B->W difference
//
 // perhaps 0-32 difference possible +/-
 // perhaps half 0-16 difference possible +/-
 //
 //  new idea - have the average have effect on each color's gradient 
 //  range to the next color giving further color depth as well as 
 // keeping a darker range from having few different colors of gradient
 //
var diff=(floatResult.average/255)*32;
var grey=(floatResult.average*255);
if(rgb>126){
if(rgb>229){    // past orange
rgbd[i]=(grey+(rgb-229));
rgbd[i+1]=(grey+(rgb-229));
rgbd[i+2]=(grey+(rgb-229));
rgbd[i+3]=255;// -((rgb-209)*diff);
}
else if(rgb>209){    // orange
rgbd[i]=255;
rgbd[i+1]=128-diff;
rgbd[i+2]=0;
rgbd[i+3]=255;// -((rgb-209)*diff);
}
else if(rgb>193){   // red
rgbd[i]=255-diff;
rgbd[i+1]=0;
rgbd[i+2]=0;
rgbd[i+3]=255;// -((rgb-193)*diff);
                   //  border
}else if(rgb>190){  
rgbd[i]=255;
rgbd[i+1]=0;
rgbd[i+2]=0;
rgbd[i+3]=255;
}else if(rgb>177){   // violet
rgbd2[i]=128-diff;
rgbd2[i+1]=0;
rgbd2[i+2]=255;
rgbd2[i+3]=255;// -((rgb-177)*diff);
}else if(rgb>161){  //  blue
rgbd2[i]=0;
rgbd2[i+1]=0;
rgbd2[i+2]=255-diff;
rgbd2[i+3]=255;// -((rgb-161)*diff);
                     //  border
}else if(rgb>158){
rgbd2[i]=0;
rgbd2[i+1]=0;
rgbd2[i+2]=255;
rgbd2[i+3]=255;
}else if(rgb>145){  // green
rgbd3[i]=0;
rgbd3[i+1]=255-diff;
rgbd3[i+2]=0;
rgbd3[i+3]=255;// -((rgb-145)*diff);
}else if(rgb>128){  // yellow
rgbd3[i]=255;
rgbd3[i+1]=255-diff;
rgbd3[i+2]=0;
rgbd3[i+3]=255;// -((rgb-128)*diff);
}else if(rgb>125){ //  border
rgbd3[i]=255;
rgbd3[i+1]=255;
rgbd3[i+2]=0;
rgbd3[i+3]=255;
}
}else{           // black / blank
rgbd[i]=255-(grey+(rgb-128));
rgbd[i+1]=255-(grey+(rgb-128));
rgbd[i+2]=255-(grey+(rgb-128));
rgbd2[i]=255-(grey+(rgb-128));
rgbd2[i+1]=255-(grey+(rgb-128));
rgbd2[i+2]=255-(grey+(rgb-128));
rgbd3[i]=255-(grey+(rgb-128));
rgbd3[i+1]=255-(grey+(rgb-128));
rgbd3[i+2]=255-(grey+(rgb-128));
// rgbd[i+3]=((rgb-128)*diff);
rgbd[i+3]=255;
rgbd2[i+3]=255;
rgbd3[i+3]=255;
}
}

let r_out = 0, g_out = 0, b_out = 0;
let alpha_out = 0; // Default to transparent

// Define target colors (incorporating diff)
const targetRed = { r: 255 - diff, g: 0, b: 0 };
const targetOrange = { r: 255, g: 128 - diff, b: 0 };
const targetViolet = { r: 128 - diff, g: 0, b: 255 };
const targetBlue = { r: 0, g: 0, b: 255 - diff };
const targetGreen = { r: 0, g: 255 - diff, b: 0 };
const targetYellow = { r: 255, g: 255 - diff, b: 0 };

// Define thresholds (using the start of each main color band)
const orangeThreshold = 209;
const redThreshold = 193;
const violetThreshold = 177;
const blueThreshold = 161;
const greenThreshold = 145;
const yellowThreshold = 128;
const darkThreshold = 126; // Below this is transparent

function smoothstep(edge0, edge1, x) {
const t = Math.max(0, Math.min(1, (x - edge0) / (edge1 - edge0)));
return t * t * (3 - 2 * t);
}

if (rgb > darkThreshold) {
    alpha_out = 255; // Make it opaque
    if (rgb > orangeThreshold) { // Pure Orange Zone (or above)
        r_out = targetOrange.r;
        g_out = targetOrange.g;
        b_out = targetOrange.b;
        // Assign to rgbd
        rgbd[i] = r_out; rgbd[i+1] = g_out; rgbd[i+2] = b_out; rgbd[i+3] = alpha_out;
        // Make others transparent for this pixel
        rgbd2[i+3] = 0; rgbd3[i+3] = 0;
    } else if (rgb > redThreshold) { // --- Transition: Red to Orange ---
     //   const factor = (rgb - redThreshold) / (orangeThreshold - redThreshold); // 0.0 to 1.0
      const factor = smoothstep(redThreshold, orangeThreshold, rgb); // Use smoothstep
        r_out = targetRed.r * (1 - factor) + targetOrange.r * factor;
        g_out = targetRed.g * (1 - factor) + targetOrange.g * factor; // Blends from 0 to (128-diff)
        b_out = targetRed.b * (1 - factor) + targetOrange.b * factor; // Stays 0
         // Assign to rgbd
        rgbd[i] = r_out; rgbd[i+1] = g_out; rgbd[i+2] = b_out; rgbd[i+3] = alpha_out;
        // Make others transparent for this pixel
        rgbd2[i+3] = 0; rgbd3[i+3] = 0;
    } else if (rgb > violetThreshold) { // Pure Red Zone (or maybe transition Violet->Red?)
         // You would need to decide if 193 is the end of Red or start of Red->Orange transition
         // Assuming for now 193 is the START of the Red->Orange blend zone above.
         // If you want a pure Red zone, you need another threshold. Let's assume pure Red is between, say, 190 and 193.
         // This part needs careful planning of your exact ranges.
         // Simplified: If not in transition above, it's pure Red before Violet.
        r_out = targetRed.r;
        g_out = targetRed.g;
        b_out = targetRed.b;
         // Assign to rgbd
        rgbd[i] = r_out; rgbd[i+1] = g_out; rgbd[i+2] = b_out; rgbd[i+3] = alpha_out;
         // Make others transparent for this pixel
        rgbd2[i+3] = 0; rgbd3[i+3] = 0;
    } else if (rgb > blueThreshold) { // --- Transition: Blue to Violet ---
        // const factor = (rgb - blueThreshold) / (violetThreshold - blueThreshold);
       factor = smoothstep(blueThreshold, violetThreshold, rgb); // Use smoothstep
        r_out = targetBlue.r * (1 - factor) + targetViolet.r * factor; // Blends 0 to (128-diff)
        g_out = targetBlue.g * (1 - factor) + targetViolet.g * factor; // Stays 0
        b_out = targetBlue.b * (1 - factor) + targetViolet.b * factor; // Blends (255-diff) to 255
         // Assign to rgbd2
        rgbd2[i] = r_out; rgbd2[i+1] = g_out; rgbd2[i+2] = b_out; rgbd2[i+3] = alpha_out;
        // Make others transparent for this pixel
        rgbd[i+3] = 0; rgbd3[i+3] = 0;
    } else if (rgb > greenThreshold) { // --- Transition: Green to Blue ---
       //  const factor = (rgb - greenThreshold) / (blueThreshold - greenThreshold);
         factor = smoothstep(greenThreshold, blueThreshold, rgb); // Use smoothstep
         r_out = targetGreen.r * (1-factor) + targetBlue.r * factor; // Stays 0
         g_out = targetGreen.g * (1-factor) + targetBlue.g * factor; // Blends (255-diff) to 0
         b_out = targetGreen.b * (1-factor) + targetBlue.b * factor; // Blends 0 to (255-diff)
          // Assign to rgbd2 (Blue/Violet target) or rgbd3 (Green/Yellow target)? Decide where the transition lives. Let's put it in rgbd2.
        rgbd2[i] = r_out; rgbd2[i+1] = g_out; rgbd2[i+2] = b_out; rgbd2[i+3] = alpha_out;
        // Make others transparent for this pixel
        rgbd[i+3] = 0; rgbd3[i+3] = 0;
    } else if (rgb > yellowThreshold) { // --- Transition: Yellow to Green ---
      //   const factor = (rgb - yellowThreshold) / (greenThreshold - yellowThreshold);
         factor = smoothstep(yellowThreshold, greenThreshold, rgb); // Use smoothstep
         r_out = targetYellow.r * (1-factor) + targetGreen.r * factor; // Blends 255 to 0
         g_out = targetYellow.g * (1-factor) + targetGreen.g * factor; // Stays (255-diff)
         b_out = targetYellow.b * (1-factor) + targetGreen.b * factor; // Stays 0
          // Assign to rgbd3
         rgbd3[i] = r_out; rgbd3[i+1] = g_out; rgbd3[i+2] = b_out; rgbd3[i+3] = alpha_out;
        // Make others transparent for this pixel
        rgbd[i+3] = 0; rgbd2[i+3] = 0;
    } else { // Pure Yellow Zone (rgb between 128 and darkThreshold)
        r_out = targetYellow.r;
        g_out = targetYellow.g;
        b_out = targetYellow.b;
         // Assign to rgbd3
        rgbd3[i] = r_out; rgbd3[i+1] = g_out; rgbd3[i+2] = b_out; rgbd3[i+3] = alpha_out;
        // Make others transparent for this pixel
        rgbd[i+3] = 0; rgbd2[i+3] = 0;
    }
} else { // Dark/Transparent Zone
    rgbd[i+3] = 0;
    rgbd2[i+3] = 0;
    rgbd3[i+3] = 0;
}

          // --- Populate the Input Float32Array (FptrView) ---
        // Copy the initial image data (0-255 integers) into the float buffer.
        // The C++ code expects floats, but the values seem to represent 0-255 range.
for (let i = 0; i < la; i++) {
FptrViewA[i] = rgbd[i]; // Direct copy of 0-255 values
}
for (let i = 0; i < la; i++) {
FptrViewB[i] = rgbd2[i]; // Direct copy of 0-255 values
}
for (let i = 0; i < la; i++) {
FptrViewC[i] = rgbd3[i]; // Direct copy of 0-255 values
}

// agavF.set(rgbdat.data);
var ang=45;
// Module.ccall("rotat",null,["Number","Number","Number","Number","Number"],[ang,ww,h,pointa,pointb]);
ctx.putImageData(rgbdat,0,0);
ctxB.putImageData(rgbdat2,0,0);
ctxC.putImageData(rgbdat3,0,0);
// Module.ccall("emem",null,["Number","Number"],[la,pointa]);
// icanvas.setAttribute("style","transform: rotate(130deg)");
// bcanvas.setAttribute("style","transform: rotate(230deg)");

function Ra(){
// bgPicA.hidden=false;
if(bgPicB.hidden==true){
bgPicB.hidden=false;
bgPicA.hidden=true;
flP.setAttribute("style","transform:scaleX(-1.0)");
flPB.setAttribute("style","transform:scaleX(-1.0)");
}else{
bgPicB.hidden=true;
bgPicA.hidden=false;
flP.setAttribute("style","transform:scaleX(-1.0)");
flPB.setAttribute("style","transform:scaleY(1.0)");
}
// bgPicA.setAttribute("style","position:absolute;");
// bgPicA.setAttribute("style","z-index:999990;");
// bgPicB.setAttribute("style","z-index:999991;");
// flP.setAttribute("style","transform: scaleX(-1.0)");
// cnP.setAttribute("style","transform: scaleY(1.0)");
// cnPB.setAttribute("style","transform:scaleY(-1);");
}

function Rb(){
// bgPicA.setAttribute("style","position:absolute;");
// bgPicA.setAttribute("style","z-index:999991;");
// bgPicB.setAttribute("style","z-index:999990;");
     flP.setAttribute("style","transform: scaleX(1.0)");
     cnP.setAttribute("style","transform: scaleY(-1.0)");
// cnPB.setAttribute("style","transform: scaleY(1);");
}

function copyFloatToUint8(floatView, uint8Data) {
for (let i = 0; i < floatView.length; ++i) {
uint8Data[i] = Math.max(0, Math.min(255, Math.round(floatView[i])));
}
}

function rrra(rta) { // Rotates and updates canvas 1 (ctx)
NFptrView.fill(0); // Fill with 0.0f
Module.rotatF(rta, ww, h, FptrViewA, NFptrView); // Pass views directly
copyFloatToUint8(NFptrView, rgbdat.data);
ctx.putImageData(rgbdat, 0, 0);
}

function rrrb(rtb) { // Rotates and updates canvas 2 (ctxB)
NFptrView.fill(0);
Module.rotatF(rtb, ww, h, FptrViewB, NFptrView);
copyFloatToUint8(NFptrView, rgbdat2.data);
ctxB.putImageData(rgbdat2, 0, 0);
}

function rrrc(rtc) { // Rotates and updates canvas 3 (ctxC)
NFptrView.fill(0);
Module.rotatF(rtc, ww, h, FptrViewC, NFptrView);
copyFloatToUint8(NFptrView, rgbdat3.data);
ctxC.putImageData(rgbdat3, 0, 0);
}

knb=document.getElementById("rra");
kna=document.getElementById("mainr");
knc=document.getElementById("rrb");
knd=document.getElementById("rrc");
knbb=document.getElementById("rrab");
kncb=document.getElementById("rrbb");
kndb=document.getElementById("rrcb");
rate=kna.innerHTML;
rott=0;
rottb=0;
rottc=0;
let dur=document.getElementById("temptime").innerHTML/10;
let dsd=false;

function $rn(){
if(dsd){
return;
}
Ra();
if((rott-knd.innerHTML)<0){
rott=(rott+360-knd.innerHTML);
}else{
rott=rott-knd.innerHTML;
}
rrra(rott);
if((rottb-knc.innerHTML)<0){
rottb=(rottb+360-knc.innerHTML);
}else{
rottb=(rottb-knc.innerHTML);
}
setTimeout(function(){
rrrb(rottb);

//  bgPicB.hidden=true;
// setTimeout(function(){
// Rb();
// },rate);
setTimeout(function(){
if((rottc+knb.innerHTML)>360){
rottc=((rottc+knb.innerHTML)-360);
}else{
rottc=(rottc+knb.innerHTML);
}
rrrc(rottc);

//  bgPicA.hidden=true;
// bgPicB.hidden=false;
  
setTimeout(function(){
$rn();
},rate);
},rate));
},rate);
}
$rn();
document.getElementById("di").onclick=function(){
dsd=true;
set();
};
return()=>{
dsd=true;
};
}
});

int main(){
emscA();
ma();
return 1;
}
