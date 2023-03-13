#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 2
#pragma STDC CX_LIMITED_RANGE ON

#include <wasm_simd128.h>
#include <tmmintrin.h> // ssse 3
#include <smmintrin.h>  // sse 4.1
#include <avxintrin.h>  // AVX

#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>  //  sse 4.2
#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <emscripten.h>
#include <emscripten/html5.h>

int rNd(int);

int rD,Th;

extern"C"{

int r4nd(int);

}
