#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为左值引用
 * @tparam T 类型
 */
template <typename T>
struct is_lvalue_reference : false_type {};

template <typename T>
struct is_lvalue_reference<T&> : true_type {};

}  // namespace detail
using detail::is_lvalue_reference;

/**
 * @brief 检查类型是否为左值引用
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

}  // namespace stl