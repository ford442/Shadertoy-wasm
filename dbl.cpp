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
#include <unistd.h>
#include <chrono>
#include <SDL2/SDL.h>

using namespace std;
using namespace std::chrono;

//  SDL
static SDL_AudioDeviceID dev;
struct{SDL_AudioSpec spec;Uint8* snd;Uint32 slen;int pos;}wave;
struct{SDL_AudioSpec spec2;Uint8* snd2;Uint32 slen2;int pos2;}wave2;

high_resolution_clock::time_point t1,t2,t3;
static GLuint DBO,EBO,VBO,CBO,shader_program,shader,frame,sampler_channel[4],sampler_channel_res,TEX;
static GLuint uniform_dtime,uniform_fps,uniform_date,VCO,ECO,CCO,vtx,frag,uniform_frame,uniform_time,uniform_res,uniform_mouse;
static long double Ttime,Dtime;
static EGLint iFrame;
static GLsizei s4=4;
static EGLint v0=0,v1=1,v2=2,v3=3,v4=4,v6=6,v8=8,v24,v32=32,a,b;
static GLfloat F=1.0f;
static GLfloat F0=0.0f;
static GLfloat Fm1=-1.0f;
static GLfloat mouseX;
static GLfloat mouseY;
static GLfloat cMouseX;
static GLfloat cMouseY;
static GLfloat x;
static GLfloat y;
static EM_BOOL mouseLPressed;
static int S;
static GLfloat Size;
static EM_BOOL clickLoc;
static GLfloat mX,mY;

static EGLDisplay display;
static EGLSurface surface;
static EGLContext contextegl;
static GLsizei i;
static GLfloat fps;
static GLfloat timeSpeed;
static EGLint config_size,major,minor,attrib_position;
EGLConfig eglconfig=NULL;
static EmscriptenWebGLContextAttributes attr;
static EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
static struct timespec rem;
static struct timespec req={0,8330000};
static EMSCRIPTEN_RESULT ret;
typedef struct{GLfloat XYZW[4];}Vertex;
static Vertex vertices[]={{Fm1,Fm1,F,F},{F,Fm1,F,F},{F,F,F,F},{Fm1,F,F,F},{Fm1,Fm1,Fm1,F},{F,Fm1,Fm1,F},{F,F,Fm1,F},{Fm1,F,F,F}};
static GLubyte Indices[]={3,0,1,1,2,3,4,0,3,3,7,4,1,5,6,6,2,1,4,7,6,6,5,4,2,6,6,7,3,0,4,1,1,4,5};
static const char *fileloc="/shader/shader1.toy";
const char *sources[4];
char8_t *result=NULL;
long length=0;
static const char common_shader_header_gles3[]=
"#version 300 es \n precision highp float;precision highp int;precision lowp sampler3D;precision highp sampler2D;";
static const char vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";
static const char fragment_shader_header_gles3[]=
"\n uniform vec3 iChannelResolution;uniform vec3 iResolution;uniform float iTime;uniform vec4 iMouse;"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"out vec4 fragColor;\n";
static const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);}\n\0";
static const char* common_shader_header=common_shader_header_gles3;
static const char* vertex_shader_body=vertex_shader_body_gles3;
static const char* fragment_shader_header=fragment_shader_header_gles3;
static const char* fragment_shader_footer=fragment_shader_footer_gles3;

static const char8_t *read_file(const char *filename){
FILE *file=fopen(filename,"r");
if(file){
int status=fseek(file,0,SEEK_END);
if(status!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
status=fseek(file,0,SEEK_SET);
if(status!=0){
fclose(file);
return nullptr;
}
result=static_cast<char8_t*>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
} 
fclose(file);
return result;
}
return nullptr;
}
static GLuint compile_shader(GLenum type,GLsizei nsources,const char **dsources){
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
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
mouseLPressed=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
mouseLPressed=false;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return 0;
}

static void uniforms(GLfloat xx,GLfloat yy,GLfloat time,EGLint fram){
if(mouseLPressed==true){
if(clickLoc==true){
const GLfloat xxx=xx;
const GLfloat yyy=yy;
mX=xxx*Size;
mY=yyy*Size;
clickLoc=false;
}
glUniform4f(uniform_mouse,(Size*xx),(Size*yy),mX,mY);
}else{
clickLoc=true;
}
glUniform1f(uniform_time,time);
glUniform1i(uniform_frame,fram);
}

static void renderFrame(){
eglSwapBuffers(display,surface);
t2=high_resolution_clock::now();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
duration<double>time_spana=duration_cast<duration<double>>(t2-t1);
Ttime=time_spana.count();
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
mouseX=x/Size;
mouseY=(Size-y)/Size;
uniforms(mouseX,mouseY,Ttime,iFrame);
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,Indices);
iFrame++;
glFlush();
nanosleep(&req,&rem);
glFinish();
}

static void avgFrm(int F,int leng,float *dat,float *aLoc){
static float max=0.0;
static float min=1.0;
static float sum=0.0;
static float avgSum=0.0;
static float minSum=0.0;
static float maxSum=0.0;
for (int i=0;i<leng;i++){
sum+=dat[i];
if(max<dat[i]){max=dat[i];}
if(min>dat[i]&&dat[i]>0){min=dat[i];}
}
sum=sum/leng;
aLoc[F]=sum;
aLoc[F+100]=min;
aLoc[F+200]=max;
for(int i=33;i<65;i++){
avgSum+=aLoc[i];
}
aLoc[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aLoc[i+100];
}
aLoc[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aLoc[i+200];
}
aLoc[200]=maxSum/32;
}

static void strt(){
iFrame=0;
clickLoc=true;
S=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
Size=(float)S;
eglBindAPI(EGL_OPENGL_ES_API);
const EGLint attribut_list[]={ 
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,v3,
EGL_CONTEXT_MINOR_VERSION_KHR,v0,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,v8,
EGL_GREEN_SIZE,v8,
EGL_BLUE_SIZE,v8,
EGL_ALPHA_SIZE,v8,
EGL_DEPTH_SIZE,v24,
EGL_STENCIL_SIZE,v8,
EGL_BUFFER_SIZE,v32,
EGL_NONE
};
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
attr.majorVersion=v2;
attr.minorVersion=v0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
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
static const char* default_fragment_shader=(char*)read_file(fileloc);
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
attrib_position=v0;
glBindAttribLocation(shader_program,v0,"iPosition");
glUseProgram(shader_program);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
attrib_position=glGetAttribLocation(shader_program,"iPosition");
glEnableVertexAttribArray(attrib_position);
glVertexAttribPointer(attrib_position,v4,GL_FLOAT,GL_TRUE,0,(GLvoid*)0);
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel_res=glGetUniformLocation(shader_program,"iChannelResolution");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_time=glGetUniformLocation(shader_program,"iTime");
uniform_frame=glGetUniformLocation(shader_program,"iFrame");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
uniform_mouse=glGetUniformLocation(shader_program,"iMouse");
glUniform3f(uniform_res,Size,Size,1.0);
glUniform3f(sampler_channel_res,Size,Size,1.0);
glClearColor(F0,F0,F0,F0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glEnable(GL_BLEND);
glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
t1=high_resolution_clock::now();
emscripten_set_main_loop((void(*)())renderFrame,0,0);
}
void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
}}
void qu(int rc){
SDL_Quit();
exit(rc);
}
void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
SDL_FreeWAV(wave2.snd2);
qu(2);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
}
static Uint8* wptr;
static Uint8* wptr2;
static int lft;
static int lft2;
void SDLCALL bfr(void *unused,Uint8* stm,int len){
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
void SDLCALL bfr2(void *unused2,Uint8* stm2,int len2){
wptr2=wave2.snd2+wave2.pos2;
lft2=wave2.slen2-wave2.pos2;
while (lft2<=len2){
SDL_memcpy(stm2,wptr2,lft2);
stm2+=lft2;
len2-=lft2;
wptr2=wave2.snd2;
lft2=wave2.slen2;
wave2.pos2=0;
}
SDL_memcpy(stm2,wptr2,len2);
wave2.pos2+=len2;
}
void plt(){
cls_aud();
static char flnm[24];
static char flnm2[24];
SDL_FreeWAV(wave.snd);
SDL_FreeWAV(wave2.snd2);
SDL_Quit();
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu(1);
}
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_strlcpy(flnm2,"/snd/sample2.wav",sizeof(flnm2));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){
qu(1);
}
if(SDL_LoadWAV(flnm2,&wave2.spec2,&wave2.snd2,&wave2.slen2)==NULL){qu(1);}
wave.pos=0;
wave2.pos2=0;
wave.spec.callback=bfr;
wave2.spec2.callback=bfr2;
opn_aud();
}

EM_JS(void,ma,(),{
var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
vv=document.getElementById("mv");
let $H=Module.HEAPF32.buffer;
var la=h$*h$*4;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);
var sz=(h$*h$)/8;
var avag=0.750;
var min=1.0;
var max=0.0;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var bcanvas=document.getElementById("bcanvas");
var contx=bcanvas.getContext('webgl2',{antialias:false,alpha:true,imageSmoothingEnabled:true,stencil:false,depth:false,preserveDrawingBuffer:false,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',majorVersion:2,minorVersion:0,desynchronized:false});
var g=new GPU({canvas:bcanvas,webGl:contx});
var g2=new GPU();
const glslAve=`float Ave(float a,float b,float c) {return (a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g) {return (1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25)));}`;
const glslAveg=`float Aveg(float a,float b) {return (1.0-(((a)-(b))*((a)*(1.0/(1.0-b))))) ;}`;

g.addNativeFunction('Ave', glslAve, { returnType: 'Number' });
g.addNativeFunction('Alphe', glslAlphe, { returnType: 'Number' });
g.addNativeFunction('Aveg', glslAveg, { returnType: 'Number' });
g2.addNativeFunction('Aveg', glslAveg, { returnType: 'Number' });
g2.addNativeFunction('Ave', glslAve, { returnType: 'Number' });

var R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setArgumentTypes(['HTMLVideo']).setFixIntegerDivisionAccuracy(false).setOutput([sz]);

var t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPipeline(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setFixIntegerDivisionAccuracy(false).setOutput([w$,h$]);

var r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$fmax,$fmin,$favg,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));

// var Min=(4.0*(($amax-$aavg)/2.0))+(($fmin+$amin)/2.0);
// var Min=(4.0*(($amax-$amin-$aavg)/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setGraphical(true).setDynamicOutput(true).setFixIntegerDivisionAccuracy(false).setOutput([w$,h$]);

var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
var vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
var l=w$*h$*16;
var la=h$*h$*4;
var al=w$*h$*8;
var sz=(h$*h$)/8;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);

R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
var pointb=77*la;
var $B=new Float32Array($H,pointb,sz);
let $F=1;
let $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});

var $$1=t(vv);
for (i=0;i<65;i++){
var j=i+1;
eval("$"+j+".set($$1);");
}

let d=S();if(d)d();d=S();function S(){
var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
var l=w$*h$*16;
var la=h$*h$*4;
var al=w$*h$*8;
var sz=(h$*h$)/8;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);

for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
var pointb=66*la;
var $B=new Float32Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;

function M(){
var vv=document.getElementById("mv");
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){return;}
for(i=64;i>0;i--){
var loca=$F+1;if(loca>64){loca=1;}
var locb=$Bu+1;if(locb>64){locb=1;}
eval("if ($F=="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+");$F="+loca+";$Bu="+locb+";}");
}
var $bb=R(vv);
$B.set($bb,0,sz);
setTimeout(function(){
var pointb=66*la;
Module.ccall('nano',null,['Number'],['Number'],['Number'],['Number'],[$F],[sz],[pointb],[pointa]);
M();
},16.6);
}
M();
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
}
})

extern "C" {

void str(){
strt();
}

void pl(){
plt();
}

void b3(){
ma();
}

void nano(int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
}

}

int main(){
EM_ASM({
FS.mkdir('/snd');
FS.mkdir('/shader');
});
return 1;
}
