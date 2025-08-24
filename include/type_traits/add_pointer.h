#pragma once

#include <cstddef>

namespace stl {
namespace detail {

/**
 * @brief 添加指针类型
 * @tparam T 类型
 */
template <typename T>
struct add_pointer {
    using type = T*;
};

template <typename T>
struct add_pointer<T*> {
    using type = T*;
};

template <typename T>
struct add_pointer<T&> {
    using type = T*;
};

template <typename T>
struct add_pointer<T&&> {
    using type = T*;
};

// 函数类型添加指针类型
template <typename F, typename... Args>
struct add_pointer<F(Args...)> {
    using type = F (*)(Args...);
};

// 数组类型添加指针类型
template <typename T>
struct add_pointer<T[]> {
    using type = T (*)[];
};

template <typename T, std::size_t N>
struct add_pointer<T[N]> {
    using type = T (*)[N];
};

template <>
struct add_pointer<void> {
    using type = void*;
};

template <>
struct add_pointer<const void> {
    using type = void*;
};

template <>
struct add_pointer<const volatile void> {
    using type = void*;
};

}  // namespace detail

using detail::add_pointer;

/**
 * @brief 添加指针类型
 * @tparam T 类型
 */
template <typename T>
using add_pointer_t = typename add_pointer<T>::type;

}  // namespace stl