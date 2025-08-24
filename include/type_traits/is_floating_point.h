#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为浮点数类型
 * @tparam T 类型
 */
template <typename T>
struct is_floating_point : false_type {};

template <>
struct is_floating_point<float> : true_type {};

template <>
struct is_floating_point<double> : true_type {};

template <>
struct is_floating_point<long double> : true_type {};

}  // namespace detail

using detail::is_floating_point;

/**
 * @brief 检查类型是否为浮点数类型
 * @tparam T 类型
 */
constexpr bool is_floating_point_v = true_type::value;

}  // namespace stl