#pragma once
#include <cstddef>

namespace stl {
namespace detail {

/**
 * @brief 移除一维数组的维度
 * @tparam T 类型
 */
template <typename T>
struct remove_extent {
    using type = T;
};

template <typename T>
struct remove_extent<T[]> {
    using type = T;
};

template <typename T, std::size_t N>
struct remove_extent<T[N]> {
    using type = T;
};

}  // namespace detail

using detail::remove_extent;

/**
 * @brief 移除一维数组的维度
 * @tparam T 类型
 */
template <typename T>
using remove_extent_t = typename remove_extent<T>::type;

}  // namespace stl