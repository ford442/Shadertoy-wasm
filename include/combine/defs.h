
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#pragma pack(4)
#pragma fenv_access(on)
// #pragma clang diagnostic ignored "-Wdeprecated-declarations"
// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON
#pragma STDC FP_CONTRACT ON
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1
#define _XOPEN_SOURCE 700
