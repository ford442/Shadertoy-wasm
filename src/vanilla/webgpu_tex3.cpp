#include "../../include/vanilla/webgpu_tex.hpp"

#include "../../highway/hwy/foreach_target.h"
#include "../../highway/hwy/highway.h"

#include "../../src/vanilla/webgpu_compute_vars.cpp"

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

/*
WGpuLoadImageBitmapCallback imageCallbackStart=[](WGpuImageBitmap bitmap,int width,int height,void *userData){
bmpImage=bitmap;
wib.at(0,0)=bmpImage;
return;
};
*/

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
return;
};

int rNd4(int randomMax){
entropySeed=(randomMax)*randomizer();
std::srand(entropySeed);
randomNumber=std::rand()%randomMax;
return randomNumber;
}

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

EM_BOOL getCode(const char * Fnm){
wgsl.at(0,0)=frag_body;
return EM_TRUE;
}

EM_BOOL texOn(){
on.at(4,4)=1;
return EM_TRUE;
}

EM_BOOL framesOff(){
on.at(3,3)=0;
return EM_TRUE;
}

boost::function<EM_BOOL()>render=[](){
u64_uni.at(3,3)++; 
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
// u64_uni.at(0,0)=u_time.time_spana.count()*100u;
// u64_uni.at(1,1)=u_time.time_spanb.count()*1000u;
f32_uniform.at(0,0)=float(u_time.time_spana.count())*100.0f;
// u64_uni.at(2,2)=u_time.time_spanb.count()/1.0f;
colorTexture=wgpu_canvas_context_get_current_texture(wcc.at(0,0));
wt.at(1,1)=colorTexture;
colorTextureView=wgpu_texture_create_view(wt.at(1,1),&wtvd.at(1,1));
wtv.at(1,1)=colorTextureView;
colorAttachment.view=wtv.at(1,1);
colorAttachment.depthSlice=0;
colorAttachment.storeOp=WGPU_STORE_OP_STORE; // WGPU_STORE_OP_DISCARD; 
// colorAttachment.loadOp=WGPU_LOAD_OP_LOAD;
colorAttachment.loadOp=WGPU_LOAD_OP_CLEAR;
colorAttachment.clearValue=clearC.at(0,0);
wrpca.at(0,0)=colorAttachment;
INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
wtv.at(3,3)=INTextureView;
OUTTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,1),&WGPU_TextureViewDescriptor.at(0,0,1));
wtv.at(4,4)=OUTTextureView;
OUTTexture2View=wgpu_texture_create_view(WGPU_Texture.at(0,0,2),&WGPU_TextureViewDescriptor.at(0,0,2));
wtv.at(5,5)=OUTTexture2View;
videoAttachment.view=wtv.at(3,3);
videoAttachment.depthSlice=0;
videoAttachment.storeOp=WGPU_STORE_OP_STORE;
// videoAttachment.loadOp=WGPU_LOAD_OP_LOAD;
videoAttachment.loadOp=WGPU_LOAD_OP_CLEAR;
videoAttachment.clearValue=clearC.at(0,0);
wrpca.at(1,1)=videoAttachment;
videoTextureView=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
wtv.at(2,2)=videoTextureView;
  /*
depthTextureView=wgpu_texture_create_view(wt.at(0,0),&wtvd.at(0,0));
wtv.at(0,0)=depthTextureView;
depthAttachment.view=wtv.at(0,0);
depthAttachment.depthClearValue=1.0f;
depthAttachment.depthReadOnly=EM_TRUE;
depthAttachment.depthLoadOp=WGPU_LOAD_OP_LOAD;
// depthAttachment.depthLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment.depthStoreOp=WGPU_STORE_OP_DISCARD; // WGPU_STORE_OP_UNDEFINED;
depthAttachment.stencilClearValue=0u;
depthAttachment.stencilReadOnly=EM_TRUE;
depthAttachment.stencilLoadOp=WGPU_LOAD_OP_LOAD;
// depthAttachment.stencilLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment.stencilStoreOp=WGPU_STORE_OP_UNDEFINED;
wrpdsa.at(0,0)=depthAttachment;
depthTextureView2=wgpu_texture_create_view(wt.at(5,5),&wtvd.at(3,3));
wtv.at(5,5)=depthTextureView2;
depthAttachment2.view=wtv.at(5,5);
depthAttachment2.depthClearValue=1.0f;
depthAttachment2.depthReadOnly=EM_TRUE;
depthAttachment2.depthLoadOp=WGPU_LOAD_OP_LOAD;
// depthAttachment2.depthLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment2.depthStoreOp=WGPU_STORE_OP_DISCARD; // WGPU_STORE_OP_UNDEFINED;
depthAttachment2.stencilClearValue=0u;
depthAttachment2.stencilReadOnly=EM_TRUE;
// depthAttachment2.stencilLoadOp=WGPU_LOAD_OP_LOAD;
depthAttachment2.stencilLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment2.stencilStoreOp=WGPU_STORE_OP_UNDEFINED;
wrpdsa.at(1,1)=depthAttachment2;
  */
passDesc.numColorAttachments=1;
passDesc.colorAttachments=&wrpca.at(1,1); // &wrpca.at(0,0); // 
// passDesc.depthStencilAttachment=wrpdsa.at(1,1);  //  wrpdsa.at(0,0); //
passDesc.occlusionQuerySet=0;
// passDesc.maxDrawCount=6;
renderTimestampWrites.querySet=0;
renderTimestampWrites.beginningOfPassWriteIndex=-1;
renderTimestampWrites.endOfPassWriteIndex=-1;
passDesc.timestampWrites=renderTimestampWrites;
wrpd.at(0,0)=passDesc;
passDesc2.numColorAttachments=1;
passDesc2.colorAttachments=&wrpca.at(0,0); // &wrpca.at(1,1); //
// passDesc2.depthStencilAttachment=wrpdsa.at(0,0);
passDesc2.occlusionQuerySet=0;
// passDesc2.maxDrawCount=6;
passDesc2.timestampWrites=renderTimestampWrites;
wrpd.at(1,1)=passDesc2;
if(on.at(4,4)==1){
INVTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,3),&WGPU_TextureViewDescriptor.at(0,0,3));
wtv.at(6,6)=INVTextureView;
      //  Frame Data 
std::ifstream fram(Fnm2,std::ios::binary);
std::vector<uint8_t>data((std::istreambuf_iterator<char>(fram)),(std::istreambuf_iterator<char>()));
/*    //  highway way
     const HWY_FULL(uint8_t) d;
    const size_t N = data.size();  
     std::vector<float> floatData(4 * N); 

    // SIMD conversion loop
    for (size_t i = 0; i < N; i += 1) {
        const auto v = Load(d, &data[i]); 
       const HWY_FULL(float) f = v / Set(d, 255.0f); // Divide as before
        Store(f, d, &floatData[i]); 
    }
*/ //  regular way
std::vector<float>floatData(data.size());
std::transform(data.begin(),data.end(),floatData.begin(),[](uint8_t val){return val/255.0f;});  // for RGBA32FLOAT
const size_t bytesPerRow=sze.at(6,6)*4*sizeof(float);
// frame_tensor.at(0,0)=data;
// fjs_data_pointer.at(0,0)=floatData.data();
// fjsv_data_pointer.at(0,0)=&floatData; // (std::vector<float*>)
//     frame_tensorf.at(0,0)=floatData;
// frame_tensorGL.at(0,0)=data;
// wetd.at(0,0).source=texid.at(0,0);
//   wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&wict.at(4,4),&frame_tensor.at(0,0),bytesPerRow,sze.at(7,7),sze.at(6,6),sze.at(7,7),1);
wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&wict.at(4,4),floatData.data(),bytesPerRow,sze.at(7,7),sze.at(6,6),sze.at(7,7),1);
on.at(4,4)=0;
}   // end if on 4,4
// void wgpu_queue_copy_external_image_to_texture(WGpuQueue queue, const WGpuImageCopyExternalImage *source NOTNULL, const WGpuImageCopyTextureTagged *destination NOTNULL, uint32_t copyWidth, uint32_t copyHeight _WGPU_DEFAULT_VALUE(1), uint32_t copyDepthOrArrayLayers _WGPU_DEFAULT_VALUE(1));
// wgpu_queue_copy_external_image_to_texture(WGPU_Queue.at(0,0,0), ,&wictt.at(0,0) ,sze.at(7,7),sze.at(6,6),sze.at(7,7),1);
 //  Render Pass
wceA=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(0,0)=wceA;
wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&wrpd.at(0,0));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
wgpu_encoder_set_bind_group(wrpe.at(0,0),0,wbg.at(0,0),0,0);
 // wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&u64_uni.at(0,0),sizeof(uint64_t));
// wgpu_queue_write_buffer(wq.at(0,0),wb.at(2,2),0,&u64_siz.at(3,3),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(2,2),0,&f32_uniform.at(2,2),sizeof(float));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(1,1),0,&u64_uni.at(3,3),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&f32_uniform.at(0,0),sizeof(float));
wgpu_render_pass_encoder_set_index_buffer(wrpe.at(0,0),wb.at(4,4),WGPU_INDEX_FORMAT_UINT32,0,36*sizeof(uint32_t));
wgpu_render_pass_encoder_set_vertex_buffer(wrpe.at(0,0),0,wb.at(3,3),0,sizeof(FUVvertices));
wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0f,0.0f,szef.at(1,1),szef.at(1,1),0.0f,1.0f);
wgpu_render_pass_encoder_set_scissor_rect(wrpe.at(0,0),0.0f,0.0f,sze.at(1,1),sze.at(1,1));
// wgpu_render_pass_encoder_draw(wrpe.at(0,0),6,1,0,0);
wgpu_render_pass_encoder_draw_indexed(wrpe.at(0,0),36,1,0,0,0);
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
// wgpu_queue_write_buffer(wq.at(0,0),wb.at(5,5),0,&u64_siz.at(2,2),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(5,5),0,&f32_uniform.at(1,1),sizeof(float));
wgpu_render_pass_encoder_set_index_buffer(wrpe.at(1,1),wb.at(4,4),WGPU_INDEX_FORMAT_UINT32,0,36*sizeof(uint32_t));
wgpu_render_pass_encoder_set_vertex_buffer(wrpe.at(1,1),0,wb.at(3,3),0,sizeof(FUVvertices));
wgpu_render_pass_encoder_set_viewport(wrpe.at(1,1),0.0f,0.0f,szef.at(0,0),szef.at(0,0),0.0f,1.0f);
wgpu_render_pass_encoder_set_scissor_rect(wrpe.at(1,1),0.0f,0.0f,sze.at(0,0),sze.at(0,0));
//  wgpu_render_pass_encoder_draw(wrpe.at(1,1),6,1,0,0);
wgpu_render_pass_encoder_draw_indexed(wrpe.at(1,1),36,1,0,0,0);
wgpu_render_pass_encoder_end(wrpe.at(1,1));
wcb.at(1,1)=wgpu_command_encoder_finish(wce.at(1,1));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(1,1));
 // Compute Pass
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(wd.at(0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&WGPU_ComputePassDescriptor.at(0,0,0));
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),32,8,1);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
  //  Move resized texture
wgpu_command_encoder_copy_texture_to_texture(WGPU_CommandEncoder.at(0,0,0),&wict.at(1,1),&wict.at(3,3),sze.at(3,3),sze.at(3,3),1);
  //  Buffer Data View
if(WGPU_BufferStatus.at(0,0,0)!=3&&on.at(1,1)==0){
  // wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,&WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
  wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
    // void wgpu_load_image_bitmap_from_url_async(const char *url NOTNULL, EM_BOOL flipY, WGpuLoadImageBitmapCallback callback, void *userData);
   // const char url_address="https://test.1ink.us/gpu/  ";
  // wgpu_load_image_bitmap_from_url_async(url_address,EM_TRUE,imageCallbackStart,WGPU_UserData.at(0,0,0));
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
return;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result,void *userData){
if(on.at(0,0)==0){wd.at(0,0)=result;}
on.at(4,4)=0;
on.at(3,3)=1;
js_data_pointer.at(0,0)=0;
fjs_data_pointer.at(0,0)=0;
wcc.at(0,0)=wgpu_canvas_get_webgpu_context("#scanvas");
const char * frag_body=(char*)rd_fl(Fnm);
const char * comp_body=(char*)rd_fl(FnmC);
const char * frag_body3=(char*)rd_fl(FnmF2);
const char * vert_body=(char*)rd_fl(FnmV);
// canvasFormat=navigator_gpu_get_preferred_canvas_format();
wtf.at(2,2)=WGPU_TEXTURE_FORMAT_RGBA32FLOAT;
// wtf.at(0,0)=navigator_gpu_get_preferred_canvas_format();
wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
  wtf.at(1,1)=WGPU_TEXTURE_FORMAT_RGBA32FLOAT;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RG11B10UFLOAT;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
wtf.at(4,4)=WGPU_TEXTURE_FORMAT_INVALID;
// wtf.at(5,5)=WGPU_TEXTURE_FORMAT_DEPTH32FLOAT_STENCIL8;
// wtf.at(5,5)=WGPU_TEXTURE_FORMAT_DEPTH24PLUS_STENCIL8;
wtf.at(5,5)=WGPU_TEXTURE_FORMAT_DEPTH16UNORM;
// wtf.at(0,0)=canvasFormat;
canvasViewFormat[0]={wtf.at(0,0)};
config.device=wd.at(0,0);
config.format=wtf.at(0,0);
config.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
// config.numViewFormats=1;
config.viewFormats=&canvasViewFormat[0];
// config.alphaMode=WGPU_CANVAS_ALPHA_MODE_PREMULTIPLIED;
config.alphaMode=WGPU_CANVAS_ALPHA_MODE_OPAQUE;
config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
// config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_SRGB;
wccf.at(0,0)=config;
clearColor.r=0.5;
clearColor.g=0.5;
clearColor.b=0.5;
clearColor.a=1.0;
clearC.at(0,0)=clearColor;
wgpu_canvas_context_configure(wcc.at(0,0),&wccf.at(0,0));
emscripten_get_canvas_element_size("canvas",&szwI,&szhI);
emscripten_get_element_css_size("canvas",&szw,&szh);
// u64_siz.at(3,3)=sze.at(1,1);
sze.at(0,0)=int(szhI);
sze.at(3,3)=int(std::max(sze.at(0,0),sze.at(1,1))*1.15);
// u64_siz.at(2,2)=int(szhI);
f32_uniform.at(1,1)=szhI;
f32_uniform.at(2,2)=float(sze.at(1,1));
szef.at(0,0)=float(szhI);
szef.at(1,1)=float(sze.at(1,1));
u64_bfrSze.at(0,0)=256; // (floor((sze.at(0,0))/256)+1)*256;
u64_bfrSze.at(1,1)=256; // (floor((sze.at(1,1))/256)+1)*256;
originXYZ.x=0;
originXYZ.y=0;
originXYZ.z=0;
originXY.x=0;
originXY.y=0;
oxyz.at(0,0)=originXYZ;
oxy.at(0,0)=originXY;
WGPU_UserData.at(0,0,0)=userData;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
textureDescriptorIn.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorIn.format=wtf.at(2,2);
textureDescriptorIn.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT|WGPU_TEXTURE_USAGE_TEXTURE_BINDING;
textureDescriptorIn.width=sze.at(1,1);
textureDescriptorIn.height=sze.at(1,1); // default = 1;
textureDescriptorIn.depthOrArrayLayers=1;
textureDescriptorIn.mipLevelCount=1;
textureDescriptorIn.sampleCount=1;
textureDescriptorIn.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureAviewFormats[0]={wtf.at(2,2)};
textureDescriptorIn.numViewFormats=0;
textureDescriptorIn.viewFormats=nullptr; // &textureAviewFormats[0];
textureDescriptorInV.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorInV.format=wtf.at(1,1);
textureDescriptorInV.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_COPY_DST;
textureDescriptorInV.width=sze.at(6,6);
textureDescriptorInV.height=sze.at(7,7); // default = 1;
textureDescriptorInV.depthOrArrayLayers=1;
textureDescriptorInV.mipLevelCount=1;
textureDescriptorInV.sampleCount=1;
textureDescriptorInV.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorInV.numViewFormats=0;
textureDescriptorInV.viewFormats=nullptr; // &textureAviewFormats[0];
textureDescriptorOut.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut.format=wtf.at(2,2);
textureDescriptorOut.usage=WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC;
textureDescriptorOut.width=sze.at(3,3);
textureDescriptorOut.height=sze.at(3,3); // default = 1;
textureDescriptorOut.depthOrArrayLayers=1;
textureDescriptorOut.mipLevelCount=1;
textureDescriptorOut.sampleCount=1;
textureDescriptorOut.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut.numViewFormats=0;
textureDescriptorOut.viewFormats=nullptr;
textureDescriptorOut2.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut2.format=wtf.at(2,2);
textureDescriptorOut2.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_COPY_DST;
textureDescriptorOut2.width=sze.at(3,3);
textureDescriptorOut2.height=sze.at(3,3); // default = 1;
textureDescriptorOut2.depthOrArrayLayers=1;
textureDescriptorOut2.mipLevelCount=1;
textureDescriptorOut2.sampleCount=1;
textureDescriptorOut2.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut2.numViewFormats=0;
textureDescriptorOut2.viewFormats=nullptr;
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorIn;
WGPU_TextureDescriptor.at(0,0,1)=textureDescriptorOut;
WGPU_TextureDescriptor.at(0,0,2)=textureDescriptorOut2;
WGPU_TextureDescriptor.at(0,0,3)=textureDescriptorInV;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
textureBindingLayoutFloat.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayoutFloat.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutFloat.multisampled=0;
textureBindingLayoutFloatM.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayoutFloatM.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutFloatM.multisampled=1;
textureBindingLayoutUint32.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_UINT;
textureBindingLayoutUint32.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutUint32.multisampled=0;
wtbl.at(1,1)=textureBindingLayoutFloat;
wtbl.at(3,3)=textureBindingLayoutFloatM;
wtbl.at(4,4)=textureBindingLayoutUint32;
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
textureViewDescriptorInV.format=wtf.at(1,1);
textureViewDescriptorInV.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorInV.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorInV.baseMipLevel=0; // default = 0
textureViewDescriptorInV.mipLevelCount=1;
textureViewDescriptorInV.baseArrayLayer=0; // default = 0
textureViewDescriptorInV.arrayLayerCount=1;
textureViewDescriptorOut.format=wtf.at(2,2);
textureViewDescriptorOut.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorOut.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorOut.baseMipLevel=0; // default = 0
textureViewDescriptorOut.mipLevelCount=1;
textureViewDescriptorOut.baseArrayLayer=0; // default = 0
textureViewDescriptorOut.arrayLayerCount=1;
textureViewDescriptorOut2.format=wtf.at(2,2);
textureViewDescriptorOut2.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorOut2.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorOut2.baseMipLevel=0; // default = 0
textureViewDescriptorOut2.mipLevelCount=1;
textureViewDescriptorOut2.baseArrayLayer=0; // default = 0
textureViewDescriptorOut2.arrayLayerCount=1;
WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorIn;
WGPU_TextureViewDescriptor.at(0,0,1)=textureViewDescriptorOut;
WGPU_TextureViewDescriptor.at(0,0,2)=textureViewDescriptorOut2;
WGPU_TextureViewDescriptor.at(0,0,3)=textureViewDescriptorInV;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;
bufferDescriptorI={u64_bfrSze.at(1,1),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
bufferDescriptorO={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,EM_FALSE};
bufferDescriptorM={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
bufferDescriptorC={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,3));
// bufferDescriptor_iTime={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
bufferDescriptor_iTime={sizeof(float),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(0,0)=bufferDescriptor_iTime;
uni_iTime_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(0,0));
wb.at(0,0)=uni_iTime_Buffer;
bufferDescriptor_iFrame={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(1,1)=bufferDescriptor_iFrame;
uni_iFrame_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(1,1));
wb.at(1,1)=uni_iFrame_Buffer;
bufferDescriptor_iResolution={sizeof(float),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(2,2)=bufferDescriptor_iResolution;
uni_iResolution_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(2,2));
wb.at(2,2)=uni_iResolution_Buffer;
bufferDescriptor_iResolution_2={sizeof(float),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(5,5)=bufferDescriptor_iResolution_2;
uni_iResolution_Buffer_2=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(5,5));
wb.at(5,5)=uni_iResolution_Buffer_2;
bufferBindingLayoutR.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayoutR.hasDynamicOffset=0,
bufferBindingLayoutR.minBindingSize=sizeof(uint64_t);
wbbl.at(0,0)=bufferBindingLayoutR;
bufferBindingLayoutF.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayoutF.hasDynamicOffset=0,
bufferBindingLayoutF.minBindingSize=sizeof(float);
wbbl.at(2,2)=bufferBindingLayoutF;
Input_Image_Buffer.buffer=WGPU_Buffers.at(1,1,1);
// wicb.at(2,2)=Input_Image_Buffer;
Output_Image_Buffer.buffer=WGPU_Buffers.at(0,0,0);
// wicb.at(1,1)=Output_Image_Buffer;
Mapped_Image_Buffer.buffer=WGPU_Buffers.at(2,0,2);
// wicb.at(0,0)=Mapped_Image_Buffer;
WGpuBufferDescriptor bufferDescriptorIn={u64_bfrSze.at(1,1),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
WGpuBufferDescriptor bufferDescriptorOut={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,EM_FALSE};
wbd.at(3,3)=bufferDescriptorIn;
wbd.at(4,4)=bufferDescriptorOut;
wb.at(3,3)=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(3,3));
wb.at(4,4)=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(4,4));
    //  vert / indice buffers
bufferDescriptor_vertex.size=sizeof(FUVvertices);
bufferDescriptor_vertex.usage=WGPU_BUFFER_USAGE_VERTEX|WGPU_BUFFER_USAGE_COPY_DST;
bufferDescriptor_vertex.mappedAtCreation=EM_FALSE;
wbd.at(6,6)=bufferDescriptor_vertex;
vertAtt.offset=0;
vertAtt.shaderLocation=0;
vertAtt.format=WGPU_VERTEX_FORMAT_FLOAT32X4;
vertAtt2.offset=16;
vertAtt2.shaderLocation=1;
vertAtt2.format=WGPU_VERTEX_FORMAT_FLOAT32X2;
  WGpuVertexAttribute atts[2];
  atts[0].offset=0;
  atts[0].shaderLocation=0;
  atts[0].format=WGPU_VERTEX_FORMAT_FLOAT32X4;
  atts[1].offset=16;
  atts[1].shaderLocation=1;
  atts[1].format=WGPU_VERTEX_FORMAT_FLOAT32X2;
vertBufLayout.numAttributes=2;
vertBufLayout.attributes=atts;
vertBufLayout.arrayStride=sizeof(VertexFUV);
vertBufLayout.stepMode=WGPU_VERTEX_STEP_MODE_VERTEX;
wvbl.at(0,0)=vertBufLayout;
bufferBindingLayoutV.type=WGPU_BUFFER_BINDING_TYPE_STORAGE;
bufferBindingLayoutV.hasDynamicOffset=0,
bufferBindingLayoutV.minBindingSize=sizeof(FUVvertices);
wbbl.at(1,1)=bufferBindingLayoutV;
vertex_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(6,6));
wb.at(6,6)=vertex_Buffer;
bufferDescriptor_indice.size=36*sizeof(uint32_t);
bufferDescriptor_indice.usage=WGPU_BUFFER_USAGE_INDEX|WGPU_BUFFER_USAGE_COPY_DST;
bufferDescriptor_indice.mappedAtCreation=EM_FALSE;
wbd.at(7,7)=bufferDescriptor_indice;
indice_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(7,7));
wb.at(7,7)=indice_Buffer;
resizeSamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.lodMinClamp=0;
resizeSamplerDescriptor.lodMaxClamp=0;
// resizeSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
resizeSamplerDescriptor.maxAnisotropy=16;
wsd.at(1,1)=resizeSamplerDescriptor;
resizeSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(1,1));
wsmp.at(3,3)=resizeSampler;
shaderModuleDescriptor.code=comp_body; // wgl_cmp_src;
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
textureInV=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,3));
WGPU_Texture.at(0,0,3)=textureInV;
textureOut=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,1));
WGPU_Texture.at(0,0,1)=textureOut;
textureOut2=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,2));
WGPU_Texture.at(0,0,2)=textureOut2;
  /*
  texid.at(0,0)=77;
  extTextureDescriptor.source=texid.at(0,0);
  extTextureDescriptor.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
  wetd.at(0,0)=extTextureDescriptor;
//  extTexture=wgpu_device_import_external_texture(wd.at(0,0),&wetd.at(0,0));
//  wet.at(0,0)=extTexture;
  videoFrm.source=wib.at(0,0);
  videoFrm.origin=oxy.at(0,0);
  videoFrm.flipY=EM_TRUE;
  wicei.at(0,0)=videoFrm;
  External_Image_Texture.texture=WGPU_Texture.at(0,0,3);
External_Image_Texture.mipLevel=0;
External_Image_Texture.origin=oxyz.at(0,0);
  External_Image_Texture.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
  */
Input_Image_Texture.texture=WGPU_Texture.at(0,0,0);
Input_Image_Texture.mipLevel=0;
Input_Image_Texture.origin=oxyz.at(0,0);
Input_Image_Texture.aspect=WGPU_TEXTURE_ASPECT_ALL;
Input_Image_TextureV.texture=WGPU_Texture.at(0,0,3);
Input_Image_TextureV.mipLevel=0;
Input_Image_TextureV.origin=oxyz.at(0,0);
Input_Image_TextureV.aspect=WGPU_TEXTURE_ASPECT_ALL;
Output_Image_Texture.texture=WGPU_Texture.at(0,0,1);
Output_Image_Texture.origin=oxyz.at(0,0);
Output_Image_Texture.mipLevel=0;
Output_Image_Texture.aspect=WGPU_TEXTURE_ASPECT_ALL;
Output_Image_Texture2.texture=WGPU_Texture.at(0,0,2);
Output_Image_Texture2.mipLevel=0;
Output_Image_Texture2.origin=oxyz.at(0,0);
Output_Image_Texture2.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(2,2)=Input_Image_Texture;
wict.at(1,1)=Output_Image_Texture;
wict.at(3,3)=Output_Image_Texture2;
wict.at(4,4)=Input_Image_TextureV;
//  wictt.at(0,0)=External_Image_Texture;
INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
INVTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,3),&WGPU_TextureViewDescriptor.at(0,0,3));
OUTTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,1),&WGPU_TextureViewDescriptor.at(0,0,1));
OUTTexture2View=wgpu_texture_create_view(WGPU_Texture.at(0,0,2),&WGPU_TextureViewDescriptor.at(0,0,2));
wtv.at(3,3)=INTextureView;
wtv.at(4,4)=OUTTextureView;
wtv.at(5,5)=OUTTexture2View;
wtv.at(6,6)=INVTextureView;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
videoTextureDescriptor.format=wtf.at(2,2);
videoTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_DST;
videoTextureDescriptor.width=sze.at(0,0);
videoTextureDescriptor.height=sze.at(0,0); // default = 1;
videoTextureDescriptor.depthOrArrayLayers=1;
videoTextureDescriptor.mipLevelCount=1;
videoTextureDescriptor.sampleCount=1;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
// videoViewFormats[0]={wtf.at(0,0)};
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
      // Compute Input Buffer
Compute_Bindgroup_Layout_Entries[0].binding=0;
Compute_Bindgroup_Layout_Entries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
        // Compute Output Buffer
Compute_Bindgroup_Layout_Entries[1].binding=1;
Compute_Bindgroup_Layout_Entries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
          // Compute Input Texture
Compute_Bindgroup_Layout_Entries[2].binding=2;
Compute_Bindgroup_Layout_Entries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Compute_Bindgroup_Layout_Entries[2].layout.texture=wtbl.at(1,1);
          // Compute Output Texture
Compute_Bindgroup_Layout_Entries[3].binding=3;
Compute_Bindgroup_Layout_Entries[3].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Compute_Bindgroup_Layout_Entries[3].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
            //  Compute Sampler
Compute_Bindgroup_Layout_Entries[4].binding=4;
Compute_Bindgroup_Layout_Entries[4].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Compute_Bindgroup_Layout_Entries[4].layout.sampler=wsbl.at(0,0);
            // Compute Time Uniform
Compute_Bindgroup_Layout_Entries[5].binding=5;
Compute_Bindgroup_Layout_Entries[5].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[5].layout.buffer=wbbl.at(2,2);
            // Compute Video Texture
Compute_Bindgroup_Layout_Entries[6].binding=6;
Compute_Bindgroup_Layout_Entries[6].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[6].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Compute_Bindgroup_Layout_Entries[6].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
            // Compute Resize Texture
Compute_Bindgroup_Layout_Entries[7].binding=7;
Compute_Bindgroup_Layout_Entries[7].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[7].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Compute_Bindgroup_Layout_Entries[7].layout.texture=wtbl.at(1,1);
              // Compute Video Input Texture
Compute_Bindgroup_Layout_Entries[8].binding=8;
Compute_Bindgroup_Layout_Entries[8].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[8].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Compute_Bindgroup_Layout_Entries[8].layout.texture=wtbl.at(1,1);
            // Compute Color Attachment Texture
// Compute_Bindgroup_Layout_Entries[7].binding=7;
// Compute_Bindgroup_Layout_Entries[7].visibility=WGPU_SHADER_STAGE_COMPUTE;
// Compute_Bindgroup_Layout_Entries[7].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
// Compute_Bindgroup_Layout_Entries[7].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
WGPU_Compute_Bindgroup_Layout_Entries.at(0,0,0)=Compute_Bindgroup_Layout_Entries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(wd.at(0,0),WGPU_Compute_Bindgroup_Layout_Entries.at(0,0,0),9);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(wd.at(0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(wd.at(0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
      // Compute Input Buffer
Compute_Bindgroup_Entries[0]={};
Compute_Bindgroup_Entries[0].binding=0;
Compute_Bindgroup_Entries[0].resource=WGPU_Buffers.at(1,1,1);
Compute_Bindgroup_Entries[0].bufferBindOffset=0;
Compute_Bindgroup_Entries[0].bufferBindSize=InputBufferBytes;
        // Compute Output Buffer
Compute_Bindgroup_Entries[1]={};
Compute_Bindgroup_Entries[1].binding=1;
Compute_Bindgroup_Entries[1].resource=WGPU_Buffers.at(0,0,0);
Compute_Bindgroup_Entries[1].bufferBindOffset=0;
Compute_Bindgroup_Entries[1].bufferBindSize=OutputBufferBytes;
          // Compute Input Texture
Compute_Bindgroup_Entries[2]={};
Compute_Bindgroup_Entries[2].binding=2;
Compute_Bindgroup_Entries[2].resource=wtv.at(3,3);
          // Compute Output Texture
Compute_Bindgroup_Entries[3]={};
Compute_Bindgroup_Entries[3].binding=3;
Compute_Bindgroup_Entries[3].resource=wtv.at(4,4);
            //  Compute Sampler
Compute_Bindgroup_Entries[4]={};
Compute_Bindgroup_Entries[4].binding=4;
Compute_Bindgroup_Entries[4].resource=wsmp.at(3,3);
            // Compute iTime Uniform
Compute_Bindgroup_Entries[5].binding=5;
Compute_Bindgroup_Entries[5].resource=wb.at(0,0);
Compute_Bindgroup_Entries[5].bufferBindOffset=0;
Compute_Bindgroup_Entries[5].bufferBindSize=sizeof(float);
            // Compute Video Texture
Compute_Bindgroup_Entries[6]={};
Compute_Bindgroup_Entries[6].binding=6;
Compute_Bindgroup_Entries[6].resource=wtv.at(2,2); 
            // Compute Resize Texture
Compute_Bindgroup_Entries[7]={};
Compute_Bindgroup_Entries[7].binding=7;
Compute_Bindgroup_Entries[7].resource=wtv.at(5,5);
              // Compute Video In Texture
Compute_Bindgroup_Entries[8]={};
Compute_Bindgroup_Entries[8].binding=8;
Compute_Bindgroup_Entries[8].resource=wtv.at(6,6);
            // Compute Color Attachment Texture
// Compute_Bindgroup_Entries[7]={};
// Compute_Bindgroup_Entries[7].binding=7;
// Compute_Bindgroup_Entries[7].resource=wtv.at(1,1); 
WGPU_BindGroupEntries.at(0,0,0)=Compute_Bindgroup_Entries;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(wd.at(0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),9);
WGpuComputePassTimestampWrites computePassTimestampWrites={};
computePassTimestampWrites.querySet=0;
computePassDescriptor.timestampWrites=computePassTimestampWrites;
WGPU_ComputePassDescriptor.at(0,0,0)=computePassDescriptor;
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(wd.at(0,0));
multiSamp.count=1;
multiSamp.mask=-1;
multiSamp2.count=1;
multiSamp2.mask=-1;
shaderModuleDescV.code=vert_body;
vs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescV);
shaderModuleDescF.code=frag_body;
shaderModuleDescF2.code=frag_body3;
fs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF);
fs2=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF2);
colorTarget32.format=wtf.at(2,2); // wtf.at(0,0);
colorTarget32.writeMask=15;
colorTarget.format=wtf.at(0,0);
colorTarget.writeMask=15;
depthState2.format=wtf.at(4,4);
depthState2.depthWriteEnabled=0;
depthState2.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;
depthState.format=wtf.at(4,4);
depthState.depthWriteEnabled=0;
depthState.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;
vertState.module=vs;
vertState.entryPoint="main";
vertState.numBuffers=1;
vertState.buffers=&wvbl.at(0,0);
vertState.numConstants=0;
vertState.constants=nullptr;
priState.topology=WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // Defaults to WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ('triangle-list')
// priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32; // Defaults to undefined, must be explicitly specified if WGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP ('line-strip') or WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ('triangle-strip') is used.
priState.frontFace=WGPU_FRONT_FACE_CW; // Defaults to WGPU_FRONT_FACE_CCW ('ccw')
priState.cullMode=WGPU_CULL_MODE_NONE; // Defaults to WGPU_CULL_MODE_NONE ('none')
priState.unclippedDepth=EM_FALSE; // defaults to EM_FALSE.
fragState.module=fs;
fragState.entryPoint="main";
fragState.numTargets=1;
fragState.targets=&colorTarget32;
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
videoSamplerDescriptor.lodMaxClamp=0;  //  default=32
// videoSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
videoSamplerDescriptor.maxAnisotropy=32;
wsd.at(0,0)=videoSamplerDescriptor;
videoSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(0,0));
wsmp.at(0,0)=videoSampler;
/*
videoTextureCopy.texture=wt.at(2,2);
videoTextureCopy.mipLevel=0;
videoTextureCopy.origin=oxyz.at(0,0);
videoTextureCopy.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(0,0)=videoTextureCopy;
  */
samplerBindingLayout.type=WGPU_SAMPLER_BINDING_TYPE_FILTERING;
wsbl.at(1,1)=samplerBindingLayout;
  //  Render Sampler
Render_Bindgroup_Layout_Entries[0]={};
Render_Bindgroup_Layout_Entries[0].binding=0;
Render_Bindgroup_Layout_Entries[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Render_Bindgroup_Layout_Entries[0].layout.sampler=wsbl.at(1,1);
  //  Render iTime Buffer
Render_Bindgroup_Layout_Entries[1]={};
Render_Bindgroup_Layout_Entries[1].binding=7;
Render_Bindgroup_Layout_Entries[1].visibility=WGPU_SHADER_STAGE_FRAGMENT|WGPU_SHADER_STAGE_VERTEX;;
Render_Bindgroup_Layout_Entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries[1].layout.buffer=wbbl.at(2,2);
  //  Render TextureIN
Render_Bindgroup_Layout_Entries[2]={};
Render_Bindgroup_Layout_Entries[2].binding=2;
Render_Bindgroup_Layout_Entries[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Render_Bindgroup_Layout_Entries[2].layout.texture=wtbl.at(1,1);
  //  Render iResolution Buffer
Render_Bindgroup_Layout_Entries[3]={};
Render_Bindgroup_Layout_Entries[3].binding=5;
Render_Bindgroup_Layout_Entries[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries[3].layout.buffer=wbbl.at(2,2);
  //  Render iFrame Buffer
Render_Bindgroup_Layout_Entries[4]={};
Render_Bindgroup_Layout_Entries[4].binding=6;
Render_Bindgroup_Layout_Entries[4].visibility=WGPU_SHADER_STAGE_FRAGMENT|WGPU_SHADER_STAGE_VERTEX;
Render_Bindgroup_Layout_Entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries[4].layout.buffer=wbbl.at(0,0);
wbgle.at(0,0)=Render_Bindgroup_Layout_Entries;
bindgroup_layout=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(0,0),5);
wbgl.at(0,0)=bindgroup_layout;
  //  Render_2 Sampler
Render_Bindgroup_Layout_Entries_2[0]={};
Render_Bindgroup_Layout_Entries_2[0].binding=0;
Render_Bindgroup_Layout_Entries_2[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Render_Bindgroup_Layout_Entries_2[0].layout.sampler=wsbl.at(1,1);
  //  Render_2 iTime Buffer
Render_Bindgroup_Layout_Entries_2[1]={};
Render_Bindgroup_Layout_Entries_2[1].binding=7;
Render_Bindgroup_Layout_Entries_2[1].visibility=WGPU_SHADER_STAGE_FRAGMENT|WGPU_SHADER_STAGE_VERTEX;
Render_Bindgroup_Layout_Entries_2[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries_2[1].layout.buffer=wbbl.at(2,2);
  //  Render_2 TextureIN
Render_Bindgroup_Layout_Entries_2[2]={};
Render_Bindgroup_Layout_Entries_2[2].binding=2;
Render_Bindgroup_Layout_Entries_2[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Render_Bindgroup_Layout_Entries_2[2].layout.texture=wtbl.at(1,1);
  //  Render_2 iResolution Buffer
Render_Bindgroup_Layout_Entries_2[3]={};
Render_Bindgroup_Layout_Entries_2[3].binding=5;
Render_Bindgroup_Layout_Entries_2[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries_2[3].layout.buffer=wbbl.at(2,2);
  //  Render_2 iFrame Buffer
Render_Bindgroup_Layout_Entries_2[4]={};
Render_Bindgroup_Layout_Entries_2[4].binding=6;
Render_Bindgroup_Layout_Entries_2[4].visibility=WGPU_SHADER_STAGE_FRAGMENT|WGPU_SHADER_STAGE_VERTEX;
Render_Bindgroup_Layout_Entries_2[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries_2[4].layout.buffer=wbbl.at(0,0);
wbgle.at(1,1)=Render_Bindgroup_Layout_Entries_2;
bindgroup_layout_2=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(1,1),5);
wbgl.at(1,1)=bindgroup_layout_2;
WGpuPipelineLayout pipeline_layout=wgpu_device_create_pipeline_layout(wd.at(0,0),&wbgl.at(0,0),1);
wrpl.at(0,0)=pipeline_layout;
WGpuRenderPipelineDescriptor renderPipelineDesc={};
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
WGpuRenderPipelineDescriptor renderPipelineDesc2={};
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
Render_Bindgroup_Entries[0]={};
Render_Bindgroup_Entries[0].binding=0;
Render_Bindgroup_Entries[0].resource=wsmp.at(0,0);
    //  Render iTime Buffer
Render_Bindgroup_Entries[1].binding=7;
Render_Bindgroup_Entries[1].resource=wb.at(0,0);
Render_Bindgroup_Entries[1].bufferBindOffset=0;
Render_Bindgroup_Entries[1].bufferBindSize=sizeof(float);
  //  Render TextureIN
Render_Bindgroup_Entries[2]={};
Render_Bindgroup_Entries[2].binding=2;
Render_Bindgroup_Entries[2].resource=wtv.at(2,2);
  //  Render iResolution Buffer
Render_Bindgroup_Entries[3]={};
Render_Bindgroup_Entries[3].binding=5;
Render_Bindgroup_Entries[3].resource=wb.at(2,2);
Render_Bindgroup_Entries[3].bufferBindOffset=0;
Render_Bindgroup_Entries[3].bufferBindSize=sizeof(float);
  //  Render iFrame Buffer
Render_Bindgroup_Entries[4]={};
Render_Bindgroup_Entries[4].binding=6;
Render_Bindgroup_Entries[4].resource=wb.at(1,1);
Render_Bindgroup_Entries[4].bufferBindOffset=0;
Render_Bindgroup_Entries[4].bufferBindSize=sizeof(uint64_t);
wbge.at(0,0)=Render_Bindgroup_Entries;
    //  Render_2 Sampler
Render_Bindgroup_Entries_2[0]={};
Render_Bindgroup_Entries_2[0].binding=0;
Render_Bindgroup_Entries_2[0].resource=wsmp.at(0,0);
    //  Render_2 iTime Buffer
Render_Bindgroup_Entries_2[1].binding=7;
Render_Bindgroup_Entries_2[1].resource=wb.at(0,0);
Render_Bindgroup_Entries_2[1].bufferBindOffset=0;
Render_Bindgroup_Entries_2[1].bufferBindSize=sizeof(float);
  //  Render_2 TextureIN
Render_Bindgroup_Entries_2[2]={};
Render_Bindgroup_Entries_2[2].binding=2;
Render_Bindgroup_Entries_2[2].resource=wtv.at(2,2);
  //  Render_2 iResolution Buffer
Render_Bindgroup_Entries_2[3]={};
Render_Bindgroup_Entries_2[3].binding=5;
Render_Bindgroup_Entries_2[3].resource=wb.at(5,5);
Render_Bindgroup_Entries_2[3].bufferBindOffset=0;
Render_Bindgroup_Entries_2[3].bufferBindSize=sizeof(float);
  //  Render_2 iFrame Buffer
Render_Bindgroup_Entries_2[4]={};
Render_Bindgroup_Entries_2[4].binding=6;
Render_Bindgroup_Entries_2[4].resource=wb.at(1,1);
Render_Bindgroup_Entries_2[4].bufferBindOffset=0;
Render_Bindgroup_Entries_2[4].bufferBindSize=sizeof(uint64_t);
wbge.at(1,1)=Render_Bindgroup_Entries_2;
colorTextureViewDescriptor.format=wtf.at(0,0);
colorTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
colorTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
colorTextureViewDescriptor.baseMipLevel=0; // default = 0
colorTextureViewDescriptor.mipLevelCount=1;
colorTextureViewDescriptor.baseArrayLayer=0; // default = 0
colorTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(1,1)=colorTextureViewDescriptor;
  /*
depthTextureViewDescriptor.format=wtf.at(5,5);
depthTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
depthTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
depthTextureViewDescriptor.baseMipLevel=0; // default = 0
depthTextureViewDescriptor.mipLevelCount=1;
depthTextureViewDescriptor.baseArrayLayer=0; // default = 0
depthTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(0,0)=depthTextureViewDescriptor;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthTextureDescriptor.format=wtf.at(5,5);
depthTextureDescriptor.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
depthTextureDescriptor.width=sze.at(0,0);
depthTextureDescriptor.height=sze.at(0,0); // default = 1;
depthTextureDescriptor.depthOrArrayLayers=1;
depthTextureDescriptor.mipLevelCount=1;
depthTextureDescriptor.sampleCount=1;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthViewFormats[0]={wtf.at(5,5)};
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
depthViewFormats2[0]={wtf.at(5,5)};
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
  */
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
wgpu_queue_write_buffer(wq.at(0,0),wb.at(6,6),0,FUVvertices,sizeof(FUVvertices));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(7,7),0,indices,36*sizeof(uint32_t));
// tme=get_current_time_in_milliseconds();
// wTime.iTime=get_current_time_in_milliseconds();
bindgroup=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(0,0),wbge.at(0,0),5);
wbg.at(0,0)=bindgroup;
bindgroup_2=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(1,1),wbge.at(1,1),5);
wbg.at(1,1)=bindgroup_2;
u64_uni.at(0,0)=0;
u64_uni.at(3,3)=0;
f32_uniform.at(0,0)=0.0f;
d64_uniform.at(0,0)=0.0;
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
if(on.at(0,0)!=0){emscripten_cancel_main_loop();}
emscripten_set_main_loop((void(*)())raf,0,0);
on.at(0,0)=1;
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
wa.at(0,0)=result;
// deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8;
deviceDesc.requiredFeatures=WGPU_FEATURE_FLOAT32_FILTERABLE;
// deviceDesc.requiredFeatures=WGPU_FEATURE_RG11B10UFLOAT_RENDERABLE;
// WGPU_FEATURES_BITFIELD ftr=wgpu_adapter_or_device_get_features(wa.at(0,0));
// deviceDesc.requiredFeatures=ftr;
  /*
WGpuSupportedLimits lmts;
lmts.maxUniformBufferBindingSize=sizeof(uint64_t);
lmts.maxStorageBufferBindingSize=1*1024*1024;
lmts.maxBufferSize=1*1024*1024;
lmts.maxColorAttachmentBytesPerSample=64;
wgpu_adapter_or_device_get_limits(wa.at(0,0),&lmts);
  */
// deviceDesc.requiredLimits=lmts;
wdd.at(0,0)=deviceDesc;
wgpu_adapter_request_device_async(wa.at(0,0),&wdd.at(0,0),ObtainedWebGpuDeviceStart,0);
}

EM_BOOL WGPU_Start(int sz){
sze.at(1,1)=sz;
sze.at(6,6)=1280;
sze.at(7,7)=720;
f32_uniform.at(2,2)=float(sze.at(1,1));
szef.at(1,1)=float(sze.at(1,1));
options.powerPreference=WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
options.forceFallbackAdapter=EM_FALSE;
wao.at(0,0)=options;
navigator_gpu_request_adapter_async(&wao.at(0,0),ObtainedWebGpuAdapterStart,0);
return EM_TRUE;
}

#include "../../src/vanilla/webgpu_compute_js_tex3.cpp"

extern"C"{

void frmOn(){
texOn();
return;
}

void frmsOff(){
framesOff();
return;
}

void startWebGPUi(int sz){
WGPU_Start(sz);
return;
}

void startWebGPUbi(int sz){
WGPU_Start(sz);
return;
}

}

int main(){
on.at(0,0)=0;
js_main();
return 0;
}
