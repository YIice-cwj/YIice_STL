#pragma once
#include "../utility/reference_wrapper.h"
#include "integral_constant.h"

namespace stl {

namespace detail {

/**
 * @brief 检查类型是否为引用包装器（reference_wrapper）
 */
template <typename T>
struct is_reference_wrapper : false_type {};

template <typename T>
struct is_reference_wrapper<reference_wrapper<T>> : true_type {};

template <typename T>
struct is_reference_wrapper<reference_wrapper<const T>> : true_type {};
}  // namespace detail
using detail::is_reference_wrapper;

/**
 * @brief 检查类型是否为引用包装器（reference_wrapper）的常量表达式
 */
template <typename T>
constexpr bool is_reference_wrapper_v = is_reference_wrapper<T>::value;

}  // namespace stl