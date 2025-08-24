#pragma once
#include "remove_const.h"
#include "remove_volatile.h"

namespace stl {
namespace detail {

/**
 * @brief 移除 const 和 volatile 修饰符
 * @tparam T 类型
 */
template <typename T>
struct remove_cv {
    using type = remove_const_t<remove_volatile_t<T>>;
};
}  // namespace detail

using detail::remove_cv;

/**
 * @brief 移除 const 和 volatile 修饰符
 * @tparam T 类型
 */
template <typename T>
using remove_cv_t = typename detail::remove_cv<T>::type;

}  // namespace stl