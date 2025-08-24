#pragma once
#include <cstddef>
#include "iterators/iterator_tag.h"

namespace stl {

template <typename Iterator>
struct iterator_traits {
   public:
    using iterator_category = typename Iterator::iterator_category;
    using value_type = typename Iterator::value_type;
    using difference_type = typename Iterator::difference_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
};

template <typename T>
struct iterator_traits<T*> {
    using iterator_category = iterator_tag::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
};

template <typename T>
struct iterator_traits<const T*> {
    using iterator_category = iterator_tag::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;
};

/**
 * @brief 获取迭代器的类别
 */
template <typename Iterator>
typename iterator_traits<Iterator>::iterator_category iterator_category(
    const Iterator&) {
    return typename iterator_traits<Iterator>::iterator_category{};
}

template <typename Iterator>
using iterator_category_t =
    typename iterator_traits<Iterator>::iterator_category;

/**
 * @brief 获取迭代器的值类型
 */
template <typename Iterator>
typename iterator_traits<Iterator>::value_type iterator_value_type(
    const Iterator&) {
    return typename iterator_traits<Iterator>::value_type{};
}

template <typename Iterator>
using iterator_value_type_t = typename iterator_traits<Iterator>::value_type;

/**
 * @brief 获取迭代器的指针类型
 */
template <typename Iterator>
typename iterator_traits<Iterator>::value_type* iterator_pointer(
    const Iterator&) {
    return static_cast<typename iterator_traits<Iterator>::value_type*>(
        nullptr);
}

template <typename Iterator>
using iterator_pointer_t = typename iterator_traits<Iterator>::pointer;

/**
 * @brief 获取迭代器的引用类型
 */
template <typename Iterator>
typename iterator_traits<Iterator>::reference iterator_reference(
    const Iterator&) {
    return typename iterator_traits<Iterator>::reference{};
}

template <typename Iterator>
using iterator_reference_t = typename iterator_traits<Iterator>::reference;

/**
 * @brief 获取迭代器的差值类型
 */
template <typename Iterator>
typename iterator_traits<Iterator>::difference_type iterator_difference_type(
    const Iterator&) {
    return typename iterator_traits<Iterator>::difference_type{};
}

template <typename Iterator>
using iterator_difference_type_t =
    typename iterator_traits<Iterator>::difference_type;
}  // namespace stl
