#pragma once
#include "is_move_assignable.h"
#include "is_move_constructible.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否可移动
 * @tparam T 类型
 */
template <typename T>
struct is_movable
    : bool_constant<is_move_constructible_v<T> && is_move_assignable_v<T>> {};

}  // namespace detail
using detail::is_movable;

/**
 * @brief 检查类型是否可移动
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_movable_v = is_movable<T>::value;
}  // namespace stl