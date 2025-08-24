#pragma once
#include "../../utility/move.h"

namespace stl {

namespace detail {}

template <typename InputIt, typename OutputIt>
OutputIt move(InputIt first, InputIt last, OutputIt d_first) {
    while (first != last) {
        *d_first++ = stl::move(*first++);
    }
    return d_first;
}

template <typename BidirIt1, typename BidirIt2>
BidirIt2 move_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_first) {
    while (first != last) {
        *--d_first = stl::move(*--last);
    }
    return d_first;
}

}  // namespace stl
