#pragma pack(4)
// #pragma float_control(precise, on)  // enable precise semantics
#pragma fenv_access(on)             // enable environment sensitivity
// #pragma float_control(except, on)   // enable exception semantics

#include <boost/cstdfloat.hpp>  // must be first include
#include <cfloat>
#include <climits>
#include <math.h>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>

// #include <torch/script.h>
// #include <torch/csrc/api/include/torch/all.h>
// #include <ATen/ATen.h>
// #include "/usr/include/x86_64-linux-gnu/gmp.h"
// #include "./mpfr.h"
// #include "./gmp.h"

// #include "/usr/include/gmpxx.h"
#include <unistd.h>

#include <experimental/simd>
using std::experimental::native_simd;
using float_v=std::experimental::simd<float,std::experimental::simd_abi::scalar>;

/*
#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD 0
#pragma STDC FP_CONTRACT ON
#pragma STDC CX_LIMITED_RANGE ON
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define _XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP 1


#define FLT_MANT_DIG
#define DBL_MANT_DIG
#define LDBL_MANT_DIG
#define FLT_DIG
#define DBL_DIG
#define LDBL_DIG
#define FLT_MIN_EXP
#define DBL_MIN_EXP
#define LDBL_MIN_EXP
#define FLT_MIN_10_EXP
#define DBL_MIN_10_EXP
#define LDBL_MIN_10_EXP
#define FLT_MAX_EXP
#define DBL_MAX_EXP
#define LDBL_MAX_EXP
#define FLT_MAX_10_EXP
#define DBL_MAX_10_EXP
#define LDBL_MAX_10_EXP
#define FLT_MAX
#define DBL_MAX
#define LDBL_MAX
#define FLT_EPSILON
#define DBL_EPSILON
#define LDBL_EPSILON
#define FLT_MIN
#define DBL_MIN
#define LDBL_MIN
#define DECIMAL_DIG
*/

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1
#define BOOST_UBLAS_MOVE_SEMANTICS
#define BOOST_UBLAS_TYPE_CHECK 0
#define BOOST_UBLAS_USE_LONG_DOUBLE
#define BOOST_NO_EXCEPTIONS
// #define BOOST_HAS_FLOAT128
// #define BOOST_HAS_CLOCK_GETTIME 1
// #define BOOST_HAS_NANOSLEEP 1
// #define BOOST_HAS_NRVO 1
// #define BOOST_HAS_STDINT_H 1


#include "boost/tuple/tuple.hpp"
#include "boost/timer/timer.hpp"
#include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/avx.hpp"
#include <boost/numeric/ublas/tensor.hpp>
// #include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <time.h>
#include <chrono>

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
#include <boost/context/fiber.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
using namespace std::chrono_literals;
using namespace ::boost::tuples;

std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;

#include <iostream>

using namespace std;
using namespace boost::numeric::ublas;
using namespace boost::multiprecision;
using namespace boost::random;

using tensorVar=tensor<GLfloat>;
using tF=tensor<GLfloat>;
using tf=tensor<float>;
using td=tensor<double>;
using tld=tensor<long double>;
using tensorVarD=tensor<GLdouble>;
using tD=tensor<GLdouble>;
using tI=tensor<GLint>;
using tV=tensor<v128_t>;

#include <cassert>
#include <iomanip>

// #define WEBGPU_CPP_IMPLEMENTATION
// #include "../../include/vanilla/webgpu/emscripten/webgpu.hpp"
#include <webgpu/webgpu.h>
#include <stdio.h>

// #include "emscripten/html5_webgpu.h"

// using namespace wgpu;
using namespace std;

WGPUAdapter adapter=nullptr;
WGPUBindGroup bindGroup=nullptr;
WGPUBindGroupLayoutDescriptor bindGroupLayoutDescriptor={};
WGPUPipelineLayout pipelineLayout=nullptr;
const WGPUComputePipelineDescriptor computePipelineDescriptor={};
WGPUComputePipeline computePipeline=nullptr;
WGPUSwapChain swapchain=nullptr;
WGPUCommandBuffer commandBuffer=nullptr;
const WGPUComputePassDescriptor computePassDescriptor={};
const WGPUDeviceDescriptor deviceDescriptor={};
const WGPUCommandEncoderDescriptor encoderDescriptor={};
const WGPURequestAdapterOptions adapterOptions={};
const WGPUInstanceDescriptor instanceDescriptor={};
WGPUInstance instance=nullptr;
WGPUBindGroupLayout bindGroupLayout=nullptr;

// }
 
WGPUDevice requestDevice(WGPUAdapter adapter,WGPUDeviceDescriptor const * descriptor){
struct UserData{
WGPUDevice device=nullptr;
bool requestEnded=false;
};
UserData userData;
auto onDeviceRequestEnded=[](WGPURequestDeviceStatus status,WGPUDevice device,char const * message,void * pUserData){
UserData& userData=*reinterpret_cast<UserData*>(pUserData);
if(status==WGPURequestDeviceStatus_Success){
userData.device=device;
}
userData.requestEnded=true;
};
std::cout << "requesting device" << std::endl;
wgpuAdapterRequestDevice(adapter,descriptor,onDeviceRequestEnded,&userData);
return userData.device;
}

WGPUAdapter requestAdapter(WGPUInstance instance,WGPURequestAdapterOptions const * options){
struct UserData{
WGPUAdapter adapter=nullptr;
bool requestEnded=false;
};
UserData userData;
auto onAdapterRequestEnded=[](WGPURequestAdapterStatus status,WGPUAdapter adapter,char const * message,void * pUserData){
UserData& userData=*reinterpret_cast<UserData*>(pUserData);
if (status==WGPURequestAdapterStatus_Success){
userData.adapter=adapter;
std::cout << "Got adapter: " << adapter << std::endl;
}
userData.requestEnded=true;
};
wgpuInstanceRequestAdapter(instance,options,onAdapterRequestEnded,&userData);
return userData.adapter;
}

WGPUDevice Gdevice;

void init1(){
adapter=requestAdapter(instance,&adapterOptions);
}

void init2(){
std::cout << "Requesting device..." << std::endl;
Gdevice=requestDevice(adapter,&deviceDescriptor);
std::cout << "Got device: " << Gdevice << std::endl;
}

void init3(){
/*
std::cout << "Got bindlayout" << std::endl;
std::array<WGPUBindGroupLayoutEntry,2>bindings;
bindings[0].binding=0;
bindings[0].buffer.type=WGPUBufferBindingType::WGPUBufferBindingType_ReadOnlyStorage;
bindings[0].visibility=WGPUShaderStage::WGPUShaderStage_Compute;
bindings[1].binding=1;
bindings[1].buffer.type=WGPUBufferBindingType::WGPUBufferBindingType_Storage;
bindings[1].visibility=WGPUShaderStage::WGPUShaderStage_Compute;
bindGroupLayoutDescriptor.entryCount=(uint32_t)bindings.size();
bindGroupLayoutDescriptor.entries=bindings.data();
bindGroupLayout=requestBindGroupLayout(Gdevice,&bindGroupLayoutDescriptor);
std::cout << "Requesting command Encoder..." << std::endl;
WGPUCommandEncoder encoder=wgpuDeviceCreateCommandEncoder(Gdevice,&encoderDescriptor);
std::cout << "Requesting command queue..." << std::endl;
const WGPUQueue commandQueue=wgpuDeviceGetQueue(Gdevice);
*/
}
#include <functional>

tf sx=tf{2,2};
std::function<float(float,float)>TensorAdd(){
return[](float a,float b){sx.at(0,0)=a;sx.at(0,1)=b;sx.at(1,0)=sx.at(0,0)+sx.at(0,1);return sx.at(1,0);};
}
auto tensorAdd=TensorAdd();

td sy=td{2,2};
std::function<double(double,double)>DoubleAdd(){
return[](double a,double b){
sy.at(0,0)=a;
sy.at(0,1)=b;
sy.at(1,0)=sy.at(0,0)+sy.at(0,1);
return sy.at(1,0);};
}
auto doubleAdd=DoubleAdd();

tV sz=tV{2,2};
std::function<v128_t(v128_t,v128_t)>IntrinsAdd(){
return[](v128_t a,v128_t b){
sz.at(0,0)=a;
sz.at(0,1)=b;
sz.at(1,0)=wasm_f64x2_add(a,b);
return sz.at(1,0);
};
}
auto intrinsAdd=IntrinsAdd();

class tens{

private:

// boost::random::random_device rng;
float lol,olo;
tensorVar A=tensorVar{8,4};
tensorVar Aa=tensorVar{2,3};
uint128_t tst128;

public:

float rtt(float nm){
setprecision(3);
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
float ppi=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f;
double ppd=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
long double ppD=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L;
std::cout << "-float------------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< ppi <<"-----" << std::endl;
std::cout << "-double------------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< ppd <<"-----" << std::endl; 
std::cout << "-long double------------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< ppD <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "Tensor adding input: 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
sx.at(1,1)=tensorAdd(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f,3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f);
std::cout << "----------float-----------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< sx.at(1,1) <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
sy.at(1,1)=doubleAdd(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679,3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679);
std::cout << "-----------double---------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< sy.at(1,1) <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
sz.at(1,1)=intrinsAdd(wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f),wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f));
// szz.at(1,1)=intrinsLDAdd(wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L),wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L));
std::cout << "------intrins-------------" << std::endl;
float ou2=wasm_f64x2_extract_lane(sz.at(1,1),0);
double ou3=wasm_f64x2_extract_lane(sz.at(1,1),0);
// long double ou5=wasm_f64x2_extract_lane(szz.at(1,1),0);
std::cout << fixed << setprecision(64) << "--float---"<< ou2 <<"-----" << std::endl;
std::cout << fixed << setprecision(64) << "--double---"<< ou3 <<"-----" << std::endl;
// std::cout << fixed << setprecision(64) << "--long double---"<< ou5 <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;

A.at(0,0)=nm;
tensorVar B=A;
lol=static_cast<float>(B.at(4,4));
olo=lol*100;
// float llo=rng();
return olo;
}

};

inline EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;

inline int32_t Size;

inline EM_BOOL ms_l,clk_l;

inline struct{
float xx;
float yy;
float mX;
float mY;
float mm;
float nn;
float S;
float mouseY;
float mouseX;
double wi;
double hi;
GLclampf x;
GLclampf y;
}mouse;

inline EM_BOOL ms_clk(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return(EM_BOOL)1;
}

inline EM_BOOL ms_mv(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
mouse.x=e->clientX;
mouse.y=e->clientY;
}}
return (EM_BOOL)1;
}

void mss(){
emscripten_get_element_css_size("canvas",&mouse.wi,&mouse.hi);
Size=static_cast<int32_t>(mouse.hi);
mouse.S=static_cast<float>(mouse.hi);
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const float xxx=mouse.mouseX;
const float yyy=mouse.mouseY;
EM_ASM({
console.log($0);
},xxx);
mouse.mX=1.0f-(xxx*Size);
mouse.mY=1.0f-(yyy*Size);
clk_l=false;
}
mouse.mm=mouse.x*Size;
mouse.nn=Size*mouse.y;
}else{
clk_l=true;
EM_ASM({
console.log($0);
},mouse.nn);
}
return;
}

static tI inte=tI{1,1};
static tF sdeci=tF{1,1};
static tV q=tV{1,1};
static tV intrn=tV{1,4};
static boost::atomic<float>farray;
static v128_t aa,vv,xx,l,tt;

class funcs{

private:
  
public:

union{
float tuple_float_short(float num){
float cc,pp,uu,cc2,pp2,uu2,nn;
int r;
float Tdlt;

cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;
for(r=0;r<100;r++){
tie(cc,pp,uu);
tie(cc2,pp2,uu2);
}
t1=std::chrono::steady_clock::now();
for(r=0;r<100;r++){
nn=cc+pp+uu+cc2+pp2+uu2;
}
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return nn;
}
  
float tuple_float_long(float num){float cc,pp,uu,cc2,pp2,uu2,nn;
float Tdlt;
int r;
cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;
cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;
for(r=0;r<100;r++){
tie(cc,pp,uu,cc2,pp2,uu2);
}
t1=std::chrono::steady_clock::now();
for(r=0;r<100;r++){
nn=cc+pp+uu+cc2+pp2+uu2;
}
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return uu;
}

GLfloat tuple_gl(GLfloat num){
float Tdlt;
t1=std::chrono::steady_clock::now();
GLfloat ggg=num,ppg=num,uug=num;
tie(ggg,ppg,uug);
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return uug;
}

v128_t tuple_avx(float num){
float Tdlt;
t1=std::chrono::steady_clock::now();
aa=wasm_i32x4_splat(num);
vv=wasm_i32x4_splat(num);
xx=wasm_i32x4_splat(num);
tie(aa,vv,xx);
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return xx;
}

v128_t simd_test(float * a){
float Tdlt;
t1=std::chrono::steady_clock::now();
int m=a[0]*1000.0;
l=wasm_i32x4_splat(m);
tt=wasm_f32x4_add(l,l);
t2=std::chrono::steady_clock::now();
std::chrono::duration<float, std::chrono::milliseconds::period> time_span=std::chrono::duration<float,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return tt;
}

v128_t double_add(float fl){
tie(inte,sdeci,q,intrn);
inte.at(0,0)=std::floor(fl);
sdeci.at(0,0)=fl-inte.at(0,0);
intrn.at(0,0)=wasm_f32x4_make(inte.at(0,0),sdeci.at(0,0),sdeci.at(0,0),sdeci.at(0,0));
intrn.at(0,1)=wasm_f32x4_make(1.0,100.0,10.0,1.0);
intrn.at(0,0)=wasm_f32x4_div(intrn.at(0,0),intrn.at(0,1));
intrn.at(0,2)=wasm_f32x4_sqrt(intrn.at(0,0));
intrn.at(0,0)=wasm_f32x4_mul(intrn.at(0,2),intrn.at(0,2));
intrn.at(0,3)=wasm_f32x4_mul(intrn.at(0,0),intrn.at(0,1));
return intrn.at(0,3);
}
  
// native_simd<float> noblock(float y){
float noblock(float y){
__m64 p={6.0,6.0};
// __m64 pt={12.0,12.0};
// __m64 py3=_mm_adds_pi16_(p,pt);
// int reet=_m_to_int_(py3);
// int reet2=_mm_cvtsi64_si32_(py3);
// int tsst=_mm_extract_epi32(pt,1);
float_v reet=7.7f;
farray=y;
// boost::float128_t tyt=farray;
return farray;
 //   std::cout << ::at::ones({3,4}, at::CPU(at::kFloat)) << "\n";
 // emscripten_set_main_loop((void(*)())mss,0,0);

}

}rnn;

};
