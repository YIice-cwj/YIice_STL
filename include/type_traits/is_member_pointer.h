#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为成员指针
 * @tparam T 类型
 */
template <typename T>
struct is_member_pointer : false_type {};

template <typename T, typename C>
struct is_member_pointer<T C::*> : true_type {};

}  // namespace detail
using detail::is_member_pointer;

/**
 * @brief 检查类型是否为成员指针
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_member_pointer_v = is_member_pointer<T>::value;
}  // namespace stl