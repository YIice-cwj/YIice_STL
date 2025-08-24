#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为有符号类型
 * @tparam T 类型
 */
template <typename T>
struct is_signed : false_type {};

template <>
struct is_signed<char> : bool_constant<(char(-1) > 0)> {};

template <>
struct is_signed<wchar_t> : bool_constant<(wchar_t(-1) > 0)> {};

template <>
struct is_signed<signed char> : true_type {};

template <>
struct is_signed<short> : true_type {};

template <>
struct is_signed<int> : true_type {};

template <>
struct is_signed<long> : true_type {};

template <>
struct is_signed<long long> : true_type {};

template <>
struct is_signed<float> : true_type {};

template <>
struct is_signed<double> : true_type {};

template <>
struct is_signed<long double> : true_type {};

}  // namespace detail
using detail::is_signed;

/**
 * @brief 检查类型是否为有符号类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_signed_v = is_signed<T>::value;
}  // namespace stl