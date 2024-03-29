#include "../include/b3emjs.hpp"

EM_JS(void,ma,(),{

"use strict";

var vv=document.getElementById("mv");
var $S=parseInt(window.innerHeight,10);
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
var $S=parseInt(window.innerHeight,10);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var la=h$*h$*4;
var pointa=77*la;
// var pointb=66*la;
// var $B=new Float64Array($H,pointb,sz);
var agav=new Float64Array($H,pointa,300);
var sz=(h$*w$)/8;
var avag=0.750;
var min=1.000;
var max=0.000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*0)/2.0),0);
var nblank$=Math.max((((h$-w$)*0)/2.0),0);
var bCan=document.getElementById("bcanvas");
var gl=bCan.getContext("webgl2",{
colorType:'float64',
preferLowPowerToHighPerformance:false,
precision:'highp',
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
imageSmoothingEnabled:true,
imageSmoothingQuality:'medium',
preserveDrawingBuffer:false,
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

var g=new GPU({mode:'gpu',canvas:bCan,webGl:gl});
var g2=new GPU();
var glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
var glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))+((f-g)*((1.0-g)*(f-g)))-((f-g)*((g)*(g-f)))))))/3.0);}`;
var glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
var R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0]*0.8,Pa[1],Pa[2]*1.2);
}).setTactic("speed").setDynamicOutput(true).setOutput([sz]);
var t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0]*0.8,P[1],P[2]*1.2);
var minuss=(av$-0.9)*(av$/(av$-0.9));
av$=av$-(minuss*(av$*0.01));
return[P[0],P[1],P[2],av$];
}).setConstants({nblnk:nblank$,blnk:blank$}).setTactic("precision").setPipeline(true).setDynamicOutput(true).setOutput([$S,$S]);
var r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
this.color(p[0],p[1],p[2],aveg);
}).setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]}).setTactic("precision").setGraphical(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([$S,$S]);
gl.getExtension('WEBGL_color_buffer_float');
// gl.getExtension('WEBGL_color_buffer_half_float');
gl.getExtension('OES_texture_float_linear');
// gl.getExtension('OES_texture_half_float_linear');
gl.getExtension('EXT_float_blend');
gl.getExtension('EXT_frag_depth');
gl.getExtension('EXT_shader_texture_lod');
gl.getExtension('EXT_sRGB');
gl.getExtension('EXT_blend_minmax');
gl.getExtension('ANGLE_instanced_arrays');
// gl.getExtension('EXT_disjoint_timer_query');
gl.getExtension('EXT_clip_cull_distance');
// gl.getExtension('EXT_disjoint_timer_query_webgl2');
gl.getExtension('KHR_parallel_shader_compile');
gl.getExtension('OES_draw_buffers_indexed');
gl.getExtension('OES_element_index_uint');
gl.getExtension('OES_fbo_render_mipmap');
// gl.getExtension('OES_standard_derivatives');
gl.getExtension('OES_vertex_array_object');
gl.getExtension('WEBGL_blend_equation_advanced_coherent');
gl.getExtension('WEBGL_depth_texture');
gl.getExtension('WEBGL_draw_buffers');
gl.getExtension('WEBGL_provoking_vertex');
gl.getExtension('EXT_framebuffer_sRGB');
gl.getExtension('OES_depth32');
// gl.getExtension('OES_fixed_point');
  //  gl.getExtension('OES_shader_multisample_interpolation');
// gl.getExtension('WEBGL_webcodecs_video_frame');
gl.getExtension('OES_single_precision');
// gl.getExtension('EXT_texture_shadow_lod');
gl.getExtension('EGL_NV_memory_attachment');
gl.getExtension('EGL_NV_depth_nonlinear');
gl.getExtension('EXT_gl_colorspace_display_p3');
gl.getExtension('EXT_gl_colorspace_display_p3_linear');
gl.getExtension('EXT_gl_colorspace_bt2020_linear');
gl.getExtension('ARB_multisample');
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
gl.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gl.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
// gl.blendColor(1.0,1.0,1.0,1.0);
gl.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gl.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gl.unpackColorSpace='display-p3';  // very slow
gl.disable(gl.DITHER);
gl.drawingBufferColorSpace='display-p3';
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
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
eval("point"+j+"="+i+"*la;$"+j+"=new Float64Array($H,point"+j+",la);$"+j+".set($$1);");
};
var d=S();if(d)d();d=S();
function S(){
$S=parseInt(window.innerHeight,10);
Module.ccall("szz",null,["Number"],[$S]);
// t.setOutput([$S,$S]);
vv=document.getElementById("mv");
var $S=parseInt(window.innerHeight,10);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var blank$=Math.max((((w$-h$)*0)/2.0),0);
var nblank$=Math.max((((h$-w$)*0)/2.0),0);
la=h$*h$*4;
sz=(h$*h$)/8;
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
r.setOutput([$S,$S]);
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
eval("if($F=="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");}");
eval("if($F=="+i+"){var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+");$F="+loca+";$Bu="+locb+";}");
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
};


};
