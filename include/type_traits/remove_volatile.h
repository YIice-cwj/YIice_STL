#pragma once

namespace stl {
namespace detail {

/**
 * @brief 移除 volatile 修饰符
 * @tparam T 类型
 */
template <typename T>
struct remove_volatile {
    using type = T;
};

template <typename T>
struct remove_volatile<volatile T> {
    using type = T;
};
}  // namespace detail

using detail::remove_volatile;

/**
 * @brief 移除 volatile 修饰符
 * @tparam T 类型
 */
template <typename T>
using remove_volatile_t = typename detail::remove_volatile<T>::type;
}  // namespace stl