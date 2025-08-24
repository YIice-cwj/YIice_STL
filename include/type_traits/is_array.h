#pragma once
#include <cstddef>
#include "integral_constant.h"

namespace stl {

template <typename T, size_t N>
class array;

namespace detail {
/**
 * @brief 检查类型是否是数组类型
 * @tparam T 类型
 */
template <typename T>
struct is_array : false_type {};

template <typename T>
struct is_array<T[]> : true_type {};

template <typename T, size_t N>
struct is_array<T[N]> : true_type {};

template <typename T, size_t N>
struct is_array<array<T, N>> : true_type {};

}  // namespace detail
using detail::is_array;

/**
 * @brief 检查类型是否是数组类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_array_v = is_array<T>::value;
}  // namespace stl