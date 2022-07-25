#pragma once
#include <assert.h>
#include <initializer_list>
#include <lstd/ClibLink.h>
#include <lstd/DataType.h>
#include <lstd/Iterator.h>
#include <lstd/SmartPointers.h>
#include <string>
namespace lstd
{
template<typename T, typename U> struct BasicStringView;
// FIXME: this is not c++20 compliend
template<typename T>
struct BasicString
    : public lstd::ForwardIterator<T>
    ,public lstd::ReverseIterator<T>
{
  protected:
    using SinglePtr = lstd::pointers::SinglePtr<T>;
    SinglePtr str;
  public:
    static const int64 npos{-1};

    explicit constexpr BasicString() noexcept = default;
    constexpr BasicString(data_size count, T ch)
    {
        T *temp = static_cast<T *>(malloc(sizeof(T) * count));
        for (data_size i = 0; i < count; i++)
            temp[i] = ch;
        str.reset(temp);
    }

    constexpr BasicString(const BasicString &other, data_size pos)
        : str(SinglePtr(other.begin() + pos, other.size() - pos))
    {
    }

    constexpr BasicString(const BasicString &other, data_size pos, data_size count)
        : str(SinglePtr((T*)other.data() + pos, count == npos ? other.size() : count))
    {
    }

    constexpr BasicString(const T *s, data_size count)
    {
        T *ptr = static_cast<T *>(malloc(count + 1));
        memset(ptr, 0, count + 1);
        memcpy_s(ptr, count + 1, s, count);
        str.reset(ptr, count);
    }

    constexpr BasicString(const T *s)
    {
        data_size count = strlen(s);
        T *ptr = static_cast<T *>(malloc(count + 1));
        memset(ptr, 0, count + 1);
        memcpy_s(ptr, count + 1, s, count);
        str.reset(ptr, count);
    }

    // FIXME: "C-style string"
    // template<class InputIt>
    // constexpr BasicString(InputIt first, InputIt last);

    constexpr BasicString(const BasicString &other)
    {
        str.reset(other.begin(),other.size());
    }

    constexpr BasicString(BasicString &&other)
    {
        str.reset(other.str.self()->release());
    }

    constexpr BasicString(std::initializer_list<T> ilist)
    {
        str.reset(ilist.begin(), ilist.size());
    }

    explicit constexpr BasicString(const lstd::BasicStringView<BasicString<T>, T> &t)
    {
        str.reset(t.begin(), t.size());
    }

    constexpr BasicString(const lstd::BasicStringView<BasicString<T>, T> &t, data_size pos, data_size n)
    {
        str.reset(t.begin() + pos, t.size() - n);
    }

    BasicString(std::nullptr_t) = delete;
    constexpr BasicString &operator=(std::nullptr_t) = delete;

    ~BasicString() = default;

    constexpr BasicString &operator=(const BasicString &other)
    {
        str.reset(other.begin(), other.size());
        return *this;
    }
    constexpr BasicString &operator=(BasicString &&other) noexcept
    {
        str.reset(other.str.self()->release());
        return *this;
    }

    constexpr BasicString &operator=(const T *s)
    {

        data_size count = strlen(s);
        T *ptr = static_cast<T *>(malloc(count + 1));
        memset(ptr, 0, count + 1);
        memcpy_s(ptr, count + 1, s, count);
        str.reset(ptr, count);
        return *this;
    }

    constexpr BasicString &operator=(T ch)
    {
        str.reset(new char[1]{ch},1);
        return *this;
    }

    constexpr BasicString &operator=(std::initializer_list<T> ilist)
    {
        str.reset(ilist.begin(), ilist.size());
        return *this;
    }

    template<class StringViewLike> constexpr BasicString &operator=(const StringViewLike &t)
    {
        str.reset(t.begin(),t.size());
        return *this;
    }

    constexpr const  T &operator[](data_size pos) const noexcept
    {
        return str[pos];
    }

    constexpr BasicString &assign(data_size count, T ch)
    {
        str.reset(new char[1]{ch},1);
        return *this;
    }

    constexpr BasicString &assign(const BasicString &other)
    {
        str = other.moveSinglePtr();
        return *this;
    }

    constexpr BasicString &assign(const BasicString &other, data_size pos, data_size count = npos)
    {
        str.reset(other.begin() + pos, count);
        return *this;
    }

    constexpr BasicString &assign(BasicString &&other)
    {
        str.reset(other.begin(), other.size());
        return *this;
    }

    constexpr BasicString &assign(const T *s, data_size count)
    {
        str.reset(s, count);
        return *this;
    }
    constexpr BasicString &assign(const T *s)
    {
        str.reset(s);
        return *this;
    }
    // FIXME: "C-style string"
    // template<class InputIt> constexpr BasicString &assign(InputIt first, InputIt last);
    constexpr BasicString &assign(std::initializer_list<T> ilist)
    {
        str.reset(ilist.begin(), ilist.size());
        return *this;
    }

    constexpr BasicString &assign(const lstd::BasicStringView<BasicString<T>, T> &t)
    {
        str.reset(t.begin(), t.size());
        return *this;
    }

    constexpr BasicString &assign(const lstd::BasicStringView<BasicString<T>, T> &t, data_size pos,
                                  data_size count = npos)
    {
        str.reset(t.begin() + pos, count);
        return *this;
    }

    constexpr BasicString &operator()(const BasicString &str)
    {
        return assign(str);
    }

    constexpr BasicString &operator()(T ch)
    {
        return assign(ch);
    }

    constexpr BasicString &operator()(const T *s)
    {
        return assign(s);
    }

    constexpr BasicString &operator()(std::initializer_list<T> ilist)
    {
        return assign(ilist);
    }

    constexpr BasicString &operator()(const lstd::BasicStringView<BasicString<T>, T> &t)
    {
        return assign(t);
    }

    constexpr T at(data_size pos)
    {
        assert(pos <= size());
        return str[pos];
    }

    constexpr const T at(data_size pos) const
    {
        assert(pos <= size());
        return str[pos];
    }

    constexpr T &front()
    {
        return operator[](0);
    }

    constexpr const T &front() const
    {
        return operator[](0);
    }

    constexpr T &back()
    {
        return operator[](size() - 1);
    }

    constexpr const T &back() const
    {
        return operator[](size() - 1);
    }

    constexpr const T *data() const noexcept
    {
        return str.get();
    }

    constexpr T *data() noexcept
    {
        return str.get();
    }

    constexpr const T *c_str() const noexcept
    {
        return str.get();
    }

    constexpr operator lstd::BasicStringView<BasicString<T>, T>() const noexcept
    {
        return lstd::BasicStringView<BasicString<T>, T>(c_str(), size());
    }

    virtual constexpr T *begin() noexcept override final
    {
        return str.get();
    }

    virtual constexpr const T *begin() const noexcept override final
    {
        return str.get();
    }

    virtual constexpr const T *cbegin() const noexcept override final
    {
        return str.get();
    }

    virtual constexpr T *rbegin() noexcept override final
    {
        return this->end();
    }

    virtual constexpr const T *rbegin() const noexcept override final
    {
        return this->end();
    }

    virtual constexpr const T *crbegin() const noexcept override final
    {
        return this->cend();
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return begin() == this->end();
    }

    constexpr data_size size() const noexcept
    {
        return str.size();
    }

    virtual data_size i_size() const noexcept override final
    {
        return size();
    }

    constexpr data_size length() const noexcept
    {
        return size();
    }

    // FIXME: constexpr data_size max_size() const noexcept;

    constexpr void reserve(data_size new_cap)
    {
        data_size new_size;
        if (new_cap < size())
            new_size = new_cap;
        else
            new_size = size();
        T *temp = static_cast<T *>(malloc(new_size));
        data_size index = 0;
        for (data_size i = new_size; i != 0; i--)
            temp[++index] = str[i];
        str.reset(temp);
    }

    constexpr data_size capacity() const noexcept
    {
        return size();
    }

    // FIXME: constexpr void shrink_to_fit()

    constexpr void clear() noexcept
    {
        str.reset(nullptr,0);
    }
    constexpr BasicString &append(const BasicString &str_in)
    {
        return append(str_in.begin(), str_in.size());
    }

    constexpr BasicString &append(const T *s)
    {
        return append(s,strlen(s));
    }

    constexpr BasicString &append(const BasicString &str_in, data_size pos, data_size count = npos)
    {
        str.expand((count != npos ? str_in.size() : count - pos));
        strcat_s(str.get() + size() - str_in.size(), str_in.size(), str_in.begin() + pos);
        return *this;
    }

    constexpr BasicString &append(const T *s, data_size count)
    {
        str.expand(count);
        strcat_s(str.get() + size() - count, count + 1, s);
        return *this;
    }

    constexpr BasicString &append(const T ch)
    {
        str.expand(1);
        strcat_s(str.get() + size() - 1, 2, &ch);
        return *this;
    }

    // FIXME: "C-style string"
    // template<class InputIt>
    // constexpr BasicString &append(InputIt first, InputIt last)

    constexpr BasicString &append(std::initializer_list<T> ilist)
    {
        str.expand(ilist.size());
        strcat_s(str.get() + size() - ilist.size(), ilist.size(), ilist.begin());
        return *this;
    }

    constexpr BasicString &append(const lstd::BasicStringView<BasicString<T>, T> &t)
    {
        str.expand(t.size());
        strcat_s(str.get() + size() - t.size(), t.size(), t.c_str());
        return *this;
    }

    constexpr BasicString &append(const lstd::BasicStringView<BasicString<T>, T> &t, data_size pos, data_size count = npos)
    {
        str.expand((count != npos ? t.size() : count - pos));
        strcat_s(str.get() + size() - t.size(), t.size(), t.begin() + pos);
        return *this;
    }

    constexpr BasicString &operator+=(const BasicString &str_in)
    {
        return append(str_in);
    }

    constexpr BasicString &operator+=(T ch)
    {
        return append(ch);
    }

    constexpr BasicString &operator+=(const T *s)
    {
        return append(s);
    }

    constexpr BasicString &operator+=(std::initializer_list<T> ilist)
    {
        return append(ilist);
    }

    constexpr BasicString &operator+=(const lstd::BasicStringView<BasicString<T>, T> &t)
    {
        return append(t);
    }

    constexpr int compare(const BasicString &str) const noexcept
    {
        return strcmp(c_str(), str.c_str());
    }
    // constexpr int compare(data_size pos1, data_size count1, const BasicString &str) const;
    // constexpr int compare(data_size pos1, data_size count1, const BasicString &str, data_size pos2, data_size count2
    // = npos) const;
    constexpr int compare(const T *s) const
    {
        return strcmp(c_str(), s);
    }
    // constexpr int compare(data_size pos1, data_size count1, const T *s) const;
    // constexpr int compare(data_size pos1, data_size count1, const T *s, data_size count2) const;
    constexpr int compare(const lstd::BasicStringView<BasicString<T>, T> &t) const
    {
        return strcmp(c_str(), t.c_str());
    }
    // template<class StringViewLike>
    // constexpr int compare(data_size pos1, data_size count1, const StringViewLike &t) const;
    // template<class StringViewLike>
    // constexpr int compare(data_size pos1, data_size count1, const StringViewLike &t, data_size pos2, data_size count2
    // = npos) const;

    constexpr bool starts_with(lstd::BasicStringView<BasicString<T>, T> sv) const noexcept
    {
        for (data_size i = 0; i < sv.size(); i++)
            if (str[i] != sv[i])
                return false;
        return true;
    }

    constexpr bool starts_with(T c) const noexcept
    {
        return str[0] == c;
    }

    constexpr bool starts_with(const T *s) const
    {
        for (data_size i = 0; i < strlen(s); i++)
            if (str[i] != s[i])
                return false;
        return true;
    }

    constexpr bool ends_with(lstd::BasicStringView<BasicString<T>, T> sv) const noexcept
    {
        for (data_size i = sv.size(); i != 0; i--)
            if (str[size() - i] != sv[i])
                return false;
        return true;
    }

    constexpr bool ends_with(T c) const noexcept
    {
        return str[size()] == c;
    }

    constexpr bool ends_with(const T *s) const
    {
        for (data_size i = str(s); i != 0; i--)
            if (str[size() - i] != s[i])
                return false;
        return true;
    }

    // constexpr basic_string &replace(const_iterator first, const_iterator last, const basic_string &str);
    // constexpr basic_string &replace(size_type pos, size_type count, const basic_string &str, size_type pos2,
    // size_type count2 = npos); template< class InputIt >  constexpr basic_string &replace(const_iterator first,
    // const_iterator last, InputIt first2, InputIt last2); constexpr basic_string& replace( const_iterator first,
    // const_iterator last,const CharT* cstr, size_type count2 ); constexpr basic_string& replace( const_iterator first,
    // const_iterator last,const CharT* cstr ); constexpr basic_string& replace( const_iterator first, const_iterator
    // last,size_type count2, CharT ch );
    //  constexpr basic_string &replace(const_iterator first, const_iterator last, std::initializer_list<CharT> ilist);
    // template < class StringViewLike > constexpr basic_string &replace(const_iterator first, const_iterator last,
    // const StringViewLike &t); template < class StringViewLike > constexpr basic_string &replace(size_type pos,
    // size_type count, const StringViewLike &t, size_type pos2, size_type count2 = npos);

    constexpr BasicString substr(data_size pos = 0, data_size count = npos) const
    {
        return BasicString(*this, pos, count);
    }

    constexpr bool operator==(const BasicString &rhs) noexcept
    {
        return compare(rhs);
    }

    constexpr bool operator==(const T *s) noexcept
    {
        return compare(s);
    }

    constexpr bool operator==(const T s) noexcept
    {
        return str[0] == s;
    }

    constexpr bool operator!=(const BasicString &rhs) noexcept
    {
        return !compare(rhs);
    }

    constexpr bool operator<(const BasicString &rhs) noexcept
    {
        return size() < rhs.size();
    }

    constexpr bool operator>(const BasicString &rhs) noexcept
    {
        return size() > rhs.size();
    }

    constexpr bool operator<=(const BasicString &rhs) noexcept
    {
        return size() <= rhs.size();
    }

    constexpr bool operator>=(const BasicString &rhs) noexcept
    {
        return size() >= rhs.size();
    }

constexpr data_size hash()
    {
        T *s = this->begin();
        data_size h = 37;
        data_size i = 0;
        while (*s)
        {
            h = (h * 54059) ^ (s[0] * 76963);
            s++;
            i++;
        }
        s = s - i;
        return h;
    }
};
typedef BasicString<char> string;
typedef BasicString<wchar_t> wstring;

template<typename T> struct hash
{
    [[nodiscard]] data_size operator()(T str) const noexcept
    {
        return str.hash();
    }
};

} // namespace lstd
#ifdef NO_DEFINED_STD
namespace std
{
typedef lstd::string string;
typedef lstd::wstring wstring;
} // namespace std
#endif