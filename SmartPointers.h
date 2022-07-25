#pragma once
#include <lstd/ClibLink.h>
#include <lstd/Util.h>
namespace lstd::pointers
{
template<typename T> struct SizedPtr
{
    T *ptr = nullptr;
    data_size ptr_size = 0;
    constexpr SizedPtr() noexcept = default;
    constexpr SizedPtr(T *ptr_in, data_size ptr_size_in) noexcept
        : ptr(ptr_in)
        , ptr_size(ptr_size_in)
    {
    }
};

template<typename T> struct SinglePtr
{
  private:
    T *ptr = nullptr;
    data_size ptr_size = 0;

    void resizeIfNeeded(const data_size s_size)
    {
        if (ptr_size > s_size)
            return;
        ptr = static_cast<T *>(realloc(ptr, s_size + 1));
        memset(ptr, 0, s_size + 1);
        ptr_size = s_size;
    }

  public:
    constexpr SinglePtr() noexcept = default;
    constexpr SinglePtr(const T *s, const data_size s_size) noexcept
    {
        resizeIfNeeded(s_size);
        memmove_s(ptr, ptr_size, s, s_size);
    }

    constexpr SinglePtr(const SizedPtr<T> &ptr_in) noexcept
    {
        resizeIfNeeded(ptr_in.ptr_size);
        memmove_s(ptr, ptr_size, ptr_in.ptr, ptr_in.ptr_size);
    }

    constexpr SinglePtr(SinglePtr<T> &&other) noexcept
    {
        resizeIfNeeded(other.size());
        memmove_s(ptr, ptr_size, other.get(), other.size());
        delete other;
    }

    constexpr SinglePtr &operator=(SinglePtr<T> &&other) noexcept
    {
        resizeIfNeeded(other.size());
        memmove_s(ptr, ptr_size, other.get(), other.size());
        delete other;
        return *this;
    }

    constexpr SinglePtr &operator=(const SizedPtr<T> &ptr_in) noexcept
    {
        resizeIfNeeded(ptr_in.ptr_size);
        memmove_s(ptr, ptr_size, ptr_in.ptr, ptr_in.ptr_size);
        return *this;
    }

    constexpr void reset(SinglePtr<T> &&other) noexcept
    {
        resizeIfNeeded(other.size());
        memmove_s(ptr, ptr_size, other.get(), other.size());
        delete other;
        return *this;
    }

    constexpr void reset(const SizedPtr<T> &ptr_in) noexcept
    {
        resizeIfNeeded(ptr_in.ptr_size);
        memmove_s(ptr, ptr_size, ptr_in.ptr, ptr_in.ptr_size);
    }

    constexpr void reset(T *s, const data_size s_size) noexcept
    {
        resizeIfNeeded(s_size);
        memmove_s(ptr, ptr_size, s, s_size);
    }

    constexpr void reset(const T *s, const data_size s_size) noexcept
    {
        resizeIfNeeded(s_size);
        memmove_s(ptr, ptr_size, s, s_size);
    }

    constexpr void expand(data_size s_size)
    {
        [[unlikely]] if (ptr_size > (ptr_size + s_size))
            return;
        ptr = static_cast<T *>(realloc(ptr, (ptr_size + s_size) + 1));
        memset(ptr + ptr_size, 0, s_size + 1);
        ptr_size += s_size;
    }

    SinglePtr(SinglePtr const &) = delete;
    template<typename U> SinglePtr(SinglePtr<U> const &) = delete;
    SinglePtr &operator=(SinglePtr const &) = delete;
    template<typename U> SinglePtr &operator=(SinglePtr<U> const &) = delete;

    constexpr data_size size() const noexcept
    {
        return ptr_size;
    }

    constexpr SinglePtr<T>* self() noexcept
    {
        return this;
    }

    constexpr T * get() const noexcept
    {
        return ptr;
    }

    constexpr SizedPtr<T> release() noexcept
    {
        SizedPtr<T> x(ptr, ptr_size);
        ptr = nullptr;
        ptr_size = 0;
        return lstd::move(x);
    }

    constexpr T *operator->()
    {
        assert(ptr);
        return ptr;
    }

    constexpr const T *operator->() const
    {
        assert(ptr);
        return ptr;
    }

    constexpr const T &operator[](data_size index) const
    {
        assert(ptr);
        return ptr[index];
    }

    constexpr T &operator*()
    {
        assert(ptr);
        return *ptr;
    }

    constexpr const T &operator*() const
    {
        assert(ptr);
        return *ptr;
    }

    constexpr operator const T *() const
    {
        return ptr;
    }

    constexpr operator T *()
    {
        return ptr;
    }

    constexpr ~SinglePtr()
    {
        if (ptr != nullptr)
                delete ptr;
    }
};
} // namespace lstd::pointers