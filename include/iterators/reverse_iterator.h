#pragma once
#include "iterator_tag.h"

namespace stl {

template <typename T>
class reverse_iterator {
   public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = iterator_tag::bidirectional_iterator_tag;

   private:
    pointer ptr_;

   public:
    reverse_iterator(pointer ptr = nullptr) : ptr_(ptr) {}

    reverse_iterator(const reverse_iterator& other) : ptr_(other.ptr_) {}

    reverse_iterator& operator=(const reverse_iterator& other) {
        if (this != &other) {
            ptr_ = other.ptr_;
        }
        return *this;
    }

    reverse_iterator& operator++() {
        --ptr_;
        return *this;
    }

    reverse_iterator operator++(int) {
        reverse_iterator temp = *this;
        --ptr_;
        return temp;
    }

    reverse_iterator& operator--() {
        ++ptr_;
        return *this;
    }

    reverse_iterator operator--(int) {
        reverse_iterator temp = *this;
        ++ptr_;
        return temp;
    }

    reference operator*() const { return *ptr_; }

    pointer operator->() const { return ptr_; }

    reference operator[](difference_type n) const { return *(*this + n); }

    bool operator==(const reverse_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const reverse_iterator& other) const {
        return ptr_ != other.ptr_;
    }

    bool operator<(const reverse_iterator& other) const {
        return ptr_ < other.ptr_;
    }

    bool operator>(const reverse_iterator& other) const {
        return ptr_ > other.ptr_;
    }

    bool operator<=(const reverse_iterator& other) const {
        return ptr_ <= other.ptr_;
    }

    bool operator>=(const reverse_iterator& other) const {
        return ptr_ >= other.ptr_;
    }

    difference_type operator-(const reverse_iterator& other) const {
        return ptr_ - other.ptr_;
    }

    reverse_iterator operator+(difference_type n) const {
        return reverse_iterator(ptr_ - n);
    }

    reverse_iterator operator-(difference_type n) const {
        return reverse_iterator(ptr_ + n);
    }

    reverse_iterator& operator+=(difference_type n) {
        ptr_ -= n;
        return *this;
    }

    reverse_iterator& operator-=(difference_type n) {
        ptr_ += n;
        return *this;
    }
};

}  // namespace stl