#pragma once
#include "../utility/declval.h"
#include "../utility/swap.h"
#include "integral_constant.h"

namespace stl {

namespace detail {

template <typename T>
auto check_swappable(int)
    -> decltype(stl::swap(declval<T&>(), declval<T&>()), true_type{});

template <typename T>
auto check_swappable(...) -> false_type;

/**
 * @brief 检查类型是否可交换
 * @tparam T 类型
 */
template <typename T>
struct is_swappable
    : bool_constant<decltype(detail::check_swappable<T>(0))::value> {};

}  // namespace detail
using detail::is_swappable;

/**
 * @brief 检查类型是否可交换
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_swappable_v = is_swappable<T>::value;
}  // namespace stl
