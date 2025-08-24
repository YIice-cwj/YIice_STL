#pragma once

namespace stl {

/**
 * @brief 大于比较函数对象
 * @tparam T 比较类型
 */
template <typename T>
struct greater {
    bool operator()(const T& lhs, const T& rhs) const { return lhs > rhs; }
};

}  // namespace stl