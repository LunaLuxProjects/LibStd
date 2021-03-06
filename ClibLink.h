#pragma once
#include <lstd/DataType.h>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
namespace lstd
{   
    #undef min
    #undef max
    template<typename T>
    constexpr inline T min(const T arg1,const T arg2) noexcept
    {
        return arg1 < arg2 ? arg1 : arg2;
    }
    
    template<typename T>
    constexpr inline T max(const T arg1,const T arg2) noexcept
    {
        return arg1 > arg2 ? arg1 : arg2;
    }

    constexpr inline data_size min(const data_size arg1,const data_size arg2) noexcept { return min<data_size>(arg1,arg2); }
    constexpr inline data_size max(const data_size arg1,const data_size arg2) noexcept { return max<data_size>(arg1,arg2); }
#if defined(__gnu_linux__) || defined(__linux__)
#    define strcpy_s(des, size, src) strcpy(des, src)
#    define strncpy_s(des, src, dest_size, src_size) strncpy(des, src, dest_size)
#    define memcpy_s(des, dest_size, src, src_size) memcpy(des, src, dest_size)
#endif
}