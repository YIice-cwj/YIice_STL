#pragma once
#include "../../memory/allocator.h"

namespace stl {
namespace base {

template <typename T, typename Allocator = stl::allocator<T>>
class vector_base {
   protected:
    using allocator_type = Allocator;
    using value_type = T;
    using size_type = size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = ptrdiff_t;

   protected:
    struct vector_impl {
        pointer start_;           // 数据开始指针
        pointer finish_;          // 数据结束指针
        pointer end_of_storage_;  // 存储结束指针

        vector_impl()
            : start_(nullptr), finish_(nullptr), end_of_storage_(nullptr) {}
    };

   protected:
    vector_impl vec_storage_;  // 向量存储
    allocator_type allocator_;

   protected:
    pointer allocate(size_type n) {
        return n != 0 ? allocator_.allocate(n) : nullptr;
    }

    void construct(pointer p, const_reference value) {
        allocator_.construct(p, value);
    }

    void destroy(pointer p) { allocator_.destroy(p); }

    void deallocate(pointer ptr, size_type n) { allocator_.deallocate(ptr, n); }

    virtual ~vector_base() {
        if (vec_storage_.start_) {
            deallocate(vec_storage_.start_,
                       vec_storage_.end_of_storage_ - vec_storage_.start_);
        }
    }
};

}  // namespace base

}  // namespace stl