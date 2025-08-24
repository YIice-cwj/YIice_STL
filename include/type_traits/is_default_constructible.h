#pragma once
#include "is_constructible.h"

namespace stl {
namespace detail {

/**
 * @brief 检查类型是否可以默认构造
 * @tparam T 类型
 */
template <typename T>
struct is_default_constructible : is_constructible<T> {};

}  // namespace detail
using detail::is_default_constructible;

/**
 * @brief 检查类型是否可以默认构造
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_default_constructible_v = is_default_constructible<T>::value;
}  // namespace stl
