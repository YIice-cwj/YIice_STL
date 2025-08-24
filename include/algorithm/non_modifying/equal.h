#pragma once
#include "../../functional/equal_to.h"
#include "iterator_traits.h"

namespace stl {

namespace detail {

template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
constexpr bool equal(Iterator1 first1,
                     Iterator1 last1,
                     Iterator2 first2,
                     BinaryPredicate pred) {
    for (; first1 != last1; ++first1, ++first2) {
        if (!pred(*first1, *first2))
            return false;
    }
    return true;
}

template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
constexpr bool equal(Iterator1 first1,
                     Iterator1 last1,
                     Iterator2 first2,
                     Iterator2 last2,
                     BinaryPredicate pred) {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (!pred(*first1, *first2))
            return false;
    }
    return (first1 == last1 && first2 == last2);
}

}  // namespace detail

/**
 * @brief 使用给定的二元谓词比较两个范围的元素是否相等
 * @tparam Iterator1 迭代器类型
 * @tparam Iterator2 迭代器类型
 * @tparam BinaryPredicate 二元谓词类型
 */
template <
    typename Iterator1,
    typename Iterator2,
    typename BinaryPredicate = stl::equal_to<iterator_value_type_t<Iterator1>>>
constexpr bool equal(Iterator1 first1,
                     Iterator1 last1,
                     Iterator2 first2,
                     BinaryPredicate pred = BinaryPredicate{}) {
    return detail::equal(first1, last1, first2, pred);
}

/**
 * @brief 使用给定的二元谓词比较两个范围的元素是否相等
 * @tparam Iterator1 迭代器类型
 * @tparam Iterator2 迭代器类型
 * @tparam BinaryPredicate 二元谓词类型
 */
template <
    typename Iterator1,
    typename Iterator2,
    typename BinaryPredicate = stl::equal_to<iterator_value_type_t<Iterator1>>>
constexpr bool equal(Iterator1 first1,
                     Iterator1 last1,
                     Iterator2 first2,
                     Iterator2 last2,
                     BinaryPredicate pred = BinaryPredicate{}) {
    return detail::equal(first1, last1, first2, last2, pred);
}

}  // namespace stl