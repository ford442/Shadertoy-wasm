#include <string>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <emscripten/html5.h>
#include "SDL2/SDL_config.h"
#include <SDL2/SDL.h>

static const char common_shader_header_gles3[] =
"#version 300 es \n"
"precision highp float; \n";
static const char vertex_shader_body_gles3[] =
"layout(location=0) in vec4 iPosition;"
"void main(){"
"gl_Position=iPosition;"
"} \n";
static const char fragment_shader_header_gles3[] =
"uniform vec3 iResolution;"
"uniform float iTime;"
"uniform float iChannelTime[4];"
"uniform vec4 iMouse;"
"uniform vec4 iDate;"
"uniform vec3 iChannelResolution[4];"
"uniform sampler2D iChannel0;"
"uniform sampler2D iChannel1;"
"uniform sampler2D iChannel2;"
"uniform sampler2D iChannel3;"
"out vec4 fragColor; \n";
static const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor, gl_FragCoord.xy);} \n";
static const char default_fragment_shader[]=
"vec2 fluid(vec2 uv1){"
"vec2 uv=uv1;"
"float t=iTime;"
"for (float i=1.0;i<15.;i++)"
"{"
"uv.x -= (t+sin(t+uv.y*i/1.5))/i;"
"uv.y -= cos(uv.x*i/1.5)/i;"
"}"
"return uv;"
"}"
"void mainImage(out vec4 fragColor, in vec2 fragCoord)"
"{"
"vec2 uv=fragCoord/iResolution.xy*10.0;"
"uv=fluid(uv);"
"float r=abs(sin(uv.x))+0.5;"
"float g=abs(sin(uv.x+2.+iTime*0.2))-0.2;"
"float b=abs(sin(uv.x+4.0));"
"vec3 col=vec3(r,g,b);"
"fragColor=vec4(col, 1.0);"
"} \n";
static SDL_AudioDeviceID dev;
static EGLDisplay display;
static EGLContext contextegl;
static EGLSurface surface;
static EmscriptenWebGLContextAttributes attr;
static struct{SDL_AudioSpec spec;Uint8* snd;Uint32 slen;int pos;}wave;
SDL_Window *win;
SDL_GLContext *glCtx;
static const char* common_shader_header=common_shader_header_gles3;
static const char* vertex_shader_body=vertex_shader_body_gles3;
static const char* fragment_shader_header=fragment_shader_header_gles3;
static const char* fragment_shader_footer=fragment_shader_footer_gles3;
static GLuint shader_program;
static GLint attrib_position;
static GLint sampler_channel[4];
static GLint uniform_cres;
static GLint uniform_ctime;
static GLint uniform_date;
static GLint uniform_gtime;
static GLint uniform_time;
static GLint uniform_res;
static GLint uniform_srate;
static GLfloat viewportSizeX=0.0;
static GLfloat viewportSizeY=0.0;
static GLuint compile_shader(GLenum type,GLsizei nsources,const char **sources){
GLuint shader;
GLint success,len;
GLsizei i,srclens[nsources];
char *log;
for (i=0;i<nsources;++i){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}
static void renderFrame(){
float cllr=(SDL_GetTicks()*0.01)/5;
float cllb=(SDL_GetTicks()*0.001)/3;
float alph=1.0;
if (cllr>=0.95){
cllr=cllr/3;
alph=0.9;
}
if (cllb>=0.85){
cllb=cllb/2;
alph=0.7;
}
glClearColor(cllb,0.0f,cllr,alph);
glDrawArrays(GL_TRIANGLE_STRIP,0,4);
glClear(GL_COLOR_BUFFER_BIT);
eglSwapBuffers(display,surface);
}
static char* read_file_into_str(const char *filename) {
char *result=NULL;
long length=0;
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
result=static_cast<char*>(malloc((length+1)*sizeof(char)));
if(result){
size_t actual_length=fread(result,sizeof(char),length,file);
result[actual_length++]={'\0'};
} 
fclose(file);
return result;
}
return NULL;
}
static void strt(){
GLuint vtx,frag;
const char *sources[4];
const char *log;
GLint success,len;
int temp_val=0;
int h=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
int w=h;
const char* texture_files[4];
for (int i=0;i<4;++i) {
texture_files[i]=NULL;
}
const char* ssrc="/shader1.glsl";
int selected_option=-1;
int selected_index=0;
static const EGLint attribut_list[]={
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE
};
static const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_RED_SIZE,16,
EGL_GREEN_SIZE,16,
EGL_BLUE_SIZE,16,
EGL_ALPHA_SIZE,16,
EGL_NONE
};
SDL_GL_SetAttribute( SDL_GL_RED_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,16);
SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,1);
attr.alpha=1;
attr.stencil=0;
attr.depth=0;
attr.antialias=0;
attr.premultipliedAlpha=0;
attr.preserveDrawingBuffer=0;
emscripten_webgl_init_context_attributes(&attr);
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=emscripten_webgl_create_context("#canvas",&attr);
EGLConfig eglconfig=NULL;
EGLint config_size,major,minor;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
if(eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size)==EGL_TRUE && eglconfig!=NULL){
if(eglBindAPI(EGL_OPENGL_ES_API)!=EGL_TRUE){
}
EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_NONE};
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
if(contextegl==EGL_NO_CONTEXT){
}
else{
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
}}
emscripten_webgl_make_context_current(ctx);
int width=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
int height=width;
win=SDL_CreateWindow("pm",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_OPENGL);
glCtx=&contextegl;
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,2,sources);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,4,sources);
shader_program=glCreateProgram();
glAttachShader(shader_program,vtx);
glAttachShader(shader_program,frag);
glLinkProgram(shader_program);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glUseProgram(shader_program);
glValidateProgram(shader_program);
attrib_position=glGetAttribLocation(shader_program,"iPosition");
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_cres=glGetUniformLocation(shader_program,"iChannelResolution");
uniform_ctime=glGetUniformLocation(shader_program,"iChannelTime");
uniform_date=glGetUniformLocation(shader_program,"iDate");
uniform_gtime=glGetUniformLocation(shader_program,"iGlobalTime");
uniform_time=glGetUniformLocation(shader_program,"iTime");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
SDL_SetWindowTitle(win,"1ink.us - Shadertoy");
SDL_Log("GL_VERSION: %s",glGetString(GL_VERSION));
SDL_Log("GLSL_VERSION: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));
GLuint vbo;
glGenBuffers(1,&vbo);
static const GLfloat vertices[]={-1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f};
glBindBuffer(GL_ARRAY_BUFFER,vbo);
glBufferData(GL_ARRAY_BUFFER,sizeof(void*),vertices,GL_STATIC_DRAW);
GLuint vao;
glGenVertexArrays(1,&vao);
glBindVertexArray(vao);
glEnableVertexAttribArray(attrib_position);
glVertexAttribPointer(attrib_position,2,GL_FLOAT,GL_FALSE,0,vertices);
glUniform3f(uniform_res,(float)w,(float)h,0.0f);
glViewport(0,0,w,h);
viewportSizeX=w;
viewportSizeY=h;
glClearColor(0.0f,0.8f,0.0f,1.0);
glClear(GL_COLOR_BUFFER_BIT);
SDL_Init(SDL_INIT_TIMER);
float abstime=SDL_GetTicks()/1000.0;
emscripten_set_main_loop((void (*)())renderFrame,0,0);
}
static void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
}}
static void qu(int rc){
SDL_Quit();
exit(rc);
}
static void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
qu(2);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
}
static void SDLCALL bfr(void *unused,Uint8* stm,int len){
Uint8* wptr;
int lft;
wptr=wave.snd+wave.pos;
lft=wave.slen-wave.pos;
while (lft<=len){
SDL_memcpy(stm,wptr,lft);
stm+=lft;
len-=lft;
wptr=wave.snd;
lft=wave.slen;
wave.pos=0;
}
SDL_memcpy(stm,wptr,len);
wave.pos+=len;
}
static void plt(){
char flnm[1024];
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu(1);
SDL_Log("SDL failed to init.");
}
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){
qu(1);
}
wave.pos=0;
wave.spec.callback=bfr;
opn_aud();
}
extern "C" {
void pl(){
plt();
}
void str(){
strt();
}}
int main(){
return 1;
}
