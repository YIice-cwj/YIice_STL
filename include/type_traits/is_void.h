#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为void
 * @tparam T 类型
 */
template <typename T>
struct is_void : false_type {};

template <>
struct is_void<void> : true_type {};

template <>
struct is_void<const void> : true_type {};

template <>
struct is_void<volatile void> : true_type {};

template <>
struct is_void<const volatile void> : true_type {};

}  // namespace detail
using detail::is_void;

/**
 * @brief 检查类型是否为void
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_void_v = is_void<T>::value;

}  // namespace stl