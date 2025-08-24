#pragma once
#include "../type_traits/decay.h"
#include "../type_traits/is_convertible.h"
#include "../type_traits/is_nothrow_swappable.h"
#include "forward.h"
#include "swap.h"

namespace stl {
template <typename T1, typename T2>
struct pair {
    using first_type = decay_t<T1>;
    using second_type = decay_t<T2>;

    first_type first;
    second_type second;

    constexpr pair() : first(), second() {}

    constexpr pair(const first_type& x, const second_type& y)
        : first(x), second(y) {}

    template <typename U1, typename U2>
    constexpr pair(const U1& x,
                   const U2& y,
                   enable_if_t<is_convertible_v<U1, first_type> &&
                               is_convertible_v<U2, second_type>>* = nullptr)
        : first(x), second(y) {}

    template <typename U1, typename U2>
    constexpr pair(U1&& x,
                   U2&& y,
                   enable_if_t<is_convertible_v<U1, first_type> &&
                               is_convertible_v<U2, second_type>>* = nullptr)
        : first(stl::forward<U1>(x)), second(stl::forward<U2>(y)) {}

    template <typename U1, typename U2>
    constexpr pair(const pair<U1, U2>& other,
                   enable_if_t<is_convertible_v<U1, first_type> &&
                               is_convertible_v<U2, second_type>>* = nullptr)
        : first(other.first), second(other.second) {}

    constexpr pair(const pair& other)
        : first(other.first), second(other.second) {}

    constexpr pair(pair&& other)
        : first(stl::move(other.first)), second(stl::move(other.second)) {}

    constexpr pair& operator=(const pair& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }

    constexpr pair& operator=(pair&& other) noexcept(
        is_nothrow_move_assignable_v<first_type> &&
        is_nothrow_move_assignable_v<second_type>) {
        if (this != &other) {
            first = stl::move(other.first);
            second = stl::move(other.second);
        }
        return *this;
    }

    template <typename U1,
              typename U2,
              typename = enable_if_t<is_convertible_v<U1, first_type> &&
                                     is_convertible_v<U2, second_type>>>
    constexpr pair& operator=(const pair<U1, U2>& other) {
        first = other.first;
        second = other.second;
        return *this;
    }

    template <typename U1,
              typename U2,
              typename = enable_if_t<is_convertible_v<U1, first_type> &&
                                     is_convertible_v<U2, second_type>>>
    constexpr pair& operator=(pair<U1, U2>&& other) noexcept(
        is_nothrow_move_assignable_v<first_type> &&
        is_nothrow_move_assignable_v<second_type>) {
        first = stl::forward<U1>(other.first);
        second = stl::forward<U2>(other.second);
        return *this;
    }

    constexpr void swap(pair& other) noexcept(is_nothrow_swappable_v<T1> &&
                                              is_nothrow_swappable_v<T2>) {
        stl::swap(first, other.first);
        stl::swap(second, other.second);
    }
};

template <typename T1, typename T2>
constexpr bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
constexpr bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs == rhs);
}

template <typename T1, typename T2>
constexpr bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return (lhs.first < rhs.first) ||
           (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <typename T1, typename T2>
constexpr bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return rhs < lhs;
}

template <typename T1, typename T2>
constexpr bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(rhs < lhs);
}

template <typename T1, typename T2>
constexpr bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs < rhs);
}

/**
 * @brief 创建一个pair对象
 *
 * @param t1 第一个元素
 * @param t2 第二个元素
 */
template <typename T1, typename T2>
constexpr pair<decay_t<T1>, decay_t<T2>> make_pair(T1&& t1, T2&& t2) {
    return pair<decay_t<T1>, decay_t<T2>>(stl::forward<T1>(t1),
                                          stl::forward<T2>(t2));
}
}  // namespace stl