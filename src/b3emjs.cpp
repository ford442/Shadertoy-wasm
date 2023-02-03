#include "../include/b3emjs.hpp"

void egl(){
emscripten_webgl_init_context_attributes(&attr_js);
attr_js.alpha=EM_TRUE;
attr_js.stencil=EM_TRUE;
attr_js.depth=EM_TRUE;
attr_js.antialias=EM_TRUE;
attr_js.premultipliedAlpha=EM_FALSE;
attr_js.preserveDrawingBuffer=EM_TRUE;
attr_js.enableExtensionsByDefault=EM_TRUE;
attr_js.renderViaOffscreenBackBuffer=EM_FALSE;
attr_js.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_js.failIfMajorPerformanceCaveat=EM_FALSE;
attr_js.majorVersion=2;
attr_js.minorVersion=0;
ctx_js=emscripten_webgl_create_context("#bcanvas",&attr_js);
eglBindAPI(EGL_OPENGL_API);
display_js=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_js,&major_js,&minor_js);
eglChooseConfig(display_js,attribute_list_js,&eglconfig_js,(EGLint)1,&config_size_js);
contextegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,anEglCtxAttribs2_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,attribut_list_js);
eglMakeCurrent(display_js,surface_js,surface_js,contextegl_js);
emscripten_webgl_make_context_current(ctx_js);
emscripten_get_element_css_size("canvas",&wi_js,&hi_js);
Size_js=(int)hi_js;
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx_js,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx_js,"OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx_js,"OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx_js,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx_js,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx_js,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx_js,"OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx_js,"OES_fixed_point");
emscripten_webgl_enable_extension(ctx_js,"OES_shader_multisample_interpolation");
// emscripten_webgl_enable_extension(ctx_js,"OES_single_precision");
// emscripten_webgl_enable_extension(ctx_js,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx_js,"OES_float_blend");
emscripten_webgl_enable_extension(ctx_js,"OES_frag_depth");
emscripten_webgl_enable_extension(ctx_js,"OES_shader_texture_lod");
emscripten_webgl_enable_extension(ctx_js,"OES_sRGB");
emscripten_webgl_enable_extension(ctx_js,"OES_depth32");
// emscripten_webgl_enable_extension(ctx_js,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx_js,"GL_disjoint_timer_query");
emscripten_webgl_enable_extension(ctx_js,"EXT_clip_cull_distance");
// emscripten_webgl_enable_extension(ctx_js,"ARB_shading_language_420pack");
// emscripten_webgl_enable_extension(ctx_js,"GL_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx_js,"EXT_framebuffer_sRGB");
emscripten_webgl_enable_extension(ctx_js,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx_js,"KHR_parallel_shader_compile");
emscripten_webgl_enable_extension(ctx_js,"EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_memory_attachment");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx_js,"KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(ctx_js,"ARB_multisample");
emscripten_webgl_enable_extension(ctx_js,"ARB_robustness");
emscripten_webgl_enable_extension(ctx_js,"ARB_robust_buffer_access_behavior");
emscripten_webgl_enable_extension(ctx_js,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx_js,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx_js,"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx_js,"ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_2_compatibility");
// emscripten_webgl_enable_extension(ctx_js,"EXT_gpu_shader5");
// emscripten_webgl_enable_extension(ctx_js,"OES_gpu_shader5");
glDisable(GL_DITHER);
glEnable(GL_SCISSOR_TEST);
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_DEPTH_TEST);
glViewport((GLint)0,(GLint)0,(GLsizei)Size_js,(GLsizei)Size_js);
glScissor((GLint)0,(GLint)0,(GLsizei)Size_js,(GLsizei)Size_js);
return;
}

void avgFrm(short int Fnum,int leng,float * ptr,float * aptr){
float max=0.0;
float min=1.0;
float sum=0.0;
float avgSum=0.0;
float minSum=0.0;
float maxSum=0.0;
for (int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];};
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];};
}
sum=sum/leng;
aptr[Fnum]=sum;
aptr[Fnum+100]=min;
aptr[Fnum+200]=max;
for(int i=33;i<65;i++){
avgSum+=aptr[i];
}
aptr[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aptr[i+100];
}
aptr[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aptr[i+200];
}
aptr[200]=maxSum/32;
return;
}

extern "C" {

void nano(short int Fnum,int leng,float * ptr,float * aptr){
avgFrm(Fnum,leng,ptr,aptr);
return;
}
 
}

EM_JS(void,ma,(),{

"use strict";

var lvv=document.getElementById("ldv");
var vv=document.getElementById("mv");
let $S=parseInt(window.innerHeight,10);
var w$=parseInt(document.getElementById("wid").innerHTML,10);
var h$=parseInt(document.getElementById("hig").innerHTML,10);
var sh4d=true;
var stp,Lstp;
const stpInc=0.016;
var setTim;
const timFrm=16.666;
var loopLoop;
var loopPart;
var mmvv;
var revv;
var $bb;

function forwardLoop(){
// setTim=mmvv.currentTime;
setTim+=stpInc;
if(setTim<stp){
mmvv.currentTime=setTim;
}else{
revv=true;
};
}
 
function reverseLoop(){
// setTim=mmvv.currentTime;
setTim-=stpInc;
if(setTim>=Lstp){
mmvv.currentTime=setTim;
}else{
revv=false;
};
}
  
function doKey(e){
if(e.code=='Space'){
e.preventDefault();
};
if (e.code=='KeyZ'){
mmvv=document.getElementById("mv");
mmvv.pause();
stp=document.getElementById("mv").currentTime;
loopPart=(stp+2.5)-(Math.floor(stp));
Lstp=stp-loopPart;
stp-=loopPart/2.0;
setTim=stp;
loopLoop=true;
revv=true;
};
if(e.code=='KeyX'){
loopLoop=false;
vv.play();
};
if(e.code=='KeyA'){
sh4d=true;
};
if(e.code=='KeyS'){
sh4d=false;
};
}
const pnnl=document.body;
pnnl.addEventListener('keydown',doKey);
const $H=Module.HEAPF64.buffer;
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var la=h$*h$*4;
var pointa=77*la;
var pointb=66*la;
var $B=new Float64Array($H,pointb,sz);
var agav=new Float64Array($H,pointa,300);
var sz=(h$*w$)/8;
var avag=0.750000;
var min=1.000000;
var max=0.000000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
  
vv=document.getElementById("mv");
var blank$=Math.max(((w$-h$)/2.0),0);
var nblank$=Math.max(((h$-w$)/2.0),0);
la=h$*h$*4;
sz=(h$*w$)/8;
pointa=77*la;
const bCan=document.getElementById("bcanvas");
const gl_js=bCan.getContext("webgl2",{
colorType:'float64',
preferLowPowerToHighPerformance:false,
precision:'highp',
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
imageSmoothingEnabled:false,
imageSmoothingQuality:'medium',
preserveDrawingBuffer:true,
premultipliedAlpha:false,
desynchronized:false,
lowLatency:true,
powerPreference:'high-performance',
antialias:true,
willReadFrequently:false,
xrCompatible:false,
majorVersion:2,
minorVersion:0
});

const g=new GPU({mode:'webgl2',canvas:bCan,webGl:gl_js});
const g2=new GPU({mode:'webgl2'});  //  A / B    'webgl2' / 'gpu' / 'cpu'
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))+((f-g)*((1.0-g)*(f-g)))-((f-g)*((g)*(g-f))))))+0.7)/4.0);}`;
const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
const R=g2.createKernel(function(tv){
const Pa=tv[this.thread.y][this.thread.x*4];
// return Ave(Pa[0]*0.8,Pa[1],Pa[2]*1.2);
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setOptimizeFloatMemory(true).setOutput([sz]);
const t=g.createKernel(function(v){
// const P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
const P=v[this.thread.y][this.thread.x];
// const av$=Ave(P[0]*0.8,P[1],P[2]*1.2);
const av$=Ave(P[0],P[1],P[2]);
var minuss=(av$-0.9)*(av$/(av$-0.9));
av$=av$-(minuss*(av$*0.01));
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPrecision('single').setPipeline(true).setDynamicOutput(true).setOutput([$S,$S]);
const r=g.createKernel(function(f){
const p=f[this.thread.y][this.thread.x];
const $amax=this.constants.amax;
const $amin=this.constants.amin;
const $aavg=this.constants.aavg;
const alph=Alphe($amax,$amin,$aavg,p[3]);
const Min=(4.0*(($amax-($aavg-$amin))/2.0));
const ouT=Math.max(Min,alph);
const aveg=Aveg(p[3],ouT);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setGraphical(true).setDynamicOutput(true).setOutput([$S,$S]);
gl_js.getExtension('WEBGL_color_buffer_float');
gl_js.getExtension('WEBGL_color_buffer_half_float');
gl_js.getExtension('OES_texture_float_linear');
gl_js.getExtension('OES_texture_half_float_linear');
gl_js.getExtension('EXT_float_blend');
gl_js.getExtension('EXT_frag_depth');
gl_js.getExtension('EXT_shader_texture_lod');
gl_js.getExtension('EXT_sRGB');
gl_js.getExtension('EXT_blend_minmax');
gl_js.getExtension('ANGLE_instanced_arrays');
// gl.getExtension('EXT_disjoint_timer_query');
gl_js.getExtension('EXT_clip_cull_distance');
// gl.getExtension('EXT_disjoint_timer_query_webgl2');
gl_js.getExtension('KHR_parallel_shader_compile');
gl_js.getExtension('OES_draw_buffers_indexed');
gl_js.getExtension('OES_element_index_uint');
gl_js.getExtension('OES_fbo_render_mipmap');
// gl_js.getExtension('OES_standard_derivatives');
gl_js.getExtension('OES_vertex_array_object');
gl_js.getExtension('WEBGL_blend_equation_advanced_coherent');
gl_js.getExtension('WEBGL_depth_texture');
gl_js.getExtension('WEBGL_draw_buffers');
gl_js.getExtension('WEBGL_provoking_vertex');
gl_js.getExtension('EXT_framebuffer_sRGB');
gl_js.getExtension('OES_depth32');
gl_js.getExtension('OES_fixed_point');
gl_js.getExtension('OES_shader_multisample_interpolation');
gl_js.getExtension('WEBGL_webcodecs_video_frame');
gl_js.getExtension('OES_single_precision');
// gl.getExtension('EXT_texture_shadow_lod');
gl_js.getExtension('EGL_NV_memory_attachment');
gl_js.getExtension('EGL_NV_depth_nonlinear');
gl_js.getExtension('EXT_gl_colorspace_display_p3');
gl_js.getExtension('EXT_gl_colorspace_display_p3_linear');
gl_js.getExtension('EXT_gl_colorspace_bt2020_linear');
gl_js.getExtension('ARB_multisample');
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
gl_js.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gl_js.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
gl_js.blendColor(1.0,1.0,1.0,1.0);
gl_js.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gl_js.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gl.unpackColorSpace='display-p3';  // very slow
gl_js.disable(gl.DITHER);
gl_js.drawingBufferColorSpace='display-p3';
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);var r"+i+",$"+i+",$$"+i+";");
};
var pointb=77*la;
var $B=new Float64Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var $$1=t(vv);
for(var i=0;i<65;i++){
var j=i+1;
eval("point"+j+"="+i+"*la;$"+j+"=new Float64Array($H,point"+j+",la);$"+j+".set($$1,0,la);");
};
var d=S();if(d)d();d=S();
function S(){
$S=parseInt(window.innerHeight,10);
Module.ccall("szz",null,["Number"],[$S]);
// t.setOutput([$S,$S]);
vv=document.getElementById("mv");
lvv=document.getElementById("ldv");
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var blank$=Math.max(((w$-h$)/2.0),0);
var nblank$=Math.max(((h$-w$)/2.0),0);
la=h$*h$*4;
sz=(h$*w$)/8;
pointa=77*la;
var agav=new Float64Array($H,pointa,300);  // has to var?
pointb=66*la;
var $B=new Float64Array($H,pointb,sz);  // has to var?
R.setOutput([sz]);
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
for(var i=0;i<65;i++){
var j=i+1;
eval("point"+j+"="+i+"*la;$"+j+"=new Float64Array($H,point"+j+",la);");
};
var T=false;
// r.setOutput([$S,$S]);
function M(){
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
if(T){
return;
};
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;};
var locb=$Bu+1;
if(locb>64){locb=1;};
if($F==i){
eval("$r"+i+"=t($"+i+");r($r"+i+");$$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+",0,la);$F="+loca+";$Bu="+locb+";");
};
};
$bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;  // has to revar?
if(sh4d==true){
Module.ccall("frm");
};
setTimeout(function(){
M();
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
Module.ccall("clr",null,["Number","Number","Number"],[agav[200],agav[100],agav[0]]);
if(loopLoop==true){
if(revv==true){
reverseLoop();
}else{
forwardLoop();
};
};
},timFrm)};
M();
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
}

});

extern "C" {

void b3(){
ma();
return;
}

void b3_egl(){
egl();
return;
}
 
}
