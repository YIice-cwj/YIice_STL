#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为联合体
 * @tparam T 类型
 */
template <typename T>
struct is_union : bool_constant<__is_union(T)> {};  // __is_union是编译器内置宏

}  // namespace detail
using detail::is_union;

/**
 * @brief 检查类型是否为联合体
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_union_v = detail::is_union<T>::value;

}  // namespace stl