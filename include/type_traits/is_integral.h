#pragma once
#include "integral_constant.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否为整数类型
 * @tparam T 类型
 */
template <typename T>
struct is_integral : false_type {};

template <>
struct is_integral<bool> : true_type {};

template <>
struct is_integral<char> : true_type {};

template <>
struct is_integral<signed char> : true_type {};

template <>
struct is_integral<unsigned char> : true_type {};

template <>
struct is_integral<short> : true_type {};

template <>
struct is_integral<unsigned short> : true_type {};

template <>
struct is_integral<int> : true_type {};

template <>
struct is_integral<unsigned int> : true_type {};

template <>
struct is_integral<long> : true_type {};

template <>
struct is_integral<unsigned long> : true_type {};

template <>
struct is_integral<long long> : true_type {};

template <>
struct is_integral<unsigned long long> : true_type {};

template <>
struct is_integral<wchar_t> : true_type {};

template <>
struct is_integral<char16_t> : true_type {};

template <>
struct is_integral<char32_t> : true_type {};

}  // namespace detail
using detail::is_integral;

/**
 * @brief 检查类型是否为整数类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_integral_v = is_integral<T>::value;
}  // namespace stl