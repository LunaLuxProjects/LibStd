#pragma once
#include <lstd/DataType.h>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cstdio>
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

    inline int strcpy(char* des, const char* src) noexcept
    {
#if defined(__gnu_linux__) || defined(__linux__)
        return strcpy(des, src);
#endif
#if defined(WIN32) || defined(WIN64)
        return strcpy_s(des, strlen(src), src);
#endif
    }
}