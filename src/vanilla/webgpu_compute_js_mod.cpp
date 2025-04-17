
EM_JS(void,js_main,(),{

FS.mkdir('/shader');
FS.mkdir('/video');
let running=0;

const body = document.body;
var video = document.querySelector("#mvi");
var intervalBackward;
var intervalForward;
var intervalLoop;

function back() {
clearInterval(intervalBackward);
intervalBackward = requestAnimationFrame(function loop() {
if (video.currentTime <= 0) {
cancelAnimationFrame(intervalBackward);
} else {
video.currentTime -= 0.032;
intervalBackward = requestAnimationFrame(loop);
}
});
}

function forward() {
clearInterval(intervalForward);
intervalForward = requestAnimationFrame(function loop() {
video.currentTime += 0.032;
intervalForward = requestAnimationFrame(loop);
});
}

function backForth(stp, strt, rate) {
var f = true;
clearInterval(intervalLoop);
intervalLoop = requestAnimationFrame(function loop() {
if (f) {
if (video.currentTime >= strt * 1000.0) {
video.currentTime -= 0.016;
} else {
video.currentTime = strt * 1000.0;
f = false;
}
} else if (video.currentTime <= stp * 1000.0) {
video.currentTime += 0.016;
} else {
video.currentTime = stp * 1000.0;
f = true;
}
setTimeout(() => requestAnimationFrame(loop), rate);
});
}

function stopForward() {
clearInterval(intervalForward);
}

function stopBack() {
clearInterval(intervalBackward);
}

function stopBackForth() {
clearInterval(intervalLoop);
}

let playing = true;

function handleKeydown(e) {
e.preventDefault();
if (e.code === 'Space') {
if (playing) {
video=document.querySelector("#mvi");
video.pause();
playing = false;
} else {
video=document.querySelector("#mvi");
video.play();
playing = true;
}
} else if (e.code === 'KeyW') {
video=document.querySelector("#mvi");
video.pause();
forward();
} else if (e.code === 'KeyS') {
video=document.querySelector("#mvi");
video.pause();
back();
} else if (e.code === 'KeyZ') {
video=document.querySelector("#mvi");
video.pause();
let ends = video.currentTime / 1000.0;
let begins = (video.currentTime - 2.5) / 1000.0;
let fps = 1000.0 / video.frameRate;
backForth(ends, begins, fps);
} else if (e.code === 'KeyX') {
video=document.querySelector("#mvi");
video.play();
stopBackForth();
}
}

function handleKeyup(e) {
if (e.code === 'KeyS') {
stopBack();
video=document.querySelector("#mvi");
video.pause();
} else if (e.code === 'KeyW') {
stopForward();
video=document.querySelector("#mvi");
video.pause();
}
}

body.addEventListener('keydown', handleKeydown);
body.addEventListener('keyup', handleKeyup);

let $h,$pt,slt,$ll,r$,$w,$r,$lt,$hg,$ls,lo,mv,he,wi;

const $iwid=document.querySelector('#iwid');
var mV=document.querySelector('#mvi');
var loadV=document.querySelector('#ldv');
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
txxt=txxt.replace('https://noahcohn.com/','');
$vids[i]=basePath+'video/'+txxt;
$vids[i]='https://noahcohn.com/video/'+txxt;
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

document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#ihig').innerHTML=parseInt(window.innerHeight,10);

if(media_mode=='vid'){
document.querySelector('#mvi').load();
document.querySelector('#ldv').load();
}

const tem=document.querySelector('#tim');
const ban=document.querySelector('#menuBtn');
const sfr=document.querySelector('#slideframe');

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
document.querySelector('#ihid').innerHTML=hii;
r$=hii/he;
$w=wi*r$;
const $ihigB=document.querySelector('#ihid');
const $ihig=document.querySelector('#ihig');
$hg=hii+'px';
$ihig.innerHTML=parseInt(window.innerHeight,10);
$iwid.innerHTML=parseInt($w,10);
document.querySelector('#wrap').style.lineheight=$hg;
document.querySelector('#wrap').style.pointerEvents='auto';
document.querySelector('#isrc').innerHTML=adr;
if(media_mode=='vid'){
mV.play();
}
var vv=document.querySelector('#mvi');
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

function loada(){
if(lockVid!=1){
// document.querySelector('#ldv').style.height=window.innerHeight+'px';
// document.querySelector('#ldv').style.width='auto';
// document.querySelector('#mvi').style.height=window.innerHeight+'px';
// document.querySelector('#mvi').style.width='auto';
if(media_mode=='vid'){
mV.addEventListener('canplay',function(){
// mV.width=this.videoWidth;
// mV.height=this.videoHeight;
});
loadV.addEventListener('canplay',function(){
// loadV.width=this.videoWidth;
// loadV.height=this.videoHeight;
document.querySelector('#wid').innerHTML=this.videoWidth;
document.querySelector('#hig').innerHTML=this.videoHeight;
document.querySelector('#blnnk').innerHTML=Math.max((this.videoWidth-this.videoHeight)/2.0,0);
var $sc=this.duration;
var mic=Math.round($sc*1000000);
$pt=Math.random()*mic;
$pt=$pt*1000000;
$pt=$pt/1000000;
$pt=Math.round($pt);
$pt=$pt/1000000;
document.querySelector('#idur').innerHTML=mic/1000000;
document.querySelector('#itim').innerHTML=$pt;
});
}
if(media_mode=='img'){
mV.addEventListener('load',function(){
});
loadV.addEventListener('load',function(){
document.querySelector('#wid').innerHTML=this.videoWidth;
document.querySelector('#hig').innerHTML=this.videoHeight;
document.querySelector('#blnnk').innerHTML=Math.max((this.videoWidth-this.videoHeight)/2.0,0);
});
}
if(media_mode=='vid'){
var vide=document.querySelectorAll('video');
}
if(media_mode=='img'){
var vide=document.querySelector('#images').querySelectorAll('img');
}
document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
hii=window.innerHeight;
document.querySelector('#ihid').innerHTML=hii;
$lt=Math.round(tem.innerHTML);
var $ldt=document.querySelector('#tim').innerHTML;
$ls=$lt/1000;
$ls=$ls*1000;
$ls=Math.round($ls);
$ls=$ls/1000;
var rnum=Math.floor((Math.random()*($vids[0]-5))+5);
document.querySelector('#isrc').innerHTML=$vids[rnum];
$h=window.innerHeight;
he=document.querySelector('#hig').innerHTML;
wi=document.querySelector('#wid').innerHTML;
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
document.querySelector('#mvi').play();
}
$iwid.innerHTML=parseInt($w,10);
$ihig.innerHTML=parseInt(window.innerHeight,10);  
document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#circle').height=parseInt(window.innerHeight,10);
document.querySelector('#circle').width=parseInt(window.innerWidth,10);
document.querySelector('#ldv').src=document.querySelector('#isrc').innerHTML;
document.querySelector('#mvi').height=window.innerHeight;
document.querySelector('#ldv').height=window.innerHeight;
if(media_mode=='img'){
document.querySelector('#mvi').height=window.innerHeight;
document.querySelector('#ldv').height=window.innerHeight;
}
if(media_mode=='vid'){
document.querySelector('#ldv').load();
document.querySelector('#ldv').currentTime=document.querySelector('#itim').innerHTML;
}
document.querySelector('#di').click();
}
setTimeout(function(){
loada();
},$ldt);
}

document.querySelector('#startBtn').addEventListener('click',function(){
scanVideos();
setTimeout(function(){
loada()},2200);
});


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



function B3_Start(){
let frameBufferViewF32 = [];
const vvi=document.querySelector('#mvi');
let vw$=vvi.videoWidth;
let vh$=vvi.videoHeight;
let SiZ=window.innerHeight;
vvi.height=vh$;
vvi.width=vw$;
let srsiz=document.querySelector('#srsiz').innerHTML;
let vsiz=document.querySelector('#vsiz').innerHTML;
if(running==0){
setTimeout(function(){
Module.ccall("startWebGPUi",null,["Number","Number","Number"],[vsiz,vsiz,srsiz]);
console.log('Starting..');
frameBufferViewF32 = Module.getPixelBufferView();
running=1;
},250);
}else{
setTimeout(function(){
Module.ccall("startWebGPUbi",null,["Number","Number","Number"],[vsiz,vsiz,srsiz]);
console.log('Starting..');
frameBufferViewF32 = Module.getPixelBufferView();
},250);
}

let w$=parseInt(document.querySelector("#wid").innerHTML,10);
let h$=parseInt(document.querySelector("#hig").innerHTML,10);
let blank$$=parseInt(document.querySelector("#blnnk").innerHTML,10);
let ch$=parseInt(window.innerHeight,10);
let vv=document.querySelector("#mvi");
let $H=Module.HEAPF64.buffer;

function nearestPowerOf2(n){
if(n&(n-1)){
return Math.pow(2,Math.ceil(Math.log2(n)));
}else{
return n;
}
}

let la=nearestPowerOf2((((h$+(blank$$*2))*h$*4)/4)*4);
let pointa=77*la;
const agav=new Float64Array($H,pointa,300);
let sz=(h$*h$)/8;
let blank$=Math.max((w$-h$)/4,0);
let nblank$=Math.max((h$-w$)/2,0);
var avag=0.750;
var min=1.0;
var max=0.0;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
const bcanvas=document.querySelector("#bcanvas");
const scanvas=document.querySelector("#scanvas");
bcanvas.height=window.innerHeight;
bcanvas.width=window.innerWidth;
scanvas.height=window.innerHeight;
scanvas.width=window.innerWidth;
const contx=bcanvas.getContext("webgl2",{colorType:'float64',precision:'highp',colorSpace:'display-p3',alpha:true,depth:true,stencil:true,preserveDrawingBuffer:false,premultipliedAlpha:false,desynchronized:false,lowLatency:false,powerPreference:'high-performance',antialias:true,willReadFrequently:false});
/*  new ext list
contx.getExtension('ARB_robust_buffer_access_behavior');
// contx.getExtension('ARB_ES3_compatibility');
// contx.getExtension('GL_EXTENSIONS');
// contx.getExtension('GL_ALL_EXTENSIONS');
// contx.getExtension('KHR_no_error');
// contx.getExtension('GL_REGAL_enable');
// contx.getExtension('OES_fragment_precision_high'); // deprecated
contx.getExtension('EGL_EXT_client_extensions');
contx.getExtension('EGL_ANGLE_platform_angle');
contx.getExtension('EXT_color_buffer_float'); // GLES float
contx.getExtension('EXT_color_buffer_half_float'); // GLES half-float
contx.getExtension('EXT_float_blend'); // GLES float
contx.getExtension('OES_blend_equation_separate');
contx.getExtension('OES_blend_func_separate');
contx.getExtension('OES_blend_subtract');
// contx.getExtension('ARB_texture_float'); // OpenGL 1.5/2.0
contx.getExtension('OES_texture_float');
// contx.getExtension('ARB_compatibility');
// contx.getExtension('ARB_texture_half_float'); // OpenGL 1.5/2.0
contx.getExtension('OES_texture_half_float');
contx.getExtension('OES_element_index_uint');
contx.getExtension('OES_shader_multisample_interpolation');
contx.getExtension('ARB_framebuffer_object');
contx.getExtension('ARB_framebuffer_sRGB');
contx.getExtension('NV_half_float');
contx.getExtension('ARB_fragment_program');
contx.getExtension('NV_fragment_program_option');
contx.getExtension('NV_fragment_program');
contx.getExtension('NV_fragment_program2');
contx.getExtension('NV_float_buffer');
contx.getExtension('ARB_gl_spirv');
contx.getExtension('ARB_spirv_extensions');
contx.getExtension('EXT_polygon_offset_clamp');
contx.getExtension('ARB_shader_atomic_counters');
contx.getExtension('ARB_shader_atomic_counter_ops');
contx.getExtension('EGL_NV_coverage_sample');
contx.getExtension('EGL_NV_coverage_sample_resolve');
contx.getExtension('EGL_NV_quadruple_buffer');
contx.getExtension('ARB_depth_buffer_float');
contx.getExtension('NV_depth_buffer_float');
// contx.getExtension('ARB_color_buffer_float'); // non-ES
// contx.getExtension('ARB_color_buffer_half_float'); // non-ES
contx.getExtension('OES_sample_shading');
contx.getExtension('OES_sample_variables');
contx.getExtension('OES_get_program_binary');
contx.getExtension('OES_texture_external');
contx.getExtension('OES_vertex_half_float');
contx.getExtension('EGL_IMG_context_priority');
contx.getExtension('EXT_texture_filter_anisotropic');
contx.getExtension('EGL_NV_context_priority_realtime');
contx.getExtension('EGL_NV_depth_nonlinear');
contx.getExtension('EGL_HI_colorformats');
contx.getExtension('EGL_EXT_pixel_format_float');
contx.getExtension('EGL_KHR_gl_colorspace');
contx.getExtension('EGL_KHR_create_context');
// contx.getExtension('ARB_robustness'); // OpenGL 1.1
// contx.getExtension('KHR_robustness'); // upgraded by gl4.5 to es31
// contx.getExtension('EXT_robustness'); // old GLES 1.1/2.0
contx.getExtension('EGL_EXT_create_context_robustness');
contx.getExtension('EGL_EXT_gl_colorspace_scrgb');
contx.getExtension('EGL_EXT_gl_colorspace_scrgb_linear');
// contx.getExtension('EGL_EXT_gl_colorspace_bt2020_pq');
// contx.getExtension('EGL_EXT_gl_colorspace_display_p3');
// contx.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
// contx.getExtension('EXT_gl_colorspace_display_p3_passthrough');
// contx.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
contx.getExtension('NV_gpu_shader4');
contx.getExtension('NV_gpu_shader5');
contx.getExtension('NV_vertex_buffer_unified_memory');
contx.getExtension('NV_gpu_program5');
contx.getExtension('NV_vertex_attrib_integer_64bit');
contx.getExtension('ARB_gpu_shader_fp64');
contx.getExtension('EXT_vertex_attrib_64bit');
contx.getExtension('EXT_sRGB_write_control');
// contx.getExtension('EXT_multisample_compatibility');
contx.getExtension('NV_framebuffer_multisample');
contx.getExtension('ARB_enhanced_layouts');
contx.getExtension('ARB_shading_language_420pack');
// contx.getExtension('ARB_get_program_binary'); // OpenGL 3.0 / 3.2 compat
contx.getExtension('ARB_shader_atomic_counters');
contx.getExtension('EXT_bindable_uniform');
// contx.getExtension('EXT_geometry_shader4');
// contx.getExtension('ARB_ES2_compatibility'); // limits to OpenGL ES 2.0?
contx.getExtension('ARB_direct_state_access');
contx.getExtension('ARB_multitexture');
// contx.getExtension('KHR_color_buffer_half_float');
contx.getExtension('EXT_texture_norm16');
contx.getExtension('EGL_ANGLE_create_context_extensions_enabled');
contx.getExtension('EGL_ANGLE_d3d_texture_client_buffer');
contx.getExtension('EGL_ANGLE_direct3d_display');
// contx.getExtension('EGL_ANGLE_robust_resource_initialization');
contx.getExtension('EGL_KHR_create_context_no_error');
contx.getExtension('EGL_ANGLE_program_cache_control');
contx.getExtension('EGL_ANGLE_create_context_client_arrays');
contx.getExtension('EGL_CHROMIUM_create_context_bind_generates_resource');
contx.getExtension('WEBGL_multi_draw');
// contx.getExtension('WEBGL_color_buffer_float');
contx.getExtension('WEBGL_render_shared_exponent');
contx.getExtension('EGL_EXT_device_base');
contx.getExtension('EGL_EXT_device_query');
contx.getExtension('EGL_EXT_output_base');
contx.getExtension('EGL_EXT_platform_base');
contx.getExtension('EGL_EXT_platform_device');
contx.getExtension('EGL_EXT_swap_buffers_with_damage');
contx.getExtension('EGL_NV_cuda_event');
contx.getExtension('EGL_NV_device_cuda');
// contx.getExtension('EGL_NV_robustness_video_memory_purge');
contx.getExtension('ARB_texture_view');
contx.getExtension('EXT_float_32_packed_float');
contx.getExtension('EGL_KHR_wait_sync');
contx.getExtension('EGL_ANDROID_image_native_buffer');
contx.getExtension('EGL_ANDROID_recordable');
contx.getExtension('EGL_ANDROID_framebuffer_target');
contx.getExtension('EGL_ANDROID_blob_cache');
contx.getExtension('EGL_KHR_fence_sync');
contx.getExtension('EGL_ANDROID_native_fence_sync');
contx.getExtension('EGL_KHR_image');
// contx.getExtension('EGL_KHR_image_base');
contx.getExtension('OES_EGL_image_external');
contx.getExtension('OES_EGL_image_external_essl3');
contx.getExtension('EXT_YUV_target');
// contx.getExtension('ARB_texture_rgb10_a2ui');
// contx.getExtension('ARB_texture_multisample');
contx.getExtension('EGL_EXT_surface_SMPTE2086_metadata');
//  contx.getExtension('ARB_texture_storage'); //  NEW 4.2??
contx.getExtension('ARB_multisample_texture');
contx.getExtension('ARB_texture_cube_map_array');
contx.getExtension('ARB_texture_buffer_object');
contx.getExtension('ARB_texture_view');
contx.getExtension('ARB_shader_storage_buffer_object');
contx.getExtension('ARB_compute_shader');
contx.getExtension('ARB_tessellation_shader');
contx.getExtension('ARB_draw_elements_base_vertex');
contx.getExtension('ARB_provoking_vertex');
contx.getExtension('ARB_seamless_cube_map_per_texture');
contx.getExtension('ARB_texture_compression_rgtc');
contx.getExtension('ARB_texture_compression_bptc');
contx.getExtension('ARB_texture_compression_astc');
contx.getExtension('ARB_texture_filter_minmax');
contx.getExtension('ARB_depth_texture');
//  contx.getExtension('ARB_multisample'); // OLD 2001!!
contx.getExtension('ARB_framebuffer_multisample');
//  contx.getExtension('ARB_shader_objects'); // OLD 2004!!
contx.getExtension('OES_vertex_array_object');
contx.getExtension('WEBGL_compressed_texture_s3tc');
contx.getExtension('WEBGL_compressed_texture_etc');
contx.getExtension('EXT_blend_func_extended');
contx.getExtension('EGL_KHR_swap_behavior');
contx.getExtension('EXT_sRGB');
contx.getExtension('EXT_texture_sRGB');
contx.getExtension('ARB_buffer_storage');
contx.getExtension('ARB_enhanced_multisample_interpolation');
contx.getExtension('ARB_texture_storage_multisample');
contx.getExtension('EXT_texture_lod_bias');
contx.getExtension('ARB_shader_image_load_store');
contx.getExtension('ARB_shader_bit_arithmetic');
contx.getExtension('ARB_shader_texture_adodge');
contx.getExtension('ARB_shader_texture_lod');
contx.getExtension('ARB_shader_subroutine');
contx.getExtension('EGL_EXT_buffer_age');
contx.getExtension('EGL_EXT_multisample_swap_control');
contx.getExtension('EGL_EXT_texture_format_2D_lock');
contx.getExtension('EGL_EXT_texture_share_group');
contx.getExtension('EGL_EXT_texture_surface');
contx.getExtension('ARB_texture_filter_minmax_hq');
contx.getExtension('EXT_texture_compression_astc');
contx.getExtension('ARB_texture_gather');
contx.getExtension('EXT_texture_buffer');
contx.getExtension('EGL_EXT_swap_request');
contx.getExtension('EGL_EXT_image_transform');
contx.getExtension('EGL_EXT_surface_orientation');
contx.getExtension('EGL_EXT_surface_pixel_format_float');
contx.getExtension('EGL_EXT_create_surface_with_modifiers');
contx.getExtension('ARB_pipeline_statistics_query');
contx.getExtension('ARB_occlusion_query2');
contx.getExtension('ARB_timer_query');
contx.getExtension('ARB_transform_feedback3');
contx.getExtension('EXT_shader_framebuffer_fetch_nonms');
contx.getExtension('EGL_EXT_swap_buffers_with_damage');
contx.getExtension('EGL_EXT_create_context_with_modifiers');
contx.getExtension('EGL_EXT_request_priority');
contx.getExtension('EGL_EXT_create_surface_from_window');
contx.getExtension('EGL_EXT_surface_attachment');
contx.getExtension('EXT_texture_storage');
 // 'new' ext list

//  'old' ext list
gl.getExtension('WEBGL_color_buffer_float');
gl.getExtension('WEBGL_color_buffer_half_float');
gl.getExtension('GL_OES_texture_float_linear');
gl.getExtension('GL_OES_texture_half_float_linear');
gl.getExtension('GL_EXT_float_blend');
gl.getExtension('GL_EXT_frag_depth');
gl.getExtension('GL_EXT_shader_texture_lod');
gl.getExtension('GL_EXT_sRGB');
gl.getExtension('GL_EXT_blend_minmax');
gl.getExtension('ANGLE_instanced_arrays');
// gl.getExtension('EXT_disjoint_timer_query');
gl.getExtension('GL_EXT_clip_cull_distance');
// gl.getExtension('EXT_disjoint_timer_query_webgl2');
gl.getExtension('KHR_parallel_shader_compile');
gl.getExtension('GL_OES_draw_buffers_indexed');
gl.getExtension('GL_OES_element_index_uint');
gl.getExtension('GL_OES_fbo_render_mipmap');
gl.getExtension('GL_OES_standard_derivatives');
gl.getExtension('GL_OES_vertex_array_object');
gl.getExtension('WEBGL_blend_equation_advanced_coherent');
gl.getExtension('WEBGL_depth_texture');
gl.getExtension('WEBGL_draw_buffers');
gl.getExtension('WEBGL_provoking_vertex');
gl.getExtension('EXT_framebuffer_sRGB');
gl.getExtension('OES_depth32');
gl.getExtension('GL_OES_fixed_point');
gl.getExtension('GL_OES_shader_multisample_interpolation');
gl.getExtension('WEBGL_webcodecs_video_frame');
gl.getExtension('GL_OES_single_precision');
// gl.getExtension('GL_EXT_texture_shadow_lod');
gl.getExtension('EGL_NV_memory_attachment');
gl.getExtension('EGL_NV_depth_nonlinear');
gl.getExtension('EGL_EXT_gl_colorspace_display_p3');
gl.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
gl.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
gl.getExtension('GL_ARB_multisample');

contx.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
contx.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
// contx.blendColor(1.0,1.0,1.0,1.0);
// contx.blendColor(1.0,1.0,1.0,0.0);
// contx.blendColor(0.0,0.0,0.0,1.0);
// contx.blendColor(0.0,0.0,0.0,0.0);
 // contx.blendColor(0.0,0.0,0.0,0.5);
  // contx.blendColor(1.0,1.0,1.0,1.0);
contx.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
// contx.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
  // contx.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.ONE_MINUS_SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
// contx.blendEquationSeparate(gl.FUNC_ADD,gl.MAX);
contx.blendEquationSeparate(gl.FUNC_ADD,gl.FUNC_SUBTRACT);
// contx.blendEquationSeparate(gl.FUNC_ADD,gl.FUNC_REVERSE_SUBTRACT);
contx.disable(gl.DITHER);
// contx.drawingBufferColorMetadata={mode:'extended'};
// contx.drawingBufferColorSpace='display-p3';
*/

const g=new GPUX({canvas:bcanvas,context:contx});
const g2=new GPUX();
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslSilver=`float Silver(float a){return((a+0.75+0.75+((a+0.75)/2.0))/4.0);}`;
const glslGoldR=`float GoldR(float a){return((a+0.831+0.831+0.831+((a+0.831)/2.0))/5.0);}`;
const glslGoldG=`float GoldG(float a){return((a+0.686+0.686+0.686+((a+0.686)/2.0))/5.0);}`;
const glslGoldB=`float GoldB(float a){return((a+0.215+0.215+0.215+((a+0.215)/2.0))/5.0);}`;

const glslAlphe1=`float AlpheV1(float a,float b,float c,float d,float e,float f,float g){return((0.7+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/4.0);}`;
// const glslAlphe1=`float AlpheV1(float a,float b,float c,float d,float e,float f,float g){return((0.7+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/3.0);}`;
// const glslAlphe1=`float AlpheV1(float a,float b,float c,float d,float e,float f,float g){return((g+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/4.0);}`;
// const glslAlphe1=`float AlpheV1(float a,float b,float c,float d,float e,float f,float g){return((g+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;

const glslAlphe2=`float AlpheV2(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;

g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('AlpheV2',glslAlphe2,{returnType:'Number'});
g.addNativeFunction('AlpheV1',glslAlphe1,{returnType:'Number'});
g.addNativeFunction('Silver',glslSilver,{returnType:'Number'});
g.addNativeFunction('GoldR',glslGoldR,{returnType:'Number'});
g.addNativeFunction('GoldG',glslGoldG,{returnType:'Number'});
g.addNativeFunction('GoldB',glslGoldB,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});

let t, r, R;

var select=document.querySelector('#b3');
var vid_mode=select.value;
var select2=document.querySelector('#media');
var media_mode=select2.value;
if(vid_mode=='B3'){
R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setImmutable(true).setTactic("speed").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setOptimizeFloatMemory(true).setOutput([sz]);
t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x+this.constants.blnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
}).setImmutable(true).setTactic("precision").setPipeline(true).setPrecision('single').setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([1024,1024]); // h$,h$]);
r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=AlpheV1($amax,$amin,$fmax,$fmin,$favg,$aavg,p[3]);
// var alph=AlpheV2($amax,$amin,$aavg,p[3]);
var Min=((p[3]-$favg)+1.0101)*(($amax-($aavg-$fmin-($amin-$fmin)))/(2.0+($aavg-p[3])));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
return [p[0]/255.0,p[1]/255.0,p[2]/255.0,aveg/255.0];
}).setImmutable(true).setTactic("precision").setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([h$,h$]);
}
if(vid_mode=='B3_B'){
R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setImmutable(true).setTactic("speed").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setOptimizeFloatMemory(true).setOutput([sz]);
t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x+this.constants.blnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
}).setImmutable(true).setTactic("precision").setPipeline(true).setPrecision('single').setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([h$,h$]);
r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=AlpheV1($amax,$amin,$fmax,$fmin,$favg,$aavg,p[3]);
// var alph=AlpheV2($amax,$amin,$aavg,p[3]);
var Min=2.0101*(($amax-($aavg-$fmin))/2.0);
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
return [p[0]/255.0,p[1]/255.0,p[2]/255.0,aveg/255.0];
// }).setImmutable(true).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([h$,h$]);
}).setImmutable(true).setTactic("precision").setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([h$,h$]);
}
if(vid_mode=='Video'){
if(media_mode=='vid'){
R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setImmutable(true).setTactic("speed").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setOptimizeFloatMemory(true).setOutput([sz]);
t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x+this.constants.blnk];
return[P[0],P[1],P[2],P[3]];
}).setImmutable(true).setTactic("precision").setPipeline(true).setPrecision('single').setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([1024,1024]); // h$,h$]);
r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x];
return [p[0]/255,p[1]/255,p[2]/255,p[3]/255];
// }).setImmutable(true).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([h$,h$]);
}).setImmutable(true).setTactic("precision").setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([1024,1024]); // h$,h$]);
}
if(media_mode=='img'){
R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setImmutable(true).setTactic("speed").setDynamicOutput(true).setArgumentTypes(["HTMLImage"]).setOptimizeFloatMemory(true).setOutput([sz]);
t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x+this.constants.blnk];
return[P[0],P[1],P[2],P[3]];
}).setImmutable(true).setTactic("precision").setPipeline(true).setPrecision('single').setArgumentTypes(["HTMLImage"]).setDynamicOutput(true).setOutput([h$,h$]);
r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x];
return [p[0]/255.0,p[1]/255.0,p[2]/255.0,p[3]/255.0];
// }).setImmutable(true).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([h$,h$]);
}).setImmutable(true).setTactic("precision").setArgumentTypes(["HTMLImage"]).setDynamicOutput(true).setOutput([h$,h$]);
}
}
w$=parseInt(document.querySelector("#wid").innerHTML,10);
h$=parseInt(document.querySelector("#hig").innerHTML,10);
blank$$=parseInt(document.querySelector("#blnnk").innerHTML,10);
vv=document.querySelector("#mvi");
blank$=Math.max((w$-h$)/4,0);
nblank$=Math.max((h$-w$)/2,0);
la=nearestPowerOf2((((h$+(blank$$*2))*h$*4)/4)*4);
sz=(h$*h$)/8;
pointa=77*la;
// agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
}
var pointb=77*la;
var $B=new Float64Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$$});
var $$1=t(vv);
for (i=0;i<65;i++){
var j=i+1;
eval("$"+j+".set($$1);");
}
var d=S();if(d)d();d=S();function S(){
w$=parseInt(document.querySelector("#wid").innerHTML,10);
h$=parseInt(document.querySelector("#hig").innerHTML,10);
blank$$=parseInt(document.querySelector("#blnnk").innerHTML,10);
blank$=Math.max((w$-h$)/4,0);
nblank$=Math.max((h$-w$)/2,0);
la=nearestPowerOf2((((h$+(blank$$*2))*h$*4)/4)*4);
sz=(h$*h$)/8;
pointa=77*la;
pointc=88*la;
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
}
pointb=66*la;
$B=new Float64Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$$});
var T=false;
function M(){
vv=document.querySelector("#mvi");
r.setConstants({nblnk:nblank$,blnk:blank$$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$$});
if(T){return;}
for(i=64;i>0;i--){
var loca=$F+1;if(loca>64){loca=1;}
var locb=$Bu+1;if(locb>64){locb=1;}

eval("if ($F==="+i+"){var $r"+i+"=t($"+i+");var frmm=new Float64Array($H,pointc,la); frmm.set( r($r"+i+") );  var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+");$F="+loca+";$Bu="+locb+";}");
}

var $bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;

const inputDataView = $B; // Or new Float64Array($H, pointb, sz);
const averageDataView = agav; // Or new Float64Array($H, pointa, 300);
// ** Calculate the byte offsets **
const ptr_offset = inputDataView.byteOffset;
const aptr_offset = averageDataView.byteOffset;
// ** Call the bound function using numerical offsets **
Module.nanoD_unsafe($F, sz, ptr_offset, aptr_offset);
setTimeout(function(){
let offset = 0;
if(frmm[0][0]){
for (let y = 0; y < h$; y++) {
for (let x = 0; x < h$; x++) {
frameBufferViewF32[offset++] = frmm[y][x][0]; // R
frameBufferViewF32[offset++] = frmm[y][x][1]; // G
frameBufferViewF32[offset++] = frmm[y][x][2]; // B
frameBufferViewF32[offset++] = frmm[y][x][3]; // A
}
}
}
M();
},16.66);
}
M();
document.querySelector("#di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
}
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
// videoStart();
B3_Start();
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
