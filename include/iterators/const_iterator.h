#pragma once
#include "iterator.h"

namespace stl {

template <typename T>
class const_iterator {
   public:
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using difference_type = ptrdiff_t;
    using iterator_category = iterator_tag::random_access_iterator_tag;

   private:
    pointer ptr_;

    template <typename U>
    friend class iterator;

   public:
    const_iterator(pointer ptr = nullptr) : ptr_(ptr) {}

    const_iterator(const const_iterator<T>& c_iterator)
        : ptr_(c_iterator.ptr_) {}

    /**
     * @brief 接受一个非const的迭代器并转换为const迭代器
     */
    const_iterator(iterator<T>&& iterator) : ptr_(iterator.ptr_) {}

    const_iterator& operator=(const const_iterator& other) {
        if (this != &other) {
            ptr_ = other.ptr_;
        }
        return *this;
    }

    const_iterator& operator++() {
        ++ptr_;
        return *this;
    }

    const_iterator operator++(int) {
        const_iterator temp = *this;
        ++(*this);
        return temp;
    }

    const_iterator& operator--() {
        --ptr_;
        return *this;
    }

    const_iterator operator--(int) {
        const_iterator temp = *this;
        --(*this);
        return temp;
    }

    reference operator*() const { return *ptr_; }

    pointer operator->() const { return ptr_; }

    reference operator[](difference_type n) const { return *(ptr_ + n); }

    bool operator==(const const_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const const_iterator& other) const {
        return ptr_ != other.ptr_;
    }

    bool operator<(const const_iterator& other) const {
        return ptr_ < other.ptr_;
    }

    bool operator>(const const_iterator& other) const {
        return ptr_ > other.ptr_;
    }

    bool operator<=(const const_iterator& other) const {
        return ptr_ <= other.ptr_;
    }

    bool operator>=(const const_iterator& other) const {
        return ptr_ >= other.ptr_;
    }

    difference_type operator-(const const_iterator& other) const {
        return ptr_ - other.ptr_;
    }

    const_iterator operator+(difference_type n) const {
        return const_iterator(ptr_ + n);
    }

    const_iterator operator-(difference_type n) const {
        return const_iterator(ptr_ - n);
    }

    const_iterator& operator+=(difference_type n) {
        ptr_ += n;
        return *this;
    }

    const_iterator& operator-=(difference_type n) {
        ptr_ -= n;
        return *this;
    }
};

}  // namespace stl