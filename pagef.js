
var tsl,slt,$ll,$h,wi,r$,$w,$r,$hi,$lt,rnum,$sc,$rn,$ls,lo,mv,vide,he,$pt,randSong;

var $iwid=document.getElementById("iwid");
let $sngs=[];
let $shds=[];

function sngs(xml){
var nparser=new DOMParser();
var htmlDoc=nparser.parseFromString(xml.responseText,'text/html');
var preList=htmlDoc.getElementsByTagName("pre")[0].getElementsByTagName("a");
$sngs[0]=preList.length;
console.log('Number of songs: '+$sngs[0]);
for (var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxt=txxt.replace(Self,"");
$sngs[i]=Self+"songs/"+txxt;
}}

function shds(xml){
var sparser=new DOMParser();
var htmlDoc=sparser.parseFromString(xml.responseText,'text/html');
var preList=htmlDoc.getElementsByTagName("pre")[0].getElementsByTagName("a");
$shds[0]=preList.length;
console.log('Number of shaders: '+$shds[0]);
for (var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxt=txxt.replace(Self,"");
$shds[i+1]=Self+"all/"+txxt;
}
var randShade=Math.random();
randShade=Math.floor($shds[0]*randShade)+5;
console.log('Random shader: #'+randShade+' '+$shds[randShade]);
document.getElementById("path").innerHTML=$shds[randShade];
}

function scanSongs(){
var nxhttp=new XMLHttpRequest();
nxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
sngs(this);
}};
nxhttp.open("GET","songs/",true);
nxhttp.send();
}

function scanShaders(){
var dxhttp=new XMLHttpRequest();
dxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
shds(this);
}};
dxhttp.open("GET","all/",true);
dxhttp.send();
}

scanShaders();
scanSongs();
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById("scanvas").height=parseInt(window.innerHeight,10);
document.getElementById("scanvas").width=parseInt(window.innerHeight,10);

document.getElementById('btnSng').addEventListener('click',function(){
setTimeout(function(){document.getElementById("btn3").click();},300);
setTimeout(function(){document.getElementById("btn8").click();},2000);
});

function snd(){
randSong=Math.floor(($sngs[0]-5)*Math.random());
console.log('Random song: #'+randSong+' '+$sngs[randSong+5]);
var songSrc=$sngs[randSong+5];
// document.getElementById("track").src=songSrc;
let sng=new BroadcastChannel('sng');
sng.postMessage({
data:songSrc
});
// var sound=new Howl({src:[songSrc],volume:1,onend:function(){snd();}});
// sound.play();
}
document.getElementById('btn8').addEventListener('click',function(){
snd();
});
const tem=document.getElementById("tim");
ban=document.getElementById("btn1");
const sfr=document.getElementById("slideframe");
function grab$lt(){
$lt=Math.round($lt);}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({"panel":document.getElementById("panel"),"menu":document.getElementById("menu"),"padding":384,"tolerance":70,"easing":"cubic-bezier(.32,2,.55,.27)"});
ban.addEventListener("click",function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
tsl=new rSlider({target:"#timeslider",values:{min:1.00,max:45.00},
step:[0.50],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById("menu").addEventListener("click",function(){
$ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});
setTimeout(function(){
slt=tem.innerHTML;
},8);},16);});

// setTimeout(function(){document.getElementById("btn2").click();},200);
// setTimeout(function(){document.getElementById("btn11").click();},900);
// setTimeout(function(){document.getElementById("btn").click();},1300);
// setTimeout(function(){document.getElementById("btn10").click();},2200);
setTimeout(function(){document.getElementById("btn3").click();},300);
setTimeout(function(){document.getElementById("btn8").click();},2000);

