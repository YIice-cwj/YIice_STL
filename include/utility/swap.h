#pragma once
#include <cstddef>
#include "../type_traits/enable_if.h"
#include "../type_traits/is_copy_assignable.h"
#include "../type_traits/is_copy_constructible.h"
#include "../type_traits/is_move_assignable.h"
#include "../type_traits/is_move_constructible.h"
#include "../type_traits/is_nothrow_copy_assignable.h"
#include "../type_traits/is_nothrow_copy_constructible.h"
#include "../type_traits/is_nothrow_move_assignable.h"
#include "../type_traits/is_nothrow_move_constructible.h"
#include "move.h"

namespace stl {

/**
 * @brief 交换两个对象的值(移动)
 * @param a 要交换的对象
 * @param b 要交换的对象
 */
template <typename T>
constexpr enable_if_t<is_move_constructible_v<T> && is_move_assignable_v<T>>
swap(T& a, T& b) noexcept(is_nothrow_move_constructible_v<T> &&
                          is_nothrow_move_assignable_v<T>) {
    T temp = stl::move(a);
    a = stl::move(b);
    b = stl::move(temp);
}

/**
 * @brief 交换两个对象的值(拷贝)
 * @param a 要交换的对象
 * @param b 要交换的对象
 */
template <typename T>
constexpr enable_if_t<!(is_move_constructible_v<T> &&
                        is_move_assignable_v<T>) &&
                      (is_copy_constructible_v<T> && is_copy_assignable_v<T>)>
swap(T& a, T& b) noexcept(is_nothrow_copy_constructible_v<T> &&
                          is_nothrow_copy_assignable_v<T>) {
    T temp = a;
    a = b;
    b = temp;
}
/**
 * @brief 交换两个数组
 * @param a 要交换的数组
 * @param b 要交换的数组
 */
template <typename T, size_t N>
constexpr enable_if_t<is_move_constructible_v<T> && is_move_assignable_v<T>>
swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(a[0], b[0]))) {
    for (size_t i = 0; i < N; ++i) {
        swap(a[i], b[i]);
    }
}

}  // namespace stl