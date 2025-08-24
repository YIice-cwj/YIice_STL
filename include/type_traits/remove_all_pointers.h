#pragma once

namespace stl {
namespace detail {

/**
 * @brief 移除所有维度的指针
 * @tparam T 类型
 */
template <typename T>
struct remove_all_pointers {
    using type = T;
};

template <typename T>
struct remove_all_pointers<T*> {
    using type = typename remove_all_pointers<T>::type;
};

template <typename T, std::size_t N>
struct remove_all_pointers<T (*)[N]> {
    using type = typename remove_all_pointers<T>::type[N];
};

template <typename T>
struct remove_all_pointers<T (*)[]> {
    using type = typename remove_all_pointers<T>::type[];
};
}  // namespace detail

using detail::remove_all_pointers;

/**
 * @brief 移除所有维度的指针
 * @tparam T 类型
 */
template <typename T>
using remove_all_pointers_t = typename detail::remove_all_pointers<T>::type;
}  // namespace stl