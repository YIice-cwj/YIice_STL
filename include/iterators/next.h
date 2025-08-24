#pragma once
#include "advance.h"
#include "iterator_traits.h"

namespace stl {

/**
 * @brief 获取迭代器的下一个元素
 * @tparam Iterator 迭代器类型
 * @param it 迭代器
 * @param n 移动的距离(默认为: 1)
 */
template <typename Iterator>
void next(Iterator& it, iterator_difference_type_t<Iterator> n = 1) {
    advance(it, n);
}

}  // namespace stl