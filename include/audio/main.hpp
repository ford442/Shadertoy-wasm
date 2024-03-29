#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>

// #pragma clang diagnostic ignored "-Wdeprecated-declarations"
/*
// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON
#pragma STDC FP_CONTRACT OFF
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1
*/

#include <wasm_simd128.h>
#include <tmmintrin.h> // ssse 3
#include <smmintrin.h>  // sse 4.1
#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>  //  sse 4.2
#include <avxintrin.h>  // AVX

#include <unistd.h>
// #include <GL/gl.h>

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>
#include "boost/tuple/tuple.hpp"
#include <functional>

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#define register

#include <boost/function.hpp>
using namespace ::boost::tuples;

#include <cstdlib>
#include <ctime>
#include <random>

class song_select{

private:

std::random_device rd;
v128_t Dr;
int rD=0;

public:

inline v128_t rNd(int Th){
tie(Th,rD,Dr);
std::srand(rd());
rD=std::rand()%Th;
Dr=wasm_i32x4_splat(rD);
return Dr;
}

};

extern "C"{
  
v128_t Rg;
int c=0;

int r4nd(int);

}
