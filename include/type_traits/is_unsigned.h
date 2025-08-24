#pragma once
#include "integral_constant.h"

namespace stl {

namespace detail {

/**
 * @brief 检查类型是否是无符号类型
 * @tparam T 类型
 */
template <typename T>
struct is_unsigned : false_type {};

template <>
struct is_unsigned<bool> : true_type {};

template <>
struct is_unsigned<unsigned char> : true_type {};

template <>
struct is_unsigned<unsigned short> : true_type {};

template <>
struct is_unsigned<unsigned int> : true_type {};

template <>
struct is_unsigned<unsigned long> : true_type {};

template <>
struct is_unsigned<unsigned long long> : true_type {};

template <>
struct is_unsigned<char> : bool_constant<(char(-1) > 0)> {};

template <>
struct is_unsigned<wchar_t> : bool_constant<(wchar_t(-1) > 0)> {};

template <>
struct is_unsigned<char16_t> : true_type {};

template <>
struct is_unsigned<char32_t> : true_type {};

}  // namespace detail
using detail::is_unsigned;

/**
 * @brief 检查类型是否是无符号类型
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_unsigned_v = is_unsigned<T>::value;

}  // namespace stl