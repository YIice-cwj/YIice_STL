#pragma once
#include "is_move_assignable.h"
#include "is_trivial.h"

namespace stl {
namespace detail {
template <typename T>
struct is_trivially_move_assignable
    : bool_constant<is_trivial_v<T> && is_move_assignable_v<T>> {};
}  // namespace detail

using detail::is_trivially_move_assignable;

/**
 * @brief 检查类型是否为平凡移动赋值
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_trivially_move_assignable_v =
    is_trivially_move_assignable<T>::value;

}  // namespace stl