
#pragma once

#ifdef __GNUC__
#define _attribute_packed_		__attribute__((packed))
#define _attribute_aligned_(s)	__attribute__((aligned(s)))
#define _attribute_session_(s)	__attribute__((section(s)))
#define _attribute_ram_code_  	_attribute_session_(".ram_code")
#define _attribute_custom_code_  	_attribute_session_(".custom") volatile
#define _attribute_no_inline_   __attribute__((noinline)) 
#define _attribute_forceinline_ __attribute__((always_inline))
#define _attribute_optimize_(x) __attribute__((optimize(x)))
#define _attribute_optimize_o2_ __attribute__((optimize("-O2")))
// #define _inline_ 				extern __attribute__ ((gnu_inline)) inline
#else
#define _attribute_packed_
#define _attribute_aligned_(s)	__declspec(align(s))
#define _attribute_session_(s)
#define _attribute_ram_code_
#define _attribute_custom_code_
#define _attribute_no_inline_   __declspec(noinline) 
#define _attribute_optimize_(x)
#define _attribute_optimize_o2_
#endif
#ifdef WIN32
#ifndef __cplusplus
#define inline 					__inline
#endif
#define STATIC
#else
#define STATIC					static
#endif
#define _inline_ 				inline				//   C99 meaning

