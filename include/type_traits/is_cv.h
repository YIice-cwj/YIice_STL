#pragma once
#include "is_const.h"
#include "is_volatile.h"

namespace stl {
namespace detail {

/**
 * @brief  检查类型是否为 cv 类型
 * @tparam T 类型
 */
template <typename T>
struct is_cv : bool_constant<is_const_v<T> && is_volatile_v<T>> {};

}  // namespace detail
using detail::is_cv;

/**
 * @brief  检查类型是否为 cv 类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_cv_v = is_cv<T>::value;

}  // namespace stl