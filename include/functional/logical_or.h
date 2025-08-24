#pragma once

namespace stl {

/**
 * @brief 逻辑或函数对象
 * @param T 类型一
 * @param U 类型二
 */
template <typename T, typename U>
struct logical_or {
    bool operator()(T const& t, U const& u) const {
        return static_cast<bool>(t) || static_cast<bool>(u);
    }
};

}  // namespace stl