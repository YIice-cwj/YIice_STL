#pragma once
#include "../type_traits/add_rvalue_reference.h"
#include "../type_traits/remove_reference.h"
namespace stl {

/**
 * @brief 移动语义
 * @tparam T 类型
 */
template <typename T>
constexpr add_rvalue_reference_t<remove_reference_t<T>> move(T&& t) noexcept {
    return static_cast<remove_reference_t<T>&&>(t);
}

}  // namespace stl