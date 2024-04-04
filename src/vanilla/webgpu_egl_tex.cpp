#include "../../include/vanilla/webgpu_fix.hpp"

char wgl_cmp_src[2000]=
// "@group(0)@binding(0)var <storage,read> inputBuffer: array<f32,64>;\n"
// "@group(0)@binding(1)var <storage,read_write> outputBuffer: array<f32,64>;\n"
"@group(0)@binding(2)var textureIN: texture_2d <f32>;\n"
// "@group(0)@binding(3)var textureOUT: texture_storage_2d <rgba32float,write>;\n"
// "@group(0)@binding(4)var resizeSampler: sampler;\n"
"@group(0)@binding(5)var <uniform> iTime: u32;\n"
"@group(0)@binding(6)var videoOUT: texture_storage_2d <rgba32float,write>;\n"
// "@group(0)@binding(7)var colorOUT: texture_storage_2d <rgba8unorm,write>;\n"
"@compute@workgroup_size(8,8,1)\n"
"fn main_image(@builtin(global_invocation_id)global_id:vec3<u32>){\n"
"var outSizeU:u32=textureDimensions(videoOUT).x;\n"
"var inSizeU:u32=textureDimensions(textureIN).x;\n"
"var sizeRatio:f32=f32(inSizeU)/f32(outSizeU);\n"
"for(var x:u32=0u;x<=outSizeU;x=x+1u){\n"
"var xPos:u32=u32(round((f32(x))*sizeRatio));\n"
"for(var y:u32=0u;y<=outSizeU;y=y+1u){\n"
"var yPos:u32=u32(round((f32(y))*sizeRatio));\n"
"var INtexCoord:vec2<u32>=vec2<u32>(xPos,yPos);\n"
"var color:vec4<f32>=textureLoad(textureIN,INtexCoord,0);\n"
"color.r-=0.000005f;\n"
"color.r+=0.00001f;\n"
"color.g-=0.000005f;\n"
"color.g+=0.00001f;\n"
"color.b-=0.000005f;\n"
"color.b+=0.00001f;\n"
"textureStore(videoOUT,vec2<u32>(x,y),color);\n"
"}\n"
"}\n"
// "outputBuffer[2]=f32(textureDimensions(textureIN).x);\n"
// "outputBuffer[3]=f32(textureDimensions(textureOUT).x);\n"
"}";

#include "../../src/vanilla/webgpu_compute_vars.cpp"

int rNd4(int randomMax){
entropySeed=(randomMax)*randomizer();
std::srand(entropySeed);
randomNumber=std::rand()%randomMax;
return randomNumber;
}

const char * frag_body2 = R"delimiter(
  //   //
@group(0)@binding(0)var videoSampler: sampler;
// @group(0)@binding(1)var textureIN: texture_storage_2d <rgba32float,write>;
@group(0)@binding(2)var videoOUT: texture_2d <f32>;
@group(0)@binding(5)var<uniform> iResolution : u32;
@group(0)@binding(6)var<uniform> iFrame : u32;
@group(0)@binding(7)var<uniform> iTime : u32;
var<private> fragColor_1 : vec4<f32>;
var<private> gl_FragCoord : vec4<f32>;
var<private> iMouse : vec4<f32>;
var<private> iPosition : vec4<f32>;
fn mainImage_vf4_vf2_(fragColor: ptr<function, vec4<f32>>,fragCoord: ptr<function, vec2<f32>>) {
var col : vec3<f32>;
col = vec3<f32>(0.40000000596046447754f, 0.0f, 0.5f);
let x_24 : vec3<f32> = col;
*(fragColor) = vec4<f32>(x_24.x, x_24.y, x_24.z, 1.0f);
//  let b3_col : vec4<f32> = *(fragColor);textureStore(textureIN,vec2<u32>(gl_FragCoord.xy),vec4<f32>(b3_col.rgb,1.0f));
return;}
fn main_1() {
var param : vec4<f32>;
var param_1 : vec2<f32>;
let x_36 : vec4<f32> = gl_FragCoord;
param_1 = vec2<f32>(x_36.x, x_36.y);
mainImage_vf4_vf2_(&(param), &(param_1));
let x_39 : vec4<f32> = param;
let tstcr:vec4<f32>=vec4<f32>(0.3,0.0,0.44,1.0);
let ress:u32=u32(textureDimensions(videoOUT).x);
// fragColor_1=vec4<f32>(textureSample(videoOUT,videoSampler,gl_FragCoord.xy/vec2<f32>(vec2<u32>(ress,ress))));
fragColor_1=vec4<f32>(textureSampleBaseClampToEdge(videoOUT,videoSampler,gl_FragCoord.xy/vec2<f32>(vec2<u32>(iResolution,iResolution))));
return;
}
struct main_out {
@location(0)
fragColor_1_1 : vec4<f32>,
@location(1)
iPosition_1 : vec4<f32>,
}
@fragment
fn main(@builtin(position) gl_FragCoord_param : vec4<f32>) -> main_out {
gl_FragCoord = gl_FragCoord_param;
main_1();
return main_out(fragColor_1, iPosition);
}
  //   //
)delimiter";

const char * vertexShader=
"struct VertexOutput{\n"
"@builtin(position) Position : vec4<f32>,\n"
"@location(0) fragUV : vec2<f32>\n"
"};\n"
"@vertex\n"
"fn main(@builtin(vertex_index) VertexIndex : u32) -> VertexOutput {\n"
"var pos=array<vec2<f32>,6>(\n"
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(1.0f,-1.0f),\n"
"vec2<f32>(-1.0f,-1.0f),\n"
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(-1.0f,-1.0f),\n"
"vec2<f32>(-1.0f,1.0f)\n"
");\n"
"var uv=array<vec2<f32>,6>(\n"
"vec2<f32>(1.0f,0.0f),\n"
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(0.0f,1.0f),\n"
"vec2<f32>(1.0f,0.0f),\n"
"vec2<f32>(0.0f,1.0f),\n"
"vec2<f32>(0.0f,0.0f)\n"
");\n"
"var output : VertexOutput;\n"
"output.Position=vec4(pos[VertexIndex],0.0f,1.0f);\n"
"output.fragUV=uv[VertexIndex];\n"
"return output;\n"
"}\n";

const char * frag_body=
"@group(0) @binding(0) var <uniform> iTime : u32;\n"
"@group(0) @binding(1) var mySampler : sampler;\n"
"@group(0) @binding(2) var myTexture : texture_2d <f32>;\n"
// "@group(0) @binding(3) var extTexture : texture_external;\n"
"@fragment\n"
"fn main(@location(0) fragUV : vec2<f32>) ->\n"
"@location(0) vec4<f32> {\n"
"return textureSample(myTexture,mySampler,fragUV);"
"}\n";

const char * rd_fl(const char * Fnm){
FILE * file=fopen(Fnm,"r");
::boost::tuples::tie(result,results,file);
if(file){
int32_t stat=fseek(file,(int32_t)0,SEEK_END);
if(stat!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
stat=fseek(file,(int32_t)0,SEEK_SET);
if(stat!=0){
fclose(file);
return nullptr;
}
result=static_cast<char *>(malloc((length+1)*sizeof(char)));
if(result){
size_t actual_length=fread(result,sizeof(char),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
return result;
}
return nullptr;
}

void getCode(const char * Fnm){
wgsl.at(0,0)=frag_body;
return;
}

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
return;
};

boost::function<EM_BOOL()>render=[](){
u64_uni.at(3,3)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u64_uni.at(0,0)=u_time.time_spana.count()*100;
u64_uni.at(1,1)=u_time.time_spanb.count()*1000;
// u64_uni.at(2,2)=u_time.time_spanb.count()/1.0f;
colorAttachment={WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER};
colorTexture=wgpu_canvas_context_get_current_texture(wcc.at(0,0));
wt.at(1,1)=colorTexture;
colorTextureView=wgpu_texture_create_view(wt.at(1,1),&wtvd.at(1,1));
wtv.at(1,1)=colorTextureView;
colorAttachment.view=wtv.at(1,1);
colorAttachment.storeOp=WGPU_STORE_OP_STORE; // WGPU_STORE_OP_DISCARD; 
// colorAttachment.loadOp=WGPU_LOAD_OP_LOAD;
colorAttachment.loadOp=WGPU_LOAD_OP_CLEAR;
colorAttachment.clearValue.r=0.0f;
colorAttachment.clearValue.g=0.0f;
colorAttachment.clearValue.b=1.0f;
colorAttachment.clearValue.a=1.0f;
wrpca.at(0,0)=colorAttachment;
INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
wtv.at(3,3)=INTextureView;
videoAttachment={WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER};
videoAttachment.view=wtv.at(3,3);
videoAttachment.storeOp=WGPU_STORE_OP_STORE;
// videoAttachment.loadOp=WGPU_LOAD_OP_LOAD;
videoAttachment.loadOp=WGPU_LOAD_OP_CLEAR;
videoAttachment.clearValue.r=1.0f;
videoAttachment.clearValue.g=1.0f;
videoAttachment.clearValue.b=1.0f;
videoAttachment.clearValue.a=1.0f;
wrpca.at(1,1)=videoAttachment;
videoTextureView=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
wtv.at(2,2)=videoTextureView;
depthAttachment={};
depthAttachment2={};
depthTextureView=wgpu_texture_create_view(wt.at(0,0),&wtvd.at(0,0));
wtv.at(0,0)=depthTextureView;
depthAttachment.view=wtv.at(0,0);
depthAttachment.depthClearValue=1.0f;
depthAttachment.depthReadOnly=EM_FALSE;
depthAttachment.depthLoadOp=WGPU_LOAD_OP_LOAD;
depthAttachment.depthLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment.depthStoreOp=WGPU_STORE_OP_STORE;
depthAttachment.stencilClearValue=0;
depthAttachment.stencilReadOnly=EM_TRUE;
depthAttachment.stencilLoadOp=WGPU_LOAD_OP_LOAD;
// depthAttachment.stencilLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment.stencilStoreOp=WGPU_STORE_OP_STORE;
wrpdsa.at(0,0)=depthAttachment;
depthTextureView2=wgpu_texture_create_view(wt.at(5,5),&wtvd.at(3,3));
wtv.at(5,5)=depthTextureView2;
depthAttachment2.view=wtv.at(5,5);
depthAttachment2.depthClearValue=1.0f;
depthAttachment2.depthReadOnly=EM_FALSE;
depthAttachment2.depthLoadOp=WGPU_LOAD_OP_LOAD;
depthAttachment2.depthLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment2.depthStoreOp=WGPU_STORE_OP_UNDEFINED;
depthAttachment2.stencilClearValue=0;
depthAttachment2.stencilReadOnly=EM_TRUE;
depthAttachment2.stencilLoadOp=WGPU_LOAD_OP_LOAD;
// depthAttachment2.stencilLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment2.stencilStoreOp=WGPU_STORE_OP_UNDEFINED;
wrpdsa.at(1,1)=depthAttachment2;
passDesc={};
passDesc.numColorAttachments=1;
passDesc.colorAttachments=&wrpca.at(1,1); // &wrpca.at(0,0); // 
passDesc.depthStencilAttachment=wrpdsa.at(1,1);  //  wrpdsa.at(0,0); //
passDesc.occlusionQuerySet=0;
// passDesc.maxDrawCount=100;
wrpd.at(0,0)=passDesc;
passDesc2={};
passDesc2.numColorAttachments=1;
passDesc2.colorAttachments=&wrpca.at(0,0); // &wrpca.at(1,1); //
passDesc2.depthStencilAttachment=wrpdsa.at(0,0);
passDesc2.occlusionQuerySet=0;
// passDesc2.maxDrawCount=100;
wrpd.at(1,1)=passDesc2;
/*       //  Frame Data
std::ifstream fram(Fnm2,std::ios::binary);
std::vector<uint8_t> data((std::istreambuf_iterator<char>(fram)),(std::istreambuf_iterator<char>()));
frame_tensor.at(0,0)=data;
  // wetd.at(0,0).source=texid.at(0,0);
// wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&wict.at(2,2),&frame_tensor.at(0,0),sze.at(1,1)*4,sze.at(1,1),sze.at(1,1),sze.at(1,1),1);
*/   //  Render Pass
wceA=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(0,0)=wceA;
wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&wrpd.at(0,0));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
wgpu_encoder_set_bind_group(wrpe.at(0,0),0,wbg.at(0,0),0,0);
wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&u64_uni.at(0,0),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(2,2),0,&u64_siz.at(3,3),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(1,1),0,&u64_uni.at(3,3),sizeof(uint64_t));
wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0f,0.0f,szef.at(1,1),szef.at(1,1),0.0f,1.0f);
wgpu_render_pass_encoder_set_scissor_rect(wrpe.at(0,0),0.0f,0.0f,sze.at(1,1),sze.at(1,1));
wgpu_render_pass_encoder_draw(wrpe.at(0,0),6,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(0,0));
wcb.at(0,0)=wgpu_command_encoder_finish(wce.at(0,0));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(0,0));
  //  Render Pass 2  (sampler)
wceA={};
wceB=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(1,1)=wceB;
wrpe.at(1,1)=wgpu_command_encoder_begin_render_pass(wce.at(1,1),&wrpd.at(1,1));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(1,1),wrp.at(1,1));
wgpu_encoder_set_bind_group(wrpe.at(1,1),0,wbg.at(1,1),0,0);
wgpu_queue_write_buffer(wq.at(0,0),wb.at(5,5),0,&u64_siz.at(2,2),sizeof(uint64_t));
wgpu_render_pass_encoder_set_viewport(wrpe.at(1,1),0.0f,0.0f,szef.at(0,0),szef.at(0,0),0.0f,1.0f);
wgpu_render_pass_encoder_set_scissor_rect(wrpe.at(1,1),0.0f,0.0f,sze.at(0,0),sze.at(0,0));
wgpu_render_pass_encoder_draw(wrpe.at(1,1),6,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(1,1));
wcb.at(1,1)=wgpu_command_encoder_finish(wce.at(1,1));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(1,1));
 // Compute Pass
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(wd.at(0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&WGPU_ComputePassDescriptor.at(0,0,0));
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),1,1,1);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
// wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,&WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
   //  Buffer Data View
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
if(WGPU_BufferStatus.at(0,0,0)!=3&&on.at(1,1)==0){
on.at(1,1)=1;
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
// wgpu_buffer_map_async(WGPU_Buffers.at(2,0,2),WGPU_MapCallback.at(0,0,0),&WGPU_UserData.at(0,0,0),mode1,0,OutputBufferBytes);
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),WGPU_BufferRange.at(0,0,1),0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
EM_ASM({
document.querySelector('#outText').innerHTML='Buffer at [2]:'+$0.toFixed(2);
document.querySelector('#outText').innerHTML+='Buffer at [3]:'+$1.toFixed(2);
},WGPU_ResultBuffer.at(0,0,0)[2],WGPU_ResultBuffer.at(0,0,0)[3]);
}
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
on.at(1,1)=3;
}
// wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one_and_destroy(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
return EM_TRUE;
};

void raf(){
render();
}

void ObtainedWebGpuDeviceStart(WGpuDevice result,void *userData){
if(on.at(0,0)==0){wd.at(0,0)=result;}
js_data_pointer.at(0,0)=0;
fjs_data_pointer.at(0,0)=0;
wcc.at(0,0)=wgpu_canvas_get_webgpu_context("canvas");
const char * frag_body=(char*)rd_fl(Fnm);
WGPU_TEXTURE_FORMAT canvasFormat=navigator_gpu_get_preferred_canvas_format();
wtf.at(2,2)=WGPU_TEXTURE_FORMAT_RGBA32FLOAT;
wtf.at(1,1)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA16FLOAT;
wtf.at(4,4)=WGPU_TEXTURE_FORMAT_INVALID;
// wtf.at(5,5)=WGPU_TEXTURE_FORMAT_DEPTH32FLOAT_STENCIL8;
// wtf.at(5,5)=WGPU_TEXTURE_FORMAT_DEPTH24PLUS_STENCIL8;
wtf.at(5,5)=WGPU_TEXTURE_FORMAT_DEPTH16UNORM;
// wtf.at(0,0)=canvasFormat;
WGPU_TEXTURE_FORMAT canvasViewFormat[1]={wtf.at(0,0)};
config=WGPU_CANVAS_CONFIGURATION_DEFAULT_INITIALIZER;
config.device=wd.at(0,0);
config.format=wtf.at(0,0);
config.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
// config.numViewFormats=1;
config.viewFormats=&canvasViewFormat[0];
config.alphaMode=WGPU_CANVAS_ALPHA_MODE_PREMULTIPLIED;
// config.alphaMode=WGPU_CANVAS_ALPHA_MODE_OPAQUE;
config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
// config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_SRGB;
wccf.at(0,0)=config;
wgpu_canvas_context_configure(wcc.at(0,0),&wccf.at(0,0));
emscripten_get_canvas_element_size("canvas",&szwI,&szhI);
emscripten_get_element_css_size("canvas",&szw,&szh);
u64_siz.at(3,3)=sze.at(1,1);
sze.at(0,0)=int(szhI);
u64_siz.at(2,2)=int(szhI);
szef.at(0,0)=floor(float(szh));
szef.at(1,1)=floor(float(sze.at(1,1)));
u64_bfrSze.at(0,0)=(floor((sze.at(0,0))/256)+1)*256;
u64_bfrSze.at(1,1)=(floor((sze.at(1,1))/256)+1)*256;
WGpuOrigin3D OriginXYZ={};
OriginXYZ.x=0;
OriginXYZ.y=0;
OriginXYZ.z=0;
oxyz.at(0,0)=OriginXYZ;
WGpuOrigin2D OriginXY={};
OriginXY.x=0;
OriginXY.y=0;
oxy.at(0,0)=OriginXY;
workgroupSize=1;
WGPU_UserData.at(0,0,0)=userData;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
textureDescriptorIn.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorIn.format=wtf.at(2,2);
// textureDescriptorIn.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT|WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_STORAGE_BINDING;
textureDescriptorIn.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT|WGPU_TEXTURE_USAGE_TEXTURE_BINDING;
textureDescriptorIn.width=sze.at(1,1);
textureDescriptorIn.height=sze.at(1,1); // default = 1;
textureDescriptorIn.depthOrArrayLayers=1;
textureDescriptorIn.mipLevelCount=1;
textureDescriptorIn.sampleCount=1;
textureDescriptorIn.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT textureAviewFormats[1]={wtf.at(2,2)};
textureDescriptorIn.numViewFormats=0; // &textureAviewFormats[0];
textureDescriptorIn.viewFormats=nullptr; // &textureAviewFormats[0];
textureDescriptorOut.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut.format=wtf.at(2,2);
textureDescriptorOut.usage=WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC|WGPU_TEXTURE_USAGE_COPY_DST;
textureDescriptorOut.width=256;
textureDescriptorOut.height=1; // default = 1;
textureDescriptorOut.depthOrArrayLayers=1;
textureDescriptorOut.mipLevelCount=1;
textureDescriptorOut.sampleCount=1;
textureDescriptorOut.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut.numViewFormats=0;
textureDescriptorOut.viewFormats=nullptr;
WGPU_TEXTURE_FORMAT textureBviewFormats[1]={wtf.at(0,0)};
videoTextureDescriptor.numViewFormats=0;
videoTextureDescriptor.viewFormats=nullptr;
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorIn;
WGPU_TextureDescriptor.at(0,0,1)=textureDescriptorOut;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
textureBindingLayoutFloat.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayoutFloat.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutFloat.multisampled=0;
textureBindingLayoutFloatM.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayoutFloatM.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutFloatM.multisampled=1;
wtbl.at(1,1)=textureBindingLayoutFloat;
wtbl.at(3,3)=textureBindingLayoutFloatM;
textureBindingLayoutDepth.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_DEPTH;
textureBindingLayoutDepth.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutDepth.multisampled=0;
wtbl.at(2,2)=textureBindingLayoutDepth;
textureViewDescriptorIn.format=wtf.at(2,2);
textureViewDescriptorIn.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorIn.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorIn.baseMipLevel=0; // default = 0
textureViewDescriptorIn.mipLevelCount=1;
textureViewDescriptorIn.baseArrayLayer=0; // default = 0
textureViewDescriptorIn.arrayLayerCount=1;
textureViewDescriptorOut.format=wtf.at(2,2);
textureViewDescriptorOut.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorOut.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorOut.baseMipLevel=0; // default = 0
textureViewDescriptorOut.mipLevelCount=1;
textureViewDescriptorOut.baseArrayLayer=0; // default = 0
textureViewDescriptorOut.arrayLayerCount=1;
WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorIn;
WGPU_TextureViewDescriptor.at(0,0,1)=textureViewDescriptorOut;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;
bufferDescriptorI={u64_bfrSze.at(1,1),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
bufferDescriptorO={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
bufferDescriptorM={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
bufferDescriptorC={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,3));
bufferDescriptor_iTime={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(0,0)=bufferDescriptor_iTime;
uni_iTime_Buffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptor_iTime);
wb.at(0,0)=uni_iTime_Buffer;
bufferDescriptor_iFrame={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(1,1)=bufferDescriptor_iFrame;
uni_iFrame_Buffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptor_iFrame);
wb.at(1,1)=uni_iFrame_Buffer;
bufferDescriptor_iResolution={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(2,2)=bufferDescriptor_iResolution;
uni_iResolution_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(2,2));
wb.at(2,2)=uni_iResolution_Buffer;
bufferDescriptor_iResolution_2={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(5,5)=bufferDescriptor_iResolution_2;
uni_iResolution_Buffer_2=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(5,5));
wb.at(5,5)=uni_iResolution_Buffer_2;
bufferBindingLayoutR.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayoutR.hasDynamicOffset=0,
bufferBindingLayoutR.minBindingSize=sizeof(uint64_t);
wbbl.at(0,0)=bufferBindingLayoutR;
Input_Image_Buffer.buffer=WGPU_Buffers.at(1,1,1);
// wicb.at(2,2)=Input_Image_Buffer;
Output_Image_Buffer.buffer=WGPU_Buffers.at(0,0,0);
// wicb.at(1,1)=Output_Image_Buffer;
Mapped_Image_Buffer.buffer=WGPU_Buffers.at(2,0,2);
// wicb.at(0,0)=Mapped_Image_Buffer;
WGpuBufferDescriptor bufferDescriptorIn={u64_bfrSze.at(1,1),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorOut={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
wbd.at(3,3)=bufferDescriptorIn;
wbd.at(4,4)=bufferDescriptorOut;
wb.at(3,3)=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(3,3));
wb.at(4,4)=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(4,4));
resizeSamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.lodMinClamp=0;
resizeSamplerDescriptor.lodMaxClamp=32;
// resizeSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
resizeSamplerDescriptor.maxAnisotropy=1;
wsd.at(1,1)=resizeSamplerDescriptor;
resizeSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(1,1));
wsmp.at(3,3)=resizeSampler;
shaderModuleDescriptor.code=wgl_cmp_src;
shaderModuleDescriptor.numHints=0;
shaderModuleDescriptor.hints=NULL;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(wd.at(0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayoutIn;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayoutOut;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
WGPU_BufferBindingLayout.at(0,0,4)=bufferBindingLayout4;
storageTextureBindingLayoutFloat32.access=WGPU_STORAGE_TEXTURE_ACCESS_WRITE_ONLY;
storageTextureBindingLayoutFloat32.format=wtf.at(2,2);
storageTextureBindingLayoutFloat32.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
storageTextureBindingLayoutFloat.access=WGPU_STORAGE_TEXTURE_ACCESS_WRITE_ONLY;
storageTextureBindingLayoutFloat.format=wtf.at(0,0);
storageTextureBindingLayoutFloat.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
WGPU_StorageTextureBindingLayout.at(0,0,0)=storageTextureBindingLayoutFloat;
WGPU_StorageTextureBindingLayout.at(1,1,1)=storageTextureBindingLayoutFloat32;
textureIn=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,0)=textureIn;
textureOut=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,1));
WGPU_Texture.at(0,0,1)=textureOut;
Input_Image_Texture.texture=WGPU_Texture.at(0,0,0);
Input_Image_Texture.origin=OriginXYZ;
Input_Image_Texture.aspect=WGPU_TEXTURE_ASPECT_ALL;
Output_Image_Texture.texture=WGPU_Texture.at(0,0,1);
Output_Image_Texture.origin=OriginXYZ;
Output_Image_Texture.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(2,2)=Input_Image_Texture;
wict.at(1,1)=Output_Image_Texture;
INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
OUTTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,1),&WGPU_TextureViewDescriptor.at(0,0,1));
wtv.at(3,3)=INTextureView;
wtv.at(4,4)=OUTTextureView;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
videoTextureDescriptor.format=wtf.at(2,2);
videoTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_DST;
videoTextureDescriptor.width=sze.at(0,0);
videoTextureDescriptor.height=sze.at(0,0); // default = 1;
videoTextureDescriptor.depthOrArrayLayers=1;
videoTextureDescriptor.mipLevelCount=1;
videoTextureDescriptor.sampleCount=1;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT videoViewFormats[1]={wtf.at(0,0)};
videoTextureDescriptor.numViewFormats=0; // &videoViewFormats[0];
videoTextureDescriptor.viewFormats=nullptr; // &videoViewFormats[0];
wtd.at(2,2)=videoTextureDescriptor;
videoTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(2,2));
wt.at(2,2)=videoTexture;
videoTextureViewDescriptor.format=wtf.at(2,2);
videoTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
videoTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
videoTextureViewDescriptor.baseMipLevel=0; // default = 0
videoTextureViewDescriptor.mipLevelCount=1;
videoTextureViewDescriptor.baseArrayLayer=0; // default = 0
videoTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(2,2)=videoTextureViewDescriptor;
videoTextureView=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
wtv.at(2,2)=videoTextureView;
      //  Input Buffer
Compute_Bindgroup_Layout_Entries[0].binding=0;
Compute_Bindgroup_Layout_Entries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
        //  Output Buffer
Compute_Bindgroup_Layout_Entries[1].binding=1;
Compute_Bindgroup_Layout_Entries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
          //  Input Texture
Compute_Bindgroup_Layout_Entries[2].binding=2;
Compute_Bindgroup_Layout_Entries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Compute_Bindgroup_Layout_Entries[2].layout.texture=wtbl.at(1,1);
          //  Output Texture
Compute_Bindgroup_Layout_Entries[3].binding=3;
Compute_Bindgroup_Layout_Entries[3].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Compute_Bindgroup_Layout_Entries[3].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
            //  Compute Sampler
Compute_Bindgroup_Layout_Entries[4].binding=4;
Compute_Bindgroup_Layout_Entries[4].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Compute_Bindgroup_Layout_Entries[4].layout.sampler=wsbl.at(0,0);
            //  Time Uniform
Compute_Bindgroup_Layout_Entries[5].binding=5;
Compute_Bindgroup_Layout_Entries[5].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[5].layout.buffer=wbbl.at(0,0);
            //  Video Texture
Compute_Bindgroup_Layout_Entries[6].binding=6;
Compute_Bindgroup_Layout_Entries[6].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[6].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Compute_Bindgroup_Layout_Entries[6].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
            //  Color Attachment Texture
// Compute_Bindgroup_Layout_Entries[7].binding=7;
// Compute_Bindgroup_Layout_Entries[7].visibility=WGPU_SHADER_STAGE_COMPUTE;
// Compute_Bindgroup_Layout_Entries[7].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
// Compute_Bindgroup_Layout_Entries[7].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
WGPU_Compute_Bindgroup_Layout_Entries.at(0,0,0)=Compute_Bindgroup_Layout_Entries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(wd.at(0,0),WGPU_Compute_Bindgroup_Layout_Entries.at(0,0,0),7);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(wd.at(0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(wd.at(0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
      //  Input Buffer
Compute_Bindgroup_Entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[0].binding=0;
Compute_Bindgroup_Entries[0].resource=WGPU_Buffers.at(1,1,1);
Compute_Bindgroup_Entries[0].bufferBindOffset=0;
Compute_Bindgroup_Entries[0].bufferBindSize=InputBufferBytes;
        //  Output Buffer
Compute_Bindgroup_Entries[1]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[1].binding=1;
Compute_Bindgroup_Entries[1].resource=WGPU_Buffers.at(0,0,0);
Compute_Bindgroup_Entries[1].bufferBindOffset=0;
Compute_Bindgroup_Entries[1].bufferBindSize=OutputBufferBytes;
          //  Input Texture
Compute_Bindgroup_Entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[2].binding=2;
Compute_Bindgroup_Entries[2].resource=wtv.at(3,3);
          //  Output Texture
Compute_Bindgroup_Entries[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[3].binding=3;
Compute_Bindgroup_Entries[3].resource=wtv.at(4,4);
            //  Compute Sampler
Compute_Bindgroup_Entries[4]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[4].binding=4;
Compute_Bindgroup_Entries[4].resource=wsmp.at(3,3);
            // Compute iTime Uniform
Compute_Bindgroup_Entries[5].binding=5;
Compute_Bindgroup_Entries[5].resource=wb.at(0,0);
Compute_Bindgroup_Entries[5].bufferBindOffset=0;
Compute_Bindgroup_Entries[5].bufferBindSize=sizeof(uint64_t);
            //  Video Texture
Compute_Bindgroup_Entries[6]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[6].binding=6;
Compute_Bindgroup_Entries[6].resource=wtv.at(2,2); 
            //  Color Attachment Texture
// Compute_Bindgroup_Entries[7]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
// Compute_Bindgroup_Entries[7].binding=7;
// Compute_Bindgroup_Entries[7].resource=wtv.at(1,1); 
WGPU_BindGroupEntries.at(0,0,0)=Compute_Bindgroup_Entries;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(wd.at(0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),7);
WGpuComputePassTimestampWrites computePassTimestampWrites={};
computePassTimestampWrites.querySet=0;
computePassDescriptor.timestampWrites=computePassTimestampWrites;
WGPU_ComputePassDescriptor.at(0,0,0)=computePassDescriptor;
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(wd.at(0,0));
multiSamp={};
multiSamp.count=1;
multiSamp.mask=-1;
multiSamp2={};
multiSamp2.count=1;
multiSamp2.mask=-1;
shaderModuleDescV={};
shaderModuleDescF={};
shaderModuleDescF2={};
shaderModuleDescV.code=vertexShader;
vs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescV);
shaderModuleDescF.code=frag_body;
shaderModuleDescF2.code=frag_body2;
// shaderModuleDescF.code=fragmentShader;
fs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF);
fs2=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF2);
WGpuColorTargetState colorTarget32={};
colorTarget32.format=wtf.at(2,2); // wtf.at(0,0);
colorTarget32.writeMask=15;
WGpuColorTargetState colorTarget={};
colorTarget.format=wtf.at(0,0);
colorTarget.writeMask=15;
depthState={};
depthState2={};
depthState2.format=wtf.at(5,5);
depthState2.depthWriteEnabled=0;
depthState2.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;
depthState.format=wtf.at(5,5);
depthState.depthWriteEnabled=0;
depthState.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;
vertState={};
vertState.module=vs;
vertState.entryPoint="main";
vertState.numBuffers=0;
vertState.buffers=nullptr;
vertState.numConstants=0;
vertState.constants=nullptr;
priState={};
priState.topology=WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // Defaults to WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ('triangle-list')
// priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32; // Defaults to undefined, must be explicitly specified if WGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP ('line-strip') or WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ('triangle-strip') is used.
priState.frontFace=WGPU_FRONT_FACE_CCW; // Defaults to WGPU_FRONT_FACE_CCW ('ccw')
priState.cullMode=WGPU_CULL_MODE_FRONT; // Defaults to WGPU_CULL_MODE_NONE ('none')
priState.unclippedDepth=EM_FALSE; // defaults to EM_FALSE.
fragState={};
fragState.module=fs;
fragState.entryPoint="main";
fragState.numTargets=1;
fragState.targets=&colorTarget32;
fragState2={};
fragState2.module=fs2;
fragState2.entryPoint="main";
fragState2.numTargets=1;
fragState2.targets=&colorTarget;
videoSamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
videoSamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
videoSamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
videoSamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
videoSamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
videoSamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
videoSamplerDescriptor.lodMinClamp=0;
videoSamplerDescriptor.lodMaxClamp=32;
// videoSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
videoSamplerDescriptor.maxAnisotropy=2;
wsd.at(0,0)=videoSamplerDescriptor;
videoSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(0,0));
wsmp.at(0,0)=videoSampler;
texid.at(0,0)=77;
extTextureDescriptor.source=texid.at(0,0);
extTextureDescriptor.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
wetd.at(0,0)=extTextureDescriptor;
// extTexture=wgpu_device_import_external_texture(wd.at(0,0),&wetd.at(0,0));
// wet.at(0,0)=extTexture;
WGpuOrigin3D xyz={};
xyz.x=0;
xyz.y=0;
xyz.z=0;
WGpuImageCopyTexture videoTextureCopy;
videoTextureCopy.texture=wt.at(2,2);
videoTextureCopy.mipLevel=0;
videoTextureCopy.origin=xyz;
videoTextureCopy.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(0,0)=videoTextureCopy;
bufferDescriptorUni={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(0,0)=bufferDescriptorUni;
uniBuffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptorUni);
wb.at(0,0)=uniBuffer;
bufferBindingLayout1.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayout1.hasDynamicOffset=0,
bufferBindingLayout1.minBindingSize=sizeof(uint64_t);
wbbl.at(0,0)=bufferBindingLayout1;
samplerBindingLayout.type=WGPU_SAMPLER_BINDING_TYPE_FILTERING;
wsbl.at(1,1)=samplerBindingLayout;
  //  Render Sampler
Render_Bindgroup_Layout_Entries[0]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[0].binding=0;
Render_Bindgroup_Layout_Entries[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Render_Bindgroup_Layout_Entries[0].layout.sampler=wsbl.at(1,1);
  //  Render iTime Buffer
Render_Bindgroup_Layout_Entries[1]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[1].binding=7;
Render_Bindgroup_Layout_Entries[1].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries[1].layout.buffer=wbbl.at(0,0);
  //  Render TextureIN
Render_Bindgroup_Layout_Entries[2]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[2].binding=2;
Render_Bindgroup_Layout_Entries[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Render_Bindgroup_Layout_Entries[2].layout.texture=wtbl.at(1,1);
  //  Render iResolution Buffer
Render_Bindgroup_Layout_Entries[3]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[3].binding=5;
Render_Bindgroup_Layout_Entries[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries[3].layout.buffer=wbbl.at(0,0);
  //  Render iFrame Buffer
Render_Bindgroup_Layout_Entries[4]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[4].binding=6;
Render_Bindgroup_Layout_Entries[4].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries[4].layout.buffer=wbbl.at(0,0);
  //  Render TextureOUT
Render_Bindgroup_Layout_Entries[5]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[5].binding=1;
Render_Bindgroup_Layout_Entries[5].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Render_Bindgroup_Layout_Entries[5].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
wbgle.at(0,0)=Render_Bindgroup_Layout_Entries;
bindgroup_layout=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(0,0),5);
wbgl.at(0,0)=bindgroup_layout;
  //  Render_2 Sampler
Render_Bindgroup_Layout_Entries_2[0]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[0].binding=0;
Render_Bindgroup_Layout_Entries_2[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Render_Bindgroup_Layout_Entries_2[0].layout.sampler=wsbl.at(1,1);
  //  Render_2 iTime Buffer
Render_Bindgroup_Layout_Entries_2[1]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[1].binding=7;
Render_Bindgroup_Layout_Entries_2[1].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries_2[1].layout.buffer=wbbl.at(0,0);
  //  Render_2 TextureIN
Render_Bindgroup_Layout_Entries_2[2]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[2].binding=2;
Render_Bindgroup_Layout_Entries_2[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Render_Bindgroup_Layout_Entries_2[2].layout.texture=wtbl.at(1,1);
  //  Render_2 iResolution Buffer
Render_Bindgroup_Layout_Entries_2[3]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[3].binding=5;
Render_Bindgroup_Layout_Entries_2[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries_2[3].layout.buffer=wbbl.at(0,0);
  //  Render_2 iFrame Buffer
Render_Bindgroup_Layout_Entries_2[4]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[4].binding=6;
Render_Bindgroup_Layout_Entries_2[4].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries_2[4].layout.buffer=wbbl.at(0,0);
  //  Render_2 TextureOUT
Render_Bindgroup_Layout_Entries_2[5]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[5].binding=1;
Render_Bindgroup_Layout_Entries_2[5].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Render_Bindgroup_Layout_Entries_2[5].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
wbgle.at(1,1)=Render_Bindgroup_Layout_Entries_2;
bindgroup_layout_2=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(1,1),5);
wbgl.at(1,1)=bindgroup_layout_2;
WGpuPipelineLayout pipeline_layout=wgpu_device_create_pipeline_layout(wd.at(0,0),&wbgl.at(0,0),1);
wrpl.at(0,0)=pipeline_layout;
WGpuRenderPipelineDescriptor renderPipelineDesc={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
renderPipelineDesc.vertex.module=vs;
renderPipelineDesc.vertex.entryPoint="main";
renderPipelineDesc.primitive=priState;
renderPipelineDesc.fragment=fragState;
renderPipelineDesc.depthStencil=depthState;
renderPipelineDesc.layout=wrpl.at(0,0);
// renderPipelineDesc.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc.multisample=multiSamp;
wrp.at(0,0)=wgpu_device_create_render_pipeline(wd.at(0,0),&renderPipelineDesc);
WGpuPipelineLayout pipeline_layout_2=wgpu_device_create_pipeline_layout(wd.at(0,0),&wbgl.at(1,1),1);
wrpl.at(1,1)=pipeline_layout_2;
WGpuRenderPipelineDescriptor renderPipelineDesc2={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
renderPipelineDesc2.vertex.module=vs;
renderPipelineDesc2.vertex.entryPoint="main";
renderPipelineDesc2.primitive=priState;
renderPipelineDesc2.fragment=fragState2;
renderPipelineDesc2.depthStencil=depthState;
renderPipelineDesc2.layout=wrpl.at(1,1);
// renderPipelineDesc.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc2.multisample=multiSamp;
wrp.at(1,1)=wgpu_device_create_render_pipeline(wd.at(0,0),&renderPipelineDesc2);
  //  Render Sampler
Render_Bindgroup_Entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[0].binding=0;
Render_Bindgroup_Entries[0].resource=wsmp.at(0,0);
    //  Render iTime Buffer
Render_Bindgroup_Entries[1].binding=7;
Render_Bindgroup_Entries[1].resource=wb.at(0,0);
Render_Bindgroup_Entries[1].bufferBindOffset=0;
Render_Bindgroup_Entries[1].bufferBindSize=sizeof(uint64_t);
  //  Render TextureIN
Render_Bindgroup_Entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[2].binding=2;
Render_Bindgroup_Entries[2].resource=wtv.at(2,2);
  //  Render iResolution Buffer
Render_Bindgroup_Entries[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[3].binding=5;
Render_Bindgroup_Entries[3].resource=wb.at(2,2);
Render_Bindgroup_Entries[3].bufferBindOffset=0;
Render_Bindgroup_Entries[3].bufferBindSize=sizeof(uint64_t);
  //  Render iFrame Buffer
Render_Bindgroup_Entries[4]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[4].binding=6;
Render_Bindgroup_Entries[4].resource=wb.at(1,1);
Render_Bindgroup_Entries[4].bufferBindOffset=0;
Render_Bindgroup_Entries[4].bufferBindSize=sizeof(uint64_t);
  //  Render TextureOUT
Render_Bindgroup_Entries[5]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[5].binding=1;
Render_Bindgroup_Entries[5].resource=wtv.at(3,3);
wbge.at(0,0)=Render_Bindgroup_Entries;
    //  Render_2 Sampler
Render_Bindgroup_Entries_2[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[0].binding=0;
Render_Bindgroup_Entries_2[0].resource=wsmp.at(0,0);
    //  Render_2 iTime Buffer
Render_Bindgroup_Entries_2[1].binding=7;
Render_Bindgroup_Entries_2[1].resource=wb.at(0,0);
Render_Bindgroup_Entries_2[1].bufferBindOffset=0;
Render_Bindgroup_Entries_2[1].bufferBindSize=sizeof(uint64_t);
  //  Render_2 TextureIN
Render_Bindgroup_Entries_2[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[2].binding=2;
Render_Bindgroup_Entries_2[2].resource=wtv.at(2,2);
  //  Render_2 iResolution Buffer
Render_Bindgroup_Entries_2[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[3].binding=5;
Render_Bindgroup_Entries_2[3].resource=wb.at(5,5);
Render_Bindgroup_Entries_2[3].bufferBindOffset=0;
Render_Bindgroup_Entries_2[3].bufferBindSize=sizeof(uint64_t);
  //  Render_2 iFrame Buffer
Render_Bindgroup_Entries_2[4]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[4].binding=6;
Render_Bindgroup_Entries_2[4].resource=wb.at(1,1);
Render_Bindgroup_Entries_2[4].bufferBindOffset=0;
Render_Bindgroup_Entries_2[4].bufferBindSize=sizeof(uint64_t);
  //  Render_2 TextureOUT
Render_Bindgroup_Entries_2[5]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[5].binding=1;
Render_Bindgroup_Entries_2[5].resource=wtv.at(3,3);
wbge.at(1,1)=Render_Bindgroup_Entries_2;
depthTextureViewDescriptor.format=wtf.at(5,5);
depthTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
depthTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
depthTextureViewDescriptor.baseMipLevel=0; // default = 0
depthTextureViewDescriptor.mipLevelCount=1;
depthTextureViewDescriptor.baseArrayLayer=0; // default = 0
depthTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(0,0)=depthTextureViewDescriptor;
colorTextureViewDescriptor.format=wtf.at(0,0);
colorTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
colorTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
colorTextureViewDescriptor.baseMipLevel=0; // default = 0
colorTextureViewDescriptor.mipLevelCount=1;
colorTextureViewDescriptor.baseArrayLayer=0; // default = 0
colorTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(1,1)=colorTextureViewDescriptor;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthTextureDescriptor.format=wtf.at(5,5);
depthTextureDescriptor.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
depthTextureDescriptor.width=sze.at(0,0);
depthTextureDescriptor.height=sze.at(0,0); // default = 1;
depthTextureDescriptor.depthOrArrayLayers=1;
depthTextureDescriptor.mipLevelCount=1;
depthTextureDescriptor.sampleCount=1;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT depthViewFormats[1]={wtf.at(5,5)};
depthTextureDescriptor.viewFormats=&depthViewFormats[0];
wtd.at(0,0)=depthTextureDescriptor;
depthTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(0,0));
wt.at(0,0)=depthTexture;
depthTextureDescriptor2.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthTextureDescriptor2.format=wtf.at(5,5);
depthTextureDescriptor2.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
depthTextureDescriptor2.width=sze.at(1,1);
depthTextureDescriptor2.height=sze.at(1,1); // default = 1;
depthTextureDescriptor2.depthOrArrayLayers=1;
depthTextureDescriptor2.mipLevelCount=1;
depthTextureDescriptor2.sampleCount=1;
depthTextureDescriptor2.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT depthViewFormats2[1]={wtf.at(5,5)};
depthTextureDescriptor2.viewFormats=&depthViewFormats2[0];
wtd.at(3,3)=depthTextureDescriptor2;
depthTexture2=wgpu_device_create_texture(wd.at(0,0),&wtd.at(3,3));
wt.at(5,5)=depthTexture2;
depthTextureViewDescriptor2.format=wtf.at(5,5);
depthTextureViewDescriptor2.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
depthTextureViewDescriptor2.aspect=WGPU_TEXTURE_ASPECT_ALL;
depthTextureViewDescriptor2.baseMipLevel=0; // default = 0
depthTextureViewDescriptor2.mipLevelCount=1;
depthTextureViewDescriptor2.baseArrayLayer=0; // default = 0
depthTextureViewDescriptor2.arrayLayerCount=1;
wtvd.at(3,3)=depthTextureViewDescriptor2;
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
colorTextureDescriptor.format=wtf.at(0,0);
colorTextureDescriptor.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
colorTextureDescriptor.width=sze.at(0,0);
colorTextureDescriptor.height=sze.at(0,0); // default = 1;
colorTextureDescriptor.depthOrArrayLayers=1;
colorTextureDescriptor.mipLevelCount=1;
colorTextureDescriptor.sampleCount=1;
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
wtd.at(1,1)=colorTextureDescriptor;
wq.at(0,0)=wgpu_device_get_queue(wd.at(0,0));
// tme=get_current_time_in_milliseconds();
// wTime.iTime=get_current_time_in_milliseconds();
bindgroup=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(0,0),wbge.at(0,0),5);
wbg.at(0,0)=bindgroup;
bindgroup_2=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(1,1),wbge.at(1,1),5);
wbg.at(1,1)=bindgroup_2;
u64_uni.at(0,0)=0;
u64_uni.at(3,3)=0;
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
if(on.at(0,0)==1){emscripten_cancel_main_loop();}
emscripten_set_main_loop((void(*)())raf,0,0);
on.at(0,0)=1;
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
wa.at(0,0)=result;
deviceDesc={WGPU_DEVICE_DESCRIPTOR_DEFAULT_INITIALIZER};
// deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8;
WGPU_FEATURES_BITFIELD ftr=wgpu_adapter_or_device_get_features(wa.at(0,0));
WGpuSupportedLimits lmts;
wgpu_adapter_or_device_get_limits(wa.at(0,0),&lmts);
deviceDesc.requiredFeatures=ftr;
deviceDesc.requiredLimits=lmts;
wdd.at(0,0)=deviceDesc;
wgpu_adapter_request_device_async(wa.at(0,0),&wdd.at(0,0),ObtainedWebGpuDeviceStart,0);
}

void WGPU_Start(int sz){
sze.at(1,1)=sz;
WGpuRequestAdapterOptions options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options.powerPreference=WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
options.forceFallbackAdapter=EM_FALSE;
wao.at(0,0)=options;
navigator_gpu_request_adapter_async(&wao.at(0,0),ObtainedWebGpuAdapterStart,0);
}

#include "../../src/vanilla/webgpu_compute_js_tex.cpp"

extern"C"{

void startWebGPUi(int sz){
WGPU_Start(sz);
}

void startWebGPUbi(int sz){
WGPU_Start(sz);
}

}

int main(){
on.at(0,0)=0;
js_main();
return 0;
}
