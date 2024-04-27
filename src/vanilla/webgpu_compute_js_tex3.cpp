EM_JS(void,js_main,(),{

FS.mkdir('/shader');
FS.mkdir('/video');
let running=0;

function flipImageData(imageData){
const width=imageData.width;
const height=imageData.height;
const data=imageData.data;
for(let y=0;y<height/2;y++){
for(let x=0;x<width;x++){
const topIndex=(y*width+x)*4;
const bottomIndex=((height-1-y)*width+x)*4;
for(let c=0;c<4;c++){
[data[topIndex+c],data[bottomIndex+c]]=[data[bottomIndex+c],data[topIndex+c]];
}}}
return imageData;
}

function nearestPowerOf2(n){
if(n&(n-1)){
return Math.pow(2,Math.ceil(Math.log2(n)));
}else{
return n;
}}

function imageStart(){
let vvi=document.querySelector('#ivi');
let SiZ=window.innerHeight;
let w$=parseInt(document.querySelector("#ivi").width);
let h$=parseInt(document.querySelector("#ivi").height);
if(running==0){
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz]);
console.log('Starting..');
running=1;
},250);
}else{
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,"Number",[vsiz]);
console.log('Starting..');
},250);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#canvas');
cnv.height=SiZ;
cnvb.height=h$;
cnv.width=SiZ;
cnvb.width=w$;
let offS=Math.floor((w$-h$)/2);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
// const gl3=cnvb.getContext('2d',{colorType:'float64',alpha:true}); // 
const gl3=cnvb.getContext('2d',{
colorType:'float64',
alpha:true,
willReadFrequently:false,
stencil:false,
depth:false,
// colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
}); // 
vvi.style.transform='scaley(-1.0)';
gl3.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
// let image=flipImageData(gl3.getImageData(0,0,w$,h$));
let image=gl3.getImageData(0,0,w$,h$);
let imageData=image.data;
// let pixelData=new Uint8ClampedArray(imageData);
let pixelData=new Float64Array(imageData);
// var pixelData=new Float64Array(imageData,0,la);
FS.writeFile('/video/frame.gl',pixelData);
Module.ccall("frmOn");
// Module.ccall("frmsOff");
}

function videoStart(){
let vvi=document.querySelector('#mvi');
let vw$=vvi.videoWidth;
let vh$=vvi.videoHeight;
let SiZ=window.innerHeight;
vvi.height=vh$;
vvi.width=vw$;
let w$=parseInt(document.querySelector("#mvi").width);
let h$=parseInt(document.querySelector("#mvi").height);
let tstSiZ=720;
if(running==0){
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz]);
console.log('Starting..');
running=1;
},250);
}else{
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,"Number",[vsiz]);
console.log('Starting..');
},250);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#canvas');
cnv.height=h$;
cnvb.height=SiZ;
cnv.width=w$;
cnvb.width=SiZ;
let offS=Math.floor((w$-h$)/2);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
// const gl3=cnvb.getContext('2d',{colorType:'float64',alpha:true}); // 
const gl3=cnv.getContext('2d',{
colorType:'float64',
alpha:true,
willReadFrequently:false,
stencil:false,
depth:false,
// colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
}); // 
gl3.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
// var image=flipImageData(gl3.getImageData(0,0,w$,h$));
let image=gl3.getImageData(0,0,w$,h$);
let imageData=image.data;
// let pixelData=new Uint8ClampedArray(imageData);
let pixelData=new Float64Array(imageData);
// var pixelData=new Float64Array(imageData,0,la);
FS.writeFile('/video/frame.gl',pixelData);
Module.ccall("frmOn");
setInterval(function(){
gl3.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
// image=flipImageData(gl3.getImageData(0,0,w$,h$));
image=gl3.getImageData(0,0,w$,h$);
imageData=image.data;
// pixelData=new Uint8ClampedArray(imageData);
pixelData=new Float64Array(imageData);
 // pixelData=new Float64Array(imageData);
 //  const externalTexture = gpuDevice.createTexture({size: [imageWidth, imageHeight, 1],format: 'rgba8unorm',usage: GPUTextureUsage.TEXTURE_BINDING | GPUTextureUsage.COPY_DST });
// gpuQueue.writeTexture({ texture }, pixelData, { bytesPerRow }, { width: w$, height: h$ } );
// pixelData=new Float64Array(imageData,0,la);  // causes sub-array data array-reforming (slower)
FS.writeFile('/video/frame.gl',pixelData);
Module.ccall("frmOn");
},10);
}

function canvasStart(){
if(running==0){
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz]);
console.log('Starting..');
running=1;
},250);
}else{
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,"Number",[vsiz]);
console.log('Starting..');
},250);
}
let vvic=document.querySelector('#mvi');
let SiZ=window.innerHeight;
let w$=vvic.width;
let h$=vvic.height;
console.log("canvas size: ",h$,", ",w$);
let cnv=document.querySelector('#canvas');
let cnvb=document.querySelector('#bcanvas');
cnv.height=SiZ;
cnvb.height=h$;
cnv.width=SiZ;
cnvb.width=w$;
let offS=Math.floor((w$-h$)/2);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
let gl3=cnvb.getContext('2d',{
colorType:'float64',
alpha:true,
willReadFrequently:false,
stencil:false,
depth:false,
// colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
gl3.drawImage(vvic,0,0,w$,h$,0,0,w$,h$);
let image=gl3.getImageData(0,0,w$,h$);
let imageData=image.data;
// let pixelData=new Uint8ClampedArray(imageData);
let pixelData=new Float64Array(imageData);
FS.writeFile('/video/frame.gl',pixelData);
Module.ccall("frmOn");
setInterval(function(){
gl3.drawImage(vvic,0,0,w$,h$,0,0,w$,h$);
image=gl3.getImageData(0,0,w$,h$);
imageData=image.data;
// pixelData=new Uint8ClampedArray(imageData);
pixelData=new Float64Array(imageData);
// pixelData=new Float64Array(imageData,0,la);  // causes sub-array data array-reforming (slower)
FS.writeFile('/video/frame.gl',pixelData);
Module.ccall("frmOn");
},10);
}

function regularStart(){
let SiZ=window.innerHeight;
let cnvb=document.querySelector('#canvas');
cnvb.height=SiZ;
cnvb.width=SiZ;
if(running==0){
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz]);
console.log('Starting..');
running=1;
},250);
}else{
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,"Number",[vsiz]);
console.log('Starting..');
},250);
}
}
  
function getShader(pth,fname){
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading Shader';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/'+fname,sfil);
document.querySelector('#stat').innerHTML='Downloaded Shader';
document.querySelector('#stat').style.backgroundColor='blue';
}
});
ff.send(null);
}
  
let codeMessage=new BroadcastChannel('codeMessage');

codeMessage.addEventListener('message',event=>{
var pth2=document.querySelector('#computePathNovid').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
document.querySelector('#status').style.backgroundColor="blue";
let flDat=event.data.data;
var buffer = new ArrayBuffer(flDat.length*2);
var bufferView = new Uint16Array(buffer);
for (var i = 0; i < flDat.length; i++) {
bufferView[i] = flDat.charCodeAt(i);
}
// console.log(bufferView);
FS.writeFile('/shader/shader.wgsl',bufferView);
// document.querySelector('#startBtn').click();
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
document.querySelector('#status').style.backgroundColor="green";
normalResSetup();
regularStart();
},250);
});

const vsiz=document.querySelector('#vsiz');

function normalResSetup(){
setTimeout(function(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#ihig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#canvas').height=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').height=parseInt(window.innerHeight,10);
document.querySelector('#canvas').width=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').width=parseInt(window.innerHeight,10);
document.querySelector('#di').click();
},500);
document.querySelector('#status').style.backgroundColor="green";
}

document.querySelector('#status').height=20;
document.querySelector('#status').width=parseInt(window.innerHeight,10);
const tem=document.querySelector('#tim');
const ban=document.querySelector('#menuBtn');
const sfr=document.querySelector('#slideframe');
var $lt=tem.innerHTML;
function grab$lt(){
$lt=Math.round($lt);
}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.querySelector('#panel'),'menu':document.querySelector('#menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();
slt=$lt/1000;
slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.05,max:3.00},
step:[0.05],labels:false,tooltip:true,scale:false,});
grab$lt();
slt=($lt/1000);
slt=slt*100;
slt=Math.round(slt);
slt=slt/100;
tsl.setValues(1.0);
vsiz.innerHTML=Math.round(window.innerHeight);
document.querySelector('#menu').addEventListener('click',function(){
$ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;
$ll=($ll*1000);
tem.innerHTML=$ll;
vsiz.innerHTML=Math.round($ll/1000*window.innerHeight);
});
setTimeout(function(){
slt=tem.innerHTML;
},8);
},16);
});

document.querySelector('#startBtn').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
normalResSetup();
videoStart();
});

document.querySelector('#startBtn2').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePathNovid').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
normalResSetup();
regularStart();
});

document.querySelector('#startBtnC').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
normalResSetup();
setTimeout(function(){
canvasStart();
},3000);
});

document.querySelector('#startBtnI').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
normalResSetup();
setTimeout(function(){
imageStart();
},3000);
});

setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
},500);
});
