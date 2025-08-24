#pragma once
namespace stl {

/**
 * @brief 逻辑非函数对象
 * @tparam T 类型
 */
template <typename T>
struct logical_not {
    bool operator()(const T& x) const { return !x; }
};

}  // namespace stl