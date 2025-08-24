#pragma once
#include "reverse_iterator.h"

namespace stl {

template <typename T>
class const_reverse_iterator {
   public:
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = iterator_tag::bidirectional_iterator_tag;

    template <typename U>
    friend class reverse_iterator;

   private:
    pointer ptr_;

   public:
    const_reverse_iterator(pointer ptr = nullptr) : ptr_(ptr) {}

    const_reverse_iterator(const reverse_iterator<T>& other)
        : ptr_(other.base()) {}

    const_reverse_iterator(const const_reverse_iterator& other)
        : ptr_(other.ptr_) {}

    const_reverse_iterator& operator=(const const_reverse_iterator& other) {
        if (this != &other) {
            ptr_ = other.ptr_;
        }
        return *this;
    }

    const_reverse_iterator& operator++() {
        --ptr_;
        return *this;
    }

    const_reverse_iterator operator++(int) {
        const_reverse_iterator temp = *this;
        --ptr_;
        return temp;
    }

    const_reverse_iterator& operator--() {
        ++ptr_;
        return *this;
    }

    const_reverse_iterator operator--(int) {
        const_reverse_iterator temp = *this;
        ++ptr_;
        return temp;
    }

    reference operator*() const { return *ptr_; }

    pointer operator->() const { return ptr_; }

    reference operator[](difference_type n) const { return *(*this + n); }

    bool operator==(const const_reverse_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const const_reverse_iterator& other) const {
        return ptr_ != other.ptr_;
    }

    bool operator<(const const_reverse_iterator& other) const {
        return ptr_ < other.ptr_;
    }

    bool operator>(const const_reverse_iterator& other) const {
        return ptr_ > other.ptr_;
    }

    bool operator<=(const const_reverse_iterator& other) const {
        return ptr_ <= other.ptr_;
    }

    bool operator>=(const const_reverse_iterator& other) const {
        return ptr_ >= other.ptr_;
    }

    difference_type operator-(const const_reverse_iterator& other) const {
        return ptr_ - other.ptr_;
    }

    const_reverse_iterator operator+(difference_type n) const {
        return const_reverse_iterator(ptr_ - n);
    }

    const_reverse_iterator operator-(difference_type n) const {
        return const_reverse_iterator(ptr_ + n);
    }

    const_reverse_iterator& operator+=(difference_type n) {
        ptr_ -= n;
        return *this;
    }

    const_reverse_iterator& operator-=(difference_type n) {
        ptr_ += n;
        return *this;
    }
};

}  // namespace stl