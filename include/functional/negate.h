#pragma once

namespace stl {

/**
 * @brief 取反函数对象
 * @tparam T 类型
 */
template <typename T>
struct negate {
    T operator()(T x) const { return -x; }
};

}  // namespace stl