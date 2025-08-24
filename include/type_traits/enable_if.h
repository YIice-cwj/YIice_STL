#pragma once

namespace stl {
namespace detail {

/**
 * @brief 当 B 为 true 时，定义 type 为 T，否则定义 type 为 void
 * @tparam B 条件
 * @tparam T 类型
 */
template <bool B, typename T>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};

}  // namespace detail

using detail::enable_if;

/**
 * @brief 当 B 为 true 时，定义 type 为 T，否则定义 type 为 void
 * @tparam B 条件
 * @tparam T 类型
 */
template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;
}  // namespace stl