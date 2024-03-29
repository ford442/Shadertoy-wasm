#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#define _XOPEN_SOURCE 700
#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD -1

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

int Size_js;
double wi_js,hi_js;

EGLContext contextegl_js;
EGLDisplay display_js;
EGLSurface surface_js;
EGLConfig eglconfig_js;
EGLint config_size_js,major_js,minor_js;

EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
EGLConfig eglconfig;
EGLint config_size,major,minor;

int iFrame,iFps,Size,iwi,ihi;

EmscriptenWebGLContextAttributes attr_js;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx_js;

EGLint const attribut_list_js[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_NONE,EGL_NONE
};

EGLint const anEglCtxAttribs2_js[]={
// EGL_CONTEXT_CLIENT_VERSION,(EGLint)3,
// EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE,EGL_NONE
};

EGLint const attribute_list_js[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR|EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
// EGL_CONFIG_CAVEAT,EGL_NONE,
// EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
// EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_TRANSPARENT_TYPE,EGL_TRANSPARENT_RGB,
// EGL_TRANSPARENT_RED_VALUE,(EGLint)128,
// EGL_TRANSPARENT_GREEN_VALUE,(EGLint)128,
// EGL_TRANSPARENT_BLUE_VALUE,(EGLint)0,
// // EGL_NATIVE_RENDERABLE,EGL_TRUE,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_RED_SIZE,(EGLint)24,
EGL_GREEN_SIZE,(EGLint)24,
EGL_BLUE_SIZE,(EGLint)24,
EGL_ALPHA_SIZE,(EGLint)24,
EGL_DEPTH_SIZE,(EGLint)32,
EGL_STENCIL_SIZE,(EGLint)16,
EGL_BUFFER_SIZE,(EGLint)32,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_SAMPLES,(EGLint)8,
EGL_MIPMAP_LEVEL,(EGLint)1,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
EGL_NONE
};

void avgFrm(int,int,float *,float *);

float max;
float min;
float sum;
float avgSum;
float minSum;
float maxSum;

extern "C"{

void b3();

void nano(short int,int,float *,float *);

}

double wi,hi;
float cMouseY,cMouseX,mouseY,mouseX,F=1.0f,Fm1=-1.0f;
float_t F0=0.0f;
double TtimeDelta,Dm1=-1.0,D=1.0;
float Ttime;
double_t D0=0.0;
char * fileloc=(char*)"/shader/shader1.toy";
std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;
std::chrono::steady_clock::time_point t3;

struct timespec rem;
struct timespec req={0,16666666};

GLclampf avrg,drk,brt;
GLclampf mX,mY;
GLclampf mm,nn;
GLuint atb_pos;
GLclampf x,y,gF=F,gF0=F0,gFm1=Fm1,y1y=1.0f;
GLclampd gD=D,gD0=D0,gDm1=Dm1;
GLfloat g1g=F,S;
GLsizei s4=4,i;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res,VCO,ECO,vtx,frag,uni_mse,shader,uni_srate,uni_res,uni_tme_dlt,uni_tme,uni_frm,uni_fps;
typedef struct{GLclampf XYZW[4];}Vertex;
const Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
const GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
const GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
GLchar * sources[4];
GLchar common_shader_header_gles3[]=
"#version 300 es\n"
"#pragma STDGL(invariant all)\n"
"#pragma optionNV(fastmath on)\n"
"#pragma optionNV(fastprecision on)\n"
"#pragma optionNV(unroll all)\n"
"#pragma optionNV(ifcvt none)\n"
"#pragma optionNV(inline all)\n"
"#pragma optionNV(strict off)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 1\n"
"precision highp float;precision lowp sampler3D;precision highp sampler2D;"
"precision lowp samplerCube;precision lowp sampler2DArray;precision lowp sampler2DShadow;"
"precision lowp isampler2D;precision lowp isampler3D;precision lowp isamplerCube;"
"precision lowp isampler2DArray;precision lowp usampler2D;precision lowp usampler3D;"
"precision lowp usamplerCube;precision lowp usampler2DArray;precision lowp samplerCubeShadow;"
"precision lowp sampler2DArrayShadow;\n";
GLchar vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n";
GLchar fragment_shader_header_gles3[]=
"uniform highp float iTime;uniform lowp float iTimeDelta;uniform lowp float iFrameRate;uniform lowp vec4 iDate;uniform float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform vec3 iChannelResolution[4];uniform highp vec3 iResolution;uniform highp vec4 iMouse;uniform lowp float iSampleRate;"
"out highp vec4 fragColor;\n";
GLchar fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);fragColor.a=1.0;}\0";
GLchar * common_shader_header=common_shader_header_gles3;
GLchar * vertex_shader_body=vertex_shader_body_gles3;
GLchar * fragment_shader_header=fragment_shader_header_gles3;
GLchar * fragment_shader_footer=fragment_shader_footer_gles3;

void uni(GLfloat,GLfloat,GLfloat,GLint,GLfloat);

GLuint compile_shader(GLenum,GLsizei,const GLchar **);

char32_t * read_file(const GLchar *);

void renderFrame();

EGLint attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_NONE,EGL_NONE
};

EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,(EGLint)3,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE,EGL_NONE
};

EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
// EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
// EGL_CONFIG_CAVEAT,EGL_NONE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
// EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_TRANSPARENT_TYPE,EGL_TRANSPARENT_RGB,
// EGL_TRANSPARENT_RED_VALUE,(EGLint)1000000000,
// EGL_TRANSPARENT_GREEN_VALUE,(EGLint)1000000000,
// EGL_TRANSPARENT_BLUE_VALUE,(EGLint)0,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_RED_SIZE,(EGLint)16,
EGL_GREEN_SIZE,(EGLint)16,
EGL_BLUE_SIZE,(EGLint)16,
EGL_ALPHA_SIZE,(EGLint)16,
EGL_DEPTH_SIZE,(EGLint)32,
EGL_STENCIL_SIZE,(EGLint)16,
EGL_BUFFER_SIZE,(EGLint)32,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_SAMPLES,(EGLint)4,
EGL_MIPMAP_LEVEL,(EGLint)0,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
EGL_NONE
};

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;
EM_BOOL ms_l,clk_l;

EM_BOOL mouse_call_click(int,const EmscriptenMouseEvent *,void *);

static EM_BOOL mouse_call_move(int,const EmscriptenMouseEvent *,void *);

void clrclr(GLfloat,GLfloat,GLfloat);

extern "C"{

void clr(GLfloat,GLfloat,GLfloat);

void str();

}
