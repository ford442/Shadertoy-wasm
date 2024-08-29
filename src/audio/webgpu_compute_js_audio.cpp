song_select song;

extern"C"{

int r4nd(int tH){
Rg=song.rNd(tH);
c=wasm_i32x4_extract_lane(Rg,0);
return c;
}
  
}

EM_JS(void,js_main,(),{

FS.mkdir('/shader');
FS.mkdir('/video');
let running=0;
let vv=document.querySelector('#mv');
let vvi=document.querySelector('#mvi');

function nearestPowerOf2(n){
if(n&(n-1)){
return Math.pow(2,Math.ceil(Math.log2(n)));
}else{
return n;
}
}
  
function flipImageData(imageData) {
const width = imageData.width;
const height = imageData.height;
const data = imageData.data;
for (let y = 0; y < height / 2; y++) {
for (let x = 0; x < width; x++) {
const topIndex = (y * width + x) * 4;
const bottomIndex = ((height - 1 - y) * width + x) * 4;
for (let c = 0; c < 4; c++) {
[data[topIndex + c], data[bottomIndex + c]] = [data[bottomIndex + c], data[topIndex + c]];
}
}
}
return imageData;
}

function pll(){
Module.ccall('pl');
}

const fll=new BroadcastChannel('file');
const shutDown=new BroadcastChannel('shutDown');
  
setTimeout(function(){
window.open('./flac');
},500);
  
setTimeout(function(){
shutDown.postMessage({data:222});
},4000);
  
fll.addEventListener('message',ea=>{
const fill=new Uint8Array(ea.data.data);
FS.writeFile('/snd/sample.wav',fill);
setTimeout(function(){
shutDown.postMessage({data:222});
pll();
},100);
});

var $sngs=[];

function sngs(xml){
const nparser=new DOMParser();
const htmlDocs=nparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocs.getElementsByTagName('pre')[0].getElementsByTagName('a');
$sngs[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/aud.1ink/,"");
txxt=txxt.replace(Self,"");
$sngs[i]=Self+'songs/'+txxt;
}}

function scanSongs(){
const nxhttp=new XMLHttpRequest();
nxhttp.addEventListener("load",function(){
sngs(this);
});
nxhttp.open('GET','songs/',true);
nxhttp.send();
}

function snd(){
var sngsNum=$sngs[0];
const randSong=Module.ccall('r4nd','Number',['Number'],[sngsNum]);
const songSrc=$sngs[randSong+5];
document.getElementById('track').src=songSrc;
const sng=new BroadcastChannel('sng');
sng.postMessage({data:songSrc});
}

document.getElementById('musicBtn').addEventListener('click',function(){
window.open('./flac');
setTimeout(function(){
snd();
},1300);
});

scanSongs();

function videoFrames(){
let vw$=parseInt(document.querySelector("#mvi").videoWidth);
let vh$=parseInt(document.querySelector("#mvi").videoHeight);
let SiZ=window.innerHeight;
vvi.height=SiZ;
let w$=parseInt(document.querySelector("#mvi").videoWidth);
let h$=parseInt(document.querySelector("#mvi").videoHeight);
let tstSiZ=720;
if(running==0){
// Module.ccall("frm",null,['Number'],['Number'],h$,h$);
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz]);
  console.log('Starting..');
running=1;
},500);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#canvas');
cnv.height=tstSiZ;
cnvb.height=SiZ;
cnv.width=tstSiZ;
cnvb.width=SiZ;
var ratio=SiZ/h$;
let offS=Math.floor((w$-h$)/2);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
const gl2=cnv.getContext('2d',{alpha:true}); // 
gl2.drawImage(vvi,offS,0,tstSiZ,tstSiZ,0,0,tstSiZ,tstSiZ);
let image=gl2.getImageData(0,0,tstSiZ,tstSiZ);
// let mageData=flipImageData(image);
let imageData=image.data;
let pixelData=new Uint8ClampedArray(imageData);
FS.writeFile('/video/frame.gl',pixelData);
setInterval(function(){
gl2.drawImage(vvi,offS,0,tstSiZ,tstSiZ,0,0,tstSiZ,tstSiZ);
image=gl2.getImageData(0,0,tstSiZ,tstSiZ);
imageData=image.data;
pixelData=new Uint8ClampedArray(imageData,0,la);
FS.writeFile('/video/frame.gl',pixelData);
},16.6);
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
var pth2=document.querySelector('#computePath').innerHTML;
getShader(pth2,'compute.wgsl');
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
normalResStart();
},1000);
});

function normalResStart(){
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
// videoFrames();
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz]);
},1500);
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
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();
slt=($lt/1000);
slt=slt*100;
slt=Math.round(slt);
slt=slt/100;
tsl.setValues(slt);
document.querySelector('#menu').addEventListener('click',function(){
$ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;$ll=($ll*1000);
tem.innerHTML=$ll;
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
getShader(pth2,'compute.wgsl');
// normalResStart();
  console.log('starting ply');
Module.ccall('ply');
});

  
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
},500);
});
