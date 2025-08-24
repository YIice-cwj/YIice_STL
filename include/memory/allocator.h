#pragma once

#include <cstddef>
#include <cstdlib>
#include <limits>
#include <new>
#include <stdexcept>
#include "../utility/forward.h"
#include "addressof.h"

namespace stl {

/**
 * @brief 自定义内存分配器
 */
template <typename T>
class allocator {
   public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    template <typename U>
    struct rebind {
        using other = allocator<U>;
    };

    allocator() noexcept {}

    allocator(const allocator&) noexcept {}

    template <typename U>
    allocator(const allocator<U>&) noexcept {}

    allocator& operator=(const allocator&) noexcept { return *this; }

    ~allocator() {}

    /**
     * @brief 分配内存
     * @param n 要分配的对象数量
     * @return 指向分配内存的指针
     * @throws std::bad_alloc 当分配失败时
     * @throws std::length_error 当请求大小超过限制时
     */
    pointer allocate(size_type n) {
        if (n == 0) {
            return nullptr;
        }

        if (n > max_size()) {
            throw std::length_error(
                "allocator::allocate: 请求的大小超过最大限制");
        }

        const size_type max_bytes = std::numeric_limits<size_type>::max();
        if (n > max_bytes / sizeof(value_type)) {
            throw std::length_error("allocator::allocate: 整数溢出");
        }

        void* ptr = std::malloc(n * sizeof(value_type));
        if (!ptr) {
            throw std::bad_alloc();
        }

        return static_cast<pointer>(ptr);
    }

    /**
     * @brief 分配内存（带对齐提示）
     * @param n 要分配的对象数量
     * @param hint 对齐提示
     * @return 指向分配内存的指针
     */
    pointer allocate(size_type n, const void* hint) {
        static_cast<void>(hint);
        return allocate(n);
    }

    /**
     * @brief 释放内存
     * @param p 要释放的内存指针
     * @param n 对象数量（必须与分配时相同）
     */
    void deallocate(pointer p, size_type n) noexcept {
        static_cast<void>(n);

        if (p != nullptr) {
            std::free(p);
        }
    }

    /**
     * @brief 在指定内存位置构造对象
     * @param p 内存位置
     * @param args 构造参数
     */
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new (static_cast<void*>(p)) U(stl::forward<Args>(args)...);
    }

    /**
     * @brief 销毁指定内存位置的对象
     * @param p 对象指针
     */
    template <typename U>
    void destroy(U* p) {
        if (p != nullptr) {
            p->~U();
        }
    }

    /**
     * @brief 返回分配器可以分配的最大对象数量
     */
    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

    /**
     * @brief 返回指定对象的地址
     */
    pointer address(reference r) const noexcept { return stl::addressof(r); }

    /**
     * @brief 返回指定对象的地址（const版本）
     */
    const_pointer address(const_reference r) const noexcept {
        return stl::addressof(r);
    }

    /**
     * @brief 选择分配器用于容器复制构造
     */
    allocator select_on_container_copy_construction() const { return *this; }
};

/**
 * @brief 分配器相等比较
 */
template <typename T, typename U>
bool operator==(const allocator<T>&, const allocator<U>&) noexcept {
    return true;
}

/**
 * @brief 分配器不等比较
 */
template <typename T, typename U>
bool operator!=(const allocator<T>&, const allocator<U>&) noexcept {
    return false;
}

/**
 * @brief void类型特化
 */
template <>
class allocator<void> {
   public:
    using value_type = void;
    using pointer = void*;
    using const_pointer = const void*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    template <typename U>
    struct rebind {
        using other = allocator<U>;
    };

    allocator() noexcept {}

    allocator(const allocator&) noexcept {}

    template <typename U>
    allocator(const allocator<U>&) noexcept {}

    allocator& operator=(const allocator&) noexcept { return *this; }
};

}  // namespace stl