@group(0)@binding(0)var<storage,read>inputBuffer:array<u32,262144>;
@group(0)@binding(1)var<storage,read_write>outputBuffer:array<u32,262144>;
@group(0)@binding(2)var textureA:texture_storage_2d<rgba32uint,write>;
@compute@workgroup_size(4,1,64)
fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>){
let f:u32=global_id.x*4*global_id.y;
for(var e:u32=0;e<65546;e++){
var m=e*4;
outputBuffer[m]=inputBuffer[0];
outputBuffer[m+1]=0;
outputBuffer[m+2]=255-inputBuffer[0];
outputBuffer[m+3]=255;
}
}
