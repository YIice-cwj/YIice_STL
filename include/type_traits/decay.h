#pragma once
#include "add_pointer.h"
#include "conditional.h"
#include "is_array.h"
#include "is_function.h"
#include "remove_cv.h"
#include "remove_extent.h"
#include "remove_reference.h"

namespace stl {
namespace detail {

/**
 * @brief 衰减类型
 * @tparam T 类型
 * @note 1. 如果 T 是函数类型，则结果是函数指针类型
 *       2. 如果 T 是数组类型，则结果是相应的指针类型
 *       3. 否则，结果是 T 的 cv 修饰符被移除的类型
 */
template <typename T>
struct decay {
   private:
    using U = remove_reference_t<T>;

   public:
    using type = conditional_t<
        is_array_v<U>,
        add_pointer_t<remove_extent_t<U>>,
        conditional_t<is_function_v<U>, add_pointer_t<U>, remove_cv_t<U>>>;
};

}  // namespace detail
using detail::decay;

/**
 * @brief 衰减类型
 * @tparam T 类型
 * @note 1. 如果 T 是函数类型，则结果是函数指针类型
 *       2. 如果 T 是数组类型，则结果是相应的指针类型
 *       3. 否则，结果是 T 的 cv 修饰符被移除的类型
 */
template <typename T>
using decay_t = typename decay<T>::type;
}  // namespace stl