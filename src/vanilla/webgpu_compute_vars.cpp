WGPUImageCopyBuffer videoFrmBfrSrc={};
WGPUImageCopyBuffer videoFrmBfrDst={};
WGpuImageCopyTexture videoTextureCopy;
WGpuExternalTexture extTexture;
WGpuExternalTextureBindingLayout extTextureBindingLayout={};
WGpuExternalTextureDescriptor extTextureDescriptor={};
WGpuTextureView depthTextureView;
WGpuTextureView colorTextureView;
WGpuTextureView videoTextureView;
WGpuTextureView INTextureView;
WGpuTextureView OUTTextureView;
WGpuTextureViewDescriptor depthTextureViewDescriptor={};
WGpuTextureViewDescriptor colorTextureViewDescriptor={};
WGpuTextureViewDescriptor videoTextureViewDescriptor={};
WGpuTextureViewDescriptor INTextureViewDescriptor={};
WGpuTextureViewDescriptor OUTTextureViewDescriptor={};
WGpuRenderPassColorAttachment colorAttachment;
WGpuRenderPassDepthStencilAttachment depthAttachment;
WGpuTexture depthTexture;
WGpuTexture colorTexture;
WGpuTexture videoTexture;
WGpuTexture textureIn;
WGpuTexture textureOut;
WGpuSampler videoSampler={};
WGpuSampler resizeSampler={};
WGpuTexture __128bit_Texture__;
WGpuTextureDescriptor highbitTextureDescriptor={};
WGpuBufferDescriptor bufferDescriptorSrc={};
WGpuBufferDescriptor bufferDescriptorDst={};
WGpuBufferDescriptor bufferDescriptorVid={};
WGpuSamplerDescriptor resizeSamplerDescriptor={};
WGpuSamplerDescriptor videoSamplerDescriptor={};
WGpuTextureDescriptor depthTextureDescriptor={};
WGpuTextureDescriptor colorTextureDescriptor={};
WGpuTextureDescriptor videoTextureDescriptor={};
WGpuRenderPassDescriptor passDesc={};
WGpuCanvasConfiguration config;
WGpuShaderModuleDescriptor shaderModuleDescV={};
WGpuShaderModuleDescriptor shaderModuleDescF={};
WGpuShaderModule vs;
WGpuShaderModule fs;
WGpuDepthStencilState depthState;
WGpuVertexState vertState;
WGpuPrimitiveState priState;
WGpuFragmentState fragState;
WGpuFragmentState fragState2;
WGpuBufferDescriptor bufferDescriptorUni={};
WGpuBufferDescriptor bufferDescriptor_iTime={};
WGpuBufferDescriptor bufferDescriptor_iResolution={};
WGpuBufferDescriptor bufferDescriptor_iFrame={};
WGpuBufferDescriptor bufferDescriptor_iTimeDelta={};
WGpuBindGroupLayout bindgroup_layout=0;
WGpuBindGroupLayoutEntry Render_Bindgroup_Layout_Entries[4]={};
WGpuBindGroupEntry Render_Bindgroup_Entries[4]={};
WGpuBindGroupEntry bindgroup_entries[4]={};  //  for video.cpp
WGpuBindGroup bindgroup=0;
WGpuRenderBundleEncoder renderBundleEncoder;
WGpuRenderBundleEncoderDescriptor renderBundleEncoderDescriptor={};
WGpuDeviceDescriptor deviceDesc={};
WGpuMultisampleState multiSamp;
WGpuBuffer uniBuffer;
WGpuBuffer srcBuffer;
WGpuBuffer dstBuffer;
WGpuBuffer vidBuffer;
WGpuBuffer uni_iTime_Buffer;
WGpuBuffer uni_iTimeDelta_Buffer;
WGpuBuffer uni_iResolution_Buffer;
WGpuBuffer uni_iFrame_Buffer;
WGpuBufferBindingLayout bufferBindingLayout1={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuBufferBindingLayout bufferBindingLayoutR={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuTextureBindingLayout textureBindingLayoutFloat={};
WGpuTextureBindingLayout textureBindingLayoutDepth={};
WGpuTextureBindingLayout textureBindingLayout1={}; // for video.cpp
WGpuSamplerBindingLayout samplerBindingLayout={};
WGpuImageCopyExternalImage videoFrm={};
double szh,szw;
int szhI,szwI;
double szhDv,szwDv;
float szhFv,szwFv;
struct WGpuUniform{
uint64_t iTime;
};

struct{
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spana;
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spanb;
boost::chrono::high_resolution_clock::time_point t1;
boost::chrono::high_resolution_clock::time_point t2;
boost::chrono::high_resolution_clock::time_point t3;
}u_time;

WGpuUniform wTime;
uint64_t tme;

xyz_tensor oxyz=xyz_tensor{2,2};
xy_tensor oxy=xy_tensor{2,2};
wtbl_tensor wtbl=wtbl_tensor{2,2};
i_tensor on=i_tensor{3,3};
wetd_tensor wetd=wetd_tensor{2,2};
wet_tensor wet=wet_tensor{2,2};
i_tensor texid=i_tensor{2,2};
i_tensor sze=i_tensor{3,3};
f_tensor szef=f_tensor{2,2};
wce_tensor wce=wce_tensor{2,2};
wrpe_tensor wrpe=wrpe_tensor{2,2};
wcb_tensor wcb=wcb_tensor{2,2};
wd_tensor wd=wd_tensor{2,2};
wq_tensor wq=wq_tensor{2,2};
wa_tensor wa=wa_tensor{2,2};
wcc_tensor wcc=wcc_tensor{2,2};
wccf_tensor wccf=wccf_tensor{2,2};
wrp_tensor wrp=wrp_tensor{2,2};
wrp_tensor wrpl=wrp_tensor{2,2};
wb_tensor wb=wb_tensor{5,5};
wbgle_tensor wbgle=wbgle_tensor{2,2};
wbge_tensor wbge=wbge_tensor{2,2};
wbgl_tensor wbgl=wbgl_tensor{2,2};
wbg_tensor wbg=wbg_tensor{2,2};
wrpd_tensor wrpd=wrpd_tensor{2,2};
wrpca_tensor wrpca=wrpca_tensor{2,2};
wbbl_tensor wbbl=wbbl_tensor{2,2};
wsbl_tensor wsbl=wsbl_tensor{2,2};
wbd_tensor wbd=wbd_tensor{5,5};
wao_tensor wao=wao_tensor{2,2};
wdd_tensor wdd=wdd_tensor{2,2};
u64_tensor u64_uni=u64_tensor{4,4};
u64_tensor u64_siz=u64_tensor{4,4};
wrbe_tensor wrbe=wrbe_tensor{2,2};
wrbed_tensor wrbed=wrbed_tensor{2,2};
wrpdsa_tensor wrpdsa=wrpdsa_tensor{2,2};
wt_tensor wt=wt_tensor{3,3};
wtd_tensor wtd=wtd_tensor{3,3};
wtvd_tensor wtvd=wtvd_tensor{3,3};
wtf_tensor wtf=wtf_tensor{5,5};
wtv_tensor wtv=wtv_tensor{3,3};
wicb_tensor wicb=wicb_tensor{6,6};
wicei_tensor wicei=wicei_tensor{2,2};
js_tensor js_data_pointer=js_tensor{2,2};
fjs_tensor fjs_data_pointer=fjs_tensor{2,2};
js_data_tensor frame_tensor=js_data_tensor{2,2};
js_data_tensor64 frame_tensor64=js_data_tensor64{2,2};
u64_tensor u64_bfrSze=u64_tensor{4,4};
wict_tensor wict=wict_tensor{4,4};
wsd_tensor wsd=wsd_tensor{2,2};
ws_tensor wsmp=ws_tensor{4,4};
v_tensor imgData=v_tensor{2,2};
wq_tensor WGPU_Queue=wq_tensor{1,1,2};
wcb_tensor WGPU_CommandBuffer=wcb_tensor{1,1,3};
wb_tensor WGPU_Buffers=wb_tensor{3,3,3};
wce_tensor WGPU_CommandEncoder=wce_tensor{1,1,4};
wcpe_tensor WGPU_ComputePassCommandEncoder=wcpe_tensor{1,1,3};
wcpd_tensor WGPU_ComputePassDescriptor=wcpd_tensor{1,1,3};
wcp_tensor WGPU_ComputePipeline=wcp_tensor{1,1,1};
wpl_tensor WGPU_ComputePipelineLayout=wpl_tensor{1,1,1};
wsm_tensor WGPU_ComputeModule=wsm_tensor{1,1,1};
wbg_tensor WGPU_BindGroup=wbg_tensor{1,1,2};
wbgl_tensor WGPU_BindGroupLayout=wbgl_tensor{1,1,2};
wbgle_tensor WGPU_Compute_Bindgroup_Layout_Entries=wbgle_tensor{1,1,2};
wbge_tensor WGPU_BindGroupEntries=wbge_tensor{1,1,2};
wbmc_tensor WGPU_MapCallback=wbmc_tensor{1,1,3};
wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,3};
wbbl_tensor WGPU_BufferBindingLayout=wbbl_tensor{1,1,4};
wbd_tensor WGPU_BufferDescriptor=wbd_tensor{1,1,4};
wsmd_tensor WGPU_ShaderModuleDescriptor=wsmd_tensor{1,1,3};
di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1};
void_tensor WGPU_UserData=void_tensor{1,1,2};
fptr_tensor WGPU_ResultBuffer=fptr_tensor{1,1,1};
fptr_tensor WGPU_InputBuffer=fptr_tensor{1,1,1};
i53_tensor WGPU_BufferRange=i53_tensor{1,1,2};
i53_tensor WGPU_BufferSize=i53_tensor{1,1,1};
wt_tensor WGPU_Texture=wt_tensor{3,3,3};
wtd_tensor WGPU_TextureDescriptor=wtd_tensor{3,3,3};
wstbl_tensor WGPU_StorageTextureBindingLayout=wstbl_tensor{1,1,1};
wtvd_tensor WGPU_TextureViewDescriptor=wtvd_tensor{3,3,3};
uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1};
wced_tensor WGPU_CommandEncoderDescriptor=wced_tensor{1,1,1};
wbms_tensor WGPU_BufferStatus=wbms_tensor{1,1,1};
c_tensor wgsl=c_tensor{2,2};
uint32_t workgroupSize=64;
uint32_t OutputBufferBytes=64*4;
uint32_t InputBufferBytes=64*4;
uint64_t WGPU_InputRangeSize=OutputBufferBytes;
const char * Entry="main_image";
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE
void * userDataA;
void * userDataB;
WGpuTexture textureA;
WGpuBindGroupLayout bindGroupLayout=0;
WGpuBindGroupLayout bindGroupLayoutB=0;
WGpuComputePipeline computePipeline=0;
WGpuBuffer inputBuffer=0;
WGpuBuffer outputBuffer=0;
WGpuBuffer mapBuffer=0;
// WGpuBuffer uniBuffer=0;
WGpuShaderModule cs=0;
WGpuCommandBuffer commandBuffer=0;
WGpuCommandEncoder encoder=0;
WGpuComputePassEncoder computePass=0;
WGpuBindGroup bindGroup=0;
WGpuPipelineLayout pipelineLayout=0;
WGpuQuerySet querySet=0;
WGpuComputePassDescriptor computePassDescriptor={};
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuDeviceDescriptor deviceDescriptor={};
WGpuBindGroupLayoutEntry Compute_Bindgroup_Layout_Entries[8]={};

WGpuBindGroupLayoutEntry bindgroup_layout_entries[8]={};
WGpuShaderModuleCompilationHint shaderModuleCompilationHint={};
WGpuBindGroupEntry Compute_Bindgroup_Entries[8]={};
WGpuBufferBindingLayout bufferBindingLayoutIn={3};
WGpuBufferBindingLayout bufferBindingLayoutOut={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferBindingLayout bufferBindingLayout4={2};
WGpuStorageTextureBindingLayout storageTextureBindingLayoutFloat={};
WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false};
WGpuBufferDescriptor bufferDescriptorI={};
WGpuBufferDescriptor bufferDescriptorO={};
WGpuBufferDescriptor bufferDescriptorM={};
WGpuBufferDescriptor bufferDescriptorC={};
WGpuTextureDescriptor textureDescriptorIn={};
WGpuTextureDescriptor textureDescriptorOut={};
WGpuTextureViewDescriptor textureViewDescriptorIn={};
WGpuTextureViewDescriptor textureViewDescriptorOut={};
char * cmp_bdy=wgl_cmp_src;
WGpuShaderModuleDescriptor shaderModuleDescriptor={};
int randomNumber=0,entropySeed=0;
std::random_device randomizer;
int raN=0;
int raND=0;
WGpuImageCopyTexture Input_Image_Texture={};
WGpuImageCopyTexture Output_Image_Texture={};
WGpuImageCopyBuffer Input_Image_Buffer={};
WGpuImageCopyBuffer Output_Image_Buffer={};
WGpuImageCopyBuffer Mapped_Image_Buffer={};
uint32_t outP;
double_int53_t WGPU_Range_PointerB;
double_int53_t WGPU_Range_PointerC;
float * WGPU_Result_Array=new float[OutputBufferBytes];
float * WGPU_Input_Array=new float[InputBufferBytes];
const char * Fnm2=reinterpret_cast<const char *>("/video/frame.gl");
uint8_t * result2=NULL;
float * resultf=NULL;
uint8_t * results2=NULL;
float * resultsf=NULL;
long int length2=0;
void * fram;
const char * Fnm=reinterpret_cast<const char *>("/shader/shader.wgsl");
static char * result=NULL;
static char * results=NULL;
static long int length=0;

struct Vertex{
GLfloat position[4];
};

Vertex vertices[]={
{-1.0,-1.0,1.0,1.0},
{1.0,-1.0,1.0,1.0},
{1.0,1.0,1.0,1.0},
{-1.0,1.0,1.0,1.0},
{-1.0,-1.0,-1.0,1.0},
{1.0,-1.0,-1.0,1.0},
{1.0,1.0,-1.0,1.0},
{-1.0,1.0,1.0,1.0}
};

uint32_t indices[35]={3,0,1,1,2,3,4,0,3,3,7,4,1,5,6,6,2,1,4,7,6,6,5,4,2,6,6,7,3,0,4,1,1,4,5};
