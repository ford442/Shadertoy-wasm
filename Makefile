WGL_BIN_NAME += w0-001

LDFLAGS += -Wl,-O3,--lto-O3,-lc++,-lpthread,-lc++abi,-lm,-lrt,-ldl,-S

SIMD_FLAGS += -DSIMD=2 -msimd128 -mavx

STDS += -std=gnu17 -std=c2x -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

LINK_SIMD_FLAGS += -mcx16 -mavxifma -mbmi -mbmi2 -mlzcnt -mavxneconvert -msse -msse2 -msse3 -mssse3 \
	 -msse4 -msse4.1 -msse4.2 -mavx -mavx2 -mpclmul -msha -mfma -mbmi2 -mpopcnt -maes -enable-fma -mavxvnni -msimd128 

COMMON_FLAGS += -openmp-simd -pthread -sSUPPORT_LONGJMP=emscripten -pipe -mextended-const -mbulk-memory -matomics \
	 -sWASM_WORKERS=1 -sSHARED_MEMORY=1 \
	 -fPIC -fPIE -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffinite-math-only -funsafe-math-optimizations -fno-trapping-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

STATIC_LINK_FLAGS += -mno-tail-call -O3 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS += -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1 -DBOOST_HAS_THREADS

GL_FLAGS += -sGL_ENABLE_GET_PROC_ADDRESS -sFULL_ES3=1 -sFULL_ES2=1 -sUSE_SDL=0 -lGL -lEGL -sLEGACY_GL_EMULATION=0 -sUSE_GLFW=0 -sUSE_REGAL=0 \
	 -sGL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=1 -sGL_SUPPORT_SIMPLE_ENABLE_EXTENSIONS=1 -sGL_MAX_TEMP_BUFFER_SIZE=33177600 \
	 -sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=1

wGL_FLAGS += -sFULL_ES3=0 -sFULL_ES2=0 -sUSE_SDL=0 -sLEGACY_GL_EMULATION=0 -sUSE_GLFW=0 -sUSE_REGAL=0 \

LINK_FLAGS += $(LDFLAGS) -sDEFAULT_TO_CXX=1 -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 \
	 -sDEMANGLE_SUPPORT=0 -sASSERTIONS=1 -jsDWEBGPU_DEBUG=1 -sABORTING_MALLOC=0 -sTEXTDECODER=2 \
	 --use-preload-plugins --closure 0 --closureFriendly \
	 -march=haswell -sWASM=1 -sTOTAL_STACK=65536 \
	 -sGLOBAL_BASE=352321536 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=3221225472 --output_eol linux -mllvm -mtune=wasm32 \
	 -sMALLOC=emmalloc --memory-init-file 0 -rtlib=compiler-rt-mt -sAUTO_ARCHIVE_INDEXES=0 -wasm-enable-eh

WEBGPU_FLAGS += -sASYNCIFY=0 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -lmath.js -lhtml5.js -lint53.js

TIMESTAMP := $(shell date +%m%y)
NAMESTAMP := v3001test-DTE.js
NAMESTAMP := $(subst DTE,$(TIMESTAMP),$(NAMESTAMP))
vanilla_test_gpujs:
	 em++ src/vanilla/main_gpujs.cpp -o $(NAMESTAMP) \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=3221225472 \
	 -sEXPORTED_RUNTIME_METHODS='["ccall"]' -sEXPORTED_FUNCTIONS=["_main","_gpu_js"] \
	 --pre-js js/gpujsx.js --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js

b3_vanilla_webgpu:
	 em++ -c src/vanilla/main_webgpu.cpp -std=c++20 $(BOOST_FLAGS) $(SIMD_FLAGS) 
	 emcc $(LDFLAGS) -o w3001.js $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) -fPIC -fPIE -DCOMPUTE \
	 -polly -sALLOW_MEMORY_GROWTH=1 -sDISABLE_EXCEPTION_THROWING=0 -sFILESYSTEM=0 \
	 -sINITIAL_MEMORY=1gb -lmath.js -lhtml5.js -lint53.js -sAUTO_JS_LIBRARIES=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=2 -sASYNCIFY_IMPORTS=['startWebGPU','runWebGPU','wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU","_runWebGPU","_runWebGPU2"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-post-js src/vanilla/filesys.js --extern-post-js js/rSlider.js --extern-post-js js/slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --memory-init-file 0 --closure-args=--externs=lib/webgpu-closure-externs.js main_webgpu.o

b3_vanilla_webgpu2:
	 emcc src/vanilla/main_webgpu.cpp -std=c++20 \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -c $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc $(LDFLAGS) --js-library lib/lib_webgpu.js -fPIC -fPIE -DCOMPUTE -o w3001.js \
	 $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) $(GL_FLAGS) \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=1024mb -lmath.js -lhtml5.js -lint53.js \
	 -sUSE_SDL=0 -sFILESYSTEM=0 -sAUTO_JS_LIBRARIES=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU','runWebGPU','wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU","_runWebGPU","_runWebGPU2"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --memory-init-file 0 main_webgpu.o 

b3_vanilla_render:
	 em++ src/vanilla/main_render.cpp -std=c++20 \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -O0 -c $(BOOST_FLAGS) $(SIMD_FLAGS)
	 em++ $(LDFLAGS) -O0 --js-library lib/lib_webgpu.js -fPIC -fPIE -DCOMPUTE -o $(WGL_BIN_NAME).js \
	 $(BOOST_FLAGS) $(SIMD_FLAGS) $(GL_FLAGS) -sASSERTIONS=0 \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=1024mb -lmath.js -lhtml5.js -lint53.js \
	 -sUSE_SDL=0 -sFILESYSTEM=0 -sAUTO_JS_LIBRARIES=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --memory-init-file 0 main_render.o 

b3_vanilla_render_a:
	 em++ src/vanilla/main_render.cpp -std=c++20 \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -O0 -c $(BOOST_FLAGS) $(SIMD_FLAGS)
	 em++ $(LDFLAGS) -O0 --js-library lib/lib_webgpu.js -fPIC -fPIE -DCOMPUTE -o $(WGL_BIN_NAME)a.js \
	 $(BOOST_FLAGS) $(SIMD_FLAGS) $(GL_FLAGS) -sASSERTIONS=0 \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=1024mb -lmath.js -lhtml5.js -lint53.js \
	 -sUSE_SDL=0 -sFILESYSTEM=0 -sAUTO_JS_LIBRARIES=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --memory-init-file 0 main_render.o 

b3_vanilla_render_b:
	 em++ src/vanilla/main_render.cpp -std=c++20 \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -O0 -c $(BOOST_FLAGS) $(SIMD_FLAGS)
	 em++ $(LDFLAGS) -O0 --js-library lib/lib_webgpu.js -fPIC -fPIE -DCOMPUTE -o $(WGL_BIN_NAME)b.js \
	 $(BOOST_FLAGS) $(SIMD_FLAGS) $(wGL_FLAGS) -sASSERTIONS=0 \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=1024mb -lmath.js -lhtml5.js -lint53.js \
	 -sUSE_SDL=0 -sFILESYSTEM=0 -sAUTO_JS_LIBRARIES=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --memory-init-file 0 main_render.o 

b3_vanilla_render_c:
	 em++ src/vanilla/main_render.cpp -std=c++20 \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -O0 -c $(BOOST_FLAGS) $(SIMD_FLAGS)
	 em++ $(LDFLAGS) -O0 --js-library lib/lib_webgpu.js -fPIC -fPIE -DCOMPUTE -o $(WGL_BIN_NAME)c.js \
	 $(BOOST_FLAGS) $(SIMD_FLAGS) $(wGL_FLAGS) -sASSERTIONS=0 \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=1024mb -lmath.js -lhtml5.js -lint53.js \
	 -sUSE_SDL=0 -sFILESYSTEM=0 -sAUTO_JS_LIBRARIES=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --memory-init-file 0 main_render.o 

b3_vanilla_render2:
	 emcc src/vanilla/main_render.cpp -std=c++20 \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -c $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc $(LDFLAGS) --js-library lib/lib_webgpu.js \
	 -DCOMPUTE -o w3001.js \
	 $(BOOST_FLAGS) $(SIMD_FLAGS) $(GL_FLAGS) \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=1024mb -lmath.js -lhtml5.js -lint53.js \
	 -sUSE_SDL=0 -sAUTO_JS_LIBRARIES=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js js/rSlider.js --pre-js js/slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --memory-init-file 0 main_render.o 

b3_glsl_render:
	 emcc src/vanilla/glsl_main.cpp -std=c++20 \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -O0 -c $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc src/vanilla/glsl_load.cpp -std=c++17 \
	 -I /content/RAMDRIVE2/b3/include/vanilla/ -O0 -I /content/RAMDRIVE2/b3/tint/ \
	 -I /content/RAMDRIVE2/b3/SPIRV-Tools/include/ -I /content/RAMDRIVE2/b3/SPIRV-Cross/ \
	 -I /content/RAMDRIVE2/b3/SPIRV-Headers/include/ -c $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc $(LDFLAGS) -O0 -std=c++17 --js-library lib/lib_webgpu.js -fPIC -fPIE -DCOMPUTE -o $(WGL_BIN_NAME).js \
	 $(BOOST_FLAGS) $(SIMD_FLAGS) $(GL_FLAGS) \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=1024mb -lspirv-cross -lmath.js -lhtml5.js -lint53.js \
	 -sAUTO_JS_LIBRARIES=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=0 -sASYNCIFY_IMPORTS=['startWebGPU'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js js/rSlider.js --pre-js js/slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --memory-init-file 0 glsl_main.o glsl_load.o

b3_glsl_render2:
	 emcc src/vanilla/glsl_main.cpp -std=c++20 \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -c $(COMMON_FLAGS) $(BOOST_FLAGS) $(SIMD_FLAGS) 
	 emcc src/vanilla/glsl_load.cpp -std=c++20 -pthread \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -c $(COMMON_FLAGS)  $(BOOST_FLAGS) $(SIMD_FLAGS) 
	 emcc $(LDFLAGS) --js-library lib/lib_webgpu.js $(COMMON_FLAGS) $(LINK_FLAGS) -o $(WGL_BIN_NAME)a.js \
	 $(BOOST_FLAGS) $(SIMD_FLAGS) $(GL_FLAGS) \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=1024mb -lmath.js -lhtml5.js -lint53.js \
	 -sUSE_SDL=0 -sFILESYSTEM=0 -sAUTO_JS_LIBRARIES=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --memory-init-file 0 glsl_load.o glsl_main.o

vanilla_opt_gpujs:
	 em++ $(STDS) $(COMMON_FLAGS) src/vanilla/main_gpujs.cpp -c
	 em++ $(STDS) $(COMMON_FLAGS) $(LINK_FLAGS) main_gpujs.o -o $(NAMESTAMP) \
	 -sEXPORTED_RUNTIME_METHODS='["ccall"]' -sEXPORTED_FUNCTIONS=["_main","_gpu_js"] \
	 --extern-pre-js js/gpujsx.js --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js

b3_vanilla_icc:
	# /opt/intel/oneapi/compiler/2023.2.0/linux/bin/icpx --target=wasm32 -o icc.o src/vanilla/icc.cpp
	# ar rcs icc.a icc.o
	 emcc src/vanilla/main_icc.cpp -O0 -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS) -BOOST_NO_EXCEPTIONS 
	 emcc main_icc.o -O0 -o w3003.js -fPIC -fPIE -Wl,-lm,-lrt,-L/content/RAMDRIVE2/b3/,-ltbb \
	 -std=c++17 $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sINITIAL_MEMORY=512mb \
	 -sSUPPORT_ERRNO=0 \
	 -sPRECISE_F32=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_icctest","_js_simd","_js_tuple_float_short","_js_tuple_float_long","_js_tuple_gl","_js_tuple_avx","_js_tuple_avx_gl","_js_Tensors","_js_double","_js_noblock"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js \
	 --memory-init-file 0 --closure 0

b3_vanilla_webgpu_debug:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 em++ src/vanilla/main_render.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc main_render.o -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -DCOMPUTE -o w3001.js \
	 $(STDS) $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) $(GL_FLAGS) \
	 -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=512mb -lmath.js -lhtml5.js -lint53.js \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=0 -sASYNCIFY_IMPORTS=['startWebGPU','runWebGPU','wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] -sPRECISE_F32=1 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_GLFW=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU","_runWebGPU","_runWebGPU2"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js

b3_vanilla_llvm:
	 em++ src/vanilla/main.cpp -c -sUSE_BOOST_HEADERS=1 -std=gnu17 -std=c++17 -mbulk-memory -mnontrapping-fptoint -msimd128 \
	 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc src/vanilla/js.c -c -std=gnu17 -mbulk-memory -mnontrapping-fptoint -msimd128
	 emcc main.o js.o -o v3020.js -mllvm -std=gnu17 -std=c++17 -mbulk-memory -mnontrapping-fptoint -msimd128 \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 -sUSE_BOOST_HEADERS=1 -sUSE_WEBGPU=1 -sINITIAL_MEMORY=2048mb \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha \
	 -rtlib=compiler-rt \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -DEMMALLOC_USE_64BIT_OPS=1 \
	 -sASYNCIFY=1 -sPRECISE_F32=1 -sWASM_BIGINT=1 -sUSE_GLFW=0 -sNO_DISABLE_EXCEPTION_CATCHING \
	 -sEXPORTED_FUNCTIONS='["_main","_wgpu_init1","_wgpu_init2","_wgpu_init3","_wgpu_init4","_js_simd","_js_hello","_js_tuple_float_short","_js_tuple_float_long","_js_tuple_gl","_js_tuple_avx","_js_tuple_avx_gl","_js_Tensors","_js_double","_js_noblock"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js 

b3_shader_webgpu:
	 em++ $(STDS) lib/lib_webgpu_cpp20.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) lib/lib_webgpu.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) include/shader/intrins.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) include/shader/gl.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o glh.o -static
	 em++ $(STDS) include/shader/egl.cpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o eglh.o -static
	 em++ $(STDS) -c -DDOUBLE src/shader/shader_webgpu.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/shader/main.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) $(COMMON_FLAGS) $(LINK_FLAGS) $(GL_FLAGS) \
	 -DDOUBLE -DINTRINS $(BOOST_FLAGS) -DLIB_WEBGPU \
	 -DLIB_WEBGPU_CPP20 -o s3028dev.js $(LINK_SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-pre-js js/gpujsx.js --extern-post-js js/rSlider.js --extern-post-js js/slideOut.js main.o shader_webgpu.o


b3_cropcircle:
	 em++ $(STDS) include/shader/intrins.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) -c -DDOUBLE src/vanilla/cropcircle.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) $(COMMON_FLAGS) $(LINK_FLAGS) $(GL_FLAGS) -DDOUBLE $(BOOST_FLAGS) \
	 -o cc001.js $(LINK_SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_nano","_rotat"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js cropcircle.o

b3_video_webgpu:
	 em++ lib/lib_webgpu_cpp20.cpp -std=gnu17 -std=c++20 -static
	 em++ lib/lib_webgpu.cpp -std=gnu17 -std=c++20 -static
	 em++ src/video/main.cpp -c \
	 -fno-math-errno -std=c++20 -mcpu=bleeding-edge \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -ffunction-sections -fdata-sections -ffp-contract=on
	 em++ src/video/video_webgpu.cpp -c -fno-math-errno -std=c++20 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fno-math-errno -mcpu=bleeding-edge \
	 -fno-fast-math -ffunction-sections -fdata-sections
	 emcc main.o video_webgpu.o -o b3020w.js -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -mllvm -O3 -std=c++20 -fno-math-errno -flto \
	 -sASYNCIFY -sASSERTIONS=0 \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mavxifma \
	 -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 \
	 -sPRECISE_F32=2 -mtune=tigerlake -march=corei7-avx \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections \
	 -fwhole-program-vtables -polly \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_b3_egl","_nano","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

b3_fire:
	 em++ src/fire/main.cpp -c -std=c++2a
	 em++ src/fire/fire.cpp -c -std=c++2a
	 emcc main.o fire.o -o f3020.js -std=c++2a \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js

b3_vanilla:
	 em++ src/vanilla/main.cpp -c -std=c++2a
	 emcc main.o -o v3020.js -std=c++2a \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 --pre-js rSlider.js --pre-js slideOut.js
	 
b3_vanilla_simd:
	 em++ src/vanilla/main_simd.cpp -c -O0 -fpie -std=c++2a \
	 -msimd128 -mavx \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fno-math-errno -mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections
	 emcc main_simd.o -o v3020.js -O0 -std=c++2a -fpie \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mrdrnd \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fno-math-errno -mcpu=bleeding-edge -fwasm-exceptions \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -ffunction-sections -fdata-sections \
	 -sPRECISE_F32=2 -sWASM_BIGINT=0 -mtune=corei7-avx \
	 -sEXPORTED_FUNCTIONS='["_main","_js_simd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js

b3_vanilla_test:
	 em++ src/vanilla/main.cpp -c -O0 -fpie \
	 -fno-math-errno -std=c++20 -mcpu=bleeding-edge \
	 -fwasm-exceptions -ftree-vectorize -ffunction-sections -fdata-sections
	 emcc main.o -o v3020.js -O0 -fno-math-errno -std=c++20 \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -fwasm-exceptions -ftree-vectorize \
	 \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sPRECISE_F32=0 -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx \
	 -mcpu=bleeding-edge -fpie -flto -ffunction-sections -fdata-sections \
	 --pre-js rSlider.js --pre-js slideOut.js

fire22:
	 em++ 112222.cpp -o g3012.js -sFORCE_FILESYSTEM=1 \
	 -sMAXIMUM_MEMORY=4096mb -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=c++20 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_ldd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagegs.js --extern-pre-js cl-gpu.js

dbl: dbl.cpp Makefile
	em++ dbl.cpp -O1 -o d3001.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2400mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	 -DNDEBUG=1=1 -sSUPPORT_ERRNO=0 -sGL_DEBUG=0 -sGL_TRACK_ERRORS=0 \
	 -sGL_POOL_TEMP_BUFFERS=0 -sMEMORY64=0 -sLEGALIZE_JS_FFI=1 -sWASM_BIGINT=0 \
	 --closure 1 -g2 -std=c++2b -flto \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --post-js filesysdbl.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageg.js


all: b3hd
	echo 'Built 1ink.us Shaders.'
