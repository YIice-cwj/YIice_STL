#pragma once
#include "is_constructible.h"

namespace stl {
namespace detail {

template <typename T, typename... Args>
auto check_nothrow_constructible(int)
    -> bool_constant<noexcept(T(declval<Args>()...))> {}

template <typename...>
false_type check_nothrow_constructible(...);

/**
 * @brief 检查类型是否可以无异常地构造
 * @tparam T 类型
 */
template <typename T, typename... Args>
struct is_nothrow_constructible
    : bool_constant<is_constructible_v<T, Args...> &&
                    (decltype(check_nothrow_constructible<T, Args...>(
                        0))::value)> {};

}  // namespace detail
using detail::is_nothrow_constructible;

/**
 * @brief 检查类型是否可以无异常地构造
 * @tparam T 类型
 */
template <typename T, typename... Args>
constexpr bool is_nothrow_constructible_v =
    is_nothrow_constructible<T, Args...>::value;
}  // namespace stl