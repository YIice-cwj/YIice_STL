#pragma once

namespace stl {

/**
 * @brief 等于比较函数对象
 * @tparam T 比较类型
 */
template <typename T>
struct equal_to {
    bool operator()(const T& lhs, const T& rhs) const { return lhs == rhs; }
};

}  // namespace stl