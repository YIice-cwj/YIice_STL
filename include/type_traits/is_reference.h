#pragma once
#include "is_lvalue_reference.h"
#include "is_rvalue_reference.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为引用类型
 * @param T 类型
 */
template <typename T>
struct is_reference
    : bool_constant<is_lvalue_reference_v<T> || is_rvalue_reference_v<T>> {};

}  // namespace detail
using detail::is_reference;

/**
 * @brief 检查类型是否为引用类型
 * @param T 类型
 */
template <typename T>
constexpr bool is_reference_v = is_reference<T>::value;
}  // namespace stl