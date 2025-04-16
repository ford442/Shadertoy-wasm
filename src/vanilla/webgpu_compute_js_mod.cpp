EM_JS(void,js_main,(),{

FS.mkdir('/shader');
FS.mkdir('/video');
let running=0;

var $h,$pt,slt,$ll,r$,$w,$r,$lt,$hg,$ls,lo,mv,he,wi;

const $iwid=document.getElementById('iwid');
var mV=document.getElementById('mv');
var loadV=document.getElementById('ldv');
var $vids=[];

function vids(xml){
const vparser=new DOMParser();
const htmlDocv=vparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocv.getElementsByTagName('pre')[0].getElementsByTagName('a');
$vids[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxt=preList[i].href;
let pathName = window.location.pathname; // e.g., "/path/page.html" or "/path/" or "/"
let lastSlashIndex = pathName.lastIndexOf('/');
let basePath = pathName.substring(0, lastSlashIndex + 1); // e.g., "/path/to/"
txxt=txxt.replace(basePath,'');
$vids[i]=basePath+'video/'+txxt;
}}

function scanVideos(){
const fxhttp=new XMLHttpRequest();
fxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
vids(this);
}};
fxhttp.open('GET','video/',true);
fxhttp.send();
}

const media_mode = document.querySelector('#media').value;

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);

if(media_mode=='vid'){
document.getElementById('mv').load();
document.getElementById('ldv').load();
}

const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');

if(media_mode=='vid'){
var adr='./intro.mp4';
wi=1280;
he=720;
}
if(media_mode=='img'){
var adr='./bezel.jpg';
wi=1920;
he=1080;
}
var hii=window.innerHeight;
document.getElementById('ihid').innerHTML=hii;
r$=hii/he;
$w=wi*r$;
const $ihigB=document.getElementById('ihid');
const $ihig=document.getElementById('ihig');
$hg=hii+'px';
$ihig.innerHTML=parseInt(window.innerHeight,10);
$iwid.innerHTML=parseInt($w,10);
document.getElementById('wrap').style.lineheight=$hg;
document.getElementById('wrap').style.pointerEvents='auto';
document.getElementById('isrc').innerHTML=adr;
if(media_mode=='vid'){
mV.play();
}
var vv=document.getElementById('mv');
let lockVid;

function spKey(e){
if(e.code=='Space'){
e.preventDefault();
if(lockVid==0){lockVid=1;};
if(lockVid==1){lockVid=0;};
};
if(e.code=='KeyZ'){lockVid=1;};
if(e.code=='KeyX'){lockVid=0;};
}

const pnnl=document.body;
pnnl.addEventListener('keydown',spKey);
/*
function loada(){
if(lockVid!=1){
document.getElementById('ldv').height=window.innerHeight;
if(media_mode=='vid'){
mV.addEventListener('canplay',function(){
mV.width=this.videoWidth;
mV.height=this.videoHeight;
});
loadV.addEventListener('canplay',function(){
loadV.width=this.videoWidth;
loadV.height=this.videoHeight;
document.getElementById('wid').innerHTML=this.videoWidth;
document.getElementById('hig').innerHTML=this.videoHeight;
document.getElementById('blnnk').innerHTML=Math.max((this.videoWidth-this.videoHeight)/2.0,0);
var $sc=this.duration;
var mic=Math.round($sc*1000000);
$pt=Math.random()*mic;
$pt=$pt*1000000;
$pt=$pt/1000000;
$pt=Math.round($pt);
$pt=$pt/1000000;
document.getElementById('idur').innerHTML=mic/1000000;
document.getElementById('itim').innerHTML=$pt;
});
}
if(media_mode=='img'){
mV.addEventListener('load',function(){
});
loadV.addEventListener('load',function(){
document.getElementById('wid').innerHTML=this.width;
document.getElementById('hig').innerHTML=this.height;
document.getElementById('blnnk').innerHTML=Math.max((this.width-this.height)/2.0,0);
});
}
if(media_mode=='vid'){
var vide=document.querySelectorAll('video');
}
if(media_mode=='img'){
var vide=document.querySelector('#images').querySelectorAll('img');
}
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
hii=window.innerHeight;
document.getElementById('ihid').innerHTML=hii;
$lt=Math.round(tem.innerHTML);
var $ldt=document.getElementById('tim').innerHTML;
$ls=$lt/1000;
$ls=$ls*1000;
$ls=Math.round($ls);
$ls=$ls/1000;
var rnum=Math.floor((Math.random()*($vids[0]-5))+5);
document.getElementById('isrc').innerHTML=$vids[rnum];
$h=window.innerHeight;
he=document.getElementById('hig').innerHTML;
wi=document.getElementById('wid').innerHTML;
r$=he/$h;
$w=wi/r$;
hii=$ihigB.innerHTML;
var $hi=$h-hii;
if($hi>1){$h=$ihigB.innerHTML;$ihig.innerHTML=$h;$r=$h/he;$r=$r*1000;$r=$r/1000;$w=wi*$r;};
$hg=$h+'px';
window.scroll(0,0);
mv=vide[0].id;
lo=vide[1].id;
vide[0].id=lo;
vide[1].id=mv;
if(media_mode=='vid'){
document.getElementById('mv').play();
}
$iwid.innerHTML=parseInt($w,10);
$ihig.innerHTML=parseInt(window.innerHeight,10);  
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('circle').height=parseInt(window.innerHeight,10);
document.getElementById('circle').width=parseInt(window.innerWidth,10);
document.getElementById('ldv').src=document.getElementById('isrc').innerHTML;
if(media_mode=='img'){
document.getElementById('mv').height=window.innerHeight;
document.getElementById('ldv').height=window.innerHeight;
}
if(media_mode=='vid'){
document.getElementById('ldv').load();
document.getElementById('ldv').currentTime=document.getElementById('itim').innerHTML;
}
document.getElementById('ldv').height=he;
document.getElementById('ldv').width=wi;
document.getElementById('di').click();
}
setTimeout(function(){
loada();
},$ldt);
}

document.getElementById('startBtn').addEventListener('click',function(){
scanVideos();
loada();
});
*/

let frameBufferViewF32 = []; // The view into C++ memory

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

let pause='ready';
    
function canvasStart2(){
let vvic=document.querySelector('#mvi');
let srsiz=document.querySelector('#srsiz').innerHTML;
let vsiz=document.querySelector('#vsiz').innerHTML;
var SiZ=window.innerHeight;
var w$=parseInt(vsiz,10);
vvic.width=SiZ;
var h$=parseInt(vsiz,10);
vvic.height=SiZ;
console.log("canvas size: ",h$,", ",w$);
const cnvb=new OffscreenCanvas(h$,w$); 
// document.querySelector('#contain2').appendChild(cnvb);
const cnv=document.querySelector('#scanvas');
const cnvc=document.querySelector('#bcanvas');
cnv.height=SiZ;
cnvb.height=vsiz;
cnvc.height=vsiz;
cnvc.style.height=vsiz+'px';
cnv.width=SiZ;
cnvb.width=vsiz;
cnvc.width=vsiz;
cnvc.style.width=vsiz+'px';
const gl3=cnvb.getContext('2d',{
colorType:'float64',
alpha:true,
willReadFrequently:true,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
gl3.imageSmoothingEnabled=false;
let fileStream=FS.open('/video/frame.gl','w');
  function drawFrame() {
    if (pause === 'ready') {
      gl3.clearRect(0, 0, w$, h$);
      gl3.drawImage(vvic, 0, 0, SiZ, SiZ, 0, 0, w$, h$);
    }else{
        console.log('frames stopped');
        }
    const image = gl3.getImageData(0, 0, w$, h$);
    const imageData = image.data;
    const pixelData = new Float64Array(imageData);
    FS.write(fileStream, pixelData, 0, pixelData.length, 0);
    Module.frmOn();
  }
  if (running == 0) {
    setTimeout(() => {
      Module.ccall("startWebGPUC", null,"Number",[vsiz,srsiz]);
      running = 1;
      setInterval(drawFrame, 16.6); 
    }, 250);
  } else {
    setInterval(drawFrame, 16.6);
  }
}
 
function canvasStartSize(){
const vvic=document.querySelector('#mvi');
const srsiz=document.querySelector('#srsiz').innerHTML;
const vsiz=document.querySelector('#vsiz').innerHTML;
const SiZ=window.innerHeight;
// vvic.width=vsiz;
// vvic.height=vsiz;
let w$; //=vsiz;
let h$; //=vsiz;
if(vvic.tagName=='CANVAS'){
vvic.width=vsiz;
vvic.height=vsiz;
w$=vsiz;
h$=vsiz;
}
if(vvic.tagName=='IMG'){
w$=vvic.naturalWidth;
h$=vvic.naturalHeight;
vvic.width=vvic.naturalWidth;
vvic.height=vvic.naturalHeight;
}
if(vvic.tagName=='VIDEO'){
w$=vvic.videoWidth;
h$=vvic.videoHeight;
vvic.width=vvic.videoWidth;
vvic.height=vvic.videoHeight;
}
const keepSizea = Math.max(h$, w$);
const keepSize = Math.min(keepSizea, vsiz);
const drawX = (keepSize - w$) / 2;
const drawY = (keepSize - h$) / 2;
console.log("canvas size: ",keepSize,", ",keepSize);
const OffscCnv=new OffscreenCanvas(keepSize,keepSize); 
// document.querySelector('#contain2').appendChild(OffscCnv);
const scnv=document.querySelector('#scanvas');
const bcnv=document.querySelector('#bcanvas');
scnv.height=SiZ;
OffscCnv.height=keepSize;
bcnv.height=keepSize;
bcnv.style.height=keepSize+'px';
scnv.width=SiZ;
OffscCnv.width=keepSize;
bcnv.width=keepSize;
bcnv.style.width=keepSize+'px';
const gl3=OffscCnv.getContext('2d',{
colorType:'float32',
alpha:true,
willReadFrequently:true,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
document.querySelector('#moveFwdb').addEventListener('click',function(){
Module.ccall('frmsOff');
console.log('stopping frames for move');
pause = 'loading';
setTimeout(function(){
pause = 'ready';
Module.ccall('frmsOn');
// console.log('restarting frames for move');
}, 1900);
});

if (running == 0) {
setTimeout(() => {
console.log('sending: ',keepSize,vsiz,srsiz);
Module.ccall("startWebGPUC", null,["Number","Number","Number"],[vsiz,vsiz,srsiz]);
running = 1;
frameBufferViewF32 = Module.getPixelBufferView();
console.log(`Obtained C++ buffer view with length: ${frameBufferViewF32.length}`);
}, 250);
} else {
Module.ccall("startWebGPUC", null,["Number","Number","Number"],[vsiz,vsiz,srsiz]);

frameBufferViewF32 = Module.getPixelBufferView();
console.log(`Obtained C++ buffer view with length: ${frameBufferViewF32.length}`);
}

// gl3.imageSmoothingEnabled=false;
// const fileStream=FS.open('/video/frame.gl','w');
setInterval(function() {
if (pause === 'ready') {
gl3.clearRect(0, 0, keepSize, keepSize);
gl3.drawImage(vvic, 0, 0, w$, h$, drawX, drawY, w$, h$); 
}
const image = gl3.getImageData(0, 0, keepSize, keepSize);
const imageData = image.data;
  // val array
const pixelCount = keepSize * keepSize * 4; // RGBA
for (let i = 0; i < pixelCount; ++i) {
// Normalize uint8 (0-255) to float (0.0-1.0)
const normalizedValue = imageData[i] / 255.0;
frameBufferViewF32[i] = normalizedValue;
}
// const pixelData = new Float32Array(imageData);
// const pixelData = new Uint8Array(imageData);
// FS.write(fileStream, pixelData, 0, pixelData.length, 0);
Module.frmOn();
},16);

}


function canvasStart(){
const vvic=document.querySelector('#mvi');
const srsiz=document.querySelector('#srsiz').innerHTML;
const vsiz=document.querySelector('#vsiz').innerHTML;
const SiZ=window.innerHeight;
const w$=parseInt(vsiz,10);
// vvic.width=SiZ;
const h$=parseInt(vsiz,10);
// vvic.height=SiZ;
console.log("canvas size: ",h$,", ",w$);
const cnvb=new OffscreenCanvas(h$,w$); 
// document.querySelector('#contain2').appendChild(cnvb);
const cnv=document.querySelector('#scanvas');
const cnvc=document.querySelector('#bcanvas');
cnv.height=SiZ;
// cnvb.height=vsiz;
cnvc.height=vsiz;
cnvc.style.height=vsiz+'px';
cnv.width=SiZ;
// cnvb.width=vsiz;
cnvc.width=vsiz;
cnvc.style.width=vsiz+'px';
const gl3=cnvb.getContext('2d',{
colorType:'float32',
alpha:true,
willReadFrequently:true,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
// gl3.imageSmoothingEnabled=false;
const fileStream=FS.open('/video/frame.gl','w+');
function drawFrame() {
if (pause === 'ready') {
gl3.clearRect(0, 0, w$, h$);
gl3.drawImage(vvic, 0, 0, SiZ, SiZ, 0, 0, w$, h$);
const image = gl3.getImageData(0, 0, w$, h$);
const imageData = image.data;
const pixelData = new Float32Array(imageData);
FS.write(fileStream, pixelData, 0, pixelData.length, 0);
Module.frmOn();
}
}
if (running == 0) {
setTimeout(() => {
Module.ccall("startWebGPUC", null,["Number","Number","Number"],[vvic.height,vsiz,srsiz]);
running = 1;
setInterval(drawFrame, 16.6); 
}, 250);
} else {
setInterval(drawFrame, 16.6);
}
}


function khz(){
let timeStart=performance.now();
let cycle;
let dot;
const srsiz=document.querySelector('#srsiz').innerHTML;
const vsiz=document.querySelector('#vsiz').innerHTML;
const SiZ=window.innerHeight;
console.log("canvas size: ",SiZ,", ",SiZ);
const OffscCnv=new OffscreenCanvas(vsiz,vsiz); 
const scnv=document.querySelector('#scanvas');
const bcnv=document.querySelector('#bcanvas');
scnv.height=SiZ;
OffscCnv.height=vsiz;
bcnv.height=vsiz;
bcnv.style.height=vsiz+'px';
scnv.width=SiZ;
OffscCnv.width=vsiz;
bcnv.width=vsiz;
bcnv.style.width=vsiz+'px';
const gl3=OffscCnv.getContext('2d',{
colorType:'float32',
alpha:true,
willReadFrequently:true,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
// gl3.imageSmoothingEnabled=false;
const fileStream=FS.open('/video/frame.gl','w+');
let matrix=    gl3.createImageData(vsiz,vsiz);
for (let i = 0; i < matrix.data.length; i += 4){
matrix.data[i+0] = 0;
matrix.data[i+1] = 0;
matrix.data[i+2] = 0;
matrix.data[i+3] = 255;
}
function drawFrame() {
if (pause === 'ready') {
gl3.clearRect(0, 0, vsiz, vsiz);
gl3.fillStyle = 'black';
gl3.fillRect(0, 0, vsiz, vsiz);
cycle=performance.now()-timeStart;
cycle=cycle%1.0;
dot=330000*cycle;
dot=(vsiz*vsiz)*dot*4;
for (let i = 0; i < matrix.data.length; i += 4){
matrix.data[i+0] = 0;
matrix.data[i+1] = 0;
matrix.data[i+2] = 0;
matrix.data[i+3] = 255;
}
matrix.data[dot] = 255;
matrix.data[dot+1] = 255;
matrix.data[dot+2] = 255;
matrix.data[dot+3] = 255;
matrix.data[dot+4] = 255;
matrix.data[dot+5] = 255;
matrix.data[dot+6] = 255;
matrix.data[dot+7] = 255;
matrix.data[dot+8] = 255;
matrix.data[dot+9] = 255;
matrix.data[dot+10] = 255;
matrix.data[dot+11] = 255;
gl3.putImageData(matrix,vsiz,vsiz);
}
const image = gl3.getImageData(0, 0, vsiz, vsiz);
const imageData = image.data;
const pixelData = new Float32Array(imageData);
FS.write(fileStream, pixelData, 0, pixelData.length, 0);
Module.frmOn();
}
if (running == 0) {
setTimeout(() => {
console.log('sending: ',vsiz,vsiz,srsiz);
Module.ccall("startWebGPUC", null,["Number","Number","Number"],[vsiz,vsiz,srsiz]);
running = 1;
setInterval(drawFrame, 16.6); 
}, 250);
} else {
setInterval(drawFrame, 16.6);
}
}

function createRGBAFrame(audioChunk, chunkIndex) {
const width = 1024;
const height = 1024;
const frameSize = width * height * 4; // RGBA frame size
const frameData = new Uint8ClampedArray(frameSize);
const vvic=document.querySelector('#mvi');
const srsiz=document.querySelector('#srsiz').innerHTML;
const vsiz=document.querySelector('#vsiz').innerHTML;
const SiZ=window.innerHeight;
const w$=parseInt(vsiz,10);
// vvic.width=SiZ;
const h$=parseInt(vsiz,10);
// vvic.height=SiZ;
console.log("canvas size: ",h$,", ",w$);
const cnvb=new OffscreenCanvas(h$,w$); 
// document.querySelector('#contain2').appendChild(cnvb);
const cnv=document.querySelector('#scanvas');
const cnvc=document.querySelector('#bcanvas');
cnv.height=SiZ;
// cnvb.height=vsiz;
cnvc.height=vsiz;
cnvc.style.height=vsiz+'px';
cnv.width=SiZ;
// cnvb.width=vsiz;
cnvc.width=vsiz;
cnvc.style.width=vsiz+'px';
const gl3=cnvb.getContext('2d',{
colorType:'float32',
alpha:true,
willReadFrequently:true,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
// gl3.imageSmoothingEnabled=false;
const fileStream=FS.open('/video/frame.gl','w+');
for (let i = 0; i < audioChunk.length; i++) {
const sampleValue = audioChunk[i];
const rgbaValue = Math.floor((sampleValue + 1) * 127.5); // Normalize to 0-255
const x = i % width;
const y = Math.floor(i / width);
const index = (y * width + x) * 4;
frameData[index] = rgbaValue; // R
frameData[index + 1] = rgbaValue; // G
frameData[index + 2] = rgbaValue; // B
frameData[index + 3] = 255; // A
}
const image = new ImageData(frameData, width, height);
const imageData = image.data;
const pixelData = new Float32Array(imageData);
FS.write(fileStream, pixelData, 0, pixelData.length, 0);
Module.frmOn();
}

function splitAudioIntoChunks(audioData) {
const chunkSize = 1024 * 1024; // 1024x1024 samples
const numberOfChunks = Math.ceil(audioData.length / chunkSize);
for (let i = 0; i < numberOfChunks; i++) {
const start = i * chunkSize;
const end = Math.min(start + chunkSize, audioData.length);
const chunk = audioData.slice(start, end);
setTimeout(function(){
createRGBAFrame(chunk, i);
},16.6);
  }
}

function processAudioBuffer(audioBuffer) {
  const channelData = audioBuffer.getChannelData(0); // Get the first channel data
  const sampleRate = audioBuffer.sampleRate;
  const duration = audioBuffer.duration;
  const numberOfChannels = audioBuffer.numberOfChannels;
  console.log('Sample Rate:', sampleRate);
  console.log('Duration:', duration);
  console.log('Number of Channels:', numberOfChannels);
  splitAudioIntoChunks(channelData);
}

function birdsongStart(){
let srsiz=document.querySelector('#srsiz').innerHTML;
let vsiz=document.querySelector('#vsiz').innerHTML;
const pth=document.querySelector('#birdsongPath').innerHTML;
const audioContext = new (window.AudioContext || window.webkitAudioContext)();
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading Song';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load", function() {
  let sarrayBuffer = ff.response;
  if (sarrayBuffer) {
    audioContext.decodeAudioData(sarrayBuffer).then(audioBuffer => {
      processAudioBuffer(audioBuffer);
    }).catch(err => {
      console.error('Error decoding audio data:', err);
    });
  }
});
ff.send();
if (running == 0) {
Module.ccall("startWebGPUC", null,["Number","Number","Number"],[1024,vsiz,srsiz]);
running = 1;
}
}
 
function videoStart(){
const vvi=document.querySelector('#mvi');
let vw$=vvi.videoWidth;
let vh$=vvi.videoHeight;
let SiZ=window.innerHeight;
vvi.height=vh$;
vvi.width=vw$;
let w$=parseInt(document.querySelector("#mvi").width);
let h$=parseInt(document.querySelector("#mvi").height);
let srsiz=document.querySelector('#srsiz').innerHTML;
let vsiz=document.querySelector('#vsiz').innerHTML;
if(running==0){
setTimeout(function(){
Module.ccall("startWebGPUi",null,["Number","Number","Number"],[vvi.height,vsiz,srsiz]);
console.log('Starting..');
frameBufferViewF32 = Module.getPixelBufferView();
running=1;
},250);
}else{
setTimeout(function(){
Module.ccall("startWebGPUbi",null,["Number","Number","Number"],[vvi.height,vsiz,srsiz]);
console.log('Starting..');
frameBufferViewF32 = Module.getPixelBufferView();
},250);
}
     //    console.log(`Obtained C++ buffer view with length: ${frameBufferViewF32.length}`);
// const bufferPtr = Module.get_buffer_ptr();
const bufferSizeFloats = w$*h$*4;
// const frameView = new Float32Array(Module.HEAPF32.buffer, bufferPtr, bufferSizeFloats);
// console.log(`JS: Created manual view at ${bufferPtr}, size ${bufferSizeFloats}`);
console.log("vid size: ",h$,", ",w$);
const cnvb=new OffscreenCanvas(h$,w$); 
// document.querySelector('#contain2').appendChild(cnvb);
const cnv=document.querySelector('#scanvas');
const cnvc=document.querySelector('#bcanvas');
cnv.height=SiZ;
cnvb.height=vsiz;
cnvc.height=vsiz;
cnvc.style.height=vsiz+'px';
cnv.width=SiZ;
cnvb.width=vsiz;
cnvc.width=vsiz;
cnvc.style.width=vsiz+'px';
const gl3=cnvb.getContext('2d',{
colorType:'float32',
alpha:true,
willReadFrequently:false,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
gl3.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
// var image=flipImageData(gl3.getImageData(0,0,w$,h$));
var image=gl3.getImageData(0,0,w$,h$);
var imageData=image.data;
// var pixelData=new Float32Array(imageData);

const pixelCount = w$ * h$ * 4; // RGBA
for (let i = 0; i < pixelCount; ++i) {
// Normalize uint8 (0-255) to float (0.0-1.0)
const normalizedValue = imageData[i] / 255.0;
frameBufferViewF32[i] = normalizedValue;
}

/*
// let pixelData=new Uint8ClampedArray(imageData);
var pixelData=new Float32Array(imageData);
// var pixelData=new Float32Array(imageData,0,la);
let fileStream=FS.open('/video/frame.gl','w');
FS.write(fileStream,pixelData,0,pixelData.length,0);
*/
/*
// Module.processCopiedDataVal(pixelData);
const floatArray = new Float32Array(imageData.length);
for(let i = 0; i < imageData.length; i++) {
floatArray[i] = imageData[i] / 255.0;
}
*/
// Module.processCopiedDataVal(imageData);
Module.frmOn();
setInterval(function(){
gl3.clearRect(0,0,w$,h$);  
gl3.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
// image=flipImageData(gl3.getImageData(0,0,w$,h$));
image=gl3.getImageData(0,0,w$,h$);
imageData=image.data;

for (let i = 0; i < pixelCount; ++i) {
// Normalize uint8 (0-255) to float (0.0-1.0)
const normalizedValue = imageData[i] / 255.0;
frameBufferViewF32[i] = normalizedValue;
}

/*
// pixelData=new Uint8ClampedArray(imageData);
pixelData=new Float32Array(imageData);
 // pixelData=new Float32Array(imageData);
 //  const externalTexture = gpuDevice.createTexture({size: [imageWidth, imageHeight, 1],format: 'rgba8unorm',usage: GPUTextureUsage.TEXTURE_BINDING | GPUTextureUsage.COPY_DST });
// gpuQueue.writeTexture({ texture }, pixelData, { bytesPerRow }, { width: w$, height: h$ } );
// pixelData=new Float32Array(imageData,0,la);  // causes sub-array data array-reforming (slower)
FS.write(fileStream,pixelData,0,pixelData.length,0);
*/
// pixelData=new Float32Array(imageData);
// Module.processCopiedDataVal(pixelData);
// console.log(`Frame data sample: [${frameBufferViewF32[0].toFixed(2)}, ${frameBufferViewF32[1].toFixed(2)}, ${frameBufferViewF32[2].toFixed(2)}, ${frameBufferViewF32[3].toFixed(2)}]`);
/*
for(let i = 0; i < imageData.length; i++) {
floatArray[i] = imageData[i] / 255.0;
}
*/
// Module.processCopiedDataVal(imageData);
Module.frmOn();
},16.666);
}

function imageStart(){
var vvi=document.querySelector('#ivi');
let SiZ=window.innerHeight;
let w$=parseInt(document.querySelector("#ivi").width);
let h$=parseInt(document.querySelector("#ivi").height);
if(running==0){
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,["Number","Number","Number"],[vvi.height,vsiz,srsiz]);
console.log('Starting..');
running=1;
},250);
}else{
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,["Number","Number","Number"],[vvi.height,vsiz,srsiz]);
console.log('Starting..');
},250);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#scanvas');
var offsetX=Math.floor((w$-h$)/2);
var offsetY=Math.floor((h$-w$)/2);
cnvb.height=SiZ;
cnv.height=h$-offsetY;
cnvb.width=SiZ;
cnv.width=w$-offsetX;
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
// const gl3=cnvb.getContext('2d',{colorType:'float32',alpha:true}); // 
const gl3=cnv.getContext('2d',{
colorType:'float32',
alpha:true,
willReadFrequently:false,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
gl3.drawImage(vvi,0,0,w$-offsetX,h$-offsetY,0,0,w$-offsetX,h$-offsetY);
var image=gl3.getImageData(0,0,w$-offsetX,h$-offsetY);
var imageData=image.data;
let pixelData=new Uint8ClampedArray(imageData);
var fileStream=FS.open('/video/frame.gl','w');
FS.write(fileStream,pixelData,0,pixelData.length,0);
Module.frmOn();
setInterval(function(){
gl3.clearRect(0,0,w$,h$);  
gl3.drawImage(vvi,0,0,w$-offsetX,h$-offsetY,0,0,w$-offsetX,h$-offsetY);
var image2=gl3.getImageData(0,0,w$-offsetX,h$-offsetY);
var imageData=image2.data;
var pixelData=new Float32Array(imageData);
FS.write(fileStream,pixelData,0,pixelData.length,0);
Module.frmOn();
},16.666);
}

function imageStartSR(){
let vvi=document.querySelector('#ivi');
let SiZ=window.innerHeight;
let w$=parseInt(document.querySelector("#ivi").width);
let h$=parseInt(document.querySelector("#ivi").height);
if(running==0){
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,["Number","Number","Number"],[vvi.height,vsiz,srsiz]);
console.log('Starting..');
running=1;
},250);
}else{
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,["Number","Number","Number"],[vvi.height,vsiz,srsiz]);
console.log('Starting..');
},250);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#scanvas');
cnv.height=SiZ;
cnvb.height=h$;
cnv.width=SiZ;
cnvb.width=w$;
let offS=Math.floor((w$-h$)/2);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
// const gl3=cnvb.getContext('2d',{colorType:'float32',alpha:true}); // 
const gl3=cnvb.getContext('2d',{
colorType:'float32',
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
 const gl4=cnv.getContext('2d',{
colorType:'float32',
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
// let image=flipImageData(gl3.getImageData(0,0,w$,h$));
let image=gl3.getImageData(0,0,w$,h$);
let imageData=image.data;
// let pixelData=new Uint8ClampedArray(imageData);
let pixelData=new Float32Array(imageData);
// var pixelData=new Float32Array(imageData,0,la);
FS.writeFile('/video/frame.gl',pixelData);
Module.frmOn();
setInterval(function(){
image=gl4.getImageData(0,0,SiZ,SiZ);
gl3.drawImage(image,0,offS,h$,h$,0,0,h$,h$);
let image2=gl3.getImageData(0,0,w$,h$);
imageData=image2.data;
pixelData=new Float32Array(imageData);
FS.writeFile('/video/frame.gl',pixelData);
Module.frmOn();
},16.666);
}

function regularStart(){
let SiZ=window.innerHeight;
let cnvb=document.querySelector('#scanvas');
const vvic=document.querySelector('#mvi');
// document.querySelector('#path').innerHTML=document.querySelector('#path').innerHTML+document.querySelector('#sh1').value;
cnvb.height=SiZ;
cnvb.width=SiZ;
if(running==0){
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,["Number","Number","Number"],[vsiz,vsiz,srsiz]);
console.log('Starting..');
running=1;
},50);
}else{
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,["Number","Number","Number"],[vsiz,vsiz,srsiz]);
console.log('Starting..');
},50);
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
let codeMessageV=new BroadcastChannel('codeMessageV');

codeMessage.addEventListener('message',event=>{
var pth2=document.querySelector('#computePathNovid').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
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
document.querySelector('#di').click();
document.querySelector('#status').style.backgroundColor="green";
regularStart();
},50);
});

codeMessageV.addEventListener('message',event=>{
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
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
document.querySelector('#di').click();
document.querySelector('#status').style.backgroundColor="green";
regularStart();
// imageStart();
// videoStart();
},50);
});

const vsiz=document.querySelector('#vsiz');
let menuSz=parseInt(window.innerWidth*.5,10);

document.querySelector('#startBtn').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
videoStart();
});

document.querySelector('#startBtn2').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePathNovid').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
regularStart();
});

document.querySelector('#startBtnC').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
setTimeout(function(){
canvasStartSize();
},3000);
});

document.querySelector('#startBtnB').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePathBird').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
setTimeout(function(){
birdsongStart();
},3000);
});


document.querySelector('#startBtnH').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePathBird').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
setTimeout(function(){
khz();
},3000);
});

document.querySelector('#startBtnI').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
setTimeout(function(){
imageStart();
},1000);
});

document.querySelector('#sizeUp').addEventListener('click',function(){
Module.ccall("zoomIn");
});

document.querySelector('#sizeDown').addEventListener('click',function(){
Module.ccall("zoomOut");
});

document.querySelector('#moveDown').addEventListener('click',function(){
Module.ccall("panDown");
});

document.querySelector('#moveUp').addEventListener('click',function(){
Module.ccall("panUp");
});

document.querySelector('#moveRight').addEventListener('click',function(){
Module.ccall("panRight");
});

document.querySelector('#moveLeft').addEventListener('click',function(){
Module.ccall("panLeft");
});

setTimeout(function(){
document.querySelector('#di').click();
},250);
});
