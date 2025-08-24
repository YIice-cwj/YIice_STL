#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为成员函数指针
 * @tparam T 类型
 */
template <typename T>
struct is_member_function_pointer : false_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...)> : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) const> : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) volatile> : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) const volatile>
    : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) &> : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) const&> : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) volatile&> : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) const volatile&>
    : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) &&> : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) const&&> : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) volatile&&> : true_type {};

template <typename T, typename R, typename... Args>
struct is_member_function_pointer<R (T::*)(Args...) const volatile&&>
    : true_type {};

}  // namespace detail

using detail::is_member_function_pointer;

/**
 * @brief 检查类型是否为成员函数
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_member_function_pointer_v =
    detail::is_member_function_pointer<T>::value;
}  // namespace stl