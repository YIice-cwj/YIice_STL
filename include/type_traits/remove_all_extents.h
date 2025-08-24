#pragma once
#include <cstddef>

namespace stl {
namespace detail {

/**
 * @brief 移除所有数组维度
 * @tparam T 类型
 */
template <typename T>
struct remove_all_extents {
    using type = T;
};

template <typename T>
struct remove_all_extents<T[]> {
    using type = typename remove_all_extents<T>::type;
};

template <typename T, std::size_t N>
struct remove_all_extents<T[N]> {
    using type = typename remove_all_extents<T>::type;
};

}  // namespace detail

using detail::remove_all_extents;

/**
 * @brief 移除所有数组维度
 * @tparam T 类型
 */
template <typename T>
using remove_all_extents_t = typename detail::remove_all_extents<T>::type;

}  // namespace stl