#include "../../include/vanilla/main_render.hpp"

WGpuShaderModuleCompilationHint fragHint={};
WGpuTextureView depthTextureView;
WGpuTextureView colorTextureView;
WGpuTextureViewDescriptor depthTextureViewDescriptor={};
WGpuTextureViewDescriptor colorTextureViewDescriptor={};
WGpuRenderPassColorAttachment colorAttachment;
WGpuRenderPassDepthStencilAttachment depthAttachment;
WGpuTexture depthTexture;
WGpuTexture colorTexture;
WGpuTexture __128bit_Texture__;
WGpuTextureDescriptor depthTextureDescriptor={};
WGpuTextureDescriptor colorTextureDescriptor={};
WGpuTextureDescriptor highbitTextureDescriptor={};
WGpuRenderPassDescriptor passDesc={};
WGpuRenderPassDescriptor passDesc2={};
WGpuCanvasConfiguration config;
WGpuShaderModuleDescriptor shaderModuleDescV={};
WGpuShaderModuleDescriptor shaderModuleDescF={};
WGpuShaderModule vs;
WGpuShaderModule fs;
WGpuDepthStencilState depthState;
WGpuDepthStencilState depthState2;
WGpuVertexState vertState;
WGpuPrimitiveState priState;
WGpuFragmentState fragState;
WGpuFragmentState fragState2;
WGpuBufferDescriptor bufferDescriptor_iTime={};
WGpuBufferDescriptor bufferDescriptor_iResolution={};
WGpuBufferDescriptor bufferDescriptor_iFrame={};
WGpuBufferDescriptor bufferDescriptor_iTimeDelta={};
// WGpuPipelineLayoutDescriptor renderPipelineLayoutDesc;  // unused by webgpu.h
// WGpuPipelineLayout pipeline_layout=0;
WGpuBindGroupLayout bindgroup_layout=0;
WGpuBindGroupLayout bindgroup_layout2=0;
WGpuBindGroupLayoutEntry bindgroup_layout_entries[8]={};
WGpuBindGroupEntry bindgroup_entries[8]={};
WGpuBindGroup bindgroup=0;
WGpuRenderPipeline renderPipeline1;
WGpuRenderPipeline renderPipeline2;
WGpuRenderPipelineDescriptor renderPipelineDesc;
WGpuRenderPipelineDescriptor renderPipelineDesc2;
WGpuRenderBundleEncoder renderBundleEncoder;
WGpuRenderBundleEncoderDescriptor renderBundleEncoderDescriptor={};
WGpuDeviceDescriptor deviceDesc={};
WGpuMultisampleState multiSamp;
WGpuMultisampleState multiSamp2;
WGpuBuffer uni_iTime_Buffer;
WGpuBuffer uni_iTimeDelta_Buffer;
WGpuBuffer uni_iResolution_Buffer;
WGpuBuffer uni_iFrame_Buffer;
WGpuBufferBindingLayout bufferBindingLayout1={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuTextureBindingLayout textureBindingLayout1={};
WGpuTextureBindingLayout textureBindingLayout2={};
WGpuTextureBindingLayout textureBindingLayout3={};
WGpuColorTargetState colorTarget={};
WGpuColorTargetState colorTarget2={};
WGpuCommandEncoder wceA={};
WGpuCommandEncoder wceB={};

WGPU_TEXTURE_FORMAT canvasViewFormats[1];
WGPU_TEXTURE_FORMAT colorViewFormats[1];
WGPU_TEXTURE_FORMAT depthViewFormats[1];
WGPU_TEXTURE_FORMAT canvasFormat;

double szh,szw;
int szhI,szwI;

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

static i_tensor sze=i_tensor{2,2};
static wce_tensor wce=wce_tensor{2,2};
static wrpe_tensor wrpe=wrpe_tensor{2,2};
static wcb_tensor wcb=wcb_tensor{2,2};
static wd_tensor wd=wd_tensor{2,2};
static wq_tensor wq=wq_tensor{2,2};
static wa_tensor wa=wa_tensor{2,2};
static wcc_tensor wcc=wcc_tensor{2,2};
static wccf_tensor wccf=wccf_tensor{2,2};
static wrp_tensor wrp=wrp_tensor{2,2};
static wrpl_tensor wrpl=wrpl_tensor{2,2};
static wb_tensor wb=wb_tensor{8,8};
static wbgle_tensor wbgle=wbgle_tensor{2,2};
static wbge_tensor wbge=wbge_tensor{2,2};
static wbgl_tensor wbgl=wbgl_tensor{2,2};
static wbg_tensor wbg=wbg_tensor{2,2};
static wrpd_tensor wrpd=wrpd_tensor{2,2};
static wrpca_tensor wrpca=wrpca_tensor{2,2};
static wbbl_tensor wbbl=wbbl_tensor{2,2};
static wbd_tensor wbd=wbd_tensor{8,8};
static wao_tensor wao=wao_tensor{2,2};
static wdd_tensor wdd=wdd_tensor{2,2};
static u64_tensor u64_uni=u64_tensor{8,8};
static u64_tensor u64_siz=u64_tensor{1,1};
static wrbe_tensor wrbe=wrbe_tensor{2,2};
static wrbed_tensor wrbed=wrbed_tensor{2,2};
static wrpdsa_tensor wrpdsa=wrpdsa_tensor{2,2};
static wt_tensor wt=wt_tensor{3,3};
static wtd_tensor wtd=wtd_tensor{3,3};
static wtvd_tensor wtvd=wtvd_tensor{2,2};
static wtf_tensor wtf=wtf_tensor{4,4};
static wtv_tensor wtv=wtv_tensor{2,2};
static wms_tensor wms=wms_tensor{2,2};
static wsm_tensor wsm=wsm_tensor{2,2};
static wcts_tensor wcts=wcts_tensor{2,2};
static wdss_tensor wdss=wdss_tensor{2,2};
static wvs_tensor wvs=wvs_tensor{2,2};
static wps_tensor wps=wps_tensor{2,2};
static wfs_tensor wfs=wfs_tensor{2,2};
static wrpid_tensor wrpid=wrpid_tensor{2,2};
static wtbl_tensor wtbl=wtbl_tensor{2,2};

const char * vertexShader =
"@vertex\n"
"fn main(@builtin(vertex_index) vertexIndex : u32) -> @builtin(position) vec4<f32> {\n"
"var pos = array<vec2<f32>, 6>(\n"
"vec2<f32>(1.0f, 1.0f),\n"
"vec2<f32>(-1.0f, 1.0f),\n"
"vec2<f32>(-1.0f, -1.0f),\n"
"vec2<f32>(1.0f, 1.0f),\n"
"vec2<f32>(1.0f, -1.0f),\n"
"vec2<f32>(-1.0f, -1.0f)\n"
");\n"
"return vec4<f32>(pos[vertexIndex], 0.0f, 1.0f);"
"}\n";

const char * fragHeader=
"fn unpack_uint8(u32Value: u32) -> f32 {"
"return f32((u32Value & 0xff)) / 255.0;"
"}"
"@group(0)@binding(0)var<uniform> Time : u32;"
"@group(0)@binding(1)var<uniform> iFrame : u32;"
"@group(0)@binding(2)var<uniform> Resolution : u32;"
"var<private> iTime: f32 = f32(unpack_uint8(Time))/1000.0;"
"var<private> iResolution: vec3<f32> = vec3<f32>(vec3<u32>(unpack_uint8(Resolution),1));";

const char * fragEntry="main_1";

const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");

static char8_t * result=NULL;
static char * results=NULL;
static long int length=0;

const inline char * rd_fl(const char * Fnm){
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
result=static_cast<char8_t *>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
results=reinterpret_cast<char *>(result);
return results;
}
return nullptr;
}

void raf(){
u64_uni.at(1,1)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u64_uni.at(0,0)=u_time.time_spana.count()*1000;
u64_uni.at(3,3)=u_time.time_spanb.count()*1000;
// u64_uni.at(4,4)=u_time.time_spanb.count()/1.0f;

colorTexture=wgpu_canvas_context_get_current_texture(wcc.at(0,0));
wt.at(1,1)=colorTexture;
colorTextureView=wgpu_texture_create_view(wt.at(1,1),&wtvd.at(1,1));
wtv.at(1,1)=colorTextureView;
// colorAttachment.view=wgpu_texture_create_view(wgpu_canvas_context_get_current_texture(wcc.at(0,0)),0);
colorAttachment.view=wtv.at(1,1);
colorAttachment.storeOp=WGPU_STORE_OP_STORE;
colorAttachment.loadOp=WGPU_LOAD_OP_LOAD;
colorAttachment.clearValue.r=0.0f;
colorAttachment.clearValue.g=0.0f;
colorAttachment.clearValue.b=0.0f;
colorAttachment.clearValue.a=1.0f;
wrpca.at(0,0)=colorAttachment;

depthAttachment={};
depthTextureView=wgpu_texture_create_view(wt.at(0,0),&wtvd.at(0,0));
wtv.at(0,0)=depthTextureView;
depthAttachment.view=wtv.at(0,0);
depthAttachment.depthClearValue=1.0f;
depthAttachment.stencilClearValue=0;
depthAttachment.depthReadOnly=0;
depthAttachment.stencilReadOnly=0;
depthAttachment.depthLoadOp=WGPU_LOAD_OP_LOAD;
depthAttachment.depthStoreOp=WGPU_STORE_OP_STORE;
depthAttachment.stencilLoadOp=WGPU_LOAD_OP_LOAD;
depthAttachment.stencilStoreOp=WGPU_STORE_OP_STORE;
wrpdsa.at(0,0)=depthAttachment;
passDesc={};
passDesc.numColorAttachments=1;
passDesc.colorAttachments=&wrpca.at(0,0);
wrpd.at(0,0)=passDesc;
passDesc2={};
passDesc2.numColorAttachments=0;
passDesc2.depthStencilAttachment=wrpdsa.at(0,0);
wrpd.at(1,1)=passDesc2;
wceA=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(0,0)=wceA;
wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&wrpd.at(0,0));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
wgpu_encoder_set_bind_group(wrpe.at(0,0),0,wbg.at(0,0),0,0);
wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&u64_uni.at(0,0),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(1,1),0,&u64_uni.at(1,1),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(2,2),0,&u64_uni.at(2,2),sizeof(uint64_t));
wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0,0.0,sze.at(0,0),sze.at(0,0),0.0f,1.0f);
wgpu_render_pass_encoder_draw(wrpe.at(0,0),6,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(0,0));
wcb.at(0,0)=wgpu_command_encoder_finish(wce.at(0,0));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(0,0));
wceA={};
wceB=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(1,1)=wceB;
wrpe.at(1,1)=wgpu_command_encoder_begin_render_pass(wce.at(1,1),&wrpd.at(1,1));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(1,1),wrp.at(1,1));
wgpu_encoder_set_bind_group(wrpe.at(1,1),0,wbg.at(0,0),0,0);
wgpu_render_pass_encoder_set_viewport(wrpe.at(1,1),0.0,0.0,sze.at(0,0),sze.at(0,0),0.0f,1.0f);
wgpu_render_pass_encoder_draw(wrpe.at(1,1),6,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(1,1));
wcb.at(1,1)=wgpu_command_encoder_finish(wce.at(1,1));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(1,1));
wceB={};
return;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result, void *userData){
wd.at(0,0)=result;
wcc.at(0,0)=wgpu_canvas_get_webgpu_context("canvas");
const char * frag_body=(char*)rd_fl(Fnm);
      #include <string.h>
char full_frag_body[strlen(fragHeader) + strlen(frag_body) + 1];
strcpy(full_frag_body, fragHeader);
strcat(full_frag_body, frag_body);
// canvasFormat=navigator_gpu_get_preferred_canvas_format();
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_BGRA8UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGB10A2UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_BGRA8UNORM;
// canvasFormat=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA8UNORM_SRGB;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA16FLOAT;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RG11B10UFLOAT;
canvasFormat=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
wtf.at(0,0)=canvasFormat;
canvasViewFormats[0]={wtf.at(0,0)};
config=WGPU_CANVAS_CONFIGURATION_DEFAULT_INITIALIZER;
config.device=wd.at(0,0);
config.format=canvasFormat;
config.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT|WGPU_TEXTURE_USAGE_TEXTURE_BINDING;
config.viewFormats=&canvasViewFormats[0];
config.alphaMode=WGPU_CANVAS_ALPHA_MODE_PREMULTIPLIED;
// config.alphaMode=WGPU_CANVAS_ALPHA_MODE_OPAQUE;
config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
wccf.at(0,0)=config;
wgpu_canvas_context_configure(wcc.at(0,0),&wccf.at(0,0));
emscripten_get_element_css_size("canvas",&szw,&szh);
emscripten_get_canvas_element_size("canvas",&szwI,&szhI);
u64_siz.at(0,0)=szhI;
sze.at(0,0)=szhI;
sze.at(0,1)=szhI;
multiSamp={};
multiSamp.count=1;
multiSamp.mask=-1;
multiSamp2={};
multiSamp2.count=4;
multiSamp2.mask=-1;
wms.at(1,1)=multiSamp2;
colorTarget.format=wtf.at(0,0);
colorTarget.writeMask=WGPU_COLOR_WRITE_ALL;
      /*
colorTarget.blend.color.operation=WGPU_BLEND_OPERATION_ADD;
colorTarget.blend.color.srcFactor=WGPU_BLEND_FACTOR_ZERO;
colorTarget.blend.color.dstFactor=WGPU_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
colorTarget.blend.alpha.operation=WGPU_BLEND_OPERATION_ADD;
colorTarget.blend.alpha.srcFactor=WGPU_BLEND_FACTOR_ZERO;
colorTarget.blend.alpha.dstFactor=WGPU_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
*/
wcts.at(0,0)=colorTarget;
wtf.at(1,1)=WGPU_TEXTURE_FORMAT_INVALID;
wtf.at(2,2)=WGPU_TEXTURE_FORMAT_DEPTH32FLOAT_STENCIL8;
colorTarget2.format=wtf.at(1,1);
// colorTarget2.writeMask=WGPU_COLOR_WRITE_ALL;
wcts.at(1,1)=colorTarget2;
shaderModuleDescV={};
shaderModuleDescF={};
fragHint.entryPointName=fragEntry;
shaderModuleDescF.code=full_frag_body;
// shaderModuleDescF.hint=fragHint;
shaderModuleDescV.code=vertexShader;
vs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescV);
wsm.at(0,0)=vs;
fs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF);
wsm.at(1,1)=fs;
depthState={};
depthState.format=WGPU_TEXTURE_FORMAT_INVALID;
depthState.depthWriteEnabled=0;
depthState.depthCompare=WGPU_COMPARE_FUNCTION_INVALID;
wdss.at(0,0)=depthState;
depthState2={};
depthState2.format=wtf.at(2,2);
depthState2.depthWriteEnabled=1;
depthState2.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;
wdss.at(1,1)=depthState2;
vertState={};
vertState.module=wsm.at(0,0);
vertState.entryPoint="main";
vertState.numBuffers=0;
vertState.buffers=nullptr;
vertState.numConstants=0;
vertState.constants=nullptr;
wvs.at(0,0)=vertState;
priState={};
priState.topology=WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // Defaults to WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ('triangle-list')
// priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32; // Defaults to undefined, must be explicitly specified if WGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP ('line-strip') or WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ('triangle-strip') is used.
priState.frontFace=WGPU_FRONT_FACE_CCW; // Defaults to WGPU_FRONT_FACE_CCW ('ccw')
priState.cullMode=WGPU_CULL_MODE_NONE; // Defaults to WGPU_CULL_MODE_NONE ('none')
priState.unclippedDepth=EM_FALSE; // defaults to EM_FALSE.
wps.at(0,0)=priState;
fragState={};
fragState.module=wsm.at(1,1);
fragState.entryPoint="main";
fragState.numTargets=1;
fragState.targets=&wcts.at(0,0);
wfs.at(0,0)=fragState;
fragState2={};
fragState2.module=wsm.at(1,1);
fragState2.entryPoint="main";
fragState2.numTargets=0;
// fragState2.targets=&wcts.at(1,1);
wfs.at(1,1)=fragState;
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
uni_iResolution_Buffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptor_iResolution);
wb.at(2,2)=uni_iResolution_Buffer;
bufferBindingLayout1.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayout1.hasDynamicOffset=0,
bufferBindingLayout1.minBindingSize=sizeof(uint64_t);
wbbl.at(0,0)=bufferBindingLayout1;
textureBindingLayout1.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_UINT;
textureBindingLayout1.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout1.multisampled=1;
wtbl.at(0,0)=textureBindingLayout1;
textureBindingLayout2.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayout2.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout2.multisampled=1;
wtbl.at(1,1)=textureBindingLayout2;
textureBindingLayout3.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_DEPTH;
textureBindingLayout3.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout3.multisampled=1;
wtbl.at(2,2)=textureBindingLayout3;
bindgroup_layout_entries[0]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[0].binding=0;
bindgroup_layout_entries[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[0].layout.buffer=wbbl.at(0,0);
bindgroup_layout_entries[1]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[1].binding=1;
bindgroup_layout_entries[1].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[1].layout.buffer=wbbl.at(0,0);
bindgroup_layout_entries[2]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[2].binding=2;
bindgroup_layout_entries[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[2].layout.buffer=wbbl.at(0,0);
bindgroup_layout_entries[3]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[3].binding=3;
bindgroup_layout_entries[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
bindgroup_layout_entries[3].layout.texture=wtbl.at(0,0);
bindgroup_layout_entries[4]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[4].binding=4;
bindgroup_layout_entries[4].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
bindgroup_layout_entries[4].layout.texture=wtbl.at(1,1);
bindgroup_layout_entries[5]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[5].binding=5;
bindgroup_layout_entries[5].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
bindgroup_layout_entries[5].layout.texture=wtbl.at(2,2);
wbgle.at(0,0)=bindgroup_layout_entries;
bindgroup_layout=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(0,0),3);
wbgl.at(0,0)=bindgroup_layout;
WGpuPipelineLayout pipeline_layout=wgpu_device_create_pipeline_layout(wd.at(0,0),&wbgl.at(0,0),1);
wrpl.at(0,0)=pipeline_layout;
renderPipelineDesc={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
renderPipelineDesc.vertex=wvs.at(0,0);
renderPipelineDesc.vertex.entryPoint="main";
renderPipelineDesc.primitive=wps.at(0,0);
renderPipelineDesc.fragment=wfs.at(0,0);
renderPipelineDesc.depthStencil=wdss.at(0,0);
renderPipelineDesc.layout=wrpl.at(0,0);
renderPipelineDesc.multisample=wms.at(0,0);
wrpid.at(0,0)=renderPipelineDesc;
renderPipeline1=wgpu_device_create_render_pipeline(wd.at(0,0),&wrpid.at(0,0));
wrp.at(0,0)=renderPipeline1;
renderPipelineDesc2={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
renderPipelineDesc2.vertex=wvs.at(0,0);
renderPipelineDesc2.vertex.entryPoint="main";
renderPipelineDesc2.primitive=wps.at(0,0);
// renderPipelineDesc2.fragment=wfs.at(1,1);
renderPipelineDesc2.depthStencil=wdss.at(1,1);
renderPipelineDesc2.layout=wrpl.at(0,0);
// renderPipelineDesc2.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc2.multisample=wms.at(1,1);
wrpid.at(1,1)=renderPipelineDesc2;
renderPipeline2=wgpu_device_create_render_pipeline(wd.at(0,0),&wrpid.at(1,1));
wrp.at(1,1)=renderPipeline2;
depthTextureViewDescriptor.format=wtf.at(2,2);
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
depthTextureDescriptor.format=wtf.at(2,2);
depthTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
depthTextureDescriptor.width=sze.at(0,0);
depthTextureDescriptor.height=sze.at(0,0); // default = 1;
depthTextureDescriptor.depthOrArrayLayers=1;
depthTextureDescriptor.mipLevelCount=1;
depthTextureDescriptor.sampleCount=4;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthViewFormats[0]={wtf.at(2,2)};
depthTextureDescriptor.viewFormats=&depthViewFormats[0];
wtd.at(0,0)=depthTextureDescriptor;
depthTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(0,0));
wt.at(0,0)=depthTexture;
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
colorTextureDescriptor.format=wtf.at(0,0);
colorTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING;
colorTextureDescriptor.width=sze.at(0,0);
colorTextureDescriptor.height=sze.at(0,0); // default = 1;
colorTextureDescriptor.depthOrArrayLayers=1;
colorTextureDescriptor.mipLevelCount=1;
colorTextureDescriptor.sampleCount=1;
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
colorViewFormats[0]={wtf.at(0,0)};
colorTextureDescriptor.viewFormats=&colorViewFormats[0];
wtd.at(1,1)=colorTextureDescriptor;
colorTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(1,1));
wt.at(1,1)=colorTexture;
highbitTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
highbitTextureDescriptor.format=WGPU_TEXTURE_FORMAT_RGBA32FLOAT;
highbitTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING;
highbitTextureDescriptor.width=sze.at(0,0);
highbitTextureDescriptor.height=sze.at(0,0); // default = 1;
highbitTextureDescriptor.depthOrArrayLayers=1;
highbitTextureDescriptor.mipLevelCount=1;
highbitTextureDescriptor.sampleCount=1;
highbitTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
colorViewFormats[0]={WGPU_TEXTURE_FORMAT_RGBA32FLOAT};
highbitTextureDescriptor.viewFormats=&colorViewFormats[0];
wtd.at(2,2)=highbitTextureDescriptor;
__128bit_Texture__=wgpu_device_create_texture(wd.at(0,0),&wtd.at(2,2));
wt.at(2,2)=__128bit_Texture__;
bindgroup_entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[0].binding=0;
bindgroup_entries[0].resource=wb.at(0,0);
bindgroup_entries[0].bufferBindOffset=0;
bindgroup_entries[0].bufferBindSize=sizeof(uint64_t);
bindgroup_entries[1]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[1].binding=1;
bindgroup_entries[1].resource=wb.at(1,1);
bindgroup_entries[1].bufferBindOffset=0;
bindgroup_entries[1].bufferBindSize=sizeof(uint64_t);
bindgroup_entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[2].binding=2;
bindgroup_entries[2].resource=wb.at(2,2);
bindgroup_entries[2].bufferBindOffset=0;
bindgroup_entries[2].bufferBindSize=sizeof(uint64_t);

bindgroup_entries[3]={};
bindgroup_entries[3].binding=3;
bindgroup_entries[3].resource=wt.at(1,1);
bindgroup_entries[4]={};
bindgroup_entries[4].binding=4;
bindgroup_entries[4].resource=wt.at(2,2);
bindgroup_entries[5]={};
bindgroup_entries[5].binding=5;
bindgroup_entries[5].resource=wt.at(0,0);

wbge.at(0,0)=bindgroup_entries;
// renderBundleEncoderDescriptor.sampleCount=1;
// renderBundleEncoderDescriptor.depthStencilFormat=wtf.at(2,2);
// wrbed.at(0,0)=renderBundleEncoderDescriptor;
// renderBundleEncoder=wgpu_device_create_render_bundle_encoder(wd.at(0,0),&wrbed.at(0,0));
// wrbe.at(0,0)=renderBundleEncoder;
wt.at(2,2)=__128bit_Texture__;
wq.at(0,0)=wgpu_device_get_queue(wd.at(0,0));
// tme=get_current_time_in_milliseconds();
// wTime.iTime=get_current_time_in_milliseconds();
bindgroup=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(0,0),wbge.at(0,0),3);
wbg.at(0,0)=bindgroup;
colorAttachment={WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER};
// colorTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(1,1));
u64_uni.at(0,0)=0;
u64_uni.at(1,1)=0;
u64_uni.at(2,2)=u64_siz.at(0,0);
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
emscripten_set_main_loop_timing(2,1);
emscripten_set_main_loop((void(*)())raf,0,0);
// emscripten_request_animation_frame_loop(raf,0);
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
wa.at(0,0)=result;
deviceDesc={WGPU_DEVICE_DESCRIPTOR_DEFAULT_INITIALIZER};
deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8|WGPU_FEATURE_FLOAT32_FILTERABLE|WGPU_FEATURE_RG11B10UFLOAT_RENDERABLE;
wdd.at(0,0)=deviceDesc;
wgpu_adapter_request_device_async(wa.at(0,0),&wdd.at(0,0),ObtainedWebGpuDeviceStart,0);
}

void WGPU_Start(){
WGpuRequestAdapterOptions options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options.powerPreference=WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
options.forceFallbackAdapter=EM_FALSE;
wao.at(0,0)=options;
navigator_gpu_request_adapter_async(&wao.at(0,0),ObtainedWebGpuAdapterStart,0);
}

EM_JS(void,js_main,(),{
FS.mkdir('/shader');
window.scroll(0,0);
function highResStart(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#scanvas').width=window.innerWidth*2;
document.querySelector('#scanvas').height=window.innerHeight*2;
document.querySelector('#di').click();
setTimeout(function(){
document.querySelector('#stat').innerHTML='Sending Start';
document.querySelector('#stat').style.backgroundColor='green';
Module.ccall('str',{async:true});
},50);
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#scanvas').width=window.innerHeight;
document.querySelector('#scanvas').height=window.innerHeight;
document.querySelector('#di').click();
},50);
}
function normalResStart(){
setTimeout(function(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
Module.ccall("startWebGPU",{async:true});
},100);
document.querySelector('#status').style.backgroundColor="green";
}
var $shds=[];

function shds(xml){
const sparser=new DOMParser();
let htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
let preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
$shds[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxts=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxts=txxts.replace(Self,"");
var x=document.getElementById("sh1");
var option=document.createElement("option");
option.text=txxts;
$shds[i+1]='https://glsl.1ink.us/wgsl/'+txxts;
option.value=txxts;
x.add(option);
}
}

function scanShaders(){
const dxhttp=new XMLHttpRequest();
// dxhttp.withCredentials=false;
dxhttp.addEventListener("load",function(){
shds(this);
});
dxhttp.open('GET','https://glsl.1ink.us/wgsl/',true);
dxhttp.send();
}
scanShaders();

document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#ihig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#scanvas').height=parseInt(window.innerHeight,10);
document.querySelector('#scanvas').width=parseInt(window.innerHeight,10);
document.querySelector('#canvas').height=parseInt(window.innerHeight,10);
document.querySelector('#canvas').width=parseInt(window.innerHeight,10);
document.querySelector('#status').height=20;
document.querySelector('#status').width=parseInt(window.innerHeight,10);
const tem=document.querySelector('#tim');
const ban=document.querySelector('#menuBtn');
const sfr=document.querySelector('#slideframe');
var $lt=tem.innerHTML;
function grab$lt(){
$lt=Math.round($lt);
}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.querySelector('#panel'),'menu':document.querySelector('#menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
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
document.querySelector('#menu').addEventListener('click',function(){
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

document.querySelector('#startBtn').addEventListener('click',function(){
// var pth="https://glsl.1ink.us/wgsl/galaxy.wgsl";
let shdMenu=document.querySelector('#sh1');
let highRes=document.querySelector('#resMode').value;
document.querySelector('#path').innerHTML='https://glsl.1ink.us/wgsl/'+shdMenu.value;
var pth=document.querySelector('#path').innerHTML;
// var pth="https://test.1ink.us/3arth/melt.wgsl";
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading Shader';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/shader.glsl',sfil);
document.querySelector('#stat').innerHTML='Downloaded Shader';
document.querySelector('#stat').style.backgroundColor='blue';
normalResStart();
}
});
ff.send(null);
});
  
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
},500);
});

extern"C"{

void startWebGPU(){
WGPU_Start();
}

}

int main(void){
js_main();
return 0;
}