#pragma once
#include "../type_traits/is_iterator.h"
#include "../type_traits/is_trivially_copyable.h"
#include "../utility/min.h"
#include "iterator.h"
#include "iterator_traits.h"

namespace stl {
namespace detail {

template <typename InputIt, typename ForwardIt>
ForwardIt uninitialized_copy(InputIt first,
                             InputIt last,
                             ForwardIt d_first,
                             iterator_tag::input_iterator_tag) {}

template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 uninitialized_copy(ForwardIt1 first,
                              ForwardIt1 last,
                              ForwardIt2 d_first,
                              iterator_tag::forward_iterator_tag) {}

template <typename BidirectionalIt, typename ForwardIt>
BidirectionalIt uninitialized_copy(BidirectionalIt first,
                                   BidirectionalIt last,
                                   ForwardIt d_first,
                                   iterator_tag::bidirectional_iterator_tag) {}

template <typename RandomAccessIt, typename ForwardIt>
RandomAccessIt uninitialized_copy(RandomAccessIt first,
                                  RandomAccessIt last,
                                  ForwardIt d_first,
                                  iterator_tag::random_access_iterator_tag) {}

// 迭代器分发
template <typename Iterator, typename ForwardIt>
ForwardIt uninitialized_copy(Iterator first,
                             Iterator last,
                             ForwardIt d_first,
                             true_type) {
    uninitialized_copy(first, last, d_first, iterator_category_t<iterator>{});
}

// 指针分发
template <typename T>
T* uninitialized_copy(T* first, T* last, T* d_first, true_type) {
    return uninitialized_copy(first, last, d_first,
                              bool_constant<is_trivially_copyable_v<T>>{});
}

}  // namespace detail

/**
 * @brief 在未初始化的内存区域中构造元素
 * @tparam Iterator 迭代器类型
 * @tparam ForwardIt 前向迭代器类型
 * @param first 源序列的开始位置
 * @param last 源序列的结束位置
 * @param d_first 目标序列的开始位置
 */
template <typename Iterator, typename ForwardIt>
ForwardIt uninitialized_copy(Iterator first, Iterator last, ForwardIt d_first) {
    detail::uninitialized_copy(first, last, d_first,
                               bool_constant<is_iterator_v<Iterator>>{});
}

}  // namespace stl