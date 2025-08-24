#pragma once
#include "is_assignable.h"
#include "is_trivial.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为平凡可赋值
 * @tparam T 类型
 */
template <typename T>
struct is_trivially_assignable
    : bool_constant<is_trivial_v<T> && is_assignable_v<T>> {};
}  // namespace detail

using detail::is_trivially_assignable;

/**
 * @brief 检查类型是否为平凡可赋值
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_trivially_assignable_v = is_trivially_assignable<T>::value;

}  // namespace stl