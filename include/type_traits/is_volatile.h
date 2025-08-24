#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为 volatile修饰类型
 * @tparam T 类型
 */
template <typename T>
struct is_volatile : false_type {};

template <typename T>
struct is_volatile<volatile T> : true_type {};

}  // namespace detail

using detail::is_volatile;

/**
 * @brief 检查类型是否为 volatile修饰类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_volatile_v = is_volatile<T>::value;

}  // namespace stl