#pragma once
#include "enable_if.h"
#include "is_member_function_pointer.h"
#include "is_member_pointer.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为成员对象指针
 * @tparam T 类型
 */
template <typename T, typename = void>
struct is_member_object_pointer : false_type {};

template <typename T>
struct is_member_object_pointer<
    T,
    enable_if_t<!is_member_function_pointer_v<T> && is_member_pointer_v<T>>>
    : true_type {};

}  // namespace detail
using detail::is_member_object_pointer;

/**
 * @brief 检查类型是否为成员对象指针
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;
}  // namespace stl