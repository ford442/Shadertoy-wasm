#include "../../include/combine/shader.hpp"

EM_BOOL mouse_call_click(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return(EM_BOOL)1;
}

static EM_BOOL mouse_call_move(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return (EM_BOOL)1;
}

void clrclr(GLclampf rlc,GLclampf alc,GLclampf avr){
avrg=(((avr+(1.0-rlc))/2.0)+alc);
drk=1.0-(avr-0.5);
brt=((1.0-rlc)-(alc-0.5));
glBlendColor(avrg,avrg,avrg,1.0);
glClearColor(drk,drk,drk,brt);
return;
}

void uni(GLfloat xx,GLfloat yy,GLfloat stime,GLint fram,GLfloat delt){
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_click);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_click);
iFps=60.0/delt;
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_move);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_click);
if(clk_l==true){
const float xxx=xx;
const float yyy=yy;
mX=1.0-(xxx*Size);
mY=1.0-(yyy*Size);
clk_l=false;
}
mm=S*xx;
nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
}
glUniform1f(uni_tme,stime);
glUniform1f(uni_tme_dlt,delt);
glUniform1f(uni_fps,iFps);
glUniform1i(uni_frm,fram);
return;
}

void renderFrame(){
auto t3=t2;
auto t2=std::chrono::steady_clock::now();
std::chrono::duration<float>time_spanb=duration_cast<std::chrono::duration<float>>(t2-t3);
TtimeDelta=time_spanb.count();
std::chrono::duration<float>time_spana=duration_cast<std::chrono::duration<float>>(t2-t1);
Ttime=time_spana.count();
mouseX=x/S;
mouseY=(S-y)/S;
uni(mouseX,mouseY,Ttime,iFrame,TtimeDelta);
iFrame++;
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_DEPTH_BUFFER_BIT);
// glClear(GL_STENCIL_BUFFER_BIT);
glDrawElements(GL_TRIANGLES,(GLsizei)36,GL_UNSIGNED_BYTE,indc);
glFlush();
nanosleep(&req,&rem);
glDrawElements(GL_TRIANGLES,(GLsizei)36,GL_UNSIGNED_BYTE,indc);
glFinish();
return;
}

void fr4m(){
void(*FrM)();
FrM=&renderFrame;
FrM();
return;
}

char32_t * read_file(const GLchar * filename){
char32_t * result=NULL;
long length=0;
FILE * file=fopen(filename,"r");
if(file){
short int status=fseek(file,(long int)0,SEEK_END);
if(status!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
status=fseek(file,(long int)0,SEEK_SET);
if(status!=0){
fclose(file);
return nullptr;
}
result=static_cast<char32_t *>(malloc((length+1)*sizeof(char32_t)));
if(result){
size_t actual_length=fread(result,sizeof(char32_t),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
return result;
}
return nullptr;
}

GLuint compile_shader(GLenum type,GLsizei nsources,const GLchar ** dsources){
GLsizei srclens[nsources];
for(i=0;i<nsources;i++){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}

void strt(){
eglconfig=NULL;
iFrame=0;
clk_l=true;
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_FALSE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_TRUE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
eglBindAPI(EGL_OPENGL_API);
// eglBindAPI(EGL_OPENGL_ES_API);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,attribute_list,&eglconfig,(EGLint)1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=(int)hi;
S=(float)Size;
mX=0.5*S;
mY=0.5*S;
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx_js,"EXT_pixel_format_float");  //  required for float/alpha (must be 'EXT_pixel_format_float' and not 'EGL_EXT_pixel_format_float')
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_pixel_format_float");  //  required for float/alpha (must be 'EXT_pixel_format_float' and not 'EGL_EXT_pixel_format_float')
emscripten_webgl_enable_extension(ctx_js,"IMG_context_priority");     //     vv  required for realtime
emscripten_webgl_enable_extension(ctx_js,"EGL_IMG_context_priority");     //     vv  required for realtime
emscripten_webgl_enable_extension(ctx_js,"NV_context_priority_realtime"); // ^^
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_context_priority_realtime"); // ^^
emscripten_webgl_enable_extension(ctx_js,"NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"EXT_texture_filter_anisotropic");
  /*
emscripten_webgl_enable_extension(ctx_js,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx_js,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx_js,"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx_js,"ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_2_compatibility");
*/
// emscripten_webgl_enable_extension(ctx_js,"ARB_gpu_shader5");
emscripten_webgl_enable_extension(ctx_js,"KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx_js,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_scrgb_linear");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_scrgb_linear");
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glClearDepth(D);
glEnable(GL_POLYGON_OFFSET_FILL);
glPolygonOffset((GLfloat)0.5f,(GLfloat)500.0f);
// glDisable(GL_STENCIL_TEST);
glDisable(GL_DITHER);
glEnable(GL_CULL_FACE);
glFrontFace(GL_CW);
glEnable(GL_BLEND);
//glDisable(GL_BLEND);
glBlendFuncSeparate(GL_SRC_COLOR,GL_ONE_MINUS_DST_COLOR,GL_DST_COLOR,GL_SRC_ALPHA);
glBlendEquationSeparate(GL_FUNC_SUBTRACT,GL_MIN);
glClearColor((GLclampf)gF,(GLclampf)gF,(GLclampf)gF,(GLclampf)gF);
// glBlendColor((GLclampf)gF,(GLclampf)gF,(GLclampf)gF,(GLclampf)gF);
glGenBuffers((GLsizei)1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
nanosleep(&req,&rem);
glGenBuffers((GLsizei)1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STATIC_DRAW);
nanosleep(&req,&rem);
GLchar * default_fragment_shader=(GLchar *)read_file(fileloc);
nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,2,sources);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,4,sources);
nanosleep(&req,&rem);
shd_prg=glCreateProgram();
glAttachShader(shd_prg,frag);
glAttachShader(shd_prg,vtx);
atb_pos=0;
glBindAttribLocation(shd_prg,0,"iPosition");
glLinkProgram(shd_prg);
glUseProgram(shd_prg);
nanosleep(&req,&rem);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays((GLsizei)1,&VCO);
glBindVertexArray(VCO);
atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
uni_tme=glGetUniformLocation(shd_prg,"iTime");
uni_tme_dlt=glGetUniformLocation(shd_prg,"iTimeDelta");
uni_frm=glGetUniformLocation(shd_prg,"iFrame");
uni_fps=glGetUniformLocation(shd_prg,"iFrameRate");
uni_res=glGetUniformLocation(shd_prg,"iResolution");
uni_mse=glGetUniformLocation(shd_prg,"iMouse");
uni_srate=glGetUniformLocation(shd_prg,"iSampleRate");
smp_chn_res=glGetUniformLocation(shd_prg,"iChannelResolution");
smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");
glUniform1f(uni_srate,44100.0f);
glUniform3f(uni_res,S,S,gF);
glUniform3f(smp_chn_res,S,S,gF);
glViewport((GLint)0,(GLint)0,Size,Size);  //  viewport/scissor after UsePrg runs at full resolution
glEnable(GL_SCISSOR_TEST);
glScissor((GLint)0,(GLint)0,Size,Size);
auto t1=std::chrono::steady_clock::now();
// emscripten_set_main_loop((void(*)())renderFrame,0,0);
return;
}

void egl(){
eglconfig_js=NULL;
emscripten_get_element_css_size("canvas",&wi_js,&hi_js);
Size_js=(GLsizei)hi_js;
emscripten_webgl_init_context_attributes(&attr_js);
attr_js.alpha=EM_TRUE;
attr_js.stencil=EM_FALSE;
attr_js.depth=EM_TRUE;
attr_js.antialias=EM_TRUE;
attr_js.premultipliedAlpha=EM_TRUE;
attr_js.preserveDrawingBuffer=EM_FALSE;
attr_js.enableExtensionsByDefault=EM_TRUE;
attr_js.renderViaOffscreenBackBuffer=EM_FALSE;
attr_js.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_js.failIfMajorPerformanceCaveat=EM_FALSE;
attr_js.majorVersion=2;
attr_js.minorVersion=0;
ctx_js=emscripten_webgl_create_context("#bcanvas",&attr_js);
eglBindAPI(EGL_OPENGL_API);
// eglBindAPI(EGL_OPENGL_ES_API);
display_js=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_js,&major_js,&minor_js);
eglChooseConfig(display_js,attribute_list_js,&eglconfig_js,(EGLint)1,&config_size_js);
contextegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,anEglCtxAttribs2_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,attribut_list_js);
eglMakeCurrent(display_js,surface_js,surface_js,contextegl_js);
emscripten_webgl_make_context_current(ctx_js);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glDisable(GL_DITHER);
glEnable(GL_SCISSOR_TEST);
emscripten_webgl_enable_extension(ctx_js,"EGL_IMG_context_priority");     //     vv  required for realtime
emscripten_webgl_enable_extension(ctx_js,"IMG_context_priority");     //     vv  required for realtime
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_context_priority_realtime"); // ^^
emscripten_webgl_enable_extension(ctx_js,"NV_context_priority_realtime"); // ^^
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_pixel_format_float");  //  required for float/alpha (must be 'EXT_pixel_format_float' not 'EGL_EXT_pixel_format_float')
emscripten_webgl_enable_extension(ctx_js,"EXT_pixel_format_float");  //  required for float/alpha (must be 'EXT_pixel_format_float' not 'EGL_EXT_pixel_format_float')
emscripten_webgl_enable_extension(ctx_js,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx_js,"NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"KHR_gl_colorspace");
  /*
emscripten_webgl_enable_extension(ctx_js,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx_js,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx_js,"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx_js,"ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_2_compatibility");
*/
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_scrgb_linear");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_scrgb_linear");
// emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_bt2020_pq");
// emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_bt2020_linear");
// emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_display_p3");
// emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_display_p3_linear");
// emscripten_webgl_enable_extension(ctx_js,"EXT_texture_filter_anisotropic");
glDisable(GL_STENCIL_TEST);
// glDisable(GL_DEPTH_TEST);
glViewport((GLint)0,(GLint)0,Size_js,Size_js);
glScissor((GLint)0,(GLint)0,Size_js,Size_js);
return;
}

extern "C" {

void frm(){
void(*fRm)();
fRm=&fr4m;
fRm();
return;
}

void clr(GLclampf cllr,GLclampf alp,GLclampf avr){
clrclr(cllr,alp,avr);
return;
}

void b3_egl(){
void(*b4e)();
b4e=&egl;
b4e();
return;
}

void str(){
void(*sTr)();
sTr=&strt;
sTr();
return;
}

}
