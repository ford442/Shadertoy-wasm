#include <emscripten.h>
#include <emscripten/html5.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#define __gl2_h_
#include <GLES2/gl2ext.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point t1,t2,t3;
GLuint DBO,EBO,VBO,CBO,tex2d[4],shader_program,shader,frame,attrib_position,sampler_channel[4];
GLuint uniform_dtime,uniform_fps,uniform_date,VCO,ECO,CCO,vtx,frag,uniform_frame,uniform_time,uniform_res,uniform_mouse;
double Ttime,Dtime;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
GLsizei nsources,i;
GLsizei s4=4;
EGLint config_size,major,minor;
EGLConfig eglconfig=NULL;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EGLint v0=0,v1=1,v2=2,v3=3,v4=4,v6=6,v8=8,v32=32,a,b;
struct timespec rem;
struct timespec req={0,8500000};
GLfloat F=1.0f;
GLfloat F0=0.0f;
GLfloat Fm1=-1.0f;
GLfloat fps;
GLfloat x;
GLfloat y;
GLfloat mouseX;
GLfloat mouseY;
GLfloat mouseLPressed=0.0f;
static EMSCRIPTEN_RESULT ret;

typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vertices[]={{Fm1,Fm1,F,F},{F,Fm1,F,F},{F,F,F,F},{Fm1,F,F,F},{Fm1,Fm1,Fm1,F},{F,Fm1,Fm1,F},{F,F,Fm1,F},{Fm1,F,F,F}};
GLubyte Indices[]={3,0,1,1,2,3,4,0,3,3,7,4,1,5,6,6,2,1,4,7,6,6,5,4,2,6,6,7,3,0,4,1,1,4,5};
const char *fileloc="/shader/shader1.toy";
const char *sources[4];
char8_t *result=NULL;
long length=0;
// const GLenum attt[]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3};
const char common_shader_header_gles3[]=
"#version 300 es\n precision mediump float; \n";
// "precision highp sampler3D;"
// "precision highp sampler2D;"

const char vertex_shader_body_gles3[]=
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;} \n\0";
const char fragment_shader_header_gles3[]=
"uniform vec3 iResolution;uniform float iTime;uniform vec4 iMouse;uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;out vec4 fragColor;\n";
const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);} \n\0";
const char* common_shader_header=common_shader_header_gles3;
const char* vertex_shader_body=vertex_shader_body_gles3;
const char* fragment_shader_header=fragment_shader_header_gles3;
const char* fragment_shader_footer=fragment_shader_footer_gles3;
const char8_t *read_file(const char *filename){
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
GLuint compile_shader(GLenum type,GLsizei nsources,const char **sources){
GLsizei srclens[nsources];
for(i=0;i<nsources;++i){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}

static EM_BOOL mouse_callback(int eventType,const EmscriptenMouseEvent *e,void *userData){
// printf("%s,screen: (%ld,%ld),client: (%ld,%ld),%s%s%s%s button: %hu,buttons: %hu,movement: (%ld,%ld),target: (%ld,%ld)\n",emscripten_event_type_to_string(eventType),e->screenX,e->screenY,e->clientX,e->clientY,e->ctrlKey ? " CTRL" : "",e->shiftKey ? " SHIFT" : "",e->altKey ? " ALT" : "",e->metaKey ? " META" : "",e->button,e->buttons,e->movementX,e->movementY,e->targetX,e->targetY);
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
mouseLPressed=1.0f;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
mouseLPressed=0.0f;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return 0;
}
GLsizei S;
void renderFrame(){
eglSwapBuffers(display,surface);
t2=steady_clock::now();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
duration<double>time_spana=duration_cast<duration<double>>(t2-t1);
Ttime=time_spana.count();
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
mouseX=(float)x/S;
mouseY=(float)y/S;
if(mouseLPressed==1.0f){
// EM_ASM({console.log("S = "+$0);},S);
// EM_ASM({console.log("x = "+$0);},x);
EM_ASM({console.log("mouseX = "+$0);},mouseX);
const float cMouseX=mouseX;
const float cMouseY=mouseY;
EM_ASM({console.log("cMouseX = "+$0);},cMouseX);
glUniform4f(uniform_mouse,mouseX,mouseY,cMouseX,cMouseY);
}
glUniform1f(uniform_time,(float)Ttime);
glUniform1i(uniform_frame,frame);
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,Indices);
frame++;
}

void strt(){
S=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
eglBindAPI(EGL_OPENGL_ES_API);
// double client_w,client_h;
// emscripten_get_element_css_size("#canvas",&client_w,&client_h);
// S=(int)client_h;
const EGLint attribut_list[]={ 
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,8,
EGL_GREEN_SIZE,8,
EGL_BLUE_SIZE,8,
EGL_ALPHA_SIZE,8,
EGL_DEPTH_SIZE,24,
EGL_STENCIL_SIZE,8,
EGL_BUFFER_SIZE,32,
EGL_NONE
};
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_FALSE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_DEFAULT;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#canvas",&attr);
// emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&v3,&v0);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glGenBuffers(v1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices),Indices,GL_STATIC_DRAW);
glGenVertexArrays(v1,&VCO);
glBindVertexArray(VCO);
glGenBuffers(v1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
const char* default_fragment_shader=(char*)read_file(fileloc);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,v2,sources);
nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,v4,sources);
nanosleep(&req,&rem);
shader_program=glCreateProgram();
glAttachShader(shader_program,vtx);
glAttachShader(shader_program,frag);
glLinkProgram(shader_program);
nanosleep(&req,&rem);
glUseProgram(shader_program);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
attrib_position=glGetAttribLocation(shader_program,"iPosition");
glEnableVertexAttribArray(attrib_position);
glVertexAttribPointer(attrib_position,v4,GL_FLOAT,GL_TRUE,0,(void*)0);

/*
glGenBuffers(1,&CBO);
glBindBuffer(GL_ARRAY_BUFFER,CBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_DYNAMIC_READ);
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER,CBO);
glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(void*)0);

glGenTextures(v4,tex2d);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,tex2d[0]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glGenerateMipmap(GL_TEXTURE_2D);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D,tex2d[1]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glGenerateMipmap(GL_TEXTURE_2D);
glActiveTexture(GL_TEXTURE2);
glBindTexture(GL_TEXTURE_2D,tex2d[2]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glGenerateMipmap(GL_TEXTURE_2D);
glActiveTexture(GL_TEXTURE3);
glBindTexture(GL_TEXTURE_2D,tex2d[3]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glGenerateMipmap(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,v0);
glGenFramebuffers(v1,&FBO);
glBindFramebuffer(GL_FRAMEBUFFER,FBO);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,tex2d[0],v0);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,tex2d[1],v0);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT2,GL_TEXTURE_2D,tex2d[2],v0);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT3,GL_TEXTURE_2D,tex2d[3],v0);
glBindFramebuffer(GL_FRAMEBUFFER,v0);
*/
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_time=glGetUniformLocation(shader_program,"iTime");
// uniform_dtime=glGetUniformLocation(shader_program,"iTimeDelta");
// uniform_date=glGetUniformLocation(shader_program,"iDate");
uniform_frame=glGetUniformLocation(shader_program,"iFrame");
// uniform_fps=glGetUniformLocation(shader_program,"iFrameRate");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
uniform_mouse=glGetUniformLocation(shader_program,"iMouse");
glUniform3f(uniform_res,(float)S,(float)S,(float)S);
/*
glUniform1i(sampler_channel[0],v0);
glUniform1i(sampler_channel[1],v0);
glUniform1i(sampler_channel[2],v0);
glUniform1i(sampler_channel[3],v0);
*/
glEnable(GL_CULL_FACE);
glCullFace(GL_FRONT);
glEnable(GL_DITHER);
glEnable(GL_BLEND);
glEnable(GL_DEPTH_TEST);
// glDepthMask(GL_TRUE);
glDepthFunc(GL_LESS);
// glDepthMask(F);
// glClearDepthf(F);
// glDisable(GL_SCISSOR_TEST);
// glDisable(GL_STENCIL_TEST);
glClearColor(F0,F0,F0,F);
glViewport(0,0,S,S);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
t1=steady_clock::now();
emscripten_set_main_loop((void(*)())renderFrame,0,0);
}
extern "C" {
void str(){
strt();
}}
int main(){
EM_ASM({
FS.mkdir('/shader');
});
return 1;
}
