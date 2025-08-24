#pragma once
#include "integral_constant.h"

namespace stl {

namespace detail {

/**
 * @brief 检查类型是否为类
 * @tparam T 类型
 */
template <typename T>

struct is_class : bool_constant<__is_class(T)> {
};  // __is_class 是编译器内置的宏，用于检查类型是否为类

}  // namespace detail
using detail::is_class;

/**
 * @brief 检查类型是否为类
 * @tparam T 类型
 */
template <typename T>
constexpr bool is_class_v = is_class<T>::value;
}  // namespace stl