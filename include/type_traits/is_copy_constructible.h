#pragma once
#include "add_const.h"
#include "add_lvalue_reference.h"
#include "is_constructible.h"
#include "remove_reference.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否可复制构造
 * @tparam T 类型
 */
template <typename T>
struct is_copy_constructible
    : is_constructible<
          remove_reference_t<T>,
          add_const_t<add_lvalue_reference_t<remove_reference_t<T>>>> {};

}  // namespace detail
using detail::is_copy_constructible;

/**
 * @brief 检查类型是否可复制构造
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;
}  // namespace stl
