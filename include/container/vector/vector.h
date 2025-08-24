#pragma once
#include "../../algorithm/modifying/copy.h"
#include "../../algorithm/modifying/move.h"
#include "../../iterators/const_iterator.h"
#include "../../iterators/const_reverse_iterator.h"
#include "../../iterators/distance.h"
#include "../../utility/move.h"
#include "../../utility/swap.h"
#include "vector_base.h"

namespace stl {

template <typename T, typename Allocator = stl::allocator<T>>
class vector : public base::vector_base<T, Allocator> {
   public:
    using allocator_type = Allocator;
    using size_type = size_t;
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = ptrdiff_t;
    using iterator = iterator<T>;
    using const_iterator = const_iterator<T>;
    using reverse_iterator = reverse_iterator<T>;
    using const_reverse_iterator = const_reverse_iterator<T>;

   private:
    size_type calculate_new_capacity(size_type new_capacity = 0) const {
        if (new_capacity == 0) {
            return capacity() == 0 ? 1 : capacity() * 2;
        }
        return (new_capacity > (capacity() * 2)) ? new_capacity
               : (capacity() > 0)                ? capacity() * 2
                                                 : new_capacity;
    }

   public:
    vector();

    vector(const vector& other);

    vector(vector&& other) noexcept;

    vector(iterator first, iterator last);

    vector(std::initializer_list<value_type> init);

    vector(size_type n, const value_type& value = value_type{});

    ~vector();

   public:
    vector& operator=(const vector& other);

    vector& operator=(vector&& other) noexcept;

    reference operator[](size_type index) {
        return *(this->vec_storage_.start_ + index);
    }

    const_reference operator[](size_type index) const {
        return *(this->vec_storage_.start_ + index);
    }

   public:
    iterator begin() { return iterator(this->vec_storage_.start_); }

    const_iterator begin() const {
        return const_iterator(this->vec_storage_.start_);
    }

    iterator end() { return iterator(this->vec_storage_.finish_); }

    const_iterator end() const {
        return const_iterator(this->vec_storage_.finish_);
    }

    const_iterator cbegin() const {
        return const_iterator(this->vec_storage_.start_);
    }

    const_iterator cend() const {
        return const_iterator(this->vec_storage_.finish_);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(this->vec_storage_.finish_ - 1);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(this->vec_storage_.finish_ - 1);
    }

    reverse_iterator rend() {
        return reverse_iterator(this->vec_storage_.start_ - 1);
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(this->vec_storage_.start_ - 1);
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(this->vec_storage_.finish_ - 1);
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(this->vec_storage_.start_ - 1);
    }

    const_reference front() const {
        if (empty()) {
            throw std::out_of_range("索引超出范围!!!");
        }
        return *this->vec_storage_.start_;
    }

    const_reference back() const {
        if (empty()) {
            throw std::out_of_range("索引超出范围!!!");
        }
        return *(this->vec_storage_.finish_ - 1);
    }

    reference at(size_type index) {
        if (index >= size()) {
            throw std::out_of_range("索引超出范围!!!");
        }
        return *(this->vec_storage_.start_ + index);
    }

    const_reference at(size_type index) const {
        if (index >= size()) {
            throw std::out_of_range("索引超出范围!!!");
        }
        return *(this->vec_storage_.start_ + index);
    }

    pointer data() { return this->vec_storage_.start_; }

    const_pointer data() const { return this->vec_storage_.start_; }

    size_type size() const noexcept {
        if (this->vec_storage_.start_ == nullptr) {
            return 0;
        }
        return this->vec_storage_.finish_ - this->vec_storage_.start_;
    }

    size_type capacity() const noexcept {
        if (this->vec_storage_.start_ == nullptr) {
            return 0;
        }
        return this->vec_storage_.end_of_storage_ - this->vec_storage_.start_;
    }

    bool empty() const {
        return (this->vec_storage_.start_ == this->vec_storage_.finish_) ||
               (this->vec_storage_.start_ == nullptr);
    }

   public:
    iterator insert(const_iterator pos, const value_type& value);

    iterator insert(const_iterator pos, value_type&& value);

    iterator insert(const_iterator pos, size_type n, const value_type& value);

    iterator insert(const_iterator pos, iterator first, iterator last);

    iterator insert(const_iterator pos, std::initializer_list<value_type> init);

    void push_back(value_type&& value);

    void push_back(const value_type& value);

    void pop_back();

    iterator erase(const_iterator pos);

    iterator erase(const_iterator first, const_iterator last);

    void assign(size_type count, const value_type& value);

    void assign(std::initializer_list<value_type> init);

    void reserve(size_type new_cap);

    void resize(size_type new_size, const value_type& value = value_type());

    void shrink_to_fit();

    void clear();

    void swap(vector& other) noexcept;
};

template <typename T, typename Allocator>
vector<T, Allocator>::vector() : base::vector_base<T, Allocator>() {}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const vector& other)
    : base::vector_base<T, Allocator>() {
    reserve(other.size());
    for (auto& it : other) {
        this->construct(this->vec_storage_.finish_, (it));
        ++this->vec_storage_.finish_;
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other) noexcept
    : base::vector_base<T, Allocator>() {
    this->vec_storage_.start_ = std::move(other.vec_storage_.start_);
    this->vec_storage_.finish_ = std::move(other.vec_storage_.finish_);
    this->vec_storage_.end_of_storage_ =
        std::move(other.vec_storage_.end_of_storage_);
    other.vec_storage_ = {};
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(iterator first, iterator last)
    : base::vector_base<T, Allocator>() {
    size_type n = last - first;
    reserve(n);

    while (first != last) {
        this->construct(this->vec_storage_.finish_, (*first));
        ++this->vec_storage_.finish_;
        ++first;
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<value_type> init)
    : base::vector_base<T, Allocator>() {
    reserve(init.size());
    for (const auto& elem : init) {
        this->construct(this->vec_storage_.finish_, elem);
        ++this->vec_storage_.finish_;
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type n, const value_type& value)
    : base::vector_base<T, Allocator>() {
    reserve(n);
    for (size_type i = 0; i < n; ++i) {
        this->construct(this->vec_storage_.finish_, value);
        ++this->vec_storage_.finish_;
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>::~vector() {
    clear();
}

template <typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
    if (this != &other) {
        if (!empty()) {
            clear();
            this->deallocate(this->vec_storage_.start_, capacity());
        }
        reserve(other.size());
        for (auto& it : other) {
            this->construct(this->vec_storage_.finish_, (it));
            ++this->vec_storage_.finish_;
        }
        stl::copy(other.begin(), other.end(), begin());
    }
    return *this;
}

template <typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other) noexcept {
    if (this != &other) {
        if (!empty()) {
            clear();
            this->deallocate(this->vec_storage_.start_, capacity());
        }
        this->vec_storage_.start_ = std::move(other.vec_storage_.start_);
        this->vec_storage_.finish_ = std::move(other.vec_storage_.finish_);
        this->vec_storage_.end_of_storage_ =
            std::move(other.vec_storage_.end_of_storage_);
        other.vec_storage_ = {};
    }
    return *this;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
    const_iterator pos,
    const value_type& value) {
    if (&(*pos) < this->vec_storage_.start_ ||
        &(*pos) > this->vec_storage_.finish_) {
        throw std::out_of_range("迭代器超出范围!!!");
    }
    return insert(pos, 1, value);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
    const_iterator pos,
    value_type&& value) {
    if (&(*pos) < this->vec_storage_.start_ ||
        &(*pos) > this->vec_storage_.finish_) {
        throw std::out_of_range("迭代器超出范围!!!");
    }
    if (size() + 1 > capacity()) {
        size_type iterator_pos = stl::distance(cbegin(), pos);
        reserve(calculate_new_capacity());
        pos = cbegin() + iterator_pos;
    }
    stl::move_backward(iterator(pos), end(), end() + 1);
    this->construct(&(*iterator(pos)), stl::move(value));
    ++this->vec_storage_.finish_;

    return pos;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
    const_iterator pos,
    size_type n,
    const value_type& value) {
    if (&(*pos) < this->vec_storage_.start_ ||
        &(*pos) > this->vec_storage_.finish_) {
        throw std::out_of_range("迭代器超出范围!!!");
    }
    if (n == 0) {
        return pos;
    }
    if ((size() + n) > capacity()) {
        size_type iterator_pos = stl::distance(cbegin(), pos);
        reserve(calculate_new_capacity((size() + n)));
        pos = cbegin() + iterator_pos;
    }
    stl::move_backward(iterator(pos), end(), end() + n);
    auto pos_iter = iterator(pos);
    for (size_type i = 0; i < n; ++i) {
        this->construct(&(*pos_iter), value);
        ++pos_iter;
    }
    this->vec_storage_.finish_ += n;

    return pos;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
    const_iterator pos,
    iterator first,
    iterator last) {
    if (&(*pos) < this->vec_storage_.start_ ||
        &(*pos) > this->vec_storage_.finish_) {
        throw std::out_of_range("迭代器超出范围!!!");
    }
    if (first == last) {
        return pos;
    }
    size_type n = stl::distance(first, last);
    if ((size() + n) > capacity()) {
        size_type iterator_pos = stl::distance(cbegin(), pos);
        reserve(calculate_new_capacity((size() + n)));
        pos = cbegin() + iterator_pos;
    }
    stl::move_backward(iterator(pos), end(), end() + n);
    auto pos_iter = iterator(pos);
    while (first != last) {
        {
            this->construct(&(*pos_iter), (*first));
            ++pos_iter;
            ++first;
        }
    }
    this->vec_storage_.finish_ += n;
    return pos;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
    const_iterator pos,
    std::initializer_list<value_type> init) {
    if (&(*pos) < this->vec_storage_.start_ ||
        &(*pos) > this->vec_storage_.finish_) {
        throw std::out_of_range("迭代器超出范围!!!");
    }
    size_type n = init.size();
    if (n == 0) {
        return pos;
    }
    if ((size() + n) > capacity()) {
        size_type iterator_pos = stl::distance(cbegin(), pos);
        reserve(calculate_new_capacity((size() + n)));
        pos = cbegin() + iterator_pos;
    }
    stl::move_backward(iterator(pos), end(), end() + n);
    auto pos_iter = iterator(pos);
    for (auto& it : init) {
        this->construct(&(*pos_iter), it);
    }
    this->vec_storage_.finish_ += n;
    return pos;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(value_type&& value) {
    if (size() + 1 > capacity()) {
        reserve(calculate_new_capacity());
    }
    this->construct(this->vec_storage_.finish_, stl::move(value));
    ++this->vec_storage_.finish_;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(const value_type& value) {
    if (size() + 1 > capacity()) {
        reserve(calculate_new_capacity());
    }
    this->construct(this->vec_storage_.finish_, value);
    ++this->vec_storage_.finish_;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::pop_back() {
    if (!empty()) {
        --this->vec_storage_.finish_;
        this->destroy(this->vec_storage_.finish_);
    }
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(
    const_iterator pos) {
    if (&(*pos) < this->vec_storage_.start_ ||
        &(*pos) > this->vec_storage_.finish_) {
        throw std::out_of_range("迭代器超出范围!!!");
    }
    if (pos == end()) {
        pop_back();
    }
    destroy(&(*pos));
    stl::move(iterator(pos) + 1, end(), iterator(pos));
    --this->vec_storage_.finish_;

    return pos;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(
    const_iterator first,
    const_iterator last) {
    if (&(*first) < this->vec_storage_.start_ ||
        &(*last) > this->vec_storage_.finish_ || first > last) {
        throw std::out_of_range("迭代器超出范围!!!");
    }
    if (first == last) {
        return first;
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::assign(size_type count, const value_type& value) {}

template <typename T, typename Allocator>
void vector<T, Allocator>::assign(std::initializer_list<value_type> init) {}

template <typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type new_cap) {
    if (new_cap > capacity()) {
        pointer new_start = this->allocate(new_cap);
        pointer new_finish = new_start + size();
        stl::move(this->vec_storage_.start_, this->vec_storage_.finish_,
                  new_start);
        this->deallocate(this->vec_storage_.start_, capacity());
        this->vec_storage_.start_ = new_start;
        this->vec_storage_.finish_ = new_finish;
        this->vec_storage_.end_of_storage_ = new_start + new_cap;
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::resize(size_type new_size, const value_type& value) {
    if (new_size < size()) {
        for (size_type i = new_size; i < size(); ++i) {
            this->destroy(this->vec_storage_.start_ + i);
        }
        this->vec_storage_.finish_ = this->vec_storage_.start_ + new_size;
    } else {
        if (new_size > capacity()) {
            reserve(calculate_new_capacity(new_size));
        }
        for (size_type i = size(); i < new_size; ++i) {
            this->construct(this->vec_storage_.finish_, value);
            ++this->vec_storage_.finish_;
        }
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::shrink_to_fit() {
    if (!empty()) {
        pointer new_start = this->allocate(size());
        pointer new_finish = new_start + size();
        stl::move(this->vec_storage_.start_, this->vec_storage_.finish_,
                  new_start);
        this->deallocate(this->vec_storage_.start_, capacity());
        this->vec_storage_.start_ = new_start;
        this->vec_storage_.finish_ = new_finish;
        this->vec_storage_.end_of_storage_ = new_start + size();
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::clear() {
    if (!empty()) {
        for (auto& it : *this) {
            this->destroy(&it);
        }
        this->vec_storage_.finish_ = this->vec_storage_.start_;
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::swap(vector& other) noexcept {
    stl::swap(this->vec_storage_, other.vec_storage_);
    stl::swap(this->allocator_, other.allocator_);
}

}  // namespace stl
