#pragma once
#include "../utility/declval.h"
#include "integral_constant.h"

namespace stl {
namespace detail {

template <typename T, typename... Args>
auto check_constructible(int) -> decltype(T(declval<Args>()...), true_type{});

template <typename...>
false_type check_constructible(...);

/**
 * @brief 检查类型是否可构造
 * @param T 类型
 * @param Args 构造参数类型
 */
template <typename T, typename... Args>
struct is_constructible
    : bool_constant<decltype(check_constructible<T, Args...>(0))::value> {};

}  // namespace detail
using detail::is_constructible;

/**
 * @brief 检查类型是否可构造
 * @param T 类型
 * @param Args 构造参数类型
 */
template <typename T, typename... Args>
constexpr bool is_constructible_v = detail::is_constructible<T, Args...>::value;
}  // namespace stl