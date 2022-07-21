#pragma once
namespace lstd
{
	template<typename T>constexpr T &&move(T& arg) noexcept
	{
        return static_cast<T &&>(arg);
	}
}