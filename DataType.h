#pragma once
#if defined(__gnu_linux__) || defined(__linux__)
typedef __UINT_FAST8_TYPE__ uint8;
typedef __UINT_FAST16_TYPE__ uint16;
typedef wchar_t unicode;
typedef __UINT_FAST32_TYPE__ uint32;
typedef __UINT_FAST64_TYPE__ uint64;
typedef __UINT8_TYPE__ uint8_slow;
typedef __UINT16_TYPE__ uint16_slow;
typedef __UINT16_TYPE__ unicode_slow;
typedef __UINT32_TYPE__ uint32_slow;
typedef __UINT64_TYPE__ uint64_slow;
typedef __SIZE_TYPE__ data_size;

typedef __INT_FAST8_TYPE__ int8;
typedef __INT_FAST16_TYPE__ int16;
typedef __INT_FAST32_TYPE__ int32;
typedef __INT_FAST64_TYPE__ int64;
typedef __INT8_TYPE__ int8_slow;
typedef __INT16_TYPE__ int16_slow;
typedef __INT32_TYPE__ int32_slow;
typedef __INT64_TYPE__ int64_slow;
typedef signed long long sdata_size;
#endif
#if defined(WIN32) || defined(WIN64)
#    define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef  UINT8  uint8;
typedef  UINT16 uint16;
typedef  WCHAR unicode;
typedef UINT32 uint32;
typedef UINT64 uint64;
typedef uint8 uint8_slow;
typedef uint16 uint16_slow;
typedef unicode unicode_slow;
typedef uint32 uint32_slow;
typedef uint64 uint64_slow;
typedef size_t data_size;

typedef  INT8 int8;
typedef  INT16 int16;
typedef INT32 int32;
typedef INT64 int64;
typedef int8 int8_slow;
typedef int16 int16_slow;
typedef int32 int32_slow;
typedef int64 int64_slow;
typedef signed long long sdata_size;
#endif

typedef float float32;
typedef double float64;