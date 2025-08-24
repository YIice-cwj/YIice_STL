#pragma once

namespace stl {

namespace detail {

/**
 * @brief 添加const修饰符
 * @tparam T 类型
 */
template <typename T>
struct add_const {
    using type = const T;
};

template <typename T>
struct add_const<const T> {
    using type = const T;
};

// 数组类型可以添加const修饰符
template <typename T, std::size_t N>
struct add_const<T[N]> {
    using type = T[N];
};

template <typename T>
struct add_const<T[]> {
    using type = T[];
};

// 引用不能添加const修饰符
template <typename T>
struct add_const<T&> {
    using type = T&;
};

template <typename T>
struct add_const<T&&> {
    using type = T&&;
};

// void类型不能添加const修饰符
template <>
struct add_const<void> {
    using type = void;
};

// 函数类型不能添加const修饰符
template <typename F, typename... Args>
struct add_const<F(Args...)> {
    using type = F(Args...);
};

}  // namespace detail

using detail::add_const;

/**
 * @brief 添加const修饰符
 * @tparam T 类型
 */
template <typename T>
using add_const_t = typename add_const<T>::type;

}  // namespace stl