#pragma once
#include "is_nothrow_constructible.h"
#include "remove_reference.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否可以无异常地可移动构造
 * @tparam T 类型
 */
template <typename T>
struct is_nothrow_move_constructible
    : is_nothrow_constructible<remove_reference_t<T>,
                               add_rvalue_reference_t<remove_reference_t<T>>> {
};
}  // namespace detail
using detail::is_nothrow_move_constructible;

/**
 * @brief 检查类型是否是无异常地可移动构造
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_nothrow_move_constructible_v =
    is_nothrow_move_constructible<T>::value;
}  // namespace stl