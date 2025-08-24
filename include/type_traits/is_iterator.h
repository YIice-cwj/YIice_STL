
#pragma once
#include "../iterators/iterator_traits.h"
#include "../type_traits/integral_constant.h"
#include "../utility/declval.h"

namespace stl {

namespace detail {

template <typename T>
auto check_iterator(int) -> decltype(declval<iterator_category_t<T>>(),
                                     declval<iterator_value_type_t<T>>(),
                                     declval<iterator_difference_type_t<T>>(),
                                     declval<iterator_pointer_t<T>>(),
                                     declval<iterator_reference_t<T>>(),
                                     true_type{});

template <typename T>
false_type check_iterator(...);

/**
 * @brief 检查类型是否为迭代器
 * @tparam T 迭代器类型
 */
template <typename T>
struct is_iterator : bool_constant<decltype(check_iterator<T>(0))::value> {};

template <typename T>
struct is_iterator<T*> : true_type {};

template <typename T>
struct is_iterator<const T*> : true_type {};

}  // namespace detail
using detail::is_iterator;

/**
 * @brief 检查类型是否为迭代器
 * @tparam T 迭代器类型
 */
template <typename T>
constexpr bool is_iterator_v = is_iterator<T>::value;

}  // namespace stl
