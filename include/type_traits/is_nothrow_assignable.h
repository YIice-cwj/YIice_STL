#pragma once
#include "../utility/declval.h"
#include "integral_constant.h"
#include "is_assignable.h"

namespace stl {
namespace detail {

template <typename T, typename U>
auto check_nothrow_assignable(int)
    -> bool_constant<noexcept(declval<T>() = declval<U>())>;

template <typename...>
false_type check_nothrow_assignable(...);

/**
 * @brief 检查是否可以无异常地赋值
 * @param T 目标类型
 * @param U 源类型
 */
template <typename T, typename U>
struct is_nothrow_assignable
    : bool_constant<is_assignable_v<T, U> &&
                    (decltype(check_nothrow_assignable<T, U>(0))::value)> {};

}  // namespace detail
using detail::is_nothrow_assignable;

/**
 * @brief 检查是否可以无异常地赋值
 * @param T 目标类型
 * @param U 源类型
 */
template <typename T, typename U>
constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<T, U>::value;

}  // namespace stl