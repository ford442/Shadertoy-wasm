#include "../../include/vanilla/main_webgpu.h"

inline char wgl_cmp_src[2000]=
"@group(0)@binding(0)var<storage,read_write>inputBuffer:array<u32,262144>;"
"@group(0)@binding(1)var<storage,read_write>outputBuffer:array<u32,262144>;"
"@group(0)@binding(2)var textureA:texture_storage_2d<rgba32uint,write>;"
"@compute@workgroup_size(4,1,64)"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>){"
"let f:u32=global_id.z;"
"let g:u32=global_id.x;"
// "let coord:vec2<u32>=vec2<u32>(0,0);"
// "let flo:vec4<u32>=vec4<u32>(24,24,24,255);"
// "let u0:u32=0;"
// "let clr:f32=textureLoad(textureA:texture_storage_2d<u32>,coord,u0);"
// "textureStore(textureA,coord,vec4<u32>(24,24,24,255));"
"let h:u32=f*g;"
"var i: i32;"
"loop {"
"outputBuffer[f*g]=42;"
"outputBuffer[f*g]=42;"
"outputBuffer[f*g]=42;"
"outputBuffer[f*g]=1;"
"  i+=4;"
"  if i == 256 { break; }"
"}"
"}";

using mouse_tensor=boost::numeric::ublas::tensor<float>;
using shad_tensor=boost::numeric::ublas::tensor<boost::uint_t<32>::exact>;
using prg_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
using sz_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using f_tensor=boost::numeric::ublas::tensor<float>;
using d_tensor=boost::numeric::ublas::tensor<double>;
using di_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;
using i_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using iptr_tensor=boost::numeric::ublas::tensor<int *>;
using fptr_tensor=boost::numeric::ublas::tensor<float *>;
using uiptr_tensor=boost::numeric::ublas::tensor<uint32_t *>;
using gi_tensor=boost::numeric::ublas::tensor<GLint>;
using li_tensor=boost::numeric::ublas::tensor<long>;
using void_tensor=boost::numeric::ublas::tensor<void *>;
using bgle_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayoutEntry *>;
using bge_tensor=boost::numeric::ublas::tensor<WGpuBindGroupEntry *>;
using bmc_tensor=boost::numeric::ublas::tensor<WGpuBufferMapCallback>;
using wdc_tensor=boost::numeric::ublas::tensor<WGpuOnSubmittedWorkDoneCallback>;
using oac_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterCallback>;
using odc_tensor=boost::numeric::ublas::tensor<WGpuRequestDeviceCallback>;
using bbl_tensor=boost::numeric::ublas::tensor<WGpuBufferBindingLayout>;
using bd_tensor=boost::numeric::ublas::tensor<WGpuBufferDescriptor>;
using md_tensor=boost::numeric::ublas::tensor<WGpuShaderModuleDescriptor>;
using dd_tensor=boost::numeric::ublas::tensor<WGpuDeviceDescriptor>;
using rao_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterOptions>;
using wa_tensor=boost::numeric::ublas::tensor<WGpuAdapter>;
using wq_tensor=boost::numeric::ublas::tensor<WGpuQueue>;
using cb_tensor=boost::numeric::ublas::tensor<WGpuCommandBuffer>;
using wb_tensor=boost::numeric::ublas::tensor<WGpuBuffer>;
using ce_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoder>;
using wd_tensor=boost::numeric::ublas::tensor<WGpuDevice>;
using cpe_tensor=boost::numeric::ublas::tensor<WGpuComputePassEncoder>;
using cp_tensor=boost::numeric::ublas::tensor<WGpuComputePipeline>;
using pl_tensor=boost::numeric::ublas::tensor<WGpuPipelineLayout>;
using cm_tensor=boost::numeric::ublas::tensor<WGpuShaderModule>;
using bg_tensor=boost::numeric::ublas::tensor<WGpuBindGroup>;
using bgl_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayout>;
using i53_tensor=boost::numeric::ublas::tensor<double_int53_t>;
using tex_tensor=boost::numeric::ublas::tensor<WGpuTexture>;
using td_tensor=boost::numeric::ublas::tensor<WGpuTextureDescriptor>;
using stbl_tensor=boost::numeric::ublas::tensor<WGpuStorageTextureBindingLayout>;
using tv_tensor=boost::numeric::ublas::tensor<WGpuTextureView>;
using tvd_tensor=boost::numeric::ublas::tensor<WGpuTextureViewDescriptor>;
using ced_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoderDescriptor>;

static v_tensor sse=v_tensor{2,2};
static v_tensor sse2=v_tensor{2,2};
static v_tensor sse3=v_tensor{2,2};
static v_tensor sse4=v_tensor{1,1};
static shad_tensor Sh=shad_tensor{3,3};
static prg_tensor S1=prg_tensor{1,1,1};
static sz_tensor Si=sz_tensor{1,1};
static d_tensor d_time=d_tensor{2,2};
static f_tensor Fi=f_tensor{2,2};
static d_tensor Di=d_tensor{2,2};
static gi_tensor uni_i=gi_tensor{1,1};
static i_tensor i_view=i_tensor{1,2};
static i_tensor i_date=i_tensor{2,2};
static f_tensor t_size=f_tensor{1,2};
static li_tensor i_size=li_tensor{1,2};
static void_tensor cntx=void_tensor{2,2};
static i_tensor cntxi=i_tensor{2,2};
static mouse_tensor mms=mouse_tensor{2,2};
static li_tensor mms2=li_tensor{2,2};
static void_tensor bin=void_tensor{1,1};
static wa_tensor WGPU_Adapter=wa_tensor{1,1,2};
static wd_tensor WGPU_Device=wd_tensor{1,1,2};
static wq_tensor WGPU_Queue=wq_tensor{1,1,2};
static cb_tensor WGPU_CommandBuffer=cb_tensor{1,1,3};
static wb_tensor WGPU_Buffers=wb_tensor{3,3,3};
static ce_tensor WGPU_CommandEncoder=ce_tensor{1,1,4};
static cpe_tensor WGPU_ComputePassCommandEncoder=cpe_tensor{1,1,3};
static cp_tensor WGPU_ComputePipeline=cp_tensor{1,1,1};
static pl_tensor WGPU_ComputePipelineLayout=pl_tensor{1,1,1};
static cm_tensor WGPU_ComputeModule=cm_tensor{1,1,1};
static bg_tensor WGPU_BindGroup=bg_tensor{1,1,2};
static bgl_tensor WGPU_BindGroupLayout=bgl_tensor{1,1,2};
static bgle_tensor WGPU_BindGroupLayoutEntries=bgle_tensor{1,1,2};
static bge_tensor WGPU_BindGroupEntries=bge_tensor{1,1,2};
static bmc_tensor WGPU_MapCallback=bmc_tensor{1,1,3};
static wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,3};
static oac_tensor WGPU_ObtainedAdapterCallback=oac_tensor{1,1,2};
static odc_tensor WGPU_ObtainedDeviceCallback=odc_tensor{1,1,2};
static bbl_tensor WGPU_BufferBindingLayout=bbl_tensor{1,1,4};
static bd_tensor WGPU_BufferDescriptor=bd_tensor{1,1,4};
static md_tensor WGPU_ShaderModuleDescriptor=md_tensor{1,1,3};
static di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1};
static void_tensor WGPU_UserData=void_tensor{1,1,2};
static rao_tensor WGPU_RequestAdapterOptions=rao_tensor{1,1,1};
static dd_tensor WGPU_DeviceDescriptor=dd_tensor{1,1,1};
static uiptr_tensor WGPU_ResultBuffer=uiptr_tensor{1,1,1};
static uiptr_tensor WGPU_InputBuffer=uiptr_tensor{1,1,1};
static i53_tensor WGPU_BufferRange=i53_tensor{1,1,2};
static i53_tensor WGPU_BufferSize=i53_tensor{1,1,1};
static tex_tensor WGPU_Texture=tex_tensor{1,1,1};
static td_tensor WGPU_TextureDescriptor=td_tensor{1,1,1};
static stbl_tensor WGPU_StorageTextureBindingLayout=stbl_tensor{1,1,1};
static tvd_tensor WGPU_TextureViewDescriptor=tvd_tensor{1,1,1};
static tv_tensor WGPU_TextureView=tv_tensor{1,1,1};
static uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1};
static ced_tensor WGPU_CommandEncoderDescriptor=ced_tensor{1,1,1};

uint32_t workgroupSize=64;
uint32_t OutputBufferUnits=262144;
uint32_t OutputBufferBytes=262144*4;
uint32_t InputBufferUnits=262144;
uint32_t InputBufferBytes=262144*4;
uint64_t WGPU_InputRangeSize=OutputBufferBytes;

const char * Entry="computeStuff";
// uint32_t invocationCount=BufferMapSize/sizeof(int);
// uint32_t workgroupCount=(invocationCount+workgroupSize-1)/workgroupSize;
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE
void * userDataA;
void * userDataB;
GLsizei width=256;
GLsizei height=256;
GLuint wtexture[4];
WGpuTexture textureA;
  WGpuAdapter adapter=0;
  WGpuDevice device=0;
  WGpuQueue queue=0;
WGpuBindGroupLayout bindGroupLayout=0;
WGpuBindGroupLayout bindGroupLayoutB=0;
WGpuComputePipeline computePipeline=0;
WGpuBuffer inputBuffer=0;
WGpuBuffer outputBuffer=0;
WGpuBuffer mapBuffer=0;
WGpuBuffer uniBuffer=0;
WGpuShaderModule cs=0;
WGpuCommandBuffer commandBuffer=0;
WGpuCommandEncoder encoder=0;
WGpuComputePassEncoder computePass=0;
WGpuBindGroup bindGroup=0;
WGpuBindGroup bindGroupB=0;
WGpuPipelineLayout pipelineLayout=0;
WGpuQuerySet querySet=0;
WGpuComputePassDescriptor computePassDescriptor={};
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuDeviceDescriptor deviceDescriptor={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[3]={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntriesB[2]={};
WGpuBindGroupEntry bindGroupEntry[3]={};
WGpuBindGroupEntry bindGroupEntryB[2]={};
WGpuBufferBindingLayout bufferBindingLayout1={3};
WGpuBufferBindingLayout bufferBindingLayout2={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferBindingLayout bufferBindingLayout4={2};
WGpuStorageTextureBindingLayout storageTextureBindingLayout1={1,34,2};
WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false};
std::vector<float>color_input(InputBufferUnits);
std::vector<uint8_t>input(InputBufferBytes);
std::vector<uint8_t>outputd(OutputBufferBytes);
std::vector<uint8_t>outpute(OutputBufferBytes);
WGpuBufferDescriptor bufferDescriptorI={InputBufferBytes,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorO={OutputBufferBytes,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
WGpuBufferDescriptor bufferDescriptorM={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorC={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
// 14 = R32FLOAT   34 = RGBA32UINT
WGpuTextureDescriptor textureDescriptorA={256,256,1,1,1,2,34,WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC|WGPU_TEXTURE_USAGE_COPY_DST};
WGpuTextureViewDescriptor textureViewDescriptorA={34,WGPU_TEXTURE_VIEW_DIMENSION_2D};
char * cmp_bdy=wgl_cmp_src;
WGpuShaderModuleDescriptor shaderModuleDescriptor={cmp_bdy,0,NULL};
int randomNumber=0,entropySeed=0;
std::random_device randomizer;
int raN=0;
int raND=0;
uint32_t * WGPU_Result_Array=new uint32_t[OutputBufferBytes];
uint32_t * WGPU_Input_Array=new uint32_t[InputBufferBytes];
uint32_t * WGPU_Color_Input_Array=new uint32_t[InputBufferBytes];
WGpuImageCopyTexture WGPU_Input_Image={};
WGpuImageCopyTexture WGPU_Output_Image={};
WGpuImageCopyBuffer WGPU_Input_Buffer={};
WGpuImageCopyBuffer WGPU_Output_Buffer={};
WGpuImageCopyBuffer WGPU_Mapped_Buffer={};
inline int rNd4(int randomMax){
entropySeed=(randomMax)*randomizer();
std::srand(entropySeed);
randomNumber=std::rand()%randomMax;
return randomNumber;
}

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
double_int53_t WGPU_Range_Pointer=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(1,0,1),0,size);
WGPU_BufferRange.at(0,0,0)=WGPU_Range_Pointer;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(1,0,1),0,0,WGPU_ResultBuffer.at(0,0,0),size);
std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
std::cout << "\n" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[1] << std::endl;
std::cout << "\n" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[2] << std::endl;
std::cout << "\n" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[3] << std::endl;
wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
// wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
return;
};

WGpuBufferMapCallback mapCallbackRun=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
WGPU_BufferSize.at(0,0,0)=size;
std::cout << "Output buffer size:" << std::endl;
std::cout << "\n" << std::endl;
std::cout << uint32_t(WGPU_BufferSize.at(0,0,0)) << std::endl;
double_int53_t WGPU_Range_Pointer=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(1,0,1),0,size);
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(1,0,1),WGPU_Range_Pointer,0,WGPU_ResultBuffer.at(0,0,0),size);
std::cout << "Output buffer:" << std::endl;
std::cout << "\n" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
return;
};

WGpuBufferMapCallback mapCallbackRun2=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
double_int53_t WGPU_Range_Pointer=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),WGPU_Range_Pointer,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
std::cout << "End Buffer:" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
std::cout << "----------" << std::endl;
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
  //  wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);
double_int53_t WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
// WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2), 0 ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
std::cout << "Mapped range of result buffer:" << std::endl;
std::cout << "\n" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
std::cout << "\n" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[1] << std::endl;
std::cout << "\n" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[2] << std::endl;
std::cout << "\n" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[3] << std::endl;
WGPU_BUFFER_MAP_STATE stateb=wgpu_buffer_map_state(WGPU_Buffers.at(1,0,1));
if(stateb=='mapped'){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
 }
//   wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
// wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),mapCallbackStart,&WGPU_UserData.at(0,0,0),mode1,0,WGPU_InputRangeSize);
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun=[](WGpuQueue queue,void *userData){
  std::cout << "On Run 1" << std::endl;
// wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),WGPU_MapCallback.at(0,0,1),&WGPU_UserData.at(0,0,0),mode1,0,WGPU_InputRangeSize);
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun2=[](WGpuQueue queue,void *userData){
double_int53_t WGPU_Range_Pointer=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),WGPU_Range_Pointer,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
std::cout << "End Buffer:" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
std::cout << "----------" << std::endl;
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
// wgpu_buffer_map_async(WGPU_Buffers.at(2,0,2),WGPU_MapCallback.at(0,0,2),&WGPU_UserData.at(0,0,0),mode1,0,WGPU_InputRangeSize);
return;
};

static void raf(){
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorA;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorA;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;
WGPU_ColorBuffer.at(0,0,0)=WGPU_Color_Input_Array;
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,3));
WGPU_Output_Buffer.buffer=WGPU_Buffers.at(0,0,0);
WGPU_Output_Buffer.bytesPerRow=4096;
WGPU_Output_Buffer.rowsPerImage=256;
WGPU_Mapped_Buffer.buffer=WGPU_Buffers.at(2,0,2);
WGPU_Mapped_Buffer.bytesPerRow=4096;
WGPU_Mapped_Buffer.rowsPerImage=256;
raN=rNd4(1024);
input[0]=raN;
WGPU_InputBuffer.at(0,0,0)[0]=raN;
std::cout << "Random input int:" << std::endl;
std::cout << raN << std::endl;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(WGPU_Device.at(0,0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayout1;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayout2;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
WGPU_BufferBindingLayout.at(0,0,4)=bufferBindingLayout4;
WGPU_StorageTextureBindingLayout.at(0,0,0)=storageTextureBindingLayout1;
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=1;
bindGroupLayoutEntries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=1;
bindGroupLayoutEntries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
bindGroupLayoutEntries[2].binding=2;
bindGroupLayoutEntries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[2].type=4;
bindGroupLayoutEntries[2].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
WGPU_BindGroupLayoutEntries.at(0,0,0)=bindGroupLayoutEntries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(WGPU_Device.at(0,0,0),WGPU_BindGroupLayoutEntries.at(0,0,0),2);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(WGPU_Device.at(0,0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(WGPU_Device.at(0,0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=WGPU_Buffers.at(1,1,1);
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=InputBufferBytes;
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=WGPU_Buffers.at(0,0,0);
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=OutputBufferBytes;
bindGroupEntry[2].binding=2;
bindGroupEntry[2].resource=WGPU_Texture.at(0,0,0);
WGPU_BindGroupEntries.at(0,0,0)=bindGroupEntry;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(WGPU_Device.at(0,0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),2);
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_Queue.at(0,0,1)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,2)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,&WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
// wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&WGPU_Input_Image,&WGPU_ColorBuffer.at(0,0,0),1024,0,1,1,1);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
 // wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
//  WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,3));
// wgpu_object_destroy(WGPU_Buffers.at(2,0,2));
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(1,0,1),0,OutputBufferBytes);
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(1,0,1),0,OutputBufferBytes);
 wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
  // wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
return;
}

static void WGPU_Run(){
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,1)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
/*
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,1),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,1),0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,&input,InputBufferBytes);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),64,4,1);
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,1),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,1),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(1,0,1),0,OutputBufferBytes);
WGPU_CommandBuffer.at(0,0,1)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,1));
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,1));
*/
double_int53_t WGPU_Range_Pointer=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),WGPU_Range_Pointer,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
std::cout << "End Buffer:" << std::endl;
std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
std::cout << "----------" << std::endl;
return;
}

static void WGPU_Run2(){
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,2)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,2),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,2),0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,&input,InputBufferBytes);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),64,4,1);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,2),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(1,0,1),0,OutputBufferBytes);
WGPU_CommandBuffer.at(0,0,2)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,2));
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,2));
return;
}

static void ObtainedWebGpuDeviceStart2(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,1)=result;
 //  wgpu_is_device(WGPU_Device.at(0,0,1));
raf();
return;
}

static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,0)=result;
 //  wgpu_is_device(WGPU_Device.at(0,0,0));
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,1),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}

static void ObtainedWebGpuAdapterStart2(WGpuAdapter result,void * userData){
WGPU_Adapter.at(0,0,1)=result;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,0),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
}

static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData){
adapter=result;
WGPU_Adapter.at(0,0,0)=result;
WGPU_ObtainedDeviceCallback.at(0,0,0)=ObtainedWebGpuDeviceStart;
WGPU_ObtainedDeviceCallback.at(0,0,1)=ObtainedWebGpuDeviceStart2;
navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}

void WGPU_Start(){
WGPU_UserData.at(0,0,0)=userDataA;
WGPU_UserData.at(0,0,1)=userDataB;
WGPU_DeviceDescriptor.at(0,0,0)=deviceDescriptor;
WGPU_RequestAdapterOptions.at(0,0,0)=options;
WGPU_ObtainedAdapterCallback.at(0,0,0)=ObtainedWebGpuAdapterStart;
WGPU_ObtainedAdapterCallback.at(0,0,1)=ObtainedWebGpuAdapterStart2;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
WGPU_ComputeDoneCallback.at(0,0,1)=onComputeDoneRun;
WGPU_ComputeDoneCallback.at(0,0,2)=onComputeDoneRun2;
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
WGPU_MapCallback.at(0,0,1)=mapCallbackRun;
WGPU_MapCallback.at(0,0,2)=mapCallbackRun2;
 navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
//  WGPU_Adapter.at(0,0,0)=navigator_gpu_request_adapter_sync(&WGPU_RequestAdapterOptions.at(0,0,0));
//  WGPU_Adapter.at(0,0,1)=navigator_gpu_request_adapter_sync(&WGPU_RequestAdapterOptions.at(0,0,0));
 // wgpu_adapter_request_device_sync(WGPU_Adapter.at(0,0,0),&WGPU_DeviceDescriptor.at(0,0,0));
//  wgpu_adapter_request_device_sync(WGPU_Adapter.at(0,0,1),&WGPU_DeviceDescriptor.at(0,0,0));
 // raf();
return;
}

EM_JS(void,js_main,(),{

function normalResStart(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
Module.ccall("startWebGPU",{async:true});
setTimeout(function(){
// Module.ccall("runWebGPU");
},1500);
setTimeout(function(){
// Module.ccall("runWebGPU2");
},2500);
});
}

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);

const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var $lt=tem.innerHTML;

function grab$lt(){
$lt=Math.round($lt);
}

$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
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
document.getElementById('menu').addEventListener('click',function(){
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

document.getElementById('startBtn').addEventListener('click',function(){
normalResStart();
});

setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},500);

});

extern"C"{

void startWebGPU(){
WGPU_Start();
}

void runWebGPU(){
WGPU_Run();
}

void runWebGPU2(){
WGPU_Run2();
}

}

int main(void){
js_main();
 // WGPU_Start();
return 0;
}
