#pragma once
#include <lstd/ClibLink.h>
#include <lstd/DataType.h>
#include <lstd/Iterator.h>
namespace lstd
{

template<typename T> struct BasicString : public lstd::Iterator<T>
{
  private:
    T *str;
    data_size str_size = 0;
  public:
    static const int64 npos{-1};
    constexpr BasicString()
        : str(static_cast<T *>(malloc(sizeof(T)))) {}
    constexpr BasicString(const T data_in)
        : str(static_cast<T *>(malloc(sizeof(T))))
    {
        str[0] = data_in;
    }
    constexpr BasicString(const T *data_in)
    {
        str_size = strlen(data_in) + 1;
        str = static_cast<T *>(malloc(sizeof(T) * str_size));
        memcpy(str, data_in, str_size);
    }
    constexpr BasicString(const T *data_in,const data_size offset,const data_size size)
    {
        str_size = size;
        str = static_cast<T *>(malloc(sizeof(T) * size));
        memcpy(str, data_in + offset, size);
    }
    constexpr BasicString(T *data_in)
    {
        str = new T[(str_size = (strlen(data_in) + 1))];
        memcpy(str, data_in, strlen(data_in));
    }

    constexpr inline BasicString &operator=(const T *data_in) noexcept
    {
        if (str)
            delete str;
        str = new T[strlen(data_in) + 1];
        memcpy(str, data_in, strlen(data_in));
        return *this;
    }

    constexpr bool compare(const T *data_in) noexcept
    {
        const T* true_str  = begin();
        for(data_size i = 0; i <= strlen(data_in); i++)
        {
            if(true_str[i] != str[i])
                return false;
        }
        return true;
    }

    constexpr inline bool operator==(const T &data_in) noexcept
    {
        return compare(&data_in);
    }

    constexpr inline bool operator!=(const T &data_in) noexcept
    {
        return !compare(&data_in);
    }

    constexpr inline bool operator==(const T *data_in) noexcept
    {
        return compare(data_in);
    }

    constexpr inline bool operator!=(const T *data_in) noexcept
    {
        return !compare(data_in);
    }

    constexpr inline bool operator==(const BasicString &data_in) noexcept
    {
        return compare(data_in.c_str());
    }

    constexpr inline bool operator!=(const BasicString &data_in) noexcept
    {
        return !compare(data_in.c_str());
    }

    constexpr inline bool operator==(const BasicString *data_in) noexcept
    {
        return compare(data_in->c_str());
    }

    constexpr inline bool operator!=(const BasicString *data_in) noexcept
    {
        return !compare(data_in->c_str());
    }

    constexpr void append(const T* data, data_size size_in) noexcept
    {
        str_size += size_in;
#if defined(__gnu_linux__) || defined(__linux__)
        strncat(this->str, data, size_in);
#endif
#if defined(WIN32) || defined(WIN64)
        strcat_s(this->str, str_size, data);
#endif
    }

    constexpr inline BasicString& operator+=(const BasicString &data_in) noexcept
    {
        append(data_in.c_str(), data_in.size());
        return *this;
    }

    constexpr inline BasicString& operator+=(const char* data_in) noexcept
    {
        append(data_in, strlen(data_in));
        return *this;
    }

    constexpr inline BasicString& operator+=(const T letter) noexcept
    {
        append(&letter,sizeof(T));
        return *this;
    }

    constexpr inline T operator[](data_size index) const noexcept
    {
        return at(index);
    }

    constexpr T at(const data_size index) const noexcept
    {
        return str[index];
    }
    constexpr T *data() const noexcept
    {
        return str;
    }
    constexpr const T *c_str() const noexcept
    {
        return str;
    }

    constexpr void clear() noexcept
    {
        free(str);
        str = static_cast<T*>(malloc(sizeof(T)));
        memset(str, 0, sizeof(T));
        str_size = 1;
    }

    virtual constexpr data_size size() const noexcept override final
    {
        return str_size;
    };

    virtual constexpr const T *begin() const noexcept override final
    {
        return str;
    };

    virtual constexpr T *cbegin() const noexcept override final
    {
        return str;
    };
    constexpr const T *begin(const data_size index) const noexcept
    {
        return begin() + min(index,size());
    };
    BasicString substr(const data_size start_index) noexcept
    {
        return substr(start_index, size());
    };
    BasicString substr(const data_size start_index, const data_size end_index) noexcept
    {
        data_size size = (end_index - start_index) - 2;
        T *temp = static_cast<T*>(malloc(size));
        memset(temp, 0, size);
        memcpy(temp, str + start_index, size);
        return BasicString(temp);
    }

    constexpr int64 find(const char find_letter) const noexcept
    {
        for(data_size i = 0; i < str_size; i++)
        {
            if(str[i] == find_letter)
                return i;
        }
        return npos;
    }
};

typedef BasicString<char> string;
typedef BasicString<wchar_t> wstring;
} // namespace lstd
#ifdef NO_DEFINED_STD
namespace std
{
typedef lstd::string string;
typedef lstd::wstring wstring;
} // namespace std
#endif