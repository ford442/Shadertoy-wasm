extern "C"{  
  
void pl();
  
}

// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON
#pragma STDC FP_CONTRACT ON

#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define _XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1

#include <float.h>
#include <math.h>

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1

#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/atomic.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer.hpp>

using namespace ::boost::tuples;
using namespace boost::numeric::ublas;

#include <cstdint>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <climits>
#include <iostream>
#include <emscripten.h>

using void_tensor=tensor<boost::atomic<void *>>;
using gi_tensor=tensor<boost::atomic<long long>>;
using ub_tensor=tensor<boost::atomic<unsigned char *>>;
using lu_tensor=tensor<boost::atomic<unsigned long long>>;
using v_tensor=tensor<v128_t>;

ub_tensor sound=ub_tensor{1,2};
gi_tensor sound_pos=gi_tensor{2,2};
lu_tensor sound_pos_u=lu_tensor{1,1};
v_tensor sse=v_tensor{1,2};
v_tensor sse2=v_tensor{1,1};
v_tensor sse3=v_tensor{1,1};

inline struct{
GLubyte * snd;
long long pos;
SDL_AudioDeviceID dev;
unsigned int slen;
GLubyte * wptr;
}wave;

class Audio{

private:

GLchar flnm[24];
SDL_AudioSpec request;

public:

static inline void snd_pos(boost::atomic<int> set){
sse3.at(0,0)=wasm_i64x2_splat(set);
sound_pos.at(0,0)=wasm_i64x2_extract_lane(sse3.at(0,0),0);
// sound_pos.at(0,0)=set;
return;
}

static inline void snd_lft(long long set){
sse.at(0,1)=wasm_i64x2_splat(set);
sound_lft.at(0,0)=wasm_i64x2_extract_lane(sse.at(0,1),0);
return;
}

inline void snd_pos_u(unsigned long long set){
sse2.at(0,0)=wasm_u64x2_splat(set);
sound_pos_u.at(0,0)=wasm_u64x2_extract_lane(sse2.at(0,0),0);
return;
}

static inline void SDLCALL bfr(void * unused,GLubyte * stm,GLint len){
tie(stm,len);
wave.wptr=sound.at(0,0)+sound_pos.at(0,0);
snd_lft(sound_pos_u.at(0,0)-sound_pos.at(0,0));
while(sound_lft.at(0,0)<=len){
SDL_UnlockAudioDevice(wave.dev);
SDL_memcpy(stm,wave.wptr,sound_lft.at(0,0));
stm+=sound_lft.at(0,0);
len-=sound_lft.at(0,0);
wave.wptr=sound.at(0,0);
snd_lft(sound_pos_u.at(0,0));
snd_pos(0);
SDL_LockAudioDevice(wave.dev);
}
SDL_memcpy(stm,wave.wptr,len);
snd_pos(sound_pos.at(0,0)+len);
return;
}

inline void plt(){
tie(sound,sound_pos,sound_pos_u);
tie(wave,sse,sse2);
tie(bfr,request);
request.freq=44100;
request.format=AUDIO_S32;
request.channels=2;
request.samples=1024;
SDL_memset(&request,0,sizeof(request));
request.freq=44100;
request.format=AUDIO_S32;
request.channels=2;
request.samples=1024;
snd_pos(0);
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_Init(SDL_INIT_AUDIO);
SDL_LoadWAV(flnm,&request,&wave.snd,&wave.slen);
sound.at(0,0)=wave.snd;
snd_pos_u(wave.slen);
request.callback=bfr;
wave.dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&request,NULL,0);
SDL_PauseAudioDevice(wave.dev,SDL_FALSE);
return;
}
  
};
