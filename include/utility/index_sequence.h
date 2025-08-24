#pragma once

namespace stl {

/**
 * @brief 生成索引序列
 */
template <size_t... Ns>
struct index_sequence {
    static constexpr size_t size() { return sizeof...(Ns); }
};

/**
 * @brief 生成索引序列
 * @tparam N 序列长度
 *
 * @note 递归生成索引序列
 *
 * make_index_sequence<4>
 * ├── type = make_index_sequence<4-1, 4-1>::type
 * ├── type = make_index_sequence<3, 3>::type
 *     ├── type = make_index_sequence<3-1, 3-1, 3>::type
 *     ├── type = make_index_sequence<2, 2, 3>::type
 *         ├── type = make_index_sequence<2-1, 2-1, 2, 3>::type
 *         ├── type = make_index_sequence<1, 1, 2, 3>::type
 *             ├── type = make_index_sequence<1-1, 1-1, 1, 2, 3>::type
 *             ├── type = make_index_sequence<0, 0, 1, 2, 3>::type
 *                 └── 匹配特化版本: index_sequence<0, 1, 2, 3>
 *
 */

template <size_t N, size_t... Ints>
struct make_index_sequence {
    using type = typename make_index_sequence<N - 1, N - 1, Ints...>::type;
};

template <size_t... Ints>
struct make_index_sequence<0, Ints...> {
    // index_sequence<0, 1, 2, 3>
    using type = index_sequence<Ints...>;
};

/**
 * @brief 获取索引序列类型
 */
template <size_t N>
using make_index_sequence_t = typename make_index_sequence<N>::type;

/**
 * @brief 生成索引序列类型
 */
template <typename... T>
using index_sequence_for = make_index_sequence_t<sizeof...(T)>;

}  // namespace stl