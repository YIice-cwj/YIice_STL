#pragma once

namespace stl {
namespace detail {

/**
 * @brief 所有类型都可以转换为void类型
 * @tparam Ts 可变参数模板
 */
template <typename... Ts>
using void_t = void;

}  // namespace detail
using detail::void_t;
}  // namespace stl