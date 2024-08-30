BETA_BIN_NAME = d0-001

datachannel:
	 em++ datachannel.cpp $(STDS) -I./ -ldatachannel-wasm -fPIC -m64 -flto -flto=thin -pipe -ffp-contract=fast -fexcess-precision=fast \
	 -ffast-math -ffinite-math-only -funsafe-math-optimizations -fno-trapping-math -fno-math-errno \
	 -mmutable-globals -mbulk-memory -matomics -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer \
	 -mextended-const -O3 -fno-strict-aliasing $(SIMD_FLAGS) -sMEMORY64=1 -c -fno-rounding-math -fcx-limited-range -fassociative-math -freciprocal-math -fno-signed-zeros
	 em++ -O3 -fPIE -I./ -sEVAL_CTORS=1 -sEXIT_RUNTIME=0 -m64 -sMALLOC=mimalloc -sWASMFS=1 \
	 -sWASM_BIGINT=1 -mextended-const -dead_strip -mbulk-memory -matomics -pipe -DQUAD -DDOUBLE \
	 -sDEFAULT_TO_CXX=0 -stdlib=libc++ -sUSE_ES6_IMPORT_META=0 -fno-rounding-math -fassociative-math -freciprocal-math -fno-signed-zeros \
	 --use-preload-plugins --closureFriendly --typed-function-references --enable-reference-types -fno-strict-aliasing \
	 -ffast-math -ffinite-math-only -funsafe-math-optimizations -fcx-limited-range -fno-trapping-math -ffp-contract=fast -fexcess-precision=fast -sENVIRONMENT=web \
	 -DCOMPUTE -o $(BETA_BIN_NAME)-data.js -sSTRICT=1 -sSTRICT_JS=0 \
	 $(LINK_SIMD_FLAGS) -sUSE_GLFW=0 -sASSERTIONS=0 -march=haswell -sMEMORY64=2 \
	 -ftree-vectorize -fstrict-vtable-pointers -fno-math-errno --target=wasm64 -DNDEBUG=1 \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer \
	 -fwhole-program-vtables -polly -polly-position=before-vectorizer -mtune=wasm64 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=768mb -ffunction-sections -fdata-sections \
	 -sABORT_ON_WASM_EXCEPTIONS=0 -sEMULATE_FUNCTION_POINTER_CASTS=1 \
	 -sUSE_SDL=0 -sFORCE_FILESYSTEM=1 -sAUTO_JS_LIBRARIES=0 -sAUTO_NATIVE_LIBRARIES=0 -sDISABLE_EXCEPTION_THROWING=1 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=1 -sIGNORE_MISSING_MAIN=0 \
	 -sASYNCIFY=0 -sEXPORTED_FUNCTIONS='["_main"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 datachannel.o -ldatachannel-wasm --output_eol linux -rtlib=compiler-rt --closure 0 \
	 -sMODULARIZE=1 -sEXPORT_ES6=0 -sEXPORT_NAME='libChannel' -sSUPPORT_LONGJMP=wasm -sDISABLE_EXCEPTION_CATCHING=1

all: datachannel
	echo 'Built 1ink.us Datachannel Test.'
