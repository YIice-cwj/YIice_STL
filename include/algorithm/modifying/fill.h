#pragma once

namespace stl {

template <typename ForwardIt, typename T>
void fill(ForwardIt first, ForwardIt last, const T& value) {
    while (first != last) {
        *first++ = value;
    }
}

template <typename OutputIt, typename Size, typename T>
OutputIt fill_n(OutputIt first, Size n, const T& value) {
    for (Size i = 0; i < n; ++i) {
        *first++ = value;
    }
    return first;
}

}  // namespace stl
