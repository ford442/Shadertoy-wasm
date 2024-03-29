#include "../../include/vanilla/cropcircle.hpp"

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

boost::function<void(int,int,int,float *,float *)>rotateFrame=[](int angle,int wid,int hig,float *Fptr,float *NFptr){
for(int y=0;y<hig;y++){
for(int x=0;x<wid;x++){
int index=4*(y*hig+x);
unsigned char red=Fptr[index];
unsigned char green=Fptr[index+1];
unsigned char blue=Fptr[index+2];
int newX=x*cos(angle)-y*sin(angle);
int newY=x*sin(angle)+y*cos(angle);
if (newX>=0&&newX<hig&&newY>=0&&newY<wid){
int newIndex=4*(newY*wid+newX);
NFptr[newIndex]=red;
NFptr[newIndex+1]=green;
NFptr[newIndex+2]=blue;
NFptr[newIndex+3]=255;
}
}
}
return;
};

extern "C" {

void nano(int leng,float *ptr,float *aptr){
avgFrm(leng,ptr,aptr);
}

void rotat(int angle,int wd,int hi,float *Fptr,float *NFptr){
rotateFrame(angle,wd,hi,Fptr,NFptr);
}

void emsc(){

EGLConfig eglconfig=NULL;
EGLDisplay display;
EGLContext contextegl;
EGLSurface surface;
EGLint config_size,major,minor;

const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
//   EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE,EGL_NONE
};

static const EGLint attribut_list[]={
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
EGL_NONE,EGL_NONE
};

static const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_BUFFER_SIZE,32,
EGL_NONE,EGL_NONE
};

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
emscripten_get_element_css_size("zimag",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
eglBindAPI(0);
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_FALSE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
ctx=emscripten_webgl_create_context("#zimag",&attr);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
 /*
emscripten_webgl_enable_extension(ctx,"GL_ALL_EXTENSIONS");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"GL_ALL_EXTENSIONS");
emscripten_webgl_enable_extension(ctx,"GL_KHR_no_error");
emscripten_webgl_enable_extension(ctx,"GL_REGAL_enable");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_platform_angle");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_ARB_direct_state_access");
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glDisable(GL_DITHER);
*/
// glViewport(0,0,GLint(Size),GLint(Size));
}

}

EM_JS(void,ma,(),{
"use strict";
let winSize=parseInt(window.innerHeight,10);
const scanvas=document.createElement('canvas');
scanvas.id='zimag';
scanvas.imageRendering='auto';
scanvas.width=winSize;
scanvas.height=winSize;
scanvas.zoom=1;
scanvas.scale=1.0;
scanvas.style.pointerEvents='none';
scanvas.style.display='block';
scanvas.style.position='absolute';
scanvas.style.zIndex='999995';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(0,0,0,0.0)';
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
const contxVars={
// colorType:'float32',
// precision:'highp',
preferLowPowerToHighPerformance:false,
alpha:true,
depth:false,
stencil:false,
// preserveDrawingBuffer:false,
premultipliedAlpha:false,
// imageSmoothingEnabled:false,
willReadFrequently:true,
lowLatency:true,
powerPreference:'high-performance',
antialias:false
};
const ctx=scanvas.getContext('2d',contxVars);

// const ctxB=zcanvas.getContext('2d',contxVars);
const gpu=new GPUX({mode:'gpu',canvas:scanvas,webGl:ctx });

// const gpuB=new GPUX({mode:'gpu',canvas:zcanvas,webGl:ctxB });
let dis=set();
if(dis){dis();}
dis=set();
var $,$r,z,w,R,h,ww,o,l,r,m,rotm,rotmb,rottm,kna,knab,knb,knbb,knc,kncb,knd,kndb,rott,rottb,rottc;
function set(){
ww=document.getElementById("iwid").innerHTML;
h=document.getElementById("ihig").innerHTML;
ow=document.getElementById("wid").innerHTML;
oh=document.getElementById("hig").innerHTML;
let cnP=document.getElementById("cp");
// let cnPB=document.getElementById("cpB");
let flP=document.getElementById("flip");
let vd=document.getElementById("myvideo");
ctx.drawImage(vd,0,0,ww,h);
var imgData=ctx.getImageData(0,0,ww,h);
var rgbdat=ctx.createImageData(ww,h);
var rgbd=rgbdat.data;
var imgg=imgData.data;
var i;
let l=h*ww;
let la=h*ww*4;
var pointa=la*2.0;
var pointb=la*3.0;
var pointc=la*4.0;
let $H=Module.HEAPF32.buffer;
var agavF=new Float32Array($H,pointa,la);
var agavNF=new Float32Array($H,pointb,la);
agavF.set(imgData.data);
Module.ccall("nano",null,["Number","Number","Number"],[la,pointa,pointc]);
/* ctx.getExtension('GL_ALL_EXTENSIONS');
ctx.getExtension('GL_KHR_no_error');
ctx.getExtension('GL_REGAL_enable');
ctx.getExtension('GL_ARB_spirv_extensions');
ctx.getExtension('GL_ARB_ES2_compatibility');
ctx.getExtension('GL_ARB_direct_state_access');
 */
var agav=new Float32Array($H,pointc,1);
console.log(agav[0]);
for(i=0;i<(ww*h*4);i=i+4){
var rgb=(imgg[i]*0.2126)+(imgg[i+1]*0.7152)+(imgg[i+2]*0.0722);
var lightDark=128+((Math.abs(agav[0]-128))/2);
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
var diff=(agav[0]/255)*16;
if(rgb>126){
if(rgb>209){    // orange
rgbd[i]=255;
rgbd[i+1]=128+diff;
rgbd[i+2]=0;
rgbd[i+3]=255-((rgb-209)*diff);
}
else if(rgb>193){   // red
rgbd[i]=255-diff;
rgbd[i+1]=0;
rgbd[i+2]=0;
rgbd[i+3]=255-((rgb-193)*diff);
}else if(rgb>177){   // light blue
rgbd[i]=0;
rgbd[i+1]=255-diff;
rgbd[i+2]=255;
rgbd[i+3]=255-((rgb-177)*diff);
}else if(rgb>161){  //  blue
rgbd[i]=0;
rgbd[i+1]=0;
rgbd[i+2]=255-diff;
rgbd[i+3]=255-((rgb-161)*diff);
}else if(rgb>145){  // green
rgbd[i]=0;
rgbd[i+1]=255-diff;
rgbd[i+2]=0;
rgbd[i+3]=255-((rgb-145)*diff);
}else if(rgb>128){  // yellow
rgbd[i]=255;
rgbd[i+1]=255-diff;
rgbd[i+2]=0;
rgbd[i+3]=255-((rgb-128)*diff);
}
}else{
rgbd[i]=0+diff;
rgbd[i+1]=0+diff;
rgbd[i+2]=0+diff;
rgbd[i+3]=255-((rgb-128)*diff);
}
}
// agavF.set(rgbdat.data);
var ang=45;
// Module.ccall("rotat",null,["Number","Number","Number","Number","Number"],[ang,ww,h,pointa,pointb]);
ctx.putImageData(rgbdat,0,0);
function Ra(){
flP.setAttribute("style","transform:scaleX(1.0)");
cnP.setAttribute("style","transform:scaleY(1.0)");
// cnPB.setAttribute("style","transform:scaleY(-1);");
}
function Rb(){
flP.setAttribute("style","transform: scaleX(-1.0)");
cnP.setAttribute("style","transform: scaleY(-1.0)");
// cnPB.setAttribute("style","transform: scaleY(1);");
}
function rrra(rta){
cnP.setAttribute("style","transform: rotate("+rta+"deg)");
// cnPB.setAttribute("style","transform:rotate("+rta+"deg);");
}
function rrrb(rtb){
cnP.setAttribute("style","transform:rotate("+rtb+"deg)");
// cnPB.setAttribute("style","transform:rotate("+rtb+"deg);");
}
function rrrc(rtc) {
cnP.setAttribute("style","transform:rotate("+rtc+"deg)");
// cnPB.setAttribute("style","transform: rotate("+rtc+"deg);");
}
knb=document.getElementById("rra");
kna=document.getElementById("mainr");
knc=document.getElementById("rrb");
knd=document.getElementById("rrc");
knbb=document.getElementById("rrab");
kncb=document.getElementById("rrbb");
kndb=document.getElementById("rrcb");
rate=(kna.innerHTML);
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
},rate);
setTimeout(function(){
Rb();
},rate);
setTimeout(function(){
if((rottc+knb.innerHTML)>360){
rottc=((rottc+knb.innerHTML)-360);
}else{
rottc=(rottc+knb.innerHTML);
}
rrrc(rottc);
},rate);// 
setTimeout(function(){
$rn();
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

ma();
emsc();
 
return 1;
}
