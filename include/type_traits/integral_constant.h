#pragma once

namespace stl {

/**
 * @brief 整型编译时常量类型, 是type_traits中核心类型之一
 * @tparam T 整型类型
 * @tparam v 整型值
 */
template <typename T, T v>
struct integral_constant {
    static constexpr T value = v;

    using value_type = T;

    using type = integral_constant;

    constexpr operator value_type() const noexcept { return value; }

    constexpr value_type operator()() const noexcept { return value; }
};

/**
 * @brief bool类型编译时常量类型
 * @tparam v bool值
 */
template <bool v>
using bool_constant = integral_constant<bool, v>;

/**
 * @brief bool类型编译时常量特化类型, 值为true
 */
using true_type = integral_constant<bool, true>;

/**
 * @brief bool类型编译时常量特化类型, 值为false
 */
using false_type = integral_constant<bool, false>;

}  // namespace stl