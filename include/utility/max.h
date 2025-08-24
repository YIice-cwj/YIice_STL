#pragma once

namespace stl {

/**
 * @brief 返回两个值中的最大值
 * @tparam T 类型
 * @param a 第一个值
 * @param b 第二个值
 * @return 两个值中的最大值
 */
template <typename T>
constexpr const T& max(const T& a, const T& b) noexcept {
    return (a > b) ? a : b;
}

}  // namespace stl