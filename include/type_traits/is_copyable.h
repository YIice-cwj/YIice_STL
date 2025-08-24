#pragma once
#include "integral_constant.h"
#include "is_copy_assignable.h"
#include "is_copy_constructible.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否可拷贝
 * @tparam T 类型
 */
template <typename T>
struct is_copyable
    : bool_constant<is_copy_constructible_v<T> && is_copy_assignable_v<T>> {};

}  // namespace detail
using detail::is_copyable;

/**
 * @brief 检查类型是否可拷贝
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_copyable_v = is_copyable<T>::value;
}  // namespace stl