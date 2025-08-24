#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为平凡类型
 * @tparam T 类型
 */
template <typename T>
struct is_trivial : bool_constant<__is_trivial(T)> {};  // 编译器内置

}  // namespace detail
using detail::is_trivial;

/**
 * @brief 检查类型是否为平凡类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_trivial_v = is_trivial<T>::value;

}  // namespace stl