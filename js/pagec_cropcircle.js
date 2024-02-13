'use strict';

function hiResStart(){
document.getElementById('scanvas').height=window.innerHeight;//*1.333;
document.getElementById('scanvas').width=window.innerHeight;//*1.333;
document.getElementById('pmhig').innerHTML=window.innerHeight;//*1.333;
setTimeout(function(){
Module.ccall('str');},250);
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('pmhig').innerHTML=window.innerHeight;
setTimeout(function(){
Module.ccall('b3');},650);
setTimeout(function(){
const bz=new BroadcastChannel('bez');
bz.postMessage({data:222});},50);
}





var $h,$pt,slt,$ll,r$,$w,$r,$lt,$hg,$ls,lo,mv,he,wi;

const $iwid=document.getElementById('iwid');
var mV=document.getElementById('mv');
var loadV=document.getElementById('ldv');
var $vids=[];
function sngs(xml){
const nparser=new DOMParser();
const htmlDocs=nparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocs.getElementsByTagName('pre')[0].getElementsByTagName('a');
$sngs[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,'');
txxt=txxt.replace(Self,'');
$sngs[i]=Self+'songs/'+txxt;
}};

function vids(xml){
const vparser=new DOMParser();
const htmlDocv=vparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocv.getElementsByTagName('pre')[0].getElementsByTagName('a');
$vids[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,'');
txxt=txxt.replace(Self,'');
$vids[i]=Self+'video/'+txxt;
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

scanVideos();

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
// document.getElementById('mv').load();
// document.getElementById('ldv').load();

const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML='';
setTimeout(function(){
grab$lt();slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
$ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});
setTimeout(function(){slt=tem.innerHTML;},8);},16);});
// var adr='./intro.mp4';
wi=1280;
he=720;
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
mV.play();
var vv=document.getElementById('mv');
var lockVid=0;

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
// document.getElementById('ldv').height=document.innerHeight;
loadV.addEventListener('loaded',function(){
loadV.width=this.imageWidth;
loadV.height=this.imageHeight;
document.getElementById('wid').innerHTML=this.imageWidth;
document.getElementById('hig').innerHTML=this.imageHeight;
document.getElementById('blnnk').innerHTML=Math.max((this.imageWidth-this.imageHeight)/2.0,0);
// document.getElementById('wid').innerHTML=parseInt(window.innerHeight,10);
//document.getElementById('hig').innerHTML=parseInt(window.innerHeight,10);

});
var vide=document.querySelectorAll('image');
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
document.getElementById('ldv').src=document.getElementById('isrc').innerHTML;
// document.getElementById('mv').height=document.innerHeight;
document.getElementById('ldv').height=he;
document.getElementById('ldv').width=wi;
$iwid.innerHTML=parseInt($w,10);
$ihig.innerHTML=parseInt(window.innerHeight,10);
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('circle').height=parseInt(window.innerHeight,10);
document.getElementById('circle').width=parseInt(window.innerWidth,10);
document.getElementById('di').click();
};
setTimeout(function(){
loada();
},$ldt);
}

loada();