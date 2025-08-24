#pragma once
#include "../utility/declval.h"
#include "integral_constant.h"

namespace stl {
namespace detail {

template <typename T>
auto check_destructible(int) -> decltype(declval<T>().~T(), true_type{});

template <typename...>
false_type check_destructible(...);

/**
 * @brief 检查类型是否可析构
 * @tparam T 类型
 */
template <typename T>
struct is_destructible
    : bool_constant<decltype(check_destructible<T>(0))::value> {};

}  // namespace detail
using detail::is_destructible;

/**
 * @brief 检查类型是否可析构
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_destructible_v = is_destructible<T>::value;
}  // namespace stl