#pragma once

namespace stl {
namespace detail {

/**
 * @brief 移除引用类型
 * @tparam T 类型
 */
template <typename T>
struct remove_reference {
    using type = T;
};

template <typename T>
struct remove_reference<T&> {
    using type = T;
};

template <typename T>
struct remove_reference<T&&> {
    using type = T;
};
}  // namespace detail

using detail::remove_reference;

/**
 * @brief 移除引用类型
 * @tparam T 类型
 */
template <typename T>
using remove_reference_t = typename detail::remove_reference<T>::type;
}  // namespace stl