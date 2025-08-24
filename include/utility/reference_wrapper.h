#pragma once
#include "forward.h"
#include "move.h"

namespace stl {

template <typename T>
class reference_wrapper {
    using value_type = T;
    using reference_type = T&;
    using const_reference_type = const T&;

   private:
    reference_type reference_;

   public:
    reference_wrapper(reference_type reference) : reference_(reference) {}

    reference_wrapper(const reference_wrapper& other)
        : reference_(other.reference_) {}

    reference_wrapper(reference_wrapper&& other)
        : reference_(other.reference_) {}

    reference_wrapper& operator=(const reference_wrapper& other) {
        reference_ = other.reference_;
        return *this;
    }

    reference_wrapper& operator=(reference_wrapper&& other) {
        reference_ = other.reference_;
        return *this;
    }

    /**
     * @brief 获取引用
     */
    reference_type get() { return reference_; }

    /**
     * @brief 获取常量引用
     */
    const_reference_type get() const { return reference_; }

    /**
     * @brief 转换为引用类型
     * @note 可以直接使用引用包装器作为引用类型使用
     */
    operator reference_type() { return reference_; }

    /**
     * @brief 转换为常量引用类型
     */
    operator const_reference_type() const { return reference_; }

    /**
     * @brief 调用引用包装器所引用的对象
     */
    template <typename... Args>
    auto operator()(Args&&... args)
        -> decltype(reference_(stl::forward<Args>(args)...)) {
        return reference_(stl::forward<Args>(args)...);
    }

    /**
     * @brief 调用引用包装器所引用的对象
     */
    template <typename... Args>
    auto operator()(Args&&... args) const
        -> decltype(reference_(stl::forward<Args>(args)...)) {
        return reference_(stl::forward<Args>(args)...);
    }
};

/**
 * @brief 创建一个引用包装器
 * @param t 要包装的对象
 */
template <typename T>
reference_wrapper<T> ref(T& t) {
    return reference_wrapper<T>(t);
}

/**
 * @brief 创建一个常量引用包装器
 * @param t 要包装的对象
 */
template <typename T>
reference_wrapper<const T> cref(const T& t) {
    return reference_wrapper<const T>(t);
}

// 防止绑定到临时对象
template <typename T>
void ref(const T&&) = delete;

template <typename T>
void cref(const T&&) = delete;

}  // namespace stl