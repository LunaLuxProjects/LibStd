#pragma once
#include <lstd/ClibLink.h>
#include <lstd/DataType.h>
#include <lstd/Iterator.h>
#include <initializer_list>
#include <assert.h>
#include <string>
namespace lstd
{
template<typename T, typename U> struct BasicStringView;
    //FIXME: this is not c++20 compliend
template<typename T> struct BasicString : public lstd::ForwardIterator<T>, lstd::ReverseIterator<T>
{
  private:
    T *str;
    data_size str_size = 0;
    void new_string(data_size size,const T*new_str) noexcept
    {
        str_size = size + 1;
        str = static_cast<T *>(malloc(sizeof(T) * str_size));
        lstd::strcpy(str, new_str);
    }

    void delete_string() noexcept
    {
        memset(str, 0, str_size);
        free(str);
    }
  public:
    static const int64 npos{-1};

    explicit constexpr BasicString() noexcept
    {
        new_string(0, "");
    }

    constexpr BasicString(data_size count, T ch)
    {
        T *temp  = static_cast<T *>(malloc(sizeof(T) * count));
        for (data_size i = 0; i < count; i++)
            temp[i] = ch;
        new_string(count, temp);
        free(temp);
    }

    constexpr BasicString(const BasicString &other, data_size pos)
    {
        new_string(other.size() - pos, other.begin() + pos);
    }

    constexpr BasicString(const BasicString &other, data_size pos, data_size count)
    {
        new_string(count != npos ? other.size() : count, other.begin() + pos);
    }

    constexpr BasicString(const T *s, data_size count)
    {
        new_string(count, s);
    }
    constexpr BasicString(const T *s)
    {
        new_string(strlen(s), s);
    }

    //FIXME: "C-style string"
    //template<class InputIt> 
    //constexpr BasicString(InputIt first, InputIt last);

    constexpr BasicString(const BasicString &other)
    {
        new_string(other.size(), other.c_str());
    }
    constexpr BasicString(BasicString &&other)
    {
        new_string(other.size(), other.c_str());
    }

    constexpr BasicString(std::initializer_list<T> ilist)
    {
        new_string(ilist.size(), ilist.begin());
    }

    explicit constexpr BasicString(const lstd::BasicStringView<BasicString<T>, T> &t)
    {
            new_string(t.size(), t.begin());
    }

    constexpr BasicString(const lstd::BasicStringView<BasicString<T>, T> &t, data_size pos, data_size n)
    {
        //FIXME: idk what n is in the std spec
        new_string(t.size() - n, t.begin() + pos);
    }

    BasicString(std::nullptr_t) = delete;

    ~BasicString()
    {
        delete_string();
    }

    constexpr BasicString &operator=(const BasicString &other)
    {
        new_string(other.size(), other.c_str());
        return *this;
    }
    constexpr BasicString &operator=(BasicString &&other) noexcept
    {
        new_string(other.size(), other.c_str());
        return *this;
    }

    constexpr BasicString &operator=(const T *s)
    {
        new_string(strlen(s), s);
        return *this;
    }

    constexpr BasicString &operator=(T ch)
    {
        new_string(1, &ch);
        return *this;
    }

    constexpr BasicString &operator=(std::initializer_list<T> ilist)
    {
        new_string(ilist.size(), ilist.begin());
        return *this;
    }

    template<class StringViewLike> constexpr BasicString &operator=(const StringViewLike &t)
    {
        new_string(t.size(), t.begin());
        return *this;
    }

    constexpr BasicString &operator=(std::nullptr_t) = delete;

    constexpr T& operator[](data_size pos)
    {
        return str[pos];
    }

    constexpr BasicString &assign(data_size count, T ch)
    {
        new_string(1, &ch);
        return *this;
    }

    constexpr BasicString &assign(const BasicString &other)
    {
        new_string(other.size(), other.c_str());
        return *this;
    }

    constexpr BasicString &assign(const BasicString &other, data_size pos, data_size count = npos)
    {
        new_string(count, other.begin() + pos);
        return *this;
    }

    constexpr BasicString &assign(BasicString &&other)
    {
        new_string(other.size(), other.c_str());
        return *this;
    }

    constexpr BasicString &assign(const T *s, data_size count)
    {
        new_string(count, s);
        return *this;
    }
    constexpr BasicString &assign(const T *s)
    {
        new_string(strlen(s), s);
        return *this;
    }
    // FIXME: "C-style string"
    //template<class InputIt> constexpr BasicString &assign(InputIt first, InputIt last);
    constexpr BasicString &assign(std::initializer_list<T> ilist)
    {
        new_string(ilist.size(), ilist.begin());
        return *this;
    }


    constexpr BasicString &assign(const lstd::BasicStringView<BasicString<T>, T> &t)
    {
        new_string(t.size(), t.begin());
        return *this;
    }

    constexpr BasicString &assign(const lstd::BasicStringView<BasicString<T>, T> &t, data_size pos,
                                  data_size count = npos)
    {
        new_string(count, t.begin() + pos);
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

    constexpr T& at(data_size pos)
    {
        assert(pos >= this->size());
        return str[pos];
    }

    constexpr const T &at(data_size pos) const
    {
        assert(pos >= this->size());
        return str[pos];
    }

    constexpr const T &operator[](data_size pos) const
    {
        return at(pos);
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
        return str;
    }

    constexpr T *data() noexcept
    {
        return str;
    }

    constexpr const T *c_str() const noexcept
    {
        return str;
    }

    constexpr operator lstd::BasicStringView<BasicString<T>, T>() const noexcept
    {
        return lstd::BasicStringView<BasicString<T>, T>(this->c_str(), this->size());
    }

    virtual constexpr T *begin() noexcept override final
    {
        return str;
    }

    virtual constexpr const T *begin() const noexcept override final
    {
        return str;
    }

    virtual constexpr const T *cbegin() const noexcept override final
    {
        return str;
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
        return str_size;
    }

    virtual data_size i_size() const noexcept override final
    {
        return size();
    }

    constexpr data_size length() const noexcept
    {
        return str_size;
    }

    //FIXME: constexpr data_size max_size() const noexcept;

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
        new_string(new_size, temp);
        free(temp);
    }

    constexpr data_size capacity() const noexcept
    {
        return str_size;
    }

    //FIXME: constexpr void shrink_to_fit()

    constexpr void clear() noexcept
    {
        memset(str, 0, str_size);
    }
    constexpr BasicString &append(const BasicString &str_in)
    {
        data_size new_size = str_in.size() + this->size();
        T *new_str = static_cast<T *>(malloc(new_size));
        lstd::strcpy(new_str, this->str);
        lstd::strcpy(new_str + this->size() + 1, str_in.c_str());
        delete_string();
        new_string(new_size, new_str);
        free(new_str);
        return *this;
    }

    constexpr BasicString &append(const BasicString &str, data_size pos, data_size count = npos)
    {
        data_size new_size = (count != npos ? str.size() : count - pos) + this->size();
        T *new_str = static_cast<T *>(malloc(new_size));
        lstd::strcpy(new_str, this->str);
        lstd::strcpy(new_str + this->size() + 1, str.begin() + pos);
        delete_string();
        new_string(new_size, new_str);
        free(new_str);
        return *this;
    }

    constexpr BasicString &append(const T *s, data_size count)
    {
        data_size new_size = count + this->size();
        T *new_str = static_cast<T *>(malloc(new_size));
        lstd::strcpy(new_str, this->str);
        lstd::strcpy(new_str + this->size() + 1, s);
        delete_string();
        new_string(new_size, new_str);
        free(new_str);
        return *this;
    }

    constexpr BasicString &append(const T *s)
    {
        data_size new_size = strlen(s) + this->size();
        T *new_str = static_cast<T *>(malloc(new_size));
        lstd::strcpy(new_str, this->str);
        lstd::strcpy(new_str + this->size() + 1, s);
        delete_string();
        new_string(new_size, new_str);
        free(new_str);
        return *this;
    }

    // FIXME: "C-style string"
    //template<class InputIt> 
    //constexpr BasicString &append(InputIt first, InputIt last)

    constexpr BasicString &append(std::initializer_list<T> ilist)
    {
        data_size new_size = ilist.size() + this->size();
        T *new_str = static_cast<T *>(malloc(new_size));
        lstd::strcpy(new_str, this->str);
        lstd::strcpy(new_str + this->size() + 1, ilist.begin());
        delete_string();
        new_string(new_size, new_str);
        free(new_str);
        return *this;
    }

    constexpr BasicString &append(const lstd::BasicStringView<BasicString<T>, T> &t)
    {
        data_size new_size = t.size() + this->size();
        T *new_str = static_cast<T *>(malloc(new_size));
        lstd::strcpy(new_str, this->str);
        lstd::strcpy(new_str + this->size() + 1, t.c_str());
        delete_string();
        new_string(new_size, new_str);
        free(new_str);
        return *this;
    }

    constexpr BasicString &append(const lstd::BasicStringView<BasicString<T>, T> &t, data_size pos,
                                  data_size count = npos)
    {
        data_size new_size = (count != npos ? t.size() : count - pos) + this->size();
        T *new_str = static_cast<T *>(malloc(new_size));
        lstd::strcpy(new_str, this->str);
        lstd::strcpy(new_str + this->size() + 1, t.begin() + pos);
        delete_string();
        new_string(new_size, new_str);
        free(new_str);
        return *this;
    }

    constexpr BasicString &operator+=(const BasicString & str_in)
    {
        return append(str_in);
    }

    constexpr BasicString &operator+=(T ch)
    {
        return append(&ch,1);
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
        return strcmp(this->c_str(), str.c_str());
    }
    //constexpr int compare(data_size pos1, data_size count1, const BasicString &str) const;
    //constexpr int compare(data_size pos1, data_size count1, const BasicString &str, data_size pos2, data_size count2 = npos) const;
    constexpr int compare(const T *s) const
    {
        return strcmp(this->c_str(), s);
    }
   // constexpr int compare(data_size pos1, data_size count1, const T *s) const;
    //constexpr int compare(data_size pos1, data_size count1, const T *s, data_size count2) const; 
    constexpr int compare(const lstd::BasicStringView<BasicString<T>, T> &t) const
    {
        return strcmp(this->c_str(), t.c_str());
    }
    //template<class StringViewLike>
    //constexpr int compare(data_size pos1, data_size count1, const StringViewLike &t) const;
    //template<class StringViewLike>
    //constexpr int compare(data_size pos1, data_size count1, const StringViewLike &t, data_size pos2, data_size count2 = npos) const;

    constexpr bool starts_with(lstd::BasicStringView<BasicString<T>,T> sv) const noexcept
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
            if (str[this->size() - i] != sv[i])
                return false;
        return true;
    }

    constexpr bool ends_with(T c) const noexcept
    {
        return str[this->size()] == c;
    }

    constexpr bool ends_with(const T *s) const
    {
        for (data_size i = str(s); i != 0; i--)
            if (str[this->size() - i] != s[i])
                return false;
        return true;
    }

    //constexpr basic_string &replace(const_iterator first, const_iterator last, const basic_string &str);
    //constexpr basic_string &replace(size_type pos, size_type count, const basic_string &str, size_type pos2, size_type count2 = npos);
    //template< class InputIt >  constexpr basic_string &replace(const_iterator first, const_iterator last, InputIt first2, InputIt last2);
    //constexpr basic_string& replace( const_iterator first, const_iterator last,const CharT* cstr, size_type count2 );
    //constexpr basic_string& replace( const_iterator first, const_iterator last,const CharT* cstr );
    //constexpr basic_string& replace( const_iterator first, const_iterator last,size_type count2, CharT ch );
    // constexpr basic_string &replace(const_iterator first, const_iterator last, std::initializer_list<CharT> ilist);
    //template < class StringViewLike > constexpr basic_string &replace(const_iterator first, const_iterator last, const StringViewLike &t);
    //template < class StringViewLike > constexpr basic_string &replace(size_type pos, size_type count, const StringViewLike &t, size_type pos2, size_type count2 = npos);

    constexpr BasicString substr(data_size pos = 0, data_size count = npos) const
    {
        return BasicString(this->c_str(), pos, count);
    }

    constexpr bool operator == (const BasicString &rhs) noexcept
    {
        return compare(rhs);
    }

    constexpr bool operator==(const T* s) noexcept
    {
        return compare(s);
    }

    constexpr bool operator != (const BasicString &rhs) noexcept
    {
        return !compare(rhs);
    }

    constexpr bool operator < (const BasicString &rhs) noexcept
    {
       return this->size() < rhs.size();
    }

    constexpr bool operator > (const BasicString &rhs) noexcept
    {
        return this->size() > rhs.size();
    }

    constexpr bool operator <= (const BasicString &rhs) noexcept
    {
        return this->size() <= rhs.size();
    }

    constexpr bool operator >= (const BasicString &rhs) noexcept
    {
        return this->size() >= rhs.size();
    }

    constexpr data_size hash()
    {
        const T *s = this->begin();
        data_size h = 37;
        while (*s)
        {
            h = (h * 54059) ^ (s[0] * 76963);
            s++;
        }
        return h % 86969;
    }
};
typedef BasicString<char> string;
typedef BasicString<wchar_t> wstring;

template<typename T> struct hash
{
    [[nodiscard]] data_size operator()(T  str) const noexcept
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