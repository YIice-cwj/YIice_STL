#pragma once

namespace stl {

/**
 * @brief 取模函数对象
 * @tparam T 类型
 */
template <typename T>
struct modulus {
    T operator()(T a, T b) { return a % b; }
};

}  // namespace stl