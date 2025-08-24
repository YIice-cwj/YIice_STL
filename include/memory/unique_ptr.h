#pragma once
#include <cstddef>
#include "../type_traits/enable_if.h"
#include "../type_traits/is_array.h"
#include "../type_traits/remove_extent.h"
#include "../utility/move.h"
#include "../utility/swap.h"
#include "default_delete.h"

namespace stl {

/**
 * @brief 独享智能指针
 * @tparam T 类型
 * @tparam Deleter 删除器
 */
template <typename T, typename Delete = default_delete<T>>
class unique_ptr {
    using element_type = remove_extent_t<T>;
    using delete_type = Delete;
    using pointer = element_type*;
    using reference = element_type&;

   private:
    element_type* ptr_;
    delete_type delete_;

   public:
    constexpr unique_ptr() noexcept : ptr_(nullptr), delete_(Delete()) {}

    constexpr unique_ptr(pointer ptr) noexcept : ptr_(ptr), delete_(Delete()) {}

    constexpr unique_ptr(pointer ptr, const delete_type& del) noexcept
        : ptr_(ptr), delete_(del) {}

    unique_ptr(const unique_ptr&) = delete;

    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& other) noexcept
        : ptr_(other.release()), delete_(stl::move(other.delete_)) {}

    template <typename U,
              typename E,
              typename = enable_if_t<is_constructible_v<U*, element_type*>>>
    unique_ptr(unique_ptr<U, E>&& other) noexcept
        : ptr_(other.release()), delete_(move(other.get_delete())) {}

    unique_ptr& operator=(decltype(nullptr)) noexcept {
        reset();
        return *this;
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        unique_ptr(stl::move(other)).swap(*this);
    }

    T& operator*() const { return *ptr_; }

    pointer operator->() const noexcept { return ptr_; }

    enable_if_t<!is_array<T>::value, reference> operator[](size_t index) const {
        return ptr_[index];
    }

    pointer get() const noexcept { return ptr_; }

    delete_type& get_delete() noexcept { return delete_; }

    const delete_type& get_delete() const noexcept { return delete_; }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    pointer release() noexcept {
        pointer temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    void reset(pointer p = nullptr) noexcept {
        pointer old_ptr = ptr_;
        ptr_ = p;
        if (old_ptr) {
            delete_(old_ptr);
        }
    }

    void swap(unique_ptr& other) noexcept {
        swap(ptr_, other.ptr_);
        swap(delete_, other.delete_);
    }

    ~unique_ptr() {
        if (ptr_) {
            delete_(ptr_);
        }
    }
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(stl::forward<Args>(args)...));
}

template <typename T>
unique_ptr<T[]> make_unique(size_t size) {
    return unique_ptr<T[]>(new T[size]);
}

template <typename T1, typename D1, typename T2, typename D2>
bool operator==(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
    return lhs.get() == rhs.get();
}

template <typename T, typename D>
bool operator==(const unique_ptr<T, D>& ptr, decltype(nullptr)) {
    return !ptr;
}

template <typename T, typename D>
bool operator==(decltype(nullptr), const unique_ptr<T, D>& ptr) {
    return !ptr;
}

}  // namespace stl