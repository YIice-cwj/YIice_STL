#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查 T 类型 和 U 类型是否相同
 * @tparam T 类型1
 * @tparam U 类型2
 */
template <typename T, typename U>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : true_type {};

}  // namespace detail

using detail::is_same;

/**
 * @brief 检查 T 类型 和 U 类型是否相同
 * @tparam T 类型1
 * @tparam U 类型2
 */
template <typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

}  // namespace stl