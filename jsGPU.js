
const S=Math.round(document.getElementById('pmhig').innerHTML);
let o=[S,S];
const bcanvas=document.getElementById("bcanvas");
const contx=bcanvas.getContext('webgl2',{
alpha:true,stencil:false,depth:false,preserveDrawingBuffer:false,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',majorVersion:2,minorVersion:0,desynchronized:false});
const v=document.getElementById("mv");
const g=new GPU({canvas:bcanvas,webGl:contx});
const t=g.createKernel(function(v){const P=v[this.thread.y][this.thread.x];const aveg=1.0-((((P[0]+P[1]+P[2])/3)-0.75)*4.0);return[P[0],P[1],P[2],(aveg)];}).setTactic("precision").setPipeline(true).setDynamicOutput(true).setOutput(o);
const r=g.createKernel(function(f){const p=f[this.thread.y][this.thread.x];this.color(p[0],p[1],p[2],p[3]);}).setTactic("precision").setGraphical(true).setDynamicOutput(true).setOutput(o);
let l=(S*S*4);let m=Math.floor((l/65536)+1);
const W1=new WebAssembly.Memory({initial:m});
const W2=new WebAssembly.Memory({initial:m});
const W3=new WebAssembly.Memory({initial:m});
const W4=new WebAssembly.Memory({initial:m});
const W5=new WebAssembly.Memory({initial:m});
const W6=new WebAssembly.Memory({initial:m});
const W7=new WebAssembly.Memory({initial:m});
const W8=new WebAssembly.Memory({initial:m});
const $1=new Uint8ClampedArray(W1.buffer,0,l);
const $2=new Uint8ClampedArray(W2.buffer,0,l);
const $3=new Uint8ClampedArray(W3.buffer,0,l);
const $4=new Uint8ClampedArray(W4.buffer,0,l);
const $5=new Uint8ClampedArray(W5.buffer,0,l);
const $6=new Uint8ClampedArray(W6.buffer,0,l);
const $7=new Uint8ClampedArray(W7.buffer,0,l);
const $8=new Uint8ClampedArray(W8.buffer,0,l);
let Frme=1;
