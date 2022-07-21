#pragma once
#include <lstd/DataType.h>
namespace lstd
{
template<typename T>
struct Iterator
{
    typedef const T *const_iterator;
    typedef T *iterator;
    virtual constexpr data_size size() const noexcept = 0;
    virtual constexpr const_iterator begin() const noexcept = 0;
    virtual constexpr iterator cbegin() const noexcept = 0;
    constexpr const_iterator end() const noexcept
    {
        return begin() + size();
    }
    constexpr iterator cend() const noexcept
    {
        return cbegin() + size();
    }
    virtual ~Iterator() noexcept = default;
};

} // namespace lstd