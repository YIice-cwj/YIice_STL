#pragma once
#include "../type_traits/add_rvalue_reference.h"

namespace stl {

/**
 * @brief 未求值语义(用于在编译时生成一个给定类型的右值引用)
 * @tparam T 类型
 */
template <typename T>
constexpr add_rvalue_reference_t<T> declval() noexcept;

}