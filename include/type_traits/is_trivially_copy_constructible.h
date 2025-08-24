#pragma once
#include "is_copy_constructible.h"
#include "is_trivial.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为平凡拷贝构造
 * @tparam T 类型
 */
template <typename T>
struct is_trivially_copy_constructible
    : bool_constant<is_trivial_v<T> && is_copy_constructible_v<T>> {};

}  // namespace detail

using detail::is_trivially_copy_constructible;

/**
 * @brief 检查类型是否为平凡拷贝构造
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_trivially_copy_constructible_v =
    is_trivially_copy_constructible<T>::value;

}  // namespace stl
