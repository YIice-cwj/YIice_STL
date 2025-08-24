#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为指针类型
 * @tparam T 类型
 */
template <typename T>
struct is_pointer : false_type {};

template <typename T>
struct is_pointer<T*> : true_type {};

}  // namespace detail

using detail::is_pointer;

/**
 * @brief 检查类型是否为指针类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_pointer_v = is_pointer<T>::value;

}  // namespace stl