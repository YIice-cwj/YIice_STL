#pragma once
#include "is_copyable.h"
#include "is_trivial.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为平凡可拷贝
 * @tparam T 类型
 */
template <typename T>
struct is_trivially_copyable
    : bool_constant<is_trivial_v<T> && is_copyable_v<T>> {};

}  // namespace detail
using detail::is_trivially_copyable;

/**
 * @brief 检查类型是否为平凡可拷贝
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;

}  // namespace stl