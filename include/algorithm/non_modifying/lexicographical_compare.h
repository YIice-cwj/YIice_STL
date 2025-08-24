#pragma once
#include "../../functional/less.h"
#include "iterator_traits.h"

namespace stl {
namespace detail {

template <typename Iterator1, typename Iterator2, typename Compare>
constexpr bool lexicographical_compare(Iterator1 first1,
                                       Iterator1 last1,
                                       Iterator2 first2,
                                       Iterator2 last2,
                                       Compare comp) {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (comp(*first1, *first2))
            return true;
        if (comp(*first2, *first1))
            return false;
    }
    return (first1 == last1 && first2 == last2);
}

}  // namespace detail

/**
 * @brief 按照字典序比较两个范围
 * @tparam Iterator1 迭代器类型
 * @tparam Iterator2 迭代器类型
 * @tparam Compare 比较函数
 */
template <typename Iterator1,
          typename Iterator2,
          typename Compare = stl::less<iterator_value_type_t<Iterator1>>>
constexpr bool lexicographical_compare(Iterator1 first1,
                                       Iterator1 last1,
                                       Iterator2 first2,
                                       Iterator2 last2,
                                       Compare comp = Compare{}) {
    return detail::lexicographical_compare(first1, last1, first2, last2, comp);
}
}  // namespace stl