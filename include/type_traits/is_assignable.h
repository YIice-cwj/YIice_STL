#pragma once
#include "../utility/declval.h"
#include "integral_constant.h"

namespace stl {
namespace detail {

template <typename T, typename U>
auto check_assignable(int)
    -> decltype(declval<T>() = declval<U>(), true_type{});

template <typename...>
false_type check_assignable(...);

/**
 * @brief 检查类型T是否可以从类型U赋值
 * @tparam T 目标类型（通常是引用类型）
 * @tparam U 源类型
 */
template <typename T, typename U>
struct is_assignable
    : bool_constant<decltype(check_assignable<T, U>(0))::value> {};

}  // namespace detail
using detail::is_assignable;

/**
 * @brief 检查类型T是否可以从类型U赋值
 * @tparam T 目标类型（通常是引用类型）
 * @tparam U 源类型
 */
template <typename T, typename U>
constexpr bool is_assignable_v = is_assignable<T, U>::value;
}  // namespace stl