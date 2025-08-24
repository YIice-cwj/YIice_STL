#pragma once

namespace stl {

/**
 * @brief 乘法函数对象
 * @tparam T 类型
 */
template <typename T>
struct multiplies {
    T operator()(T a, T b) const { return a * b; }
};

}  // namespace stl