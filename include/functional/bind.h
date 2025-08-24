#pragma once
#include "../type_traits/conditional.h"
#include "../type_traits/decay.h"
#include "../type_traits/integral_constant.h"
#include "../type_traits/is_member_function_pointer.h"
#include "../type_traits/is_reference_wrapper.h"
#include "../utility/forward.h"
#include "../utility/index_sequence.h"
#include "../utility/reference_wrapper.h"
#include "../utility/tuple.h"

namespace stl {

// 占位符
namespace placeholders {
template <int N>
struct placeholder {
    static constexpr int value = N;
};

/**
 * @brief 判断是否是占位符
 */
template <typename T>
struct is_placeholder : false_type {};

template <int N>
struct is_placeholder<placeholder<N>> : true_type {};

template <typename T>
constexpr bool is_placeholder_v = is_placeholder<T>::value;

/**
 * @brief 获取占位符值的特化
 */
template <typename T>
struct placeholder_value {
    static constexpr int value = 0;
};

template <int N>
struct placeholder_value<placeholder<N>> {
    static constexpr int value = N;
};

template <typename T>
constexpr int placeholder_value_v = placeholder_value<T>::value;

/**
 * @brief 占位符
 */
constexpr stl::placeholders::placeholder<1> _1{};
constexpr stl::placeholders::placeholder<2> _2{};
constexpr stl::placeholders::placeholder<3> _3{};
constexpr stl::placeholders::placeholder<4> _4{};
constexpr stl::placeholders::placeholder<5> _5{};
constexpr stl::placeholders::placeholder<6> _6{};
constexpr stl::placeholders::placeholder<7> _7{};
constexpr stl::placeholders::placeholder<8> _8{};
constexpr stl::placeholders::placeholder<9> _9{};
constexpr stl::placeholders::placeholder<10> _10{};

}  // namespace placeholders

namespace tag {

/**
 * @brief 占位符标签
 */
struct placeholder_tag {};

/**
 * @brief 引用包装器标签
 */
struct reference_wrapper_tag {};

/**
 * @brief 普通参数标签
 */
struct normal_arg_tag {};

/**
 * @brief 标签选择器
 */
template <typename T>
struct tag_selector : conditional_t<placeholders::is_placeholder_v<T>,
                                    placeholder_tag,
                                    conditional_t<is_reference_wrapper_v<T>,
                                                  reference_wrapper_tag,
                                                  normal_arg_tag>> {};

}  // namespace tag

/**
 * @brief 绑定结果类型
 */
template <typename F, typename... Args>
class bind_result {
    using function_type = F;
    using args_tuple_type = tuple<Args...>;

   private:
    function_type func_;    // 绑定的函数
    args_tuple_type args_;  // 绑定参数

    /**
     * @brief 选择参数(占位符)
     * @tparam Index 占位符索引
     * @tparam CallArgsTuple 调用参数tuple
     * @param call_arg 调用参数
     */
    template <size_t Index, typename CallArgsTuple>
    auto select_arg(CallArgsTuple&& call_arg, tag::placeholder_tag) const {
        using arg_type =
            tuple_element_t<Index,
                            args_tuple_type>;  // 获取占位符对应的参数类型
        constexpr int placeholder_index =
            placeholders::placeholder_value_v<arg_type>;  // 获取占位符索引
        return get<placeholder_index - 1>(
            forward<CallArgsTuple>(call_arg));  // 返回占位符对应的参数
    }

    /**
     * @brief 选择参数(占位符)
     * @tparam Index 占位符索引
     * @tparam CallArgsTuple 调用参数tuple
     * @param call_arg 调用参数
     */
    template <size_t Index, typename CallArgsTuple>
    auto select_arg(CallArgsTuple&& call_args,
                    tag::reference_wrapper_tag) const {
        return get<Index>(args_).get();
    }

    /**
     * @brief 选择参数(普通参数)
     * @tparam Index 占位符索引
     * @tparam CallArgsTuple 调用参数tuple
     * @param call_arg 调用参数
     */
    template <size_t Index, typename CallArgsTuple>
    auto select_arg(CallArgsTuple&& call_args, tag::normal_arg_tag) const {
        return get<Index>(args_);
    }

    /**
     * @brief 选择参数(统一调用)
     * @tparam CallArgsTuple 调用参数tuple
     * @tparam Index 索引序列
     * @param call_args 调用参数
     */
    template <size_t Index, typename CallArgsTuple>
    auto select_arg(CallArgsTuple&& call_args) const {
        using arg_type = tuple_element_t<Index, args_tuple_type>;
        /**
         *  使用tag_selector选择标签，然后调用select_arg选择参数
         */
        return select_arg<Index>(forward<CallArgsTuple>(call_args),
                                 tag::tag_selector<arg_type>{});
    }

    /**
     * @brief 调用函数(成员函数)
     * @tparam CallArgsTuple 调用参数tuple
     * @tparam IndexSequence 索引序列
     * @param call_args 调用参数
     */
    template <typename CallArgsTuple, size_t... Indices>
    auto call(CallArgsTuple&& call_args,
              index_sequence<Indices...>,
              true_type) const {
        return (select_arg<0>(call_args).*
                func_)(select_arg<Indices + 1>(call_args)...);
    }

    /**
     * @brief 调用函数(普通函数)
     * @tparam CallArgsTuple 调用参数tuple
     * @tparam IndexSequence 索引序列
     * @param call_args 调用参数
     */
    template <typename CallArgsTuple, size_t... Indices>
    auto call(CallArgsTuple&& call_args,
              index_sequence<Indices...>,
              false_type) const {
        return func_(select_arg<Indices>(call_args)...);
    }

   public:
    /**
     * @brief 构造函数
     */
    bind_result(function_type func, Args... args)
        : func_(func), args_(forward<Args>(args)...) {}

    /**
     * @brief 函数调用
     */
    template <typename... CallArgs>
    auto operator()(CallArgs&&... call_args) const {
        // 将参数转换为tuple, tuple中元素类型为引用类型
        auto call_args_tuple =
            forward_as_tuple(forward<CallArgs>(call_args)...);

        /**
         * index_sequence_for:
         * 生成对应绑定参数数量的索引序列，而不是调用参数的数量
         *
         * bool_constant<is_member_function_pointer_v<function_type>>:
         * 判断绑定的函数是否为成员函数指针
         */

        return call(
            call_args_tuple, index_sequence_for<Args...>{},
            bool_constant<is_member_function_pointer_v<function_type>>{});
    }
};

/**
 * @brief 绑定函数
 */
template <typename F, typename... Args>
auto bind(F&& func, Args&&... args) {
    return bind_result<decay_t<F>, decay_t<Args>...>(forward<F>(func),
                                                     forward<Args>(args)...);
}

}  // namespace stl