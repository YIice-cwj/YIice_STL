#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 判断是否是枚举类型
 * @tparam T 类型
 */
template <typename T>
struct is_enum : bool_constant<__is_enum(T)> {};  // __is_enum 编译器内置宏
}  // namespace detail

using detail::is_enum;

/**
 * @brief 判断是否是枚举类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_enum_v = is_enum<T>::value;
}  // namespace stl
