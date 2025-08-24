#pragma once
#include "is_movable.h"
#include "is_trivial.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为平凡可移动
 * @tparam T 类型
 */
template <typename T>
struct is_trivially_movable
    : bool_constant<is_trivial_v<T> && is_movable_v<T>> {};

}  // namespace detail
using detail::is_trivially_movable;

/**
 * @brief 检查类型是否为平凡可移动
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_trivially_movable_v = is_trivially_movable<T>::value;

}  // namespace stl