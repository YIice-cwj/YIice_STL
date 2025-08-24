#pragma once

namespace stl {

/**
 * @brief 加法函数对象
 * @tparam T 类型
 */
template <typename T>
struct plus {
    T operator()(T a, T b) const { return a + b; }
};

}  // namespace stl