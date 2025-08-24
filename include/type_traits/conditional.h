#pragma once

namespace stl {
namespace detail {

/**
 * @brief 条件类型选择, 根据 B 的值选择 T 或 F
 * @tparam B 条件
 * @tparam T 当 B 为 true 时选择的类型
 * @tparam F 当 B 为 false 时选择的类型
 */
template <bool B, typename T, typename F>
struct conditional {
    using type = T;
};

template <typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

}  // namespace detail

using detail::conditional;

/**
 * @brief 条件类型选择, 根据 B 的值选择 T 或 F
 * @tparam B 条件
 * @tparam T 当 B 为 true 时选择的类型
 * @tparam F 当 B 为 false 时选择的类型
 */
template <bool B, typename T, typename F>
using conditional_t = typename detail::conditional<B, T, F>::type;
}  // namespace stl