#pragma once
#include "add_const.h"
#include "add_lvalue_reference.h"
#include "is_assignable.h"
#include "remove_reference.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否可拷贝赋值
 * @tparam T 类型
 */
template <typename T>
struct is_copy_assignable
    : is_assignable<
          add_lvalue_reference_t<remove_reference_t<T>>,
          add_const_t<add_lvalue_reference_t<remove_reference_t<T>>>> {};
}  // namespace detail
using detail::is_copy_assignable;

/**
 * @brief 检查类型是否可拷贝赋值
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;

}  // namespace stl