#pragma once

namespace stl {

/**
 * @brief 不等于函数对象
 * @tparam T 比较类型
 */
template <typename T>
struct not_equal_to {
    bool operator()(const T& lhs, const T& rhs) const { return lhs != rhs; }
};

}  // namespace stl