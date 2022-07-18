#pragma once
#include <lstd/String.h>

namespace lstd
{
template<typename T,typename U> struct BasicStringView
{
  private:
    const T *str_ptr;
    data_size offset;
    data_size length;

  public:
    BasicStringView(const T &str, const data_size offset_in = 0) noexcept
        : str_ptr(&str)
        , offset(offset_in)
        , length(str.size())
    {
    }
    BasicStringView(const T *str, const data_size offset_in = 0) noexcept
        : str_ptr(str)
        , offset(offset_in)
        , length(str->size())
    {
    }
    BasicStringView(const T &str, const data_size length_in, const data_size offset_in = 0) noexcept
        : str_ptr(&str)
        , offset(offset_in)
        , length(length_in)
    {
    }
    BasicStringView(const T *str, const data_size length_in, const data_size offset_in = 0) noexcept
        : str_ptr(str)
        , offset(offset_in)
        , length(length_in)
    {
    }

    constexpr data_size size() const noexcept
    {
        return length - offset;
    }

    constexpr char operator[](data_size index) const noexcept
    {
        return str_ptr->at(offset + index);
    }

    constexpr BasicStringView &operator=(T &data_in) noexcept
    {
        if (str_ptr)
            str_ptr = nullptr;
        str_ptr = &data_in;
        return *this;
    }

    constexpr inline bool operator==(const T str) const noexcept
    {
        const U* true_str  = str_ptr->begin(offset);
        for(data_size i = 0; i <= str.size(); i++)
        {
            if(true_str[i] != str[i])
                return false;
        }
        return true;
    }

    constexpr BasicStringView substr(const data_size start_index) noexcept
    {
        return BasicStringView(str_ptr, start_index);
    }
    constexpr BasicStringView substr(const data_size start_index, const data_size end_index) noexcept
    {
        return BasicStringView(str_ptr, end_index, start_index);
    }
};

typedef lstd::BasicStringView<lstd::string,char> string_view;
typedef lstd::BasicStringView<lstd::wstring,wchar_t> wstring_view;
} // namespace lstd
#ifdef NO_DEFINED_STD
namespace std
{
typedef lstd::string_view string_view;
typedef lstd::wstring_view wstring_view;
} // namespace std
#endif