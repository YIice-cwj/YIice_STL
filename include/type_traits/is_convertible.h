#pragma once
#include "../utility/declval.h"
#include "integral_constant.h"

namespace stl {
namespace detail {

// 辅助函数，用于将一个类型转换为另一个类型
template <typename T>
T to_type(T);

/**
 * @brief 辅助函数，用于检查类型是否可以从一个类型转换为另一个类型,
 * 如果可以转换，则decltype推导为 true_type，否则触发SFINAE(替换失败不是错误),
 * 调用check_convertible(...) decltype推导为false_type
 */
template <typename From, typename To>
auto check_convertible(int)
    /**
     * declval<From>()
     * 表示创建一个From类型的临时对象(未求值语句)并不会实际创建对象
     *
     * to_type<To>(declval<From>()) 表示将From类型的值转换为To类型
     * 如 to_type<int>(declval<double>()) 将double类型的值转换为int类型
     */
    -> decltype(to_type<To>(declval<From>()), true_type{});

template <typename...>
false_type check_convertible(...);

/**
 * @brief 检查类型是否可以从一个类型转换为另一个类型
 * @tparam From 源类型
 * @tparam To 目标类型
 */
template <typename From, typename To>
struct is_convertible
    : bool_constant<decltype(check_convertible<From, To>(0))::value> {};

// Form -> void 可以转换
template <typename Form>
struct is_convertible<Form, void> : true_type {};

// void -> To 不可以转换
template <typename To>
struct is_convertible<void, To> : false_type {};

// void -> void（最具体的特化，优先级最高）
template <>
struct is_convertible<void, void> : true_type {};

}  // namespace detail
using detail::is_convertible;

/**
 * @brief 检查类型是否可以从一个类型转换为另一个类型
 * @tparam From 源类型
 * @tparam To 目标类型
 */
template <typename From, typename To>
constexpr bool is_convertible_v = is_convertible<From, To>::value;
}  // namespace stl