#pragma once

namespace stl {

/**
 * @brief 逻辑与函数对象
 * @tparam T 类型一
 * @tparam U 类型二
 */
template <typename T>
struct logical_and {
    bool operator()(const T& lhs, const T& rhs) const {
        return static_cast<bool>(lhs) && static_cast<bool>(rhs);
    }
};

}