#pragma once

namespace stl {

/**
 * @brief 大于等于比较函数对象
 * @tparam T 比较类型
 */
template <typename T>
struct greater_equal {
    bool operator()(const T& lhs, const T& rhs) const { return lhs >= rhs; }
};

}  // namespace stl