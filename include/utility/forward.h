#pragma once
#include "../type_traits/add_lvalue_reference.h"
#include "../type_traits/add_rvalue_reference.h"
#include "../type_traits/is_lvalue_reference.h"
#include "../type_traits/remove_reference.h"

namespace stl {

/**
 * @brief 完美转发
 * @param T 类型
 * @param t 参数
 */
template <typename T>
constexpr add_rvalue_reference_t<T> forward(remove_reference_t<T>& t) noexcept {
    // add_rvalue_reference_t<T>
    // 折叠表达式如果是引用类型，会自动折叠为左值引用(&& + & = &)
    return static_cast<add_rvalue_reference_t<T>>(t);
}

/**
 * @brief 完美转发
 * @param T 类型
 * @param t 参数
 */
template <typename T>
constexpr add_rvalue_reference_t<remove_reference_t<T>> forward(
    remove_reference_t<T>&& t) noexcept {
    return static_cast<add_rvalue_reference_t<remove_reference_t<T>>>(t);
}

}  // namespace stl