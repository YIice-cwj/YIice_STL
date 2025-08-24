#pragma once
#include <cstddef>
#include "../type_traits/is_reference.h"
#include "forward.h"
#include "move.h"
#include "swap.h"

namespace stl {
namespace detail {

template <typename... Type>
class tuple;

// 主模版
template <std::size_t Index, typename... Types>
struct tuple_base {};

/**
 * 停止递归模版特化：
 * 当递归模版没有任何类型时，则停止递归
 * 此时 tuple_base<Index> 为空类
 *
 * 为什么需要定义拷贝构造函数、移动构造函数、赋值函数？
 *
 * 因为：当递归到最后一个元素时，父类为
 * tuple_base<Index>，而如果没有拷贝构造函数、移动构造函数、赋值函数,
 * 那么无法完成递归拷贝、递归移动、递归赋值, 由于 tuple_base<Index>
 * 为空类，所以报错
 */
template <std::size_t Index>
struct tuple_base<Index> {
    tuple_base() = default;
    tuple_base(const tuple_base&) = default;
    tuple_base(tuple_base&&) = default;
    tuple_base& operator=(const tuple_base&) = default;
    tuple_base& operator=(tuple_base&&) = default;
    ~tuple_base() = default;
};

/**
 * 递归模版特化：
 *
 * 假如定义了一个tuple<int, double, char>，那么继承的父类则会变为 tuple_base<0,
 * int, double, char> 且会进行以下递归特化
 *
 * tuple_base<0, int, double, char> : tuple_base<1, double, char>;
 *      |
 *      └──> tuple_base<1, double, char> : tuple_base<2, char>;
 *              |
 *              └──> tuple_base<2, char> : tuple_base<3>;
 *
 * 而Type 则依次为 int, double, char 存储在 tuple_base<0, int, double, char> 中
 * 即 tuple_base<Index, Type, Types...>
 */
template <std::size_t Index, typename Type, typename... Types>
struct tuple_base<Index, Type, Types...> : tuple_base<Index + 1, Types...> {
    using base_type = tuple_base<Index + 1, Types...>;
    using type = Type;

    type value;

    constexpr tuple_base() {};

    // constexpr tuple_base(const tuple_base& other,
    //                      enable_if_t<!is_reference_v<type>>* = nullptr)
    //     // static_cast<const base_type&>(other) 子类转为父类左引用
    //     // 从而调用父类的拷贝构造函数进行递归拷贝
    //     : base_type(static_cast<const base_type&>(other)),
    //       value(stl::forward<type>(other.value)) {}

    // constexpr tuple_base(const tuple_base&& other,
    //                      enable_if_t<is_reference_v<type>>* = nullptr)
    //     : base_type(static_cast<const base_type&>(other)) {}

    constexpr tuple_base(const tuple_base& other)
        : base_type(static_cast<const base_type&>(other)), value(other.value) {}

    constexpr tuple_base(tuple_base&& other)
        // static_cast<const base_type&&>(other) 子类转为父类右引用
        // 从而调用父类的移动构造函数进行递归移动
        : base_type(static_cast<base_type&&>(other)),
          value(stl::move(other.value)) {}

    /**
     * 用于接收子类传递的值，并存储第N个元素的值, 即 value
     * 同时递归调用父类的构造函数，将剩下的元素进行初始化
     */
    template <typename UType,
              typename... UTypes,
              typename = enable_if_t<sizeof...(UTypes) == sizeof...(Types)>>
    constexpr tuple_base(UType&& uvalue, UTypes&&... utypes)
        : base_type(stl::forward<UTypes>(utypes)...),
          value(stl::forward<UType>(uvalue)) {}

    constexpr tuple_base& operator=(const tuple_base& other) {
        // 调用父类的赋值函数进行递归赋值
        static_cast<base_type&>(*this) = static_cast<const base_type&>(other);
        value = other.value;
        return *this;
    }

    constexpr tuple_base& operator=(tuple_base&& other) {
        // 调用父类的赋值函数进行递归赋值
        static_cast<base_type&>(*this) = static_cast<base_type&&>(other);
        value = stl::move(other.value);
        return *this;
    }

    ~tuple_base() = default;

   private:
};

/**
 * @brief 元组
 * @tparam Types 元素类型
 */
template <typename... Types>
class tuple : public tuple_base<0, Types...> {
   public:
    using base_type = tuple_base<0, Types...>;

    constexpr tuple() {};

    constexpr tuple(const tuple& other)
        : base_type(static_cast<const base_type&>(other)) {}

    constexpr tuple(tuple&& other)
        : base_type(static_cast<base_type&&>(other)) {}

    template <typename... UTypes,
              typename = enable_if_t<sizeof...(UTypes) == sizeof...(Types) &&
                                     (sizeof...(Types) > 0)>>
    constexpr tuple(UTypes&&... utypes)
        : base_type(stl::forward<UTypes>(utypes)...) {}

    constexpr tuple& operator=(const tuple& other) {
        static_cast<base_type&>(*this) = static_cast<const base_type&>(other);
        return *this;
    }

    constexpr tuple& operator=(tuple&& other) {
        static_cast<base_type&>(*this) = static_cast<base_type&&>(other);
        return *this;
    }

    template <typename... Utypes>
    constexpr tuple& operator=(const tuple<Utypes...>& other) {
        static_cast<base_type&>(*this) =
            static_cast<const tuple_base<0, Utypes...>&>(other);
        return *this;
    }

    template <typename... Utypes>
    constexpr tuple& operator=(tuple<Utypes...>&& other) {
        static_cast<base_type&>(*this) =
            static_cast<tuple_base<0, Utypes...>&&>(other);
        return *this;
    }

    constexpr void swap(tuple& other) { stl::swap(*this, other); }

    template <std::size_t I, typename T, typename... Ts>
    friend constexpr auto& get(tuple_base<I, T, Ts...>& t);

    template <std::size_t I, typename T, typename... Ts>
    friend constexpr const auto& get(const tuple_base<I, T, Ts...>& t);

    template <std::size_t I, typename T, typename... Ts>
    friend constexpr auto&& get(tuple_base<I, T, Ts...>&& t);

    ~tuple() = default;
};

/**
 * @brief 获取 tuple 中第 N 个元素的类型
 * @tparam Index 元素下标
 * @tparam T tuple 类型
 *
 * @note
 * 例如：tuple_element<0, tuple<int, double, char>>::type 为 int
 */
template <std::size_t Index, typename T>
struct tuple_element {};

template <typename Type, typename... Types>
struct tuple_element<0, tuple<Type, Types...>> {
    using type = Type;
};

template <std::size_t Index, typename Type, typename... Types>
struct tuple_element<Index, tuple<Type, Types...>> {
    using type = typename tuple_element<Index - 1, tuple<Types...>>::type;
};

/**
 * @brief 获取 tuple 中第 N 个元素的类型
 * @tparam Index 元素下标
 * @tparam T tuple 类型
 *
 * @note
 * 例如：tuple_element<0, tuple<int, double, char>>::type 为 int
 */
template <std::size_t Index, typename T>
using tuple_element_t = typename tuple_element<Index, T>::type;

/**
 * @brief 获取 tuple 中元素的数量
 * @tparam T tuple 类型
 */
template <typename T>
struct tuple_size {};

template <typename... Types>
struct tuple_size<tuple<Types...>> {
    static constexpr std::size_t value = sizeof...(Types);
};

/**
 * @brief 获取 tuple 中第 N 个元素的引用
 * @tparam Index 元素下标
 * @tparam T tuple 类型
 */
template <std::size_t Index, typename Type, typename... Types>
constexpr auto& get(tuple_base<Index, Type, Types...>& t) {
    return t.value;
}

template <std::size_t Index, typename Type, typename... Types>
constexpr const auto& get(const tuple_base<Index, Type, Types...>& t) {
    return t.value;
}

template <std::size_t Index, typename Type, typename... Types>
constexpr auto&& get(tuple_base<Index, Type, Types...>&& t) {
    return stl::move(t.value);
}

/**
 * 防止 tuple 中元素数量为 0 时，递归调用 tuple_equal
 */
template <std::size_t Index, typename... Types1, typename... Types2>
constexpr enable_if_t<(Index == sizeof...(Types1)), bool> tuple_equal(
    const tuple<Types1...>&,
    const tuple<Types2...>&) {
    return true;
}

/**
 * enable_if_t<(Index < sizeof...(Types1)) 用于判断 Index 是否小于 tuple
 * 的大小, 如果小于则继续递归比较 否则返回 true
 */
template <std::size_t Index, typename... Types1, typename... Types2>
constexpr enable_if_t<(Index < sizeof...(Types1)), bool> tuple_equal(
    const tuple<Types1...>& lhs,
    const tuple<Types2...>& rhs) {
    return get<Index>(lhs) == get<Index>(rhs) &&
           tuple_equal<Index + 1>(lhs, rhs);
}

/**
 * 防止 tuple 中元素数量为 0 时，递归调用 tuple_compare
 */
template <std::size_t Index, typename... Types1, typename... Types2>
constexpr enable_if_t<(Index == sizeof...(Types1)), bool> tuple_compare(
    const tuple<Types1...>&,
    const tuple<Types2...>&) {
    return false;
}

/**
 * enable_if_t<(Index < sizeof...(Types1)) 用于判断 Index 是否小于 tuple
 * 的大小, 如果小于则继续递归比较 否则返回 false
 */
template <std::size_t Index, typename... Types1, typename... Types2>
constexpr enable_if_t<(Index < sizeof...(Types1)), bool> tuple_compare(
    const tuple<Types1...>& lhs,
    const tuple<Types2...>& rhs) {
    return get<Index>(lhs) < get<Index>(rhs) ||
           (get<Index>(lhs) == get<Index>(rhs) &&
            tuple_compare<Index + 1>(lhs, rhs));
}

template <typename... Types1, typename... Types2>
constexpr bool operator==(const tuple<Types1...>& lhs,
                          const tuple<Types2...>& rhs) {
    if (sizeof...(Types1) != sizeof...(Types2)) {
        return false;
    }
    return tuple_equal<0>(lhs, rhs);
}

template <typename... Types1, typename... Types2>
constexpr bool operator!=(const tuple<Types1...>& lhs,
                          const tuple<Types2...>& rhs) {
    return !(lhs == rhs);
}

template <typename... Types1, typename... Types2>
constexpr bool operator<(const tuple<Types1...>& lhs,
                         const tuple<Types2...>& rhs) {
    if (sizeof...(Types1) != sizeof...(Types2)) {
        return sizeof...(Types1) < sizeof...(Types2);
    }
    return tuple_compare<0>(lhs, rhs);
}

template <typename... Types1, typename... Types2>
constexpr bool operator<=(const tuple<Types1...>& lhs,
                          const tuple<Types2...>& rhs) {
    return !(rhs < lhs);
}

template <typename... Types1, typename... Types2>
constexpr bool operator>(const tuple<Types1...>& lhs,
                         const tuple<Types2...>& rhs) {
    return lhs < rhs;
}

template <typename... Types1, typename... Types2>
constexpr bool operator>=(const tuple<Types1...>& lhs,
                          const tuple<Types2...>& rhs) {
    return !(lhs < rhs);
}

}  // namespace detail
using detail::tuple;
using detail::tuple_element;
using detail::tuple_element_t;
using detail::tuple_size;
using detail::operator==;
using detail::operator!=;
using detail::operator<;
using detail::operator>;
using detail::operator<=;
using detail::operator>=;

/**数量
 * @tparam T tuple 类型
 * @brief 获取 tuple 中元素的
 */
template <typename T>
constexpr std::size_t tuple_size_v = tuple_size<T>::value;

/**
 * @brief 创建 tuple 对象
 * @tparam Types 元素类型
 * @tparam Args 元素值
 */
template <typename... Args>
constexpr tuple<Args...> make_tuple(Args&&... args) {
    return tuple<Args...>(stl::forward<Args>(args)...);
}

/**
 * @brief 创建完美转发 tuple 对象
 * @return tuple<Types...>
 */
template <typename... Args>
constexpr tuple<Args&&...> forward_as_tuple(Args&&... args) {
    return tuple<Args&&...>(stl::forward<Args>(args)...);
}

/**
 * @brief 获取 tuple 中指定下标的元素
 * @tparam Index 元素下标
 * @tparam Types tuple 类型
 * @param t tuple 对象
 */
template <std::size_t Index, typename... Types>
constexpr auto& get(tuple<Types...>& t) {
    return detail::get<Index>(static_cast<detail::tuple_base<0, Types...>&>(t));
}

/**
 * @brief 获取 tuple 中指定下标的元素
 * @tparam Index 元素下标
 * @tparam Types tuple 类型
 * @param t tuple 对象
 */
template <std::size_t Index, typename... Types>
constexpr const auto& get(const tuple<Types...>& t) {
    return detail::get<Index>(
        static_cast<const detail::tuple_base<0, Types...>&>(t));
}

/**
 * @brief 获取 tuple 中指定下标的元素
 * @tparam Index 元素下标
 * @tparam Types tuple 类型
 * @param t tuple 对象
 */
template <std::size_t Index, typename... Types>
constexpr auto&& get(tuple<Types...>&& t) {
    return detail::get<Index>(
        static_cast<detail::tuple_base<0, Types...>&&>(t));
}

}  // namespace stl