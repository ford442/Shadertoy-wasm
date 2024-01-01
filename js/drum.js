document.querySelector('#drumBtn').addEventListener('click',function(){
window.open('./drum/o8o.htm');
});

let drumTempo=new BroadcastChannel('tempo');

drumTempo.addEventListener('message',ea=>{
var tmp0=parseInt(ea.data.data);
Module.ccall('tempoSet',null,["Number"],[tmp0]);
});

let drumKick=new BroadcastChannel('kick');

drumKick.addEventListener('message',ea=>{
Module.ccall('kickDrum');
});
