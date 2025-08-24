#pragma once
#include "const_iterator.h"
#include "iterator_traits.h"

namespace stl {

namespace detail {

template <typename Iterator>
iterator_difference_type_t<Iterator> distance(
    Iterator first,
    Iterator last,
    iterator_tag::random_access_iterator_tag) {
    return last - first;
}

template <typename Iterator>
iterator_difference_type_t<Iterator>
distance(Iterator first, Iterator last, iterator_tag::input_iterator_tag) {
    iterator_difference_type_t<Iterator> n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

}  // namespace detail

/**
 * @brief 计算两个迭代器之间的距离
 * @tparam Iterator 迭代器类型
 * @param first 起始迭代器
 * @param last 结束迭代器
 * @return 两个迭代器之间的距离
 */
template <typename Iterator>
iterator_difference_type_t<Iterator> distance(Iterator first, Iterator last) {
    return detail::distance(first, last, iterator_category_t<Iterator>{});
}

}  // namespace stl