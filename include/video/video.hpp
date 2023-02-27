#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 2
#pragma STDC CX_LIMITED_RANGE ON

#include <wasm_simd128.h>
#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>
#include <unistd.h>

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cfloat>
#include <climits>

#include <unistd.h>

#include <emscripten.h>
#include <emscripten/html5.h>

#define GL_FRAGMENT_PRECISION_HIGH 1
#define GL3_PROTOTYPES 1
#define GL4_PROTOTYPES 1 //maybe??

#include <webgl/webgl2.h>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>

#define GL_GLES_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>

#define EGL_EGL_PROTOTYPES 1
#include <EGL/egl.h>
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

int_fast32_t Size;
double wi_js,hi_js;

EGLContext contextegl_js;
EGLDisplay display_js;
EGLSurface surface_js;
EGLConfig eglconfig_js;
EGLint config_size_js,major_js,minor_js;

EmscriptenWebGLContextAttributes attr_js;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx_js;

EGLint const attribut_list_js[]={ 
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_NONE
};

EGLint const anEglCtxAttribs2_js[]={
EGL_CONTEXT_CLIENT_VERSION,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)6,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE
};

EGLint const attribute_list_js[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR|EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
EGL_CONFORMANT,EGL_NONE,
// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
EGL_CONFIG_CAVEAT,EGL_NONE,
// EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_TRANSPARENT_TYPE,EGL_TRANSPARENT_RGB,
// EGL_TRANSPARENT_RED_VALUE,(EGLint)128,
// EGL_TRANSPARENT_GREEN_VALUE,(EGLint)128,
// EGL_TRANSPARENT_BLUE_VALUE,(EGLint)0,
// // EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_RED_SIZE,(EGLint)64,
EGL_GREEN_SIZE,(EGLint)64,
EGL_BLUE_SIZE,(EGLint)64,
EGL_ALPHA_SIZE,(EGLint)64,
EGL_DEPTH_SIZE,(EGLint)64,
EGL_STENCIL_SIZE,(EGLint)64,
EGL_BUFFER_SIZE,(EGLint)64,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_SAMPLES,(EGLint)64,
EGL_MIPMAP_LEVEL,(EGLint)64,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
EGL_NONE
};


void avgFrm(short int Fnum,int leng,float *ptr,float *aptr);

void egl();

extern "C"{

void b3();

void nano(short int Fnum,int leng,float *ptr,float *aptr);

}
