#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#define __gl2_h_
#include <GLES2/gl2ext.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <iostream>
#include <ctime>
using namespace std;
using namespace std::chrono;
high_resolution_clock::time_point t1,t2,t3;
GLuint EBO,VBO,CBO,tex2d[4],shader_program,shader,frame,attrib_position,sampler_channel[4];
GLuint uniform_dtime,uniform_fps,uniform_date,VCO,ECO,CCO,vtx,frag,uniform_frame,uniform_time,uniform_res,uniform_mouse;
long double Ttime,Dtime;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
GLsizei nsources,i,S;
GLsizei s4=4;
EGLint config_size,major,minor;
EGLConfig eglconfig=NULL;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EGLint v0=0,v1=1,v2=2,v3=3,v4=4,v6=6,v8=8,v32=32,a,b;
struct timespec rem;
struct timespec req={0,25000000};
GLfloat F=1.0f;
GLfloat F0=0.0f;
GLfloat Fm1=-1.0f;
GLfloat F2=2.0f;
GLfloat Fm2=-2.0f;
GLfloat fps,FS;
typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vertices[]={{Fm1,Fm1,Fm1,F},{F,Fm1,Fm1,F},{F,F,Fm1,F},{Fm1,F,Fm1,F}};
GLubyte Indices[]={0,1,3,3,2,1};
char *fileloc="/shader/shader1.toy";
const char *sources[4];
char8_t *result=NULL;
long length=0;
const char common_shader_header_gles3[]=
"#version 300 es \n precision highp float;\n";
const char vertex_shader_body_gles3[]=
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;} \n";
const char fragment_shader_header_gles3[]=
"uniform vec3 iResolution;uniform float iTime;uniform vec4 iMouse;uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;out vec4 fragColor;\n";
const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);} \n";
const char* common_shader_header=common_shader_header_gles3;
const char* vertex_shader_body=vertex_shader_body_gles3;
const char* fragment_shader_header=fragment_shader_header_gles3;
const char* fragment_shader_footer=fragment_shader_footer_gles3;
static const char8_t *read_file(const char *filename){
FILE *file=fopen(filename,"r");
if(file){
int status=fseek(file,0,SEEK_END);
if(status!=0){
fclose(file);
return NULL;
}
length=ftell(file);
status=fseek(file,0,SEEK_SET);
if(status!=0){
fclose(file);
return NULL;
}
result=static_cast<char8_t*>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
} 
fclose(file);
return result;
}
return NULL;
}
static GLuint compile_shader(GLenum type,GLsizei nsources,const char **sources){
GLsizei srclens[nsources];
for(i=0;i<nsources;++i){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}
static void renderFrame(){
t2=high_resolution_clock::now();
glClear(GL_COLOR_BUFFER_BIT);
duration<long double>time_spana=duration_cast<duration<long double>>(t2-t1);
Ttime=time_spana.count();
glUniform1f(uniform_time,Ttime);
glUniform1i(uniform_frame,frame);
glDrawElements(GL_TRIANGLES,v6,GL_UNSIGNED_BYTE,Indices);
eglSwapBuffers(display,surface);
frame++;
}
static void strt(){
S=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
FS=(float)S;
const EGLint attribut_list[]={EGL_NONE};
EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,v3,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_NONE};
const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,v32,
EGL_GREEN_SIZE,v32,
EGL_BLUE_SIZE,v32,
EGL_ALPHA_SIZE,v32,
EGL_DEPTH_SIZE,v32,
EGL_STENCIL_SIZE,v32,
EGL_BUFFER_SIZE,v32,
EGL_NONE
};
// emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_FALSE;
attr.depth=EM_FALSE;
attr.antialias=EM_FALSE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=v2;
attr.minorVersion=v0;
ctx=emscripten_webgl_create_context("#canvas",&attr);
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&v3,&v0);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
eglBindAPI(EGL_OPENGL_ES_API);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
const char* default_fragment_shader=(char*)read_file(fileloc);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,v2,sources);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,v4,sources);
shader_program=glCreateProgram();
glAttachShader(shader_program,vtx);
glAttachShader(shader_program,frag);
glLinkProgram(shader_program);
glUseProgram(shader_program);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
attrib_position=glGetAttribLocation(shader_program,"iPosition");
glGenBuffers(v1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices),Indices,GL_STATIC_READ);
glGenVertexArrays(v1,&VCO);
glBindVertexArray(VCO);
glGenBuffers(v1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_COPY);
glVertexAttribPointer(attrib_position,v4,GL_FLOAT,GL_FALSE,0,0);
glEnableVertexAttribArray(attrib_position);
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_time=glGetUniformLocation(shader_program,"iTime");
uniform_frame=glGetUniformLocation(shader_program,"iFrame");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
uniform_mouse=glGetUniformLocation(shader_program,"iMouse");
glUniform3f(uniform_res,FS,FS,FS);
glViewport(0,0,S,S);
glDisable(GL_DITHER);
glClearColor(F0,F0,F0,F);
glClear(GL_COLOR_BUFFER_BIT);
t1=high_resolution_clock::now();
emscripten_set_main_loop((void(*)())renderFrame,0,0);
}
extern "C" {
void str(){
strt();
}}
int main(){
EM_ASM({
FS.mkdir("/shader");
});
return 1;
}
