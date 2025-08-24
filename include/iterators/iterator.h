#pragma once
#include <cstdint>
#include "iterator_tag.h"

namespace stl {

template <typename U>
class const_iterator;

template <typename T>
class iterator {
   public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = iterator_tag::random_access_iterator_tag;

   private:
    pointer ptr_;

    template <typename U>
    friend class const_iterator;

   public:
    iterator(pointer ptr = nullptr) : ptr_(ptr) {}

    iterator(const iterator& other) : ptr_(other.ptr_) {}

    iterator(const const_iterator<T>& c_iterator)
        : ptr_(const_cast<pointer>(c_iterator.ptr_)) {}

    iterator& operator=(const iterator& other) {
        if (this != &other) {
            ptr_ = other.ptr_;
        }
        return *this;
    }

    iterator& operator++() {
        ++ptr_;
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    iterator& operator--() {
        --ptr_;
        return *this;
    }

    iterator operator--(int) {
        iterator temp = *this;
        --(*this);
        return temp;
    }

    reference& operator*() { return *ptr_; }

    pointer operator->() { return ptr_; }

    reference operator[](difference_type n) { return *(ptr_ + n); }

    bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }

    bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }

    bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }

    bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }

    bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }

    bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }

    difference_type operator-(const iterator& other) const {
        return ptr_ - other.ptr_;
    }

    iterator operator+(difference_type n) const { return iterator(ptr_ + n); }

    iterator operator-(difference_type n) const { return iterator(ptr_ - n); }

    iterator& operator+=(difference_type n) {
        ptr_ += n;
        return *this;
    }

    iterator& operator-=(difference_type n) {
        ptr_ -= n;
        return *this;
    }
};

}  // namespace stl