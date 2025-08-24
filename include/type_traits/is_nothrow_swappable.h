#pragma once
#include "is_swappable.h"

namespace stl {
namespace detail {

template <typename T>
auto check_nothrow_swappable(int)
    -> bool_constant<noexcept(stl::swap(declval<T&>(), declval<T&>()))>;

template <typename...>
false_type check_nothrow_swappable(...);

/**
 * @brief 类型是否可以无异常交换的
 * @tparam T 类型
 */
template <typename T>
struct is_nothrow_swappable
    : bool_constant<is_swappable_v<T> &&
                    (decltype(check_nothrow_swappable<T>(0))::value)> {};
}  // namespace detail
using detail::is_nothrow_swappable;

/**
 * @brief 类型是否可以无异常交换的
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;
}  // namespace stl