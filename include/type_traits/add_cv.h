#pragma once
#include "add_const.h"
#include "add_volatile.h"

namespace stl {
namespace detail {

/**
 * @brief 添加const和volatile修饰符
 * @tparam T 类型
 */
template <typename T>
struct add_cv {
    using type = add_const_t<add_volatile_t<T>>;
};

}  // namespace detail
using detail::add_cv;

/**
 * @brief 添加const和volatile修饰符
 * @tparam T 类型
 */
template <typename T>
using add_cv_t = typename add_cv<T>::type;

}  // namespace stl