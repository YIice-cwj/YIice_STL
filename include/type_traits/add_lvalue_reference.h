#pragma once

namespace stl {
namespace detail {

/**
 * @brief 添加左值引用
 * @tparam T 类型
 */
template <typename T>
struct add_lvalue_reference {
    using type = T&;
};

template <typename T>
struct add_lvalue_reference<T&> {
    using type = T&;
};

// 保留move语义
template <typename T>
struct add_lvalue_reference<T&&> {
    using type = T&;
};

template <>
struct add_lvalue_reference<void> {
    using type = void;
};

template <>
struct add_lvalue_reference<const void> {
    using type = const void;
};

template <>
struct add_lvalue_reference<volatile void> {
    using type = volatile void;
};

template <>
struct add_lvalue_reference<const volatile void> {
    using type = const volatile void;
};

template <typename T, std::size_t N>
struct add_lvalue_reference<T[N]> {
    using type = T[N];
};

template <typename T>
struct add_lvalue_reference<T[]> {
    using type = T[];
};

}  // namespace detail
using detail::add_lvalue_reference;

/**
 * @brief 添加左值引用
 * @tparam T 类型
 */
template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
}  // namespace stl