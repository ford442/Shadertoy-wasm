function rrr(){
var pth='https://1ink.us/files/OverNet.onnx';
console.log("Getting ONNX model...");
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
ff.addEventListener("progress",function(event){
if(event.lengthComputable){
var complete=(event.loaded/event.total*100|0);
document.getElementById('outText').innerHTML=complete;
};});
ff.onload=function(oEvent){
const sarrayBuffer=ff.response;
if(sarrayBuffer){
const sfil=new Uint8ClampedArray(sarrayBuffer);
setTimeout(function(){
console.log("Got ONNX model.");
FS.writeFile('/model.onnx',sfil);
},1150);
};};
ff.send(null);
};

document.getElementById('startBtn3').addEventListener('click',function(){
rrr();
});
