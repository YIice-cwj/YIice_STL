#pragma once
#include "integral_constant.h"

namespace stl {

namespace detail {

/**
 * @brief 检查类型是否为空指针类型
 * @tparam T 类型
 */
template <typename T>
struct is_null_pointer : false_type {};

template <>
struct is_null_pointer<decltype(nullptr)> : true_type {};

template <>
struct is_null_pointer<decltype(NULL)> : true_type {};

}  // namespace detail
using detail::is_null_pointer;

/**
 * @brief 检查类型是否为空指针类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

}  // namespace stl