#pragma once

namespace stl {
namespace detail {

/**
 * @brief 添加volatile修饰符
 * @tparam T 类型
 */
template <typename T>
struct add_volatile {
    using type = volatile T;
};

template <typename T>
struct add_volatile<volatile T> {
    using type = volatile T;
};

// 引用类型不能添加volatile修饰符
template <typename T>
struct add_volatile<T&> {
    using type = T&;
};

template <typename T>
struct add_volatile<T&&> {
    using type = T&&;
};

// 数组类型不能添加volatile修饰符
template <typename T, size_t N>
struct add_volatile<T[N]> {
    using type = T[N];
};

template <typename T>
struct add_volatile<T[]> {
    using type = T[];
};

// void类型不能添加volatile修饰符
template <>
struct add_volatile<void> {
    using type = void;
};

// 函数类型不能添加volatile修饰符
template <typename F, typename... Args>
struct add_volatile<F(Args...)> {
    using type = F(Args...);
};

}  // namespace detail

using detail::add_volatile;

/**
 * @brief 添加volatile修饰符
 * @tparam T 类型
 */
template <typename T>
using add_volatile_t = typename add_volatile<T>::type;
}  // namespace stl