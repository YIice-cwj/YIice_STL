#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 判断是否为函数类型
 * @tparam T 类型
 */
template <typename T>
struct is_function : false_type {};

template <typename R, typename... Args>
struct is_function<R(Args...)> : true_type {};

template <typename R, typename... Args>
struct is_function<R(Args......)> : true_type {};

template <typename R, typename... Args>
struct is_function<R(Args...) const> : true_type {};

template <typename R, typename... Args>
struct is_function<R(Args......) const> : true_type {};

template <typename R, typename... Args>
struct is_function<R(Args...) volatile> : true_type {};

template <typename R, typename... Args>
struct is_function<R(Args......) volatile> : true_type {};

template <typename R, typename... Args>
struct is_function<R(Args...) const volatile> : true_type {};

}  // namespace detail

using detail::is_function;

/**
 * @brief 判断是否为函数类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_function_v = is_function<T>::value;
}  // namespace stl