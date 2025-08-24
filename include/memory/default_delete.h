#pragma once

namespace stl {

template <typename T>
struct default_delete {
    void operator()(T* ptr) { delete ptr; }
};

template <typename T>
struct default_delete<T[]> {
    void operator()(T* ptr) { delete[] ptr; }
};

}  // namespace stl