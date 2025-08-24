#pragma once

namespace stl {
namespace detail {

/**
 * @brief 移除一维指针
 * @tparam T 类型
 */
template <typename T>
struct remove_pointer {
    using type = T;
};

template <typename T>
struct remove_pointer<T*> {
    using type = T;
};

template <typename T, std::size_t N>
struct remove_pointer<T (*)[N]> {
    using type = T[N];
};

template <typename T>
struct remove_pointer<T (*)[]> {
    using type = T[];
};

}  // namespace detail

using detail::remove_pointer;

/**
 * @brief 移除一维指针
 * @tparam T 类型
 */
template <typename T>
using remove_pointer_t = typename detail::remove_pointer<T>::type;

}  // namespace stl