#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为 const类型
 * @tparam T 类型
 */
template <typename T>
struct is_const : false_type {};

template <typename T>
struct is_const<const T> : true_type {};

}  // namespace detail

using detail::is_const;

/**
 * @brief 检查类型是否为 const类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_const_v = is_const<T>::value;
}  // namespace stl