#version 300 es
#extension GL_ALL_EXTENSIONS : enable
#extension all_spir_v_extensions : enable
#extension OES_standard_derivatives : disable
#extension GL_KHR_no_error : enable
#extension GL_REGAL_enable : enable
#extension EGL_ANGLE_platform_angle : enable
#extension GL_ARB_spirv_extensions : enable
#extension EGL_EXT_gl_colorspace_display_p3_linear : enable
// #pragma STDC(FP_CONTRACT ON)
#undef HW_PERFORMANCE
#define HW_PERFORMANCE 1
#pragma (fastmath on)
#pragma optionNV(fastmath on)
#pragma (fastprecision off)
#pragma (STDGL all)
#pragma optionNV(STDGL all)
/*
"#pragma (precision highp double)\n"
"#pragma (precision highp vec4)\n"
"#pragma (precision highp mat4)\n"
"#pragma (precision highp uint)\n"
"#pragma (precision highp short)\n"
"#pragma (precision highp bool)\n"
"#pragma (precision highp atomic_uint)\n"
"#pragma (precise none)\n"
 "#pragma STDGL(strict off)\n"
 "#pragma optimize(on)\n"
 "#pragma debug(off)\n"
 "#pragma (invariant none)\n"
 "#pragma (centroid all)\n"
"#pragma (sample all)\n"
"#pragma (unroll all)\n"
"#pragma optionNV(unroll all)\n"
"#pragma STDGL(ifcvt none)\n"
"#pragma (inline all)\n"
"#pragma optionNV(inline all)\n"
*/
precision highp float;
precision highp sampler3D;precision highp sampler2D;
precision highp samplerCube;
precision mediump sampler2DArray;precision mediump sampler2DShadow;
precision mediump isampler2D;precision mediump isampler3D;precision mediump isamplerCube;
precision mediump isampler2DArray;precision mediump usampler2D;precision mediump usampler3D;
precision mediump usamplerCube;precision mediump usampler2DArray;precision mediump samplerCubeShadow;
precision mediump sampler2DArrayShadow;
