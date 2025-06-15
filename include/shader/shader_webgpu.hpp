#pragma once // Added pragma once

#include <boost/cstdfloat.hpp> // Keep original includes that might be used by other parts

#include "../../include/shader/defs.hpp"
// #include <stdio.h> // Already commented
#include <stdlib.h>
#include <cstdint>
#include <stdarg.h>
#include <new>
#include <cstring> // For memcpy, strlen
#include <math.h>
#include <cfloat>
#include <ctime>
// #include <iostream> // Provided by WebGPUComputePipeline's iostream
#include <vector>
#include <climits>
#include <functional>
#include <memory> // For std::unique_ptr
#include <string> // For std::string
#include <iostream> // For std::cerr, std::cout (used by WebGPUComputePipeline)

#include <webgpu/webgpu.h> // WebGPU definitions

// Forward declaration for Run class if WebGPUComputePipeline needs to know about it.
// class Run; // Not strictly needed if Run just owns a pipeline ptr and WebGPUComputePipeline is defined first.

class WebGPUComputePipeline {
public:
    WebGPUComputePipeline(const std::string& shader_filepath, const std::string& entry_point, size_t input_size_bytes, size_t result_size_bytes); // Changed shader_source to shader_filepath
    ~WebGPUComputePipeline();

    bool initialize();
    bool runCompute();

    void setInputDataValue(uint8_t value, size_t index);
    void setInputData(const std::vector<uint8_t>& data);
    const std::vector<uint32_t>& getComputeResult() const;
    bool isInitialized() const { return initialized_; }

private:
    // WebGPU handles
    WGPUInstance instance_ = nullptr;
    WGPUAdapter adapter_ = nullptr;
    WGPUDevice device_ = nullptr;
    WGPUQueue queue_ = nullptr;
    WGPUBuffer input_buffer_ = nullptr;
    WGPUBuffer result_buffer_ = nullptr;
    WGPUBuffer staging_buffer_ = nullptr;
    WGPUShaderModule compute_module_ = nullptr;
    WGPUComputePipeline pipeline_ = nullptr;
    WGPUBindGroupLayout bind_group_layout_ = nullptr;
    WGPUBindGroup bind_group_ = nullptr;

    // Descriptors
    WGPURequestAdapterOptions adapter_options_ = {};
    WGPUDeviceDescriptor device_descriptor_ = {};
    WGPUBufferDescriptor input_buffer_desc_ = {};
    WGPUBufferDescriptor result_buffer_desc_ = {};
    WGPUBufferDescriptor staging_buffer_desc_ = {};
    WGPUShaderModuleWGSLDescriptor shader_module_wgsl_desc_ = {};
    WGPUShaderModuleDescriptor shader_module_desc_ = {};
    WGPUComputePipelineDescriptor pipeline_desc_ = {};

    // Data
    std::vector<uint8_t> input_data_;
    std::vector<uint32_t> result_data_;
    size_t input_buffer_size_bytes_;
    size_t result_buffer_size_bytes_;

    // Shader info
    std::string shader_source_;
    std::string entry_point_;

    bool initialized_ = false;
    bool buffers_created_ = false;

    // Async callback static trampolines
    static void onAdapterRequestEnded(WGPURequestAdapterStatus status, WGPUAdapter adapter, const char* message, void* userdata);
    static void onDeviceRequestEnded(WGPURequestDeviceStatus status, WGPUDevice device, const char* message, void* userdata);
    static void onStagingBufferMapCallback(WGPUBufferMapAsyncStatus status, void* userdata);


    // Instance methods for callbacks
    void handleAdapterRequestEnded(WGPURequestAdapterStatus status, WGPUAdapter adapter, const char* message);
    void handleDeviceRequestEnded(WGPURequestDeviceStatus status, WGPUDevice device, const char* message);
    void handleStagingBufferMap(WGPUBufferMapAsyncStatus status); // May not be used if polling in runCompute

    // Internal setup methods
    // bool setupAdapter(); // Integrated into initialize()
    bool setupDevice();
    bool createBuffers();
    bool createShaderModule();
    bool createPipeline();

    // Logging and error handling
    static void deviceLostCallback(WGPUDeviceLostReason reason, char const * message, void * userdata);
    static void uncapturedErrorCallback(WGPUErrorType type, char const * message, void * userdata);

    void releaseResources();

    friend class Run; // Grant Run access if needed for calling private methods or managing state
};


// Original content continues below
#include <boost/cstdfloat.hpp>

#include "../../include/shader/defs.hpp"

// #include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <stdarg.h>
#include <new>
#include <cstring>
#include <math.h>
#include <cfloat>
#include <ctime>
// #include <iostream>
#include <vector>
#include <climits>

// template<class ArgumentType,class ResultType> // This was already part of the inserted section's includes

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#define register

#include "../../include/shader/boost_defs.hpp"
// #include "../../include/shader/ext_boost_defs.hpp"

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>

#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/predef/other/endian.h>
#include <boost/lambda/lambda.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/random.hpp>
#include <boost/regex.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/thread.hpp>

// #include <boost/context/fiber_fcontext.hpp>
#include <boost/context/fiber.hpp>
#include <boost/fiber/all.hpp>
#include <thread>

#include <complex>

// #define BOOST_HAS_TR1
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/context/detail/tuple.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>
#include <boost/function_equal.hpp>
#include <boost/atomic.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/compute/core.hpp>
#include <boost/chrono.hpp>
#include <algorithm>
#include <experimental/simd>
#include <random>
#include <emscripten.h>
// #include <emscripten/proxying.h>
// #include <emscripten/wasm_worker.h>

#include "../../include/shader/intrins.hpp"
// #include "../../include/shader/gl.hpp"
#include "../../include/shader/egl.hpp"
#include "../../lib/lib_webgpu.h" // This is the C header for WebGPU, keep it.

#include <emscripten/html5.h> // Keep Emscripten specific includes

#ifndef OPENGL_CORE_PROFILE
#define OPENGL_CORE_PROFILE 1
#endif

#ifndef GL_CONTEXT_FLAG_NO_ERROR_BIT
#define GL_CONTEXT_FLAG_NO_ERROR_BIT 1
#endif

#define GL_RED_MIN 0.0
#define GL_RED_MAX 1.0
#define GL_GREEN_MIN 0.0
#define GL_GREEN_MAX 1.0
#define GL_BLUE_MIN 0.0
#define GL_BLUE_MAX 1.0
#define GL_ALPHA_MIN 0.0
#define GL_ALPHA_MAX 1.0
#define GL_INTENSITY_MIN 0.0
#define GL_INTENSITY_MAX 1.0
#define GL_LUMINANCE_MIN 0.0
#define GL_LUMINANCE_MAX 1.0

static constexpr EGLint numSamples=2;

// static constexpr float numSamplesf=float(numSamples);
static constexpr float numSamplesf=4.0f;

static constexpr EGLint att_lst2[]={ 
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
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_SRGB,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// / EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_BACK_BUFFER,
EGL_NONE,EGL_NONE
};

static constexpr EGLint ctx_att[]={
// EGL_CONTEXT_MAJOR_VERSION_KHR,2,
// EGL_CONTEXT_MINOR_VERSION_KHR,0,
EGL_CONTEXT_MAJOR_VERSION_KHR,2,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE,EGL_NONE
};

static constexpr EGLint att_lst[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FIXED_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_BIT,
// EGL_CONFORMANT,EGL_NONE,
//  EGL_CONFIG_CAVEAT,EGL_NONE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_TRIPLE_BUFFER_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
EGL_SURFACE_TYPE,EGL_MULTISAMPLE_RESOLVE_BOX_BIT,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY,EGL_NO_RESET_NOTIFICATION,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_COLOR_BUFFER_TYPE,EGL_RGB_BUFFER,
EGL_LUMINANCE_SIZE,32,
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_BUFFER_SIZE,32,
EGL_SAMPLE_BUFFERS,1,
EGL_COVERAGE_BUFFERS_NV,1,
EGL_COVERAGE_SAMPLES_NV,4,
EGL_SAMPLES,4,
EGL_NONE,EGL_NONE
};

boost::function<const EM_BOOL(boost::uint_t<32>::exact)>EBOin;

boost::function<const EM_BOOL(boost::uint_t<32>::exact)>VCOin;

boost::function<const EM_BOOL(boost::uint_t<32>::exact)>VBOin;

boost::function<const EM_BOOL()>setFloats;

static inline boost::function<const register float()>gF;

static inline boost::function<const register float()>gFm1;

static inline boost::function<const register float()>gF0;

static inline boost::function<EM_BOOL()>Rendar;

static inline boost::function<EM_BOOL()>Unifrm;

boost::function<EM_BOOL(void)>swap;

boost::function<EM_BOOL(void)>strt;

static void raf();

static void WGPU_Run();

static void ObtainedWebGpuDeviceStart2(WGpuDevice,void *);

static void ObtainedWebGpuDeviceStart(WGpuDevice,void *);

static void ObtainedWebGpuAdapterStart2(WGpuAdapter,void *);

static void ObtainedWebGpuAdapterStart(WGpuAdapter,void *);

void WGPU_Start();

static EM_BOOL u_iTimeDelta_set(register boost::compute::double_);

static void Rend();

extern "C"{

EM_BOOL str();
EM_BOOL swp();
EM_BOOL ud();
EM_BOOL uu();
EM_BOOL vd();
EM_BOOL vu();
EM_BOOL mu();
EM_BOOL md();
EM_BOOL ml();
EM_BOOL mr();

}

class Compile{

private:

GLsizei i;

public:

boost::uint_t<24>::least cmpl_shd(GLenum type,GLsizei nsrc,const char ** src){
GLsizei srclens[nsrc];
for(i=0;i<nsrc;i++){
srclens[i]=GLsizei(strlen(src[i]));
}
const GLuint shader=glCreateShader(type);
glShaderSource(shader,nsrc,src,srclens);
glCompileShader(shader);
return shader;
}

};

/* static inline char wgl_cmp_src[2000]= // Commented out as it's now loaded from shaders/compute_shader.wgsl
"@group(0)@binding(0)var<storage,read>inputBuffer:array<u32,262144>;"
"@group(0)@binding(1)var<storage,read_write>outputBuffer:array<u32,262144>;"
"@group(0)@binding(2)var textureA:texture_storage_2d<rgba32uint,write>;"
"@compute@workgroup_size(4,1,64)"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>){"
"let f:u32=global_id.x*4*global_id.y;"
"for(var e:u32=0;e<65546;e++){"
"var m=e*4;"
"outputBuffer[m]=inputBuffer[0];"
"outputBuffer[m+1]=0;"
"outputBuffer[m+2]=255-inputBuffer[0];"
"outputBuffer[m+3]=255;"
"}"
"}"; */

/* static inline char cm_hdr_src[2300]= // Commented out: loaded from shaders/common_header.glsl
"#version 300 es\n"
"#extension GL_ALL_EXTENSIONS : enable\n"
"#extension all_spir_v_extensions : enable\n"
"#extension OES_standard_derivatives : disable\n"
"#extension GL_KHR_no_error : enable\n"
"#extension GL_REGAL_enable : enable\n"
"#extension EGL_ANGLE_platform_angle : enable\n"
"#extension GL_ARB_spirv_extensions : enable\n"
"#extension EGL_EXT_gl_colorspace_display_p3_linear : enable\n"
// "#pragma STDC(FP_CONTRACT ON)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 1\n"
"#pragma (fastmath on)\n"
"#pragma optionNV(fastmath on)\n"
"#pragma (fastprecision off)\n"
"#pragma (STDGL all)\n"
"#pragma optionNV(STDGL all)\n"
/*
"#pragma (precision highp double)\n"
"#pragma (precision highp vec4)\n"
"#pragma (precision highp mat4)\n"
"#pragma (precision highp uint)\n"
"#pragma (precision highp short)\n"
"#pragma (precision highp bool)\n"
"#pragma (precision highp atomic_uint)\n"
"#pragma (precise none)\n"
 "#pragma STDGL(strict off)\n"
 "#pragma optimize(on)\n"
 "#pragma debug(off)\n"
 "#pragma (invariant none)\n"
 "#pragma (centroid all)\n"
"#pragma (sample all)\n"
"#pragma (unroll all)\n"
"#pragma optionNV(unroll all)\n"
"#pragma STDGL(ifcvt none)\n"
"#pragma (inline all)\n"
"#pragma optionNV(inline all)\n"
*/
"precision highp float;\n"
"precision highp sampler3D;precision highp sampler2D;"
"precision highp samplerCube;"
"precision mediump sampler2DArray;precision mediump sampler2DShadow;"
"precision mediump isampler2D;precision mediump isampler3D;precision mediump isamplerCube;"
"precision mediump isampler2DArray;precision mediump usampler2D;precision mediump usampler3D;"
"precision mediump usamplerCube;precision mediump usampler2DArray;precision mediump samplerCubeShadow;"
"precision mediump sampler2DArrayShadow;\n"; */

/* static inline char vrt_bdy_src[100]= // Commented out: loaded from shaders/vertex_shader.glsl
"precision mediump int;\n"
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n"; */

/* static inline char frg_hdr_src[1000]= // Commented out: loaded from shaders/fragment_header.glsl
"precision mediump int;\n"
"uniform int iFrameRate;"
"uniform int iFrame;uniform float iTime;uniform float iTimeDelta;uniform vec4 iDate;"
"uniform float iChannelTime[4];uniform vec3 iChannelResolution[4];uniform vec3 iResolution;"
"uniform vec4 iMouse;uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;"
"uniform sampler2D iChannel3;"
"out vec4 fragColor;\n"; */

/* static inline char frg_hdr_src[1000]= // Commented out as shaders/fragment_header.glsl is used
"void main(){mainImage(fragColor,gl_FragCoord.xy);}\n\0"; */
/* // This is the start of the ShaderToy multi-pass example, not frg_ftr_src itself
"#define mainImage mainImage0(out dvec4 O,dvec2 U);"
"int _N=3;void mainImage(out dvec4 O,dvec2 U){"
"dvec4 o;O=dvec4(0);"
"mainImage0(o,U+dvec2(k%_N-_N/2,k/_N-_N/2)/double(_N));"
"O += o;}O /= double(_N*_N);O=pow(O,dvec4(2.077038f/1.0f,2.184228f/1.0f,2.449715f/1.0f,1.0f));}"
// "O += o;}O /= double(_N*_N);O=pow(O,dvec4(1.077038f/1.0,1.184228f/1.0,1.449715f/1.0,1.0));}"
"void mainImage0\n";
*/

EM_BOOL ms_l,clk_l;

using gli_tensor=boost::numeric::ublas::tensor<GLint>;
using mouse_tensor=boost::numeric::ublas::tensor<boost::compute::double_>;
using shad_tensor=boost::numeric::ublas::tensor<boost::uint_t<32>::exact>;
using prg_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
using sz_tensor=boost::numeric::ublas::tensor<boost::int_t<32>::exact>;
using f_tensor=boost::numeric::ublas::tensor<boost::compute::double_>;
using d_tensor=boost::numeric::ublas::tensor<boost::compute::double_>;
using di_tensor=boost::numeric::ublas::tensor<boost::uint_t<32>::exact>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;
using rv_tensor=boost::numeric::ublas::tensor<register v128_t>;
using i_tensor=boost::numeric::ublas::tensor<boost::int_t<32>::exact>;
using iptr_tensor=boost::numeric::ublas::tensor<int *>;
using uiptr_tensor=boost::numeric::ublas::tensor<uint32_t *>;
using gi_tensor=boost::numeric::ublas::tensor<GLint>;
using li_tensor=boost::numeric::ublas::tensor<long>;
using void_tensor=boost::numeric::ublas::tensor<void *>;
using bgle_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayoutEntry *>;
using bge_tensor=boost::numeric::ublas::tensor<WGpuBindGroupEntry *>;
using bmc_tensor=boost::numeric::ublas::tensor<WGpuBufferMapCallback>;
using wdc_tensor=boost::numeric::ublas::tensor<WGpuOnSubmittedWorkDoneCallback>;
using oac_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterCallback>;
using odc_tensor=boost::numeric::ublas::tensor<WGpuRequestDeviceCallback>;
using bbl_tensor=boost::numeric::ublas::tensor<WGpuBufferBindingLayout>;
using bd_tensor=boost::numeric::ublas::tensor<WGpuBufferDescriptor>;
using md_tensor=boost::numeric::ublas::tensor<WGpuShaderModuleDescriptor>;
using dd_tensor=boost::numeric::ublas::tensor<WGpuDeviceDescriptor>;
using rao_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterOptions>;
using wa_tensor=boost::numeric::ublas::tensor<WGpuAdapter>;
using wq_tensor=boost::numeric::ublas::tensor<WGpuQueue>;
using cb_tensor=boost::numeric::ublas::tensor<WGpuCommandBuffer>;
using wb_tensor=boost::numeric::ublas::tensor<WGpuBuffer>;
using ce_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoder>;
using wd_tensor=boost::numeric::ublas::tensor<WGpuDevice>;
using cpe_tensor=boost::numeric::ublas::tensor<WGpuComputePassEncoder>;
using cp_tensor=boost::numeric::ublas::tensor<WGpuComputePipeline>;
using pl_tensor=boost::numeric::ublas::tensor<WGpuPipelineLayout>;
using cm_tensor=boost::numeric::ublas::tensor<WGpuShaderModule>;
using bg_tensor=boost::numeric::ublas::tensor<WGpuBindGroup>;
using bgl_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayout>;
using i53_tensor=boost::numeric::ublas::tensor<double_int53_t>;
using tex_tensor=boost::numeric::ublas::tensor<WGpuTexture>;
using td_tensor=boost::numeric::ublas::tensor<WGpuTextureDescriptor>;
using stbl_tensor=boost::numeric::ublas::tensor<WGpuStorageTextureBindingLayout>;
using tv_tensor=boost::numeric::ublas::tensor<WGpuTextureView>;
using tvd_tensor=boost::numeric::ublas::tensor<WGpuTextureViewDescriptor>;
using ced_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoderDescriptor>;
using bms_tensor=boost::numeric::ublas::tensor<WGPU_BUFFER_MAP_STATE>;

static v_tensor sse=v_tensor{2,2};
static v_tensor sse2=rv_tensor{2,2};
static v_tensor sse3=v_tensor{2,2};
static v_tensor sse4=rv_tensor{1,1};
static shad_tensor Sh=shad_tensor{3,3};
static shad_tensor TX=shad_tensor{3,3,3};
static prg_tensor S1=prg_tensor{1,1,1};
static sz_tensor Si=sz_tensor{1,1};
static d_tensor d_time=d_tensor{2,2};
static f_tensor Fi=f_tensor{3,3};
static d_tensor Di=d_tensor{2,2};
static gi_tensor uni_i=gi_tensor{1,1};
static i_tensor i_view=i_tensor{1,2};
static i_tensor i_date=i_tensor{2,2};
static f_tensor t_size=f_tensor{1,2};
static di_tensor i_size=di_tensor{2,2};
static void_tensor cntx=void_tensor{3,3};
static i_tensor cntxi=i_tensor{2,2};
static mouse_tensor mms=mouse_tensor{2,2};
static mouse_tensor mms2=mouse_tensor{2,2};
static void_tensor bin=void_tensor{1,1};
// static wa_tensor WGPU_Adapter=wa_tensor{1,1,2}; // Replaced by WebGPUComputePipeline member
// static wd_tensor WGPU_Device=wd_tensor{1,1,2}; // Replaced by WebGPUComputePipeline member
// static wq_tensor WGPU_Queue=wq_tensor{1,1,2}; // Replaced by WebGPUComputePipeline member
// static cb_tensor WGPU_CommandBuffer=cb_tensor{1,1,3}; // Replaced by WebGPUComputePipeline member
// static wb_tensor WGPU_Buffers=wb_tensor{3,3,3}; // Replaced by WebGPUComputePipeline member
// static ce_tensor WGPU_CommandEncoder=ce_tensor{1,1,4}; // Replaced by WebGPUComputePipeline member
// static cpe_tensor WGPU_ComputePassCommandEncoder=cpe_tensor{1,1,3}; // Replaced by WebGPUComputePipeline member
// static cp_tensor WGPU_ComputePipeline=cp_tensor{1,1,1}; // Replaced by WebGPUComputePipeline member
// static pl_tensor WGPU_ComputePipelineLayout=pl_tensor{1,1,1}; // Replaced by WebGPUComputePipeline member
// static cm_tensor WGPU_ComputeModule=cm_tensor{1,1,1}; // Replaced by WebGPUComputePipeline member
// static bg_tensor WGPU_BindGroup=bg_tensor{1,1,2}; // Replaced by WebGPUComputePipeline member
// static bgl_tensor WGPU_BindGroupLayout=bgl_tensor{1,1,2}; // Replaced by WebGPUComputePipeline member
// static bgle_tensor WGPU_BindGroupLayoutEntries=bgle_tensor{1,1,2}; // Managed by WebGPUComputePipeline
// static bge_tensor WGPU_BindGroupEntries=bge_tensor{1,1,2}; // Managed by WebGPUComputePipeline
// static bmc_tensor WGPU_MapCallback=bmc_tensor{1,1,3}; // Callbacks are now static members of WebGPUComputePipeline
// static wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,3}; // Callbacks are now static members of WebGPUComputePipeline
// static oac_tensor WGPU_ObtainedAdapterCallback=oac_tensor{1,1,2}; // Callbacks are now static members of WebGPUComputePipeline
// static odc_tensor WGPU_ObtainedDeviceCallback=odc_tensor{1,1,2}; // Callbacks are now static members of WebGPUComputePipeline
// static bbl_tensor WGPU_BufferBindingLayout=bbl_tensor{1,1,4}; // Managed by WebGPUComputePipeline
// static bd_tensor WGPU_BufferDescriptor=bd_tensor{1,1,4}; // Managed by WebGPUComputePipeline
// static md_tensor WGPU_ShaderModuleDescriptor=md_tensor{1,1,3}; // Managed by WebGPUComputePipeline
// static di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1}; // Result handling within WebGPUComputePipeline
// static void_tensor WGPU_UserData=void_tensor{1,1,2}; // Userdata for callbacks handled by WebGPUComputePipeline instance
// static rao_tensor WGPU_RequestAdapterOptions=rao_tensor{1,1,1}; // Options are members of WebGPUComputePipeline
// static dd_tensor WGPU_DeviceDescriptor=dd_tensor{1,1,1}; // Options are members of WebGPUComputePipeline
static uiptr_tensor WGPU_ResultBuffer=uiptr_tensor{1,1,1}; // Still used for GL texture update (deferred)
static uiptr_tensor WGPU_InputBuffer=uiptr_tensor{1,1,1}; // Restoring this as WGPU_Input_Array is still used externally.
// static i53_tensor WGPU_BufferRange=i53_tensor{1,1,2}; // Result handling within WebGPUComputePipeline
// static i53_tensor WGPU_BufferSize=i53_tensor{1,1,1}; // Size info in WebGPUComputePipeline
// static tex_tensor WGPU_Texture=tex_tensor{1,1,1}; // Texture resources managed by WebGPUComputePipeline if used
// static td_tensor WGPU_TextureDescriptor=td_tensor{1,1,1}; // Texture resources managed by WebGPUComputePipeline if used
// static stbl_tensor WGPU_StorageTextureBindingLayout=stbl_tensor{1,1,1}; // Texture resources managed by WebGPUComputePipeline if used
// static tvd_tensor WGPU_TextureViewDescriptor=tvd_tensor{1,1,1}; // Texture resources managed by WebGPUComputePipeline if used
// static tv_tensor WGPU_TextureView=tv_tensor{1,1,1}; // Texture resources managed by WebGPUComputePipeline if used
// static uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1}; // Related to old texture/buffer copies
// static ced_tensor WGPU_CommandEncoderDescriptor=ced_tensor{1,1,1}; // Managed by WebGPUComputePipeline
// static bms_tensor WGPU_BufferStatus=bms_tensor{1,1,1}; // Internal state, not needed globally

uint32_t workgroupSize=64; // Still potentially useful for reference or if pipeline uses it
uint32_t OutputBufferUnits=262144; // Still potentially useful for reference or if pipeline uses it
uint32_t OutputBufferBytes=262144*4; // Used by WebGPUComputePipeline constructor, keep for now
uint32_t InputBufferUnits=262144; // Still potentially useful for reference or if pipeline uses it
uint32_t InputBufferBytes=262144*4; // Used by WebGPUComputePipeline constructor, keep for now
uint64_t WGPU_InputRangeSize=OutputBufferBytes; // Potentially unused, review later
const char * Entry="computeStuff"; // Used by WebGPUComputePipeline constructor, keep for now
// uint32_t invocationCount=BufferMapSize/sizeof(int);
// uint32_t workgroupCount=(invocationCount+workgroupSize-1)/workgroupSize;
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE
void * userDataA;
void * userDataB;
GLsizei width=256;
GLsizei height=256;
GLuint wtexture[4];
GLuint colorBuffer;
GLuint renderBufferA;
GLuint renderBufferB;
GLuint renderBufferC;
GLuint srgbTexture;
GLuint frameBuffer;
GLuint depthBuffer;
WGpuTexture textureA;
// WGpuAdapter adapter=0; // Replaced by WebGPUComputePipeline member
// WGpuDevice device=0; // Replaced by WebGPUComputePipeline member
// WGpuQueue queue=0; // Replaced by WebGPUComputePipeline member
// WGpuBindGroupLayout bindGroupLayout=0; // Replaced by WebGPUComputePipeline member
// WGpuBindGroupLayout bindGroupLayoutB=0; // Unused second layout
// WGpuComputePipeline computePipeline=0; // Replaced by WebGPUComputePipeline member
// WGpuBuffer inputBuffer=0; // Replaced by WebGPUComputePipeline member
// WGpuBuffer outputBuffer=0; // Replaced by WebGPUComputePipeline member
// WGpuBuffer mapBuffer=0; // Replaced by WebGPUComputePipeline member (staging_buffer_)
// WGpuBuffer uniBuffer=0; // Potentially unused uniform buffer
// WGpuShaderModule cs=0; // Replaced by WebGPUComputePipeline member
// WGpuCommandBuffer commandBuffer=0; // Created on demand in WebGPUComputePipeline
// WGpuCommandEncoder encoder=0; // Created on demand in WebGPUComputePipeline
// WGpuComputePassEncoder computePass=0; // Created on demand in WebGPUComputePipeline
// WGpuBindGroup bindGroup=0; // Replaced by WebGPUComputePipeline member
// WGpuBindGroup bindGroupB=0; // Unused second bind group
// WGpuPipelineLayout pipelineLayout=0; // Replaced by WebGPUComputePipeline member
// WGpuQuerySet querySet=0; // Unused
// WGpuComputePassDescriptor computePassDescriptor={}; // Created on demand in WebGPUComputePipeline
// WGpuCommandBufferDescriptor commandBufferDescriptor={}; // Created on demand in WebGPUComputePipeline
// WGpuCommandEncoderDescriptor commandEncoderDescriptor={}; // Created on demand in WebGPUComputePipeline
// WGpuDeviceDescriptor deviceDescriptor={}; // Template for device creation, now member of WebGPUComputePipeline
// WGpuBindGroupLayoutEntry bindGroupLayoutEntries[3]={}; // Managed by WebGPUComputePipeline
// WGpuBindGroupLayoutEntry bindGroupLayoutEntriesB[2]={}; // Unused
// WGpuBindGroupEntry bindGroupEntry[3]={}; // Managed by WebGPUComputePipeline
// WGpuBindGroupEntry bindGroupEntryB[2]={}; // Unused
// WGpuBufferBindingLayout bufferBindingLayout1={3}; // Managed by WebGPUComputePipeline
// WGpuBufferBindingLayout bufferBindingLayout2={2}; // Managed by WebGPUComputePipeline
// WGpuBufferBindingLayout bufferBindingLayout3={2}; // Managed by WebGPUComputePipeline
// WGpuBufferBindingLayout bufferBindingLayout4={2}; // Managed by WebGPUComputePipeline
// WGpuStorageTextureBindingLayout storageTextureBindingLayout1={1,34,2}; // Managed by WebGPUComputePipeline if textures are used
// WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false}; // Member of WebGPUComputePipeline
std::vector<float>color_input(InputBufferUnits); // Potentially related to WGPU_Color_Input_Array, review if used elsewhere
// std::vector<uint8_t>input(InputBufferBytes); // This was the global input, now handled by pipeline's input_data_
std::vector<uint8_t>outputd(OutputBufferBytes); // Potentially for debugging, review if used
std::vector<uint8_t>outpute(OutputBufferBytes); // Potentially for debugging, review if used
// WGpuBufferDescriptor bufferDescriptorI={262144*4,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false}; // Member of WebGPUComputePipeline
// WGpuBufferDescriptor bufferDescriptorO={262144*4,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false}; // Member of WebGPUComputePipeline
// WGpuBufferDescriptor bufferDescriptorM={262144*4,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false}; // Member of WebGPUComputePipeline
// WGpuBufferDescriptor bufferDescriptorC={262144*4,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false}; // Unused or similar to M
// WGpuTextureDescriptor textureDescriptorA={256,256,1,1,1,2,34,WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC|WGPU_TEXTURE_USAGE_COPY_DST}; // Managed by pipeline if textures used
// WGpuTextureViewDescriptor textureViewDescriptorA={34,WGPU_TEXTURE_VIEW_DIMENSION_2D}; // Managed by pipeline if textures used
// char * cmp_bdy=wgl_cmp_src; // This is fine, wgl_cmp_src is used.
// WGpuShaderModuleDescriptor shaderModuleDescriptor={cmp_bdy,0,NULL}; // Member of WebGPUComputePipeline
int randomNumber=0,entropySeed=0; // Used by rNd4, keep
std::random_device randomizer; // Used by rNd4, keep
int raN=0; // Used in Unifrm, related to GL texture updates. Keep for now.
// int raND=0; // Unused, commenting out.
uint32_t * WGPU_Result_Array=new uint32_t[OutputBufferBytes]; // Still used for GL texture update (deferred part)
// uint32_t * WGPU_Input_Array=new uint32_t[InputBufferBytes]; // Replaced by pipeline's input_data_
uint32_t * WGPU_Color_Input_Array=new uint32_t[InputBufferBytes]; // Potentially unused. Review. (Leaving for now)
// WGpuImageCopyTexture WGPU_Input_Image={}; // Related to old texture copies, likely unused
// WGpuImageCopyTexture WGPU_Output_Image={}; // Related to old texture copies, likely unused
// WGpuImageCopyBuffer WGPU_Input_Buffer={}; // Related to old texture copies, likely unused
// WGpuImageCopyBuffer WGPU_Output_Buffer={}; // Related to old texture copies, likely unused
// WGpuImageCopyBuffer WGPU_Mapped_Buffer={}; // Related to old texture copies, likely unused
unsigned char * ColorA=new unsigned char[262144*sizeof(unsigned char)];

// Commenting out old WebGPU global functions and callbacks
// inline int rNd4(int randomMax){ // This function is still used by Run::Unifrm, so keep it.
// The following are being removed as they are part of the old global WebGPU system
/*
WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuBufferMapCallback mapCallbackRun=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
double_int53_t WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2), WGPU_BufferRange.at(0,0,1) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
raN=rNd4(3);
  /*
glActiveTexture(GL_TEXTURE0+raN);
glBindTexture(GL_TEXTURE_2D,wtexture[raN]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&WGPU_ResultBuffer.at(0,0,0));
glGenerateMipmap(GL_TEXTURE_2D); // broken gl textures without
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
  *//*
}
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun=[](WGpuQueue queue,void *userData){
int rndm=0;
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
double_int53_t WGPU_Range_PointerC=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,0)=WGPU_Range_PointerC;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),  WGPU_BufferRange.at(0,0,0) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
rndm=rNd4(3);
  /*
glActiveTexture(GL_TEXTURE0+raN);
glBindTexture(GL_TEXTURE_2D,wtexture[raN]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&WGPU_ResultBuffer.at(0,0,0));
glGenerateMipmap(GL_TEXTURE_2D); // broken gl textures without
  *//*
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
return;
};

static void raf(){
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorA;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorA;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;
WGPU_ColorBuffer.at(0,0,0)=WGPU_Color_Input_Array;
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,3));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
WGPU_Output_Buffer.buffer=WGPU_Buffers.at(0,0,0);
WGPU_Output_Buffer.bytesPerRow=4096;
WGPU_Output_Buffer.rowsPerImage=256;
WGPU_Mapped_Buffer.buffer=WGPU_Buffers.at(2,0,2);
WGPU_Mapped_Buffer.bytesPerRow=4096;
WGPU_Mapped_Buffer.rowsPerImage=256;
raN=rNd4(256);
input[0]=raN;
WGPU_InputBuffer.at(0,0,0)[0]=raN;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(WGPU_Device.at(0,0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayout1;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayout2;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
WGPU_BufferBindingLayout.at(0,0,4)=bufferBindingLayout4;
WGPU_StorageTextureBindingLayout.at(0,0,0)=storageTextureBindingLayout1;
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=1;
bindGroupLayoutEntries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=1;
bindGroupLayoutEntries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
bindGroupLayoutEntries[2].binding=2;
bindGroupLayoutEntries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[2].type=4;
bindGroupLayoutEntries[2].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
WGPU_BindGroupLayoutEntries.at(0,0,0)=bindGroupLayoutEntries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(WGPU_Device.at(0,0,0),WGPU_BindGroupLayoutEntries.at(0,0,0),2);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(WGPU_Device.at(0,0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(WGPU_Device.at(0,0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=WGPU_Buffers.at(1,1,1);
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=InputBufferBytes;
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=WGPU_Buffers.at(0,0,0);
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=OutputBufferBytes;
bindGroupEntry[2].binding=2;
bindGroupEntry[2].resource=WGPU_Texture.at(0,0,0);
WGPU_BindGroupEntries.at(0,0,0)=bindGroupEntry;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(WGPU_Device.at(0,0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),2);
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);
}
return;
}

static void WGPU_Run(){
int RraN=rNd4(256);
input[0]=RraN;
WGPU_InputBuffer.at(0,0,0)[0]=RraN;
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,1),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);
}
return;
}

static void ObtainedWebGpuDeviceStart2(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,1)=result;
raf();
return;
}

static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,0)=result;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,1),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}

static void ObtainedWebGpuAdapterStart2(WGpuAdapter result,void * userData){
WGPU_Adapter.at(0,0,1)=result;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,0),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
}

static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData){
adapter=result;
WGPU_Adapter.at(0,0,0)=result;
navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}
*/
// End of commenting out old WebGPU global functions and callbacks

inline int rNd4(int randomMax){
entropySeed=(randomMax)*randomizer();
std::srand(entropySeed);
randomNumber=std::rand()%randomMax;
return randomNumber;
}

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuBufferMapCallback mapCallbackRun=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
double_int53_t WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2), WGPU_BufferRange.at(0,0,1) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
raN=rNd4(3);
  /*
glActiveTexture(GL_TEXTURE0+raN);
glBindTexture(GL_TEXTURE_2D,wtexture[raN]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&WGPU_ResultBuffer.at(0,0,0));
glGenerateMipmap(GL_TEXTURE_2D); // broken gl textures without
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
  */
}
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun=[](WGpuQueue queue,void *userData){
int rndm=0;
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
double_int53_t WGPU_Range_PointerC=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,0)=WGPU_Range_PointerC;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),  WGPU_BufferRange.at(0,0,0) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
rndm=rNd4(3);
  /*
glActiveTexture(GL_TEXTURE0+raN);
glBindTexture(GL_TEXTURE_2D,wtexture[raN]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&WGPU_ResultBuffer.at(0,0,0));
glGenerateMipmap(GL_TEXTURE_2D); // broken gl textures without
  */
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
return;
};

static void raf(){
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorA;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorA;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;
WGPU_ColorBuffer.at(0,0,0)=WGPU_Color_Input_Array;
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,3));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
WGPU_Output_Buffer.buffer=WGPU_Buffers.at(0,0,0);
WGPU_Output_Buffer.bytesPerRow=4096;
WGPU_Output_Buffer.rowsPerImage=256;
WGPU_Mapped_Buffer.buffer=WGPU_Buffers.at(2,0,2);
WGPU_Mapped_Buffer.bytesPerRow=4096;
WGPU_Mapped_Buffer.rowsPerImage=256;
raN=rNd4(256);
input[0]=raN;
WGPU_InputBuffer.at(0,0,0)[0]=raN;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(WGPU_Device.at(0,0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayout1;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayout2;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
WGPU_BufferBindingLayout.at(0,0,4)=bufferBindingLayout4;
WGPU_StorageTextureBindingLayout.at(0,0,0)=storageTextureBindingLayout1;
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=1;
bindGroupLayoutEntries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=1;
bindGroupLayoutEntries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
bindGroupLayoutEntries[2].binding=2;
bindGroupLayoutEntries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[2].type=4;
bindGroupLayoutEntries[2].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
WGPU_BindGroupLayoutEntries.at(0,0,0)=bindGroupLayoutEntries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(WGPU_Device.at(0,0,0),WGPU_BindGroupLayoutEntries.at(0,0,0),2);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(WGPU_Device.at(0,0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(WGPU_Device.at(0,0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=WGPU_Buffers.at(1,1,1);
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=InputBufferBytes;
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=WGPU_Buffers.at(0,0,0);
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=OutputBufferBytes;
bindGroupEntry[2].binding=2;
bindGroupEntry[2].resource=WGPU_Texture.at(0,0,0);
WGPU_BindGroupEntries.at(0,0,0)=bindGroupEntry;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(WGPU_Device.at(0,0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),2);
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
}
return;
}

static void WGPU_Run(){
int RraN=rNd4(256);
input[0]=RraN;
WGPU_InputBuffer.at(0,0,0)[0]=RraN;
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,1),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
}
return;
}

static void ObtainedWebGpuDeviceStart2(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,1)=result;
raf();
return;
}

static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,0)=result;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,1),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}

static void ObtainedWebGpuAdapterStart2(WGpuAdapter result,void * userData){
WGPU_Adapter.at(0,0,1)=result;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,0),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
}

static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData){
adapter=result;
WGPU_Adapter.at(0,0,0)=result;
navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}

// void WGPU_Start(){ // Removed as it's replaced by webgpu_pipeline_->initialize() in Run::strt()
// WGPU_UserData.at(0,0,0)=userDataA;
// WGPU_UserData.at(0,0,1)=userDataB;
// WGPU_ObtainedDeviceCallback.at(0,0,0)=ObtainedWebGpuDeviceStart;
// WGPU_ObtainedDeviceCallback.at(0,0,1)=ObtainedWebGpuDeviceStart2;
// WGPU_DeviceDescriptor.at(0,0,0)=deviceDescriptor;
// WGPU_RequestAdapterOptions.at(0,0,0)=options;
// WGPU_ObtainedAdapterCallback.at(0,0,0)=ObtainedWebGpuAdapterStart;
// WGPU_ObtainedAdapterCallback.at(0,0,1)=ObtainedWebGpuAdapterStart2;
// WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
// WGPU_ComputeDoneCallback.at(0,0,1)=onComputeDoneRun;
// WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
// WGPU_MapCallback.at(0,0,1)=mapCallbackRun;
// navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
// return;
// }
  
class GPU{

private:

public:

boost::function<const EM_BOOL(boost::uint_t<24>::least)>EBOin=[](boost::uint_t<24>::least EBO){
Sh.at(1,0)=EBO;
return EM_TRUE;
};

boost::function<const EM_BOOL(boost::uint_t<24>::least)>VCOin=[](boost::uint_t<24>::least VCO){
Sh.at(2,0)=VCO;
return EM_TRUE;
};

boost::function<const EM_BOOL(boost::uint_t<24>::least)>VBOin=[](boost::uint_t<24>::least VBO){
Sh.at(2,1)=VBO;
return EM_TRUE;
};

boost::function<const EM_BOOL()>setFloats=[](){
Fi.at(0,0)=1.0f;
Fi.at(1,2)=0.5f;
Fi.at(0,1)=-1.0f;
Fi.at(2,0)=-0.5f;
Fi.at(1,1)=0.0f;
Di.at(0,0)=1.0;
Di.at(0,1)=-1.0;
Di.at(1,1)=0.0;
return EM_TRUE;
};

static inline boost::function<const register float()>gF=[](){
return Fi.at(0,0);
};

static inline boost::function<const register float()>gFm1=[](){
return Fi.at(0,1);
};

static inline boost::function<const register float()>gF0=[](){
return Fi.at(1,1);
};

};

constexpr unsigned char gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
constexpr unsigned char indc[35]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
inline GLint uni_dte=0,uni_res=0,smp_chn_res[4]={},smp_chn[5],uni_frm=0;
inline GLfloat uni_tme=0.0f,uni_fps=0.0f,uni_tme_dlt=0.0f,uni_mse=0.0f;
inline GLfloat uni_chn_tme[4];

struct{
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spana;
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spanb;
boost::chrono::high_resolution_clock::time_point t1;
boost::chrono::high_resolution_clock::time_point t2;
boost::chrono::high_resolution_clock::time_point t3;
}u_time;

union{
boost::uint_t<24>::least VBO,EBO,VCO;
}shad;

inline struct{
boost::compute::double_ wi=0.0;
boost::compute::double_ hi=0.0;
}mouse;

inline struct{
short int csswi=0;
short int csshi=0;
}css;

short int Size=0;
int tmm=166666000;
int tmm2=1000;
inline struct timespec rem;
inline struct timespec req={0,tmm};
inline struct timespec req2={0,tmm2};
static constexpr short int ele=36;

inline EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;

EM_BOOL ms_clk(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return EM_TRUE;
}

EM_BOOL ms_mv(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
mms2.at(0,0)=e->clientX;
mms2.at(0,1)=e->clientY;
}}
return EM_TRUE;
}

static char * result=NULL;
static char * results=NULL;
static long int length=0;
// boost::uint_t<24>::fast uniBlock;

EGLDisplay display=nullptr;
EGLSurface surface=nullptr;
EGLContext ctxegl=nullptr;
EGLConfig eglconfig=nullptr;
EGLint config_size,major,minor;

class Run{

private:

Compile compile;


const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");
const char * src[4];
char * vrt_bdy=vrt_bdy_src;
char * frg_hdr=frg_hdr_src;
char * frg_ftr=frg_ftr_src;
char * cm_hdr=cm_hdr_src;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=0;

GPU gpu;

// Shader content storage for GLSL parts
std::string glsl_common_header_;
std::string glsl_vertex_shader_body_;
std::string glsl_fragment_header_;
std::string glsl_fragment_main_body_; // For the content of Fnm (e.g. shader.glsl)
std::string glsl_fragment_footer_;

// Added WebGPU pipeline member
std::unique_ptr<WebGPUComputePipeline> webgpu_pipeline_;
bool enable_webgpu_compute_ = true; // Added for conditional execution

public:

static EM_BOOL PRGin(register boost::uint_t<24>::least m1){
sse4.at(0,0)=wasm_i64x2_splat(m1);
S1.at(0,0,0)=wasm_i64x2_extract_lane(sse4.at(0,0),0);
return EM_TRUE;
};

static EM_BOOL u_iTime_set(register boost::compute::double_ m80){
// d_time.at(0,0)=m80;
// sse2.at(0,0)=wasm_f64x2_splat(d_time.at(0,0));
sse2.at(0,0)=wasm_f64x2_splat(m80);
d_time.at(0,0)=wasm_f64x2_extract_lane(sse2.at(0,0),0);
return EM_TRUE;
}

static EM_BOOL u_iSize_set(boost::compute::double_ set){
sse.at(1,0)=wasm_f32x4_splat(set);
t_size.at(0,0)=wasm_f32x4_extract_lane(sse.at(1,0),0);
t_size.at(0,1)=wasm_f32x4_extract_lane(sse.at(1,0),0);
return EM_TRUE;
}

// static void i_iSize_set(boost::int_t<24>::fast set){
static EM_BOOL i_iSize_set(short int set){
sse3.at(0,0)=wasm_i32x4_splat(set);
i_size.at(0,0)=wasm_i32x4_extract_lane(sse3.at(0,0),0);
i_size.at(0,1)=wasm_i32x4_extract_lane(sse3.at(0,0),0);
i_size.at(1,0)=wasm_i32x4_extract_lane(sse3.at(0,0),0)*1.25;
i_size.at(1,1)=wasm_i32x4_extract_lane(sse3.at(0,0),0)*1.25;
return EM_TRUE;
}

static EM_BOOL u_iTimeDelta_set(register boost::compute::double_ m64){
sse.at(0,1)=wasm_f64x2_splat(m64);
d_time.at(1,1)=wasm_f64x2_extract_lane(sse.at(0,1),0);
return EM_TRUE;
}

EM_BOOL uniUP(){
t_size.at(0,1)=t_size.at(0,1)*1.01;
glUniform3f(uni_res,t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[0],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[1],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[2],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[3],t_size.at(0,1),t_size.at(0,1),gpu.gF());
//  glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
return EM_TRUE;
}

EM_BOOL uniDOWN(){
t_size.at(0,1)=t_size.at(0,1)*0.99;
glUniform3f(uni_res,t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[0],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[1],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[2],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[3],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
return EM_TRUE;
}

static EM_BOOL viewUP(){
i_size.at(0,1)=i_size.at(0,1)*1.5;
glViewport(0,0,i_size.at(0,1),i_size.at(0,1));
return EM_TRUE;
}

static EM_BOOL viewDOWN(){
i_size.at(0,1)=i_size.at(0,1)/1.5;
glViewport(0,0,i_size.at(0,1),i_size.at(0,1));
return EM_TRUE;
}

static EM_BOOL moveDOWN(){
i_view.at(0,0)=i_view.at(0,0)-1;
glViewport(i_view.at(0,0),i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return EM_TRUE;
}

static EM_BOOL moveUP(){
i_view.at(0,0)=i_view.at(0,0)+1;
glViewport(i_view.at(0,0),i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return EM_TRUE;
}

static EM_BOOL moveLEFT(){
i_view.at(0,1)=i_view.at(0,1)-1;
glViewport(i_view.at(0,0),i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return EM_TRUE;
}

static EM_BOOL moveRIGHT(){
i_view.at(0,1)=i_view.at(0,1)+1;
glViewport(i_view.at(0,0),i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return EM_TRUE;
}

static inline boost::function<EM_BOOL()>RendarA=[](){
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
// non multisampled
// glEnable(GL_DITHER);
// glDisable(GL_POLYGON_OFFSET_FILL);
// glDisable(GL_CULL_FACE);
// glDepthMask(GL_TRUE);
// glDepthFunc(GL_LEQUAL);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
glSampleCoverage(1.0f,GL_FALSE);
glBindFramebuffer(GL_READ_FRAMEBUFFER,TX.at(2,0,0));
glBindFramebuffer(GL_READ_FRAMEBUFFER,0);
glDrawElements(GL_TRIANGLES,ele,GL_UNSIGNED_BYTE,indc);
glBindFramebuffer(GL_READ_FRAMEBUFFER,TX.at(2,0,0));
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(3,0,0));
glBlitFramebuffer(0,0,i_size.at(1,0),i_size.at(1,0),0,0,i_size.at(0,1),i_size.at(0,1),GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT,GL_NEAREST);
// end
// glFlush();
return EM_TRUE;
};

static inline boost::function<EM_BOOL()>RendarB=[](){
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
// multisampled
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
glBindFramebuffer(GL_READ_FRAMEBUFFER,0);
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(1,0,0));
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
glSampleCoverage(numSamplesf,GL_FALSE);
// glEnable(GL_POLYGON_OFFSET_FILL);
// glDepthMask(GL_FALSE);
// glDepthFunc(GL_LESS);
// glDisable(GL_DITHER);
glDrawElements(GL_TRIANGLES,ele,GL_UNSIGNED_BYTE,indc);
glFlush();
return EM_TRUE;
};

static inline boost::function<EM_BOOL()>Unifrm=[](){
uni_i.at(0,0)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
glUniform1f(uni_fps,u_time.time_spanb.count()/1.0f);
if(ms_l==true){
mms.at(0,1)=round(mms2.at(0,0)/i_size.at(0,1));
mms.at(1,1)=round((mms2.at(0,1))/i_size.at(0,1));
}
// retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
// retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
// retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
// retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const long xxx=mms2.at(0,0);
const long yyy=mms2.at(0,1);
mms.at(0,0)=float(xxx);
mms.at(1,0)=float((i_size.at(0,1)-yyy));
clk_l=false;
}
mms.at(2,0)=float(mms2.at(0,0));
mms.at(2,1)=float(i_size.at(0,1)-mms2.at(0,1));
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
}
else{
clk_l=true;
}
// glUniform1f(uni_tme,d_time.at(0,0));
 //   boost::compute::interop::opengl::set_uniform(uni_tme,wasm_f64x2_extract_lane(sse2.at(0,0),0));
  
glUniform1f(uni_tme,std::real(std::complex<double>(wasm_f64x2_extract_lane(sse2.at(0,0),0),0.0)));
// glUniform1f(uni_tme,wasm_f64x2_extract_lane(sse2.at(0,0),0));
  
// glUniform1d(uni_tme,double(wasm_f64x2_extract_lane(sse2.at(0,0),0)));
glUniform1f(uni_chn_tme[0],wasm_f64x2_extract_lane(sse2.at(0,0),0));
glUniform1f(uni_chn_tme[1],wasm_f64x2_extract_lane(sse2.at(0,0),0));
glUniform1f(uni_chn_tme[2],wasm_f64x2_extract_lane(sse2.at(0,0),0));
glUniform1f(uni_chn_tme[3],wasm_f64x2_extract_lane(sse2.at(0,0),0));
glUniform1f(uni_tme_dlt,d_time.at(1,1));

//========== WebGPU Compute Integration Point Start ==========
// if (enable_webgpu_compute_ && webgpu_pipeline_ && webgpu_pipeline_->isInitialized()) { // Check enable_webgpu_compute_ flag
if (webgpu_pipeline_ && webgpu_pipeline_->isInitialized()) { // Keeping previous unconditional behavior for now
    int random_val = rNd4(256); // Using existing random function
    webgpu_pipeline_->setInputDataValue(static_cast<uint8_t>(random_val), 0);
    webgpu_pipeline_->runCompute();
}
//========== WebGPU Compute Integration Point End ==========
// glUniform1f(uni_tme_dlt,wasm_f64x2_extract_lane(sse.at(0,1),0));
  // webgpu
const time_t timE=time(0);
struct tm *datE=localtime(&timE);
int yr=1900+datE->tm_year;
int mn=1+datE->tm_mon;
int dy=datE->tm_mday-1;
int hr=5+datE->tm_hour;
int mi=datE->tm_min;
int sc=datE->tm_sec;
i_date.at(1,0)=dy;
i_date.at(1,1)=(hr*3600)+(mi*60)+(sc);
glUniform4i(uni_dte,i_date.at(0,0),i_date.at(0,1),i_date.at(1,0),i_date.at(1,1));

// New WebGPU logic, replacing the old commented out WGPU_Run and texture update logic.
// int tfrm=(uni_i.at(0,0)%4); // Original comment line

if(uni_i.at(0,0)%45==0) { // This condition was used for WGPU_Run
    if (webgpu_pipeline_ && webgpu_pipeline_->isInitialized()) {
        int random_val = rNd4(256);
        webgpu_pipeline_->setInputDataValue(static_cast<uint8_t>(random_val), 0);
        if (!webgpu_pipeline_->runCompute()) {
            // Optional: handle compute run failure
            // std::cerr << "WebGPU compute run failed in Unifrm." << std::endl;
        }
    }
}

if(uni_i.at(0,0)%15==0) { // This block used WGPU_ResultBuffer for GL texture update.
    // The task defers updating GL textures with webgpu_pipeline_->getComputeResult().
    // So, for now, this will continue to use the global WGPU_ResultBuffer.
    // This global WGPU_ResultBuffer will no longer be updated by WebGPU calls once WGPU_Run is fully removed.
    // This part of the code will eventually need to use webgpu_pipeline_->getComputeResult().
    // For now, to prevent breaking GL rendering completely, we leave it using the (potentially stale) global.
    int current_raN_tex_update = rNd4(3); // Use a distinct variable name to avoid collision if raN was used above
                                       // and to ensure this block has its own random texture index.
    glActiveTexture(GL_TEXTURE0 + current_raN_tex_update);
    glBindTexture(GL_TEXTURE_2D, wtexture[current_raN_tex_update]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // If webgpu_pipeline_ is ready and has results, could use them. For now, using old global.
    // const std::vector<uint32_t>& results = webgpu_pipeline_->getComputeResult();
    // if (webgpu_pipeline_ && webgpu_pipeline_->isInitialized() && !results.empty() && (results.size() * sizeof(uint32_t) >= (size_t)width * height * 4) ) {
    //    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE, results.data());
    // } else {
       glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,WGPU_ResultBuffer.at(0,0,0));
    // }
    glGenerateMipmap(GL_TEXTURE_2D);
    glUniform1i(smp_chn[current_raN_tex_update], current_raN_tex_update);
}

// Original uniform buffer logic (kept as is)
// glBindBuffer(GL_UNIFORM_BUFFER,uniBlock);
// glBufferSubData(GL_UNIFORM_BUFFER,8,4,&uni_i.at(0,0)); 
// glBufferSubData(GL_UNIFORM_BUFFER,12,4,&d_time.at(0,0)); 
// glBindBuffer(GL_UNIFORM_BUFFER,0);

// Original iChannel samplers (kept as is)
// These were inside the commented block but seem generally useful for ShaderToy compatibility.
// If they are only for WebGPU updated textures, this might need adjustment later.
glUniform1i(smp_chn[0],0);
glUniform1i(smp_chn[1],1);
glUniform1i(smp_chn[2],2);
glUniform1i(smp_chn[3],3);

// End of new WebGPU logic block
glUniform1i(uni_frm,uni_i.at(0,0));
// glFlush();
eglSwapBuffers(display,surface);
return EM_TRUE;
};

static EM_BOOL Rend()noexcept{
RendarA();
Unifrm();
RendarB();
return EM_TRUE;
}

boost::function<EM_BOOL()>swap=[](){
emscripten_get_element_css_size("canvas",&mouse.wi,&mouse.hi);
emscripten_set_element_css_size("zcanvas",mouse.hi,mouse.hi);
emscripten_cancel_main_loop();
// emscripten_get_canvas_element_size("#zcanvas",&css.csswi,&css.csshi);
Size=(short int)mouse.hi;
i_iSize_set(Size);
u_iSize_set(float(mouse.hi));
i_view.at(0,0)=0;
i_view.at(0,1)=0;
mms.at(0,0)=0.5*t_size.at(0,0);
mms.at(0,1)=0.5*t_size.at(0,0);
mms.at(1,0)=0.5*t_size.at(0,0);
mms.at(1,1)=0.5*t_size.at(0,0);
// glUniform3f(uni_res,t_size.at(0,0),t_size.at(0,0),1.0f);
mms.at(2,0)=t_size.at(0,0)*0.5;
mms.at(2,1)=t_size.at(0,0)*0.5;
// glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
// glUniform3f(smp_chn_res[0],t_size.at(0,0),t_size.at(0,0),1.0f);
// glUniform3f(smp_chn_res[1],t_size.at(0,0),t_size.at(0,0),1.0f);
// glUniform3f(smp_chn_res[2],t_size.at(0,0),t_size.at(0,0),1.0f);
// glUniform3f(smp_chn_res[3],t_size.at(0,0),t_size.at(0,0),1.0f);
glViewport(0,0,i_size.at(0,0),i_size.at(0,0));  //  viewport/scissor after UsePrg runs at full resolution
glScissor(0,0,i_size.at(0,0),i_size.at(0,0));
u_iTime_set(0.0);
u_iTimeDelta_set(0.0);
u_time.t1=boost::chrono::high_resolution_clock::now();
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
glUseProgram(0);
glFlush();
glDeleteProgram(S1.at(0,0,0));
glDeleteBuffers(1,&Sh.at(2,1));
glDeleteBuffers(1,&Sh.at(1,0));
glDeleteVertexArrays(1,&Sh.at(2,0));
return EM_TRUE;
};

inline char * rd_fl(const char * Fnm){
FILE * file=fopen(Fnm,"r");
::boost::tuples::tie(result,results,file);
if(file){
int32_t stat=fseek(file,(int32_t)0,SEEK_END);
if(stat!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
stat=fseek(file,(int32_t)0,SEEK_SET);
if(stat!=0){
fclose(file);
return nullptr;
}
result=static_cast<char *>(malloc((length+1)*sizeof(char)));
if(result){
size_t actual_length=fread(result,sizeof(char),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
results=reinterpret_cast<char *>(result);
return results;
}
return nullptr;
}

boost::function<EM_BOOL()>strt=[this](){
//========== OpenGL/EGL Initialization Start ==========
typedef struct{GLfloat XYZW[4];}Vertex;
gpu.setFloats();
const Vertex vrt[8]={{gpu.gFm1(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gFm1(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()}};
::boost::tuples::tie(Fi,sse);
::boost::tuples::tie(uni_i,Si,sse3);
::boost::tuples::tie(cntx,mms);
::boost::tuples::tie(i_size,cntxi);
::boost::tuples::tie(mouse.hi,mouse.wi,d_time);
::boost::tuples::tie(u_time.t1,u_time.t2,u_time.t3);
::boost::tuples::tie(shad.EBO,shad.VBO,shad.VCO,sse4);
::boost::tuples::tie(config_size,major,minor);
::boost::tuples::tie(display,surface,eglconfig);
::boost::tuples::tie(attr,ctxegl,ctx);
::boost::tuples::tie(cm_hdr_src,vrt_bdy_src,frg_hdr_src,frg_ftr_src);
::boost::tuples::tie(vrt,indc,ele);
::boost::tuples::tie(retCl,retMu,retMd,retMv);
::boost::tuples::tie(retSa,retSb,retSc);
::boost::tuples::tie(ms_l,clk_l);
::boost::tuples::tie(u_time.time_spana,u_time.time_spanb);
::boost::tuples::tie(rem,req,tmm);
eglconfig=NULL;
uni_i.at(0,0)=0;
clk_l=true;

// Load GLSL shader parts from files
char* temp_shader_cstr;

temp_shader_cstr = rd_fl("shaders/common_header.glsl");
if (!temp_shader_cstr) { std::cerr << "FATAL: Failed to read shaders/common_header.glsl" << std::endl; /* Handle error, maybe return EM_FALSE */ }
else { glsl_common_header_ = temp_shader_cstr; free(temp_shader_cstr); }

temp_shader_cstr = rd_fl("shaders/vertex_shader.glsl");
if (!temp_shader_cstr) { std::cerr << "FATAL: Failed to read shaders/vertex_shader.glsl" << std::endl; /* Handle error */ }
else { glsl_vertex_shader_body_ = temp_shader_cstr; free(temp_shader_cstr); }

temp_shader_cstr = rd_fl("shaders/fragment_header.glsl");
if (!temp_shader_cstr) { std::cerr << "FATAL: Failed to read shaders/fragment_header.glsl" << std::endl; /* Handle error */ }
else { glsl_fragment_header_ = temp_shader_cstr; free(temp_shader_cstr); }

temp_shader_cstr = rd_fl(Fnm); // Fnm is "shaders/shader.glsl"
if (!temp_shader_cstr) { std::cerr << "FATAL: Failed to read " << Fnm << std::endl; /* Handle error */ }
else { glsl_fragment_main_body_ = temp_shader_cstr; free(temp_shader_cstr); }

temp_shader_cstr = rd_fl("shaders/fragment_footer.glsl");
if (!temp_shader_cstr) { std::cerr << "FATAL: Failed to read shaders/fragment_footer.glsl" << std::endl; /* Handle error */ }
else { glsl_fragment_footer_ = temp_shader_cstr; free(temp_shader_cstr); }

// std::string frag_body_S=frag_body; // Old line, frag_body char* is freed. Use glsl_fragment_main_body_ if needed as string.
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#zcanvas",&attr);
cntxi.at(0,0)=ctx;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
// emscripten_webgl_make_context_current(cntxi.at(0,0));
// nanoPause();
//   emscripten_get_canvas_element_size("#zcanvas",&css.csswi,&css.csshi);
emscripten_get_element_css_size("canvas",&mouse.wi,&mouse.hi);
emscripten_set_element_css_size("zcanvas",mouse.hi,mouse.hi);
Size=(short int)mouse.hi;
// Size=css.csshi;
i_iSize_set(Size);
// u_iSize_set(mouse.hi);
u_iSize_set(float(mouse.hi));
i_view.at(0,0)=0;
i_view.at(0,1)=0;
mms.at(0,0)=0.5*t_size.at(0,0);
mms.at(0,1)=0.5*t_size.at(0,0);
mms.at(1,0)=0.5*t_size.at(0,0);
mms.at(1,1)=0.5*t_size.at(0,0);
  
// eglMakeCurrent(display,surface,surface,cntx.at(0,0));
emscripten_webgl_make_context_current(cntxi.at(0,0));

// eglBindAPI(EGL_OPENGL_ES_API);
// eglBindAPI(0);
///glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
  
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_ALL_EXTENSIONS");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_KHR_no_error");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_REGAL_enable");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_ANGLE_platform_angle");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_ARB_spirv_extensions");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_color_buffer_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_sample_shading");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_framebuffer_object");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_framebuffer_sRGB");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_fragment_program");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_fragment_program_option");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_fragment_program");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_fragment_program2");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_float_buffer");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_sample_shading");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_gl_spirv");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_spirv_extensions");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_polygon_offset_clamp");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shader_atomic_counter_ops");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_coverage_sample_resolve");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_quadruple_buffer");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_coverage_sample");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_depth_buffer_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_color_buffer_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_color_buffer_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_texture_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_texture_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_IMG_context_priority");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_element_index_uint");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_sample_variables");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_HI_colorformats");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_KHR_create_context");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_ARB_robustness");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_create_context_robustness");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_scrgb");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_scrgb_linear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_gpu_shader4");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_gpu_shader5");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_vertex_buffer_unified_memory");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_gpu_program5");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_vertex_attrib_integer_64bit");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_gpu_shader_fp64");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_vertex_attrib_64bit");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_sRGB_write_control");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_sample_shading");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_multisample_compatibility");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_vertex_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_framebuffer_multisample");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_enhanced_layouts");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shading_language_420pack");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_get_program_binary");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_bindable_uniform");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_EXT_geometry_shader4");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_ARB_ES2_compatibility");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_ARB_direct_state_access");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_multitexture");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_KHR_color_buffer_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_EXT_texture_norm16");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_color_buffer_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_EXT_color_buffer_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_ANGLE_d3d_texture_client_buffer");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_ANGLE_direct3d_display");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_ANGLE_robust_resource_initialization");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_device_base");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_output_base");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_platform_base");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_platform_device");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_swap_buffers_with_damage");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_cuda_event");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_device_cuda");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_robustness_video_memory_purge");
        
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
eglChooseConfig(display,att_lst,&eglconfig,1,&config_size);
eglInitialize(display,&major,&minor);
ctxegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,ctx_att);
cntx.at(0,0)=ctxegl;
// eglSwapBuffers(display,surface);
eglMakeCurrent(display,surface,surface,cntx.at(0,0));
emscripten_webgl_make_context_current(cntxi.at(0,0));
glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
glDepthMask(GL_TRUE);
// glClearDepth(Di.at(0,0));
 //    glDepthFunc(GL_GREATER);
// // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// glEnable(BLEND_ADVANCED_COHERENT_NV);
glDisable(GL_DITHER);
// glDepthFunc(GL_LEQUAL);
// glDepthFunc(GL_LESS);
// glDisable(GL_BLEND);
glEnable(GL_DEPTH_TEST);
// glEnable(GL_BLEND);
glEnable(GL_STENCIL_TEST);
// glDisable(GL_STENCIL_TEST);
// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
// glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
// glStencilFunc(GL_ALWAYS,1,0xFF);
// glStencilMask(0xFF);
glFrontFace(GL_CW);
// glCullFace(GL_BACK);
// glEnable(GL_CULL_FACE);
// glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_DST_COLOR,GL_ONE_MINUS_SRC_ALPHA);
// glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
 // glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
// glBlendEquationSeparate(GL_MIN,GL_MAX);
// glBlendEquation(GL_FUNC_SUBTRACT);
//   glClearColor(1.0f,1.0f,1.0f,1.0f);
glGenBuffers((GLsizei)1,&shad.VBO);
gpu.VBOin(shad.VBO);
glBindBuffer(GL_ARRAY_BUFFER,Sh.at(2,1));
glBufferData(GL_ARRAY_BUFFER,sizeof(vrt),vrt,GL_DYNAMIC_DRAW);
 /* 
auto CLdevice=boost::compute::system::default_device();
auto CLcontext=boost::compute::context(CLdevice);
auto command_queue=boost::compute::command_queue(CLcontext,CLdevice);
std::cout << "Got OpenCL context:" << CLcontext << '\n'; 
   // Boost Compute / Interop / OpenGL
boost::compute::buffer_object_interface buffer_object(CLdevice,GL_ARRAY_BUFFER);
boost::compute::vertex_array_object vertex_array(CLdevice);
vertex_array.bind_buffer(GL_ARRAY_BUFFER,buffer_object);
vertex_array.set_attribute_pointer(0,4,GL_FLOAT,GL_FALSE,0,0);
boost::compute::interop::opengl::buffer vertex_buffer(CLcontext,sizeof(float)*4);
vertex_buffer.write(new float[8]{gpu.gFm1(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gFm1(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()},0,sizeof(float)*4);
buffer_object.bind(GL_ARRAY_BUFFER);
buffer_object.set_data(vertex_buffer);
*/
// nanoPause();
  
glGenBuffers((GLsizei)1,&shad.EBO);
gpu.EBOin(shad.EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Sh.at(1,0));
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_DYNAMIC_DRAW);
  //    boost::compute::buffer index_buffer(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STATIC_DRAW);
// nanoPause();
// src[0]=cm_hdr; // Old way
// src[1]=vrt_bdy; // Old way
if (glsl_common_header_.empty() || glsl_vertex_shader_body_.empty()) {
    std::cerr << "FATAL: Vertex shader parts not loaded into strings." << std::endl; return EM_FALSE;
}
src[0]=glsl_common_header_.c_str();
src[1]=glsl_vertex_shader_body_.c_str();
boost::uint_t<24>::least vtx=compile.cmpl_shd(GL_VERTEX_SHADER,2,src);

// src[0]=cm_hdr; // Old way
// src[1]=frg_hdr; // Old way
// src[2]=frag_body; // Old way, original frag_body char* is freed. Use glsl_fragment_main_body_.c_str()
// src[3]=frg_ftr; // Old way
if (glsl_common_header_.empty() || glsl_fragment_header_.empty() || glsl_fragment_main_body_.empty() || glsl_fragment_footer_.empty()) {
    std::cerr << "FATAL: Fragment shader parts not loaded into strings." << std::endl; return EM_FALSE;
}
src[0]=glsl_common_header_.c_str();
src[1]=glsl_fragment_header_.c_str();
src[2]=glsl_fragment_main_body_.c_str();
src[3]=glsl_fragment_footer_.c_str();
boost::uint_t<24>::least frag=compile.cmpl_shd(GL_FRAGMENT_SHADER,4,src);
boost::uint_t<24>::least shd_prg=glCreateProgram();
PRGin(shd_prg);
::boost::tuples::tie(Sh,shd_prg);
::boost::tuples::tie(frag,vtx);
glAttachShader(S1.at(0,0,0),frag);
glAttachShader(S1.at(0,0,0),vtx);
glBindAttribLocation(S1.at(0,0,0),0,"iPosition");
glLinkProgram(S1.at(0,0,0));
  /*
boost::uint_t<24>::fast uniIndex=glGetUniformBlockIndex(S1.at(0,0,0),"uniBlock");   
glUniformBlockBinding(S1.at(0,0,0),0,uniIndex);
glGenBuffers(1,&uniBlock);
glBindBuffer(GL_UNIFORM_BUFFER,uniBlock);
glBufferData(GL_UNIFORM_BUFFER,4,NULL,GL_DYNAMIC_DRAW);
glBindBufferBase(GL_UNIFORM_BUFFER,0,uniBlock);
glBindBuffer(GL_UNIFORM_BUFFER,0);
*/
GLsizei * binLength;
GLenum * binaryFormat;
void * GLbin;
glDetachShader(S1.at(0,0,0),frag);
glDetachShader(S1.at(0,0,0),vtx);
glGetProgramBinary(S1.at(0,0,0),sizeof(GLbin),binLength,binaryFormat,&GLbin);
bin.at(0,0)=GLbin;
// nanoPause();
glProgramBinary(S1.at(0,0,0),*binaryFormat,bin.at(0,0),*binLength);
// nanoPause();
// glGenRenderbuffers(1,&colorBuffer);
glSampleCoverage(1.0f,GL_FALSE);
    // draw framebuffer
glGenFramebuffers(1,&TX.at(3,0,0));
glGenRenderbuffers(1,&TX.at(2,2,0));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(2,2,0));
glRenderbufferStorage(GL_RENDERBUFFER,GL_RGBA32UI,i_size.at(0,0),i_size.at(0,0));
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(3,0,0));
glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_COLOR_ATTACHMENT3,GL_RENDERBUFFER,TX.at(2,2,0));
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(3,0,0));
//  //  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
  //  non multisampled color renderbuffer (32UI bit?)
glGenFramebuffers(1,&TX.at(2,0,0));
glGenRenderbuffers(1,&TX.at(2,1,0));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(2,1,0));
// glRenderbufferStorage(GL_RENDERBUFFER,GL_RGBA32UI,i_size.at(0,0),i_size.at(0,0));
glRenderbufferStorage(GL_RENDERBUFFER,GL_RGBA16_EXT,i_size.at(0,0),i_size.at(0,0));
glBindFramebuffer(GL_READ_FRAMEBUFFER,TX.at(2,0,0));
glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER,GL_COLOR_ATTACHMENT2,GL_RENDERBUFFER,TX.at(2,1,0));

    //  non multisampled color renderbuffer (12,12,12,12 bit?)
glGenRenderbuffers(1,&TX.at(2,2,0));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(2,2,0));
glRenderbufferStorage(GL_RENDERBUFFER,GL_RGB10_A2UI,i_size.at(0,0),i_size.at(0,0));
// glRenderbufferStorage(GL_RENDERBUFFER,GL_RGBA32UI,i_size.at(0,0),i_size.at(0,0));
glBindFramebuffer(GL_READ_FRAMEBUFFER,TX.at(2,0,0));
glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER,GL_COLOR_ATTACHMENT4,GL_RENDERBUFFER,TX.at(2,2,0));

  
//  glBindFramebuffer(GL_FRAMEBUFFER,0);
   //  non multisampled depth renderbuffer  (GL_DEPTH_COMPONENT24)
glGenRenderbuffers(1,&TX.at(0,0,2));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(0,0,2));
glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,i_size.at(0,0),i_size.at(0,0));
// glDepthRange(0.0f,1.0f);
// glClearDepthf(1.0f);
/// glClearDepthf(1.0);
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(2,0,0));
glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,TX.at(0,0,2));
/* //  non-multisample COVERAGE_COMPONENT4_NV  renderbuffer
glGenRenderbuffers(1,&TX.at(1,0,1));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(1,0,1));
glRenderbufferStorage(GL_RENDERBUFFER,GL_COVERAGE_COMPONENT4_NV,i_size.at(0,0),i_size.at(0,0));
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(2,0,0));
glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_COVERAGE_ATTACHMENT_NV,GL_RENDERBUFFER,TX.at(1,0,1));
*/
/*  // non multisampled stencil renderbuffer
glGenRenderbuffers(1,&TX.at(0,1,2));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(0,1,2));
glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL_INDEX8,i_size.at(0,0),i_size.at(0,0));
glStencilMask(1);
glClearStencil(1);
glBindFramebuffer(GL_READ_FRAMEBUFFER,TX.at(2,0,0));
glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER,GL_STENCIL_ATTACHMENT,GL_RENDERBUFFER,TX.at(0,0,2));
  */
glBindFramebuffer(GL_READ_FRAMEBUFFER,TX.at(2,0,0));
//// glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
// glBindRenderbuffer(GL_RENDERBUFFER,0);
glBindFramebuffer(GL_READ_FRAMEBUFFER,0);
////  glClearColor(0.0f,0.0f,0.0f,1.0f);
//// glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
//// glFlush();
//// glFinish();
glSampleCoverage(numSamplesf,GL_FALSE);
  //  multisample
glGenFramebuffers(1,&TX.at(1,0,0));
     //  color renderbuffer
glGenRenderbuffers(1,&TX.at(0,0,0));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(0,0,0));
// glRenderbufferStorageMultisample(GL_RENDERBUFFER,numSamples,GL_R11F_G11F_B10F,i_size.at(1,0),i_size.at(1,0));
glRenderbufferStorageMultisample(GL_RENDERBUFFER,2,GL_RGBA32F,i_size.at(1,0),i_size.at(1,0));
// glBindRenderbuffer(GL_COLOR_ATTACHMENT0,TX.at(0,0,0));
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(1,0,0));
glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_RENDERBUFFER,TX.at(0,0,0));
/*        //  alpha renderbuffer
glGenRenderbuffers(1,&TX.at(0,1,1));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(0,1,1));
// glRenderbufferStorageMultisample(GL_RENDERBUFFER,numSamples,GL_SRGB8_ALPHA8,i_size.at(1,0),i_size.at(1,0));
glRenderbufferStorageMultisample(GL_RENDERBUFFER,numSamples,GL_RGB10_A2,i_size.at(1,0),i_size.at(1,0));
// glBindRenderbuffer(GL_COLOR_ATTACHMENT1,TX.at(0,1,1));
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(1,0,0));
glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_RENDERBUFFER,TX.at(0,1,1));
*/  //  depth32 stencil8 renderbuffer
glGenRenderbuffers(1,&TX.at(0,0,1));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(0,0,1));
// glRenderbufferStorageMultisample(GL_RENDERBUFFER,numSamples,GL_DEPTH_COMPONENT24,i_size.at(1,0),i_size.at(1,0));
glRenderbufferStorageMultisample(GL_RENDERBUFFER,8,GL_DEPTH32F_STENCIL8,i_size.at(1,0),i_size.at(1,0));
// glBindRenderbuffer(GL_DEPTH_STENCIL_ATTACHMENT,TX.at(0,0,1));
// glDepthRange(0.0f,1.0f);
// glClearDepthf(1.0f);
/// glClearDepthf(1.0f);
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(1,0,0));
glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,TX.at(0,0,1));
/// glStencilMask(1);
/// glClearStencil(0);
 /*   //  depth32 renderbuffer
glGenRenderbuffers(1,&TX.at(0,1,0));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(0,1,0));
glRenderbufferStorageMultisample(GL_RENDERBUFFER,2,GL_DEPTH_COMPONENT32F,i_size.at(1,0),i_size.at(1,0));
/// glClearDepth(1.0);
glBindFramebuffer(GL_FRAMEBUFFER,TX.at(1,0,0));
glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,TX.at(0,1,0));
*/
  //  sRGB
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(1,0,0));
 /*   // initiate textures for Shadertoy Channel
glGenTextures(1,&wtexture[0]);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,wtexture[0]);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,t_size.at(0,0),t_size.at(0,0),0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
glGenerateMipmap(GL_TEXTURE_2D);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,wtexture[0],0);  
*/
//// glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
// glBindRenderbuffer(GL_RENDERBUFFER,0);
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
//// glClearColor(0.0f,0.0f,0.0f,1.0f);
// glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_COVERAGE_BUFFER_BIT_NV);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
glFlush();
// glFinish();
// glPolygonOffset(-1.0,-1.0);
// glEnable(GL_POLYGON_OFFSET_FILL);
glUseProgram(S1.at(0,0,0));
// nanoPause();
glUniform1i(glGetUniformLocation(S1.at(0,0,0),"renderBuffer"),0);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays((GLsizei)1,&shad.VCO);
gpu.VCOin(shad.VCO);
glBindVertexArray(Sh.at(2,0));
// nanoPause();
const GLuint atb_pos=glGetAttribLocation(S1.at(0,0,0),"iPosition");
glEnableVertexAttribArray(atb_pos);
// nanoPause();
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
uni_dte=glGetUniformLocation(S1.at(0,0,0),"iDate");
uni_tme=glGetUniformLocation(S1.at(0,0,0),"iTime");
uni_tme_dlt=glGetUniformLocation(S1.at(0,0,0),"iTimeDelta");
uni_chn_tme[0]=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[0]");
uni_chn_tme[1]=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[1]");
uni_chn_tme[2]=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[2]");
uni_chn_tme[3]=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[3]");
uni_frm=glGetUniformLocation(S1.at(0,0,0),"iFrame");
uni_fps=glGetUniformLocation(S1.at(0,0,0),"iFrameRate");
uni_res=glGetUniformLocation(S1.at(0,0,0),"iResolution");
uni_mse=glGetUniformLocation(S1.at(0,0,0),"iMouse");
smp_chn_res[0]=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[0]");
smp_chn_res[1]=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[1]");
smp_chn_res[2]=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[2]");
smp_chn_res[3]=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[3]");
smp_chn[0]=glGetUniformLocation(S1.at(0,0,0),"iChannel0");
smp_chn[1]=glGetUniformLocation(S1.at(0,0,0),"iChannel1");
smp_chn[2]=glGetUniformLocation(S1.at(0,0,0),"iChannel2");
smp_chn[3]=glGetUniformLocation(S1.at(0,0,0),"iChannel3");
  /*
  // uni non-block
GLuint Ubuffer;
glGenBuffers(1,&Ubuffer);
glBindBuffer(GL_UNIFORM_BUFFER_EXT,Ubuffer);
glBufferData(GL_UNIFORM_BUFFER_EXT,4,NULL,GL_DYNAMIC_DRAW);
UniformBufferEXT(S1.at(0,0,0),uni_tme,Ubuffer);
// glBindBufferBase(GL_UNIFORM_BUFFER,0,uniBlock);
*/
    // texture
glGenTextures(1,&wtexture[0]);
glGenTextures(1,&wtexture[1]);
glGenTextures(1,&wtexture[2]);
glGenTextures(1,&wtexture[3]);
GLsizei width1=256;
GLsizei height1=256;
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,wtexture[0]);
// glBindTextureUnit(GLuint(0),wtexture[0]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width1,height1,0,GL_RGBA,GL_UNSIGNED_BYTE,ColorA);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[0],0);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D,wtexture[1]);
// glBindTextureUnit(GLuint(1),wtexture[1]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width1,height1,0,GL_RGBA,GL_UNSIGNED_BYTE,ColorA);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[1],1);
glActiveTexture(GL_TEXTURE2);
glBindTexture(GL_TEXTURE_2D,wtexture[2]);
// glBindTextureUnit(GLuint(2),wtexture[2]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width1,height1,0,GL_RGBA,GL_UNSIGNED_BYTE,ColorA);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[2],2);
glGenTextures(1,&wtexture[3]);
glActiveTexture(GL_TEXTURE3);
glBindTexture(GL_TEXTURE_2D,wtexture[3]);
// glBindTextureUnit(GLuint(3),wtexture[3]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width1,height1,0,GL_RGBA,GL_UNSIGNED_BYTE,ColorA);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[3],3);
//========== OpenGL/EGL Initialization End ==========

//========== WebGPU Compute Pipeline Initialization Start ==========
if (!webgpu_pipeline_) {
    webgpu_pipeline_ = std::make_unique<WebGPUComputePipeline>(
        "shaders/compute_shader.wgsl", // WGSL Shader filepath
        Entry,                         // Entry point, defined in this file
        InputBufferBytes,              // Defined in this file
        OutputBufferBytes              // Defined in this file
    );
}
if (webgpu_pipeline_) {
    webgpu_pipeline_->initialize();
}
// usleep(125); // Original sleep call, kept for now
//========== WebGPU Compute Pipeline Initialization End ==========


  // date/time
const time_t timE=time(0);
struct tm *datE=localtime(&timE);
int yr=1900+datE->tm_year;
int mn=1+datE->tm_mon;
int dy=datE->tm_mday-1;
int hr=5+datE->tm_hour;
int mi=datE->tm_min;
int sc=datE->tm_sec;
int shaderToySeconds=(hr*3600)+(mi*60)+(sc);
i_date.at(0,0)=yr;
i_date.at(0,1)=mn;
i_date.at(1,0)=dy;
i_date.at(1,1)=shaderToySeconds;
glUniform4i(uni_dte,i_date.at(0,0),i_date.at(0,1),i_date.at(1,0),i_date.at(1,1));
glUniform3f(uni_res,4096.0f,4096.0f,gpu.gF());
glUniform3f(uni_res,t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform3f(smp_chn_res[0],t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform3f(smp_chn_res[1],t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform3f(smp_chn_res[2],t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform3f(smp_chn_res[3],t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform1i(smp_chn[0],0);
glUniform1i(smp_chn[1],1);
glUniform1i(smp_chn[2],2);
glUniform1i(smp_chn[3],3);
glUniform1i(uni_fps,60.0);
mms.at(2,0)=t_size.at(0,0)*0.5;
mms.at(2,1)=t_size.at(0,0)*0.5;
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
glViewport(0,0,8192,8192);  //  viewport/scissor after UsePrg runs at full resolution
glViewport(0,0,i_size.at(0,0),i_size.at(0,0));  //  viewport/scissor after UsePrg runs at full resolution
glEnable(GL_SCISSOR_TEST);
glScissor(0,0,i_size.at(0,0),i_size.at(0,0));
u_iTime_set(0.0);
u_iTimeDelta_set(0.0);
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
//  glBindBuffer(GL_UNIFORM_BUFFER,uniBlock);
//  glBufferSubData(GL_UNIFORM_BUFFER,0,4,&iFps); 
//  glBindBuffer(GL_UNIFORM_BUFFER,0);
// glClear(GL_COLOR_BUFFER_BIT);
// glClear(GL_DEPTH_BUFFER_BIT);
// glClear(GL_STENCIL_BUFFER_BIT);
// glDisable(GL_DEPTH_TEST);
// glDisable(GL_STENCIL_TEST);
// eglBindAPI(0);
emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
// glBindVertexArray(0);
glEnableVertexAttribArray(0);
emscripten_set_main_loop((void(*)())Run::Rend,0,0);
return EM_TRUE;
};

};
