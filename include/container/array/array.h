#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include "../../algorithm/modifying/copy.h"
#include "../../algorithm/modifying/fill.h"
#include "../../algorithm/non_modifying/equal.h"
#include "../../algorithm/non_modifying/lexicographical_compare.h"
#include "../../iterators/const_iterator.h"
#include "../../iterators/const_reverse_iterator.h"
#include "../../utility/swap.h"

namespace stl {
template <typename T, size_t N>
class array {
   public:
    using value_type = T;
    using size_type = size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = ptrdiff_t;
    using iterator = iterator<value_type>;
    using const_iterator = const_iterator<value_type>;
    using reverse_iterator = reverse_iterator<value_type>;
    using const_reverse_iterator = const_reverse_iterator<value_type>;

   private:
    value_type element_[N];
    size_type size_;

   public:
    constexpr array() : size_(N) {}

    constexpr array(array&& other) : size_(other.size_) {
        stl::copy(other.element_, element_, size_);
        other.size_ = 0;
    }

    constexpr array(const array& other) : size_(other.size_) {
        stl::copy(other.element_, element_, size_);
    }

    constexpr array(std::initializer_list<value_type> init)
        : size_(init.size()) {
        if (size_ > N) {
            throw std::length_error("初始化列表大小超过数组容量!!!");
        }
        auto it = init.begin();
        for (size_type i = 0; i < size_; ++i) {
            element_[i] = *it++;
        }
    }

    ~array() {}

   public:
    iterator begin() { return iterator(element_); }

    iterator end() { return iterator(element_ + size_); }

    const_iterator begin() const { return const_iterator(element_); }

    const_iterator end() const { return const_iterator(element_ + size_); }

    const_iterator cbegin() const { return const_iterator(element_); }

    const_iterator cend() const { return const_iterator(element_ + size_); }

    reverse_iterator rbegin() { return reverse_iterator(element_ + size_ - 1); }

    reverse_iterator rend() { return reverse_iterator(element_ - 1); }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(element_ + size_ - 1);
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(element_ - 1);
    }

    reference front() { return element_[0]; }

    const_reference front() const { return element_[0]; }

    reference back() { return element_[size_ - 1]; }

    const_reference back() const { return element_[size_ - 1]; }

    pointer data() { return element_; }

    const_pointer data() const { return element_; }

    size_type size() const { return size_; }

    size_type max_size() const { return N; }

    bool empty() const { return size_ == 0; }

    void fill(const value_type& value) { stl::fill(begin(), end(), value); }

    void swap(array& other) noexcept {
        if (this != &other) {
            stl::swap(element_, other.element_);
            stl::swap(size_, other.size_);
        }
    }

   public:
    array& operator=(const array& other) {
        if (this != &other) {
            size_ = other.size_;
            stl::copy(other.element_, element_, size_);
        }
        return *this;
    }

    array& operator=(array&& other) {
        if (this != &other) {
            size_ = other.size_;
            stl::copy(other.element_, element_, size_);
            other.size_ = 0;
        }
        return *this;
    }

    array& operator=(std::initializer_list<value_type> init) {
        if (init.size() > N) {
            throw std::length_error("初始化列表大小超过数组容量!!!");
        }
        size_ = init.size();
        stl::copy(init.begin(), begin(), size_);
        return *this;
    }

    reference operator[](size_type index) {
        if (index >= size_) {
            throw std::out_of_range("数组下标越界!!!");
        }
        return element_[index];
    }

    const_reference operator[](size_type index) const {
        if (index >= size_) {
            throw std::out_of_range("数组下标越界!!!");
        }
        return element_[index];
    }

    bool operator==(const array& other) const {
        if (size_ != other.size_)
            return false;
        return stl::equal(begin(), end(), other.begin());
    }

    bool operator!=(const array& other) const { return !(*this == other); }

    bool operator<(const array& other) const {
        return stl::lexicographical_compare(begin(), end(), other.begin(),
                                            other.end());
    }

    bool operator<=(const array& other) const { return !(other < *this); }

    bool operator>(const array& other) const { return other < *this; }

    bool operator>=(const array& other) const { return !(*this < other); }
};
}  // namespace stl
