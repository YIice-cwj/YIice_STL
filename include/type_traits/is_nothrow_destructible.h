#pragma once
#include "is_destructible.h"

namespace stl {
namespace detail {

template <typename T>
auto check_nothrow_destructible(int)
    -> bool_constant<noexcept(declval<T>().~T())> {}

template <typename...>
false_type check_nothrow_destructible(...);

/**
 * @brief 检查类型是否可以无异常地析构
 * @tparam T 类型
 */
template <typename T>
struct is_nothrow_destructible
    : bool_constant<is_destructible_v<T> &&
                    (decltype(check_nothrow_destructible<T>(0))::value)> {};
}  // namespace detail
using detail::is_nothrow_destructible;

/**
 * @brief 检查类型是否可以无异常地析构
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<T>::value;

}  // namespace stl