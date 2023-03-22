#pragma once

#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <random>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "../../include/combine/intrins.hpp"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE OFF
#pragma STDC FP_CONTRACT OFF
#undef FLT_ROUNDS
#define FLT_ROUNDS 1

v128_t rNd(int);
int rD;
v128_t Dr;
std::random_device rd;

extern"C"{

int c;
v128_t Rg;
int r4nd(int);

}
