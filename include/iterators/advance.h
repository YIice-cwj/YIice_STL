#pragma once
#include "iterator_traits.h"

namespace stl {
namespace detail {

template <typename Iterator>
void advance(Iterator& it,
             iterator_difference_type_t<Iterator> n,
             iterator_tag::random_access_iterator_tag) {
    it += n;
}

template <typename Iterator>
void advance(Iterator& it,
             iterator_difference_type_t<Iterator> n,
             iterator_tag::bidirectional_iterator_tag) {
    if (n > 0) {
        while (n--) {
            ++it;
        }
    } else {
        while (n++) {
            --it;
        }
    }
}

template <typename Iterator>
void advance(Iterator& it,
             iterator_difference_type_t<Iterator> n,
             iterator_tag::input_iterator_tag) {
    while (n--) {
        ++it;
    }
}

}  // namespace detail

/**
 * @brief 将迭代器向前移动指定的距离
 * @tparam Iterator 迭代器类型
 * @param it 迭代器
 * @param n 移动的距离(默认为: 1)
 */
template <typename Iterator>
void advance(Iterator& it, iterator_difference_type_t<Iterator> n = 1) {
    detail::advance(it, n, iterator_category_t<Iterator>{});
}

}  // namespace stl