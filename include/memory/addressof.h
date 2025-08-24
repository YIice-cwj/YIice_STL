#pragma once

namespace stl {

/**
 * @brief 获取对象的地址
 * @tparam T 类型
 * @param value 值
 */
template <typename T>
constexpr T* addressof(T& value) noexcept {
    return reinterpret_cast<T*>(
        &const_cast<char&>(reinterpret_cast<const volatile char&>(value)));
}

}  // namespace stl