#pragma once

namespace stl {

namespace detail {

/**
 * @brief 移除 const 修饰
 * @tparam T 类型
 */
template <typename T>
struct remove_const {
    using type = T;
};

template <typename T>
struct remove_const<const T> {
    using type = T;
};

}  // namespace detail

using detail::remove_const;

/**
 * @brief 移除 const 修饰
 * @tparam T 类型
 */
template <typename T>
using remove_const_t = typename detail::remove_const<T>::type;

}  // namespace stl