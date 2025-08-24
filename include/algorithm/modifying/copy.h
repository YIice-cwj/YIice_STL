#pragma once
#include "../../type_traits/is_iterator.h"
#include "../../type_traits/is_trivially_copyable.h"
#include "../../utility/min.h"
#include "iterator.h"
#include "iterator_traits.h"

namespace stl {

namespace detail {

template <typename Src, typename Dest>
Dest copy_unroll_4x(Src first, Src last, Dest d_first) {
    while ((first + 4) <= last) {
        d_first[0] = first[0];
        d_first[1] = first[1];
        d_first[2] = first[2];
        d_first[3] = first[3];
        first += 4;
        d_first += 4;
    }
    while (first != last) {
        *d_first++ = *first++;
    }
    return d_first;
}

template <typename Src, typename Dest>
Dest copy_blocked(Src first, Src last, Dest d_first) {
    const size_t block_size = 64;

    while (true) {
        ptrdiff_t n = last - first;
        if (n <= 0)
            break;

        size_t count = min(static_cast<size_t>(n), block_size / sizeof(*first));

        for (size_t i = 0; i < count; ++i) {
            d_first[i] = first[i];
        }

        first += count;
        d_first += count;
    }
    return d_first;
}

template <typename InputIt, typename OutputIt>
OutputIt copy(InputIt first,
              InputIt last,
              OutputIt d_first,
              iterator_tag::input_iterator_tag) {
    while (first != last) {
        *d_first++ = *first++;
    }
    return d_first;
}

template <typename ForwardIt, typename OutputIt>
OutputIt copy(ForwardIt first,
              ForwardIt last,
              OutputIt d_first,
              iterator_tag::forward_iterator_tag) {
    ptrdiff_t n = stl::distance(first, last);
    size_t count = n / 2;
    size_t remaining = n % 2;
    for (size_t i = 0; i < count; i++) {
        *d_first++ = *first++;
        *d_first++ = *first++;
    }

    if (remaining) {
        *d_first++ = *first++;
    }

    return d_first;
}

template <typename BidirectionalIt, typename OutputIt>
OutputIt copy(BidirectionalIt first,
              BidirectionalIt last,
              OutputIt d_first,
              iterator_tag::bidirectional_iterator_tag) {
    ptrdiff_t n = stl::distance(first, last);

    size_t count = n / 4;
    size_t remaining = n % 4;
    for (size_t i = 0; i < count; i++) {
        *d_first++ = *first++;
        *d_first++ = *first++;
        *d_first++ = *first++;
        *d_first++ = *first++;
    }

    for (size_t i = 0; i < remaining; i++) {
        *d_first++ = *first++;
    }

    return d_first;
}

template <typename RandomAccessIt>
RandomAccessIt copy(RandomAccessIt first,
                    RandomAccessIt last,
                    RandomAccessIt d_first,
                    iterator_tag::random_access_iterator_tag) {
    size_t n = last - first;

    if (n < 32) {
        for (size_t i = 0; i < n; i++) {
            d_first[i] = first[i];
        }
    } else if (n < 1024) {
        return copy_unroll_4x(first, last, d_first);
    } else {
        return copy_blocked(first, last, d_first);
    }
    return d_first + n;
}

template <typename RandomAccessIt, typename OutputIt>
OutputIt copy(RandomAccessIt first,
              RandomAccessIt last,
              OutputIt d_first,
              iterator_tag::random_access_iterator_tag) {
    size_t n = last - first;

    if (n < 32) {
        for (size_t i = 0; i < n; i++) {
            *d_first++ = first[i];
        }
    } else if (n < 1024) {
        while ((first + 4) <= last) {
            *d_first++ = first[0];
            *d_first++ = first[1];
            *d_first++ = first[2];
            *d_first++ = first[3];
            first += 4;
        }
        while (first != last) {
            *d_first++ = *first++;
        }

    } else {
        size_t block_size = 64;
        size_t num_blocks = n / block_size;
        for (size_t i = 0; i < num_blocks; ++i) {
            for (size_t j = 0; j < block_size / sizeof(*first); ++j) {
                *d_first++ = first[i * block_size / sizeof(*first) + j];
            }
        }
        for (size_t i = num_blocks * block_size / sizeof(*first); i < n; ++i) {
            *d_first++ = first[i];
        }
    }
    return d_first;
}

void memory_copy(const void* src, void* dest, size_t n, true_type) {
    const uint8_t* src_bytes_8 = reinterpret_cast<const uint8_t*>(src);
    uint8_t* dest_bytes_8 = reinterpret_cast<uint8_t*>(dest);
    // 处理内存对齐
    while (n > 0 && (reinterpret_cast<uintptr_t>(dest_bytes_8) & 7) != 0 &&
           (reinterpret_cast<uintptr_t>(src_bytes_8) & 7) != 0) {
        *dest_bytes_8++ = *src_bytes_8++;
        --n;
    }

    const uint64_t* src_bytes_64 =
        reinterpret_cast<const uint64_t*>(src_bytes_8);
    uint64_t* dest_bytes_64 = reinterpret_cast<uint64_t*>(dest_bytes_8);

    size_t count = n / 8;
    size_t remaining = n % 8;
    if (n < 32) {
        for (size_t i = 0; i < count; i++) {
            dest_bytes_64[i] = src_bytes_64[i];
        }

        char* dest_bytes_8 = reinterpret_cast<char*>(dest_bytes_64 + count);
        const char* src_bytes_8 =
            reinterpret_cast<const char*>(src_bytes_64 + count);

        for (size_t i = 0; i < remaining; i++) {
            dest_bytes_8[i] = src_bytes_8[i];
        }
    } else if (n < 1024) {
        copy_unroll_4x(src_bytes_64, src_bytes_64 + count, dest_bytes_64);
    } else {
        copy_blocked(src_bytes_64, src_bytes_64 + count, dest_bytes_64);
    }
}

template <typename T>
void memory_copy(const T* src, T* dest, size_t n, false_type) {
    n = n / sizeof(T);
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// 迭代器分发
template <typename Iterator, typename OutputIt>
OutputIt copy(Iterator first, Iterator last, OutputIt d_first, true_type) {
    return copy(first, last, d_first, iterator_category_t<Iterator>{});
}

// 指针特化
template <typename T>
T* copy(const T* first, const T* last, T* d_first, true_type) {
    size_t n = static_cast<size_t>(last - first);
    memory_copy(first, d_first, n * sizeof(T),
                bool_constant<is_trivially_copyable_v<T>>{});
    return d_first + n;
}

// 类型不同的指针 - 回退到迭代器分发
template <typename Src_T, typename Dest_T>
Dest_T copy(Src_T* first, Src_T* last, Dest_T* d_first, false_type) {
    return copy(first, last, d_first, true_type{});
}

}  // namespace detail

/**
 * @brief 将范围 [first, last) 的元素复制到 d_first 中
 * @tparam Iterator 源范围迭代器类型
 * @tparam OutputIt 目标范围迭代器类型
 * @param first 源范围起始迭代器
 * @param last 源范围结束迭代器
 * @param d_first 目标范围起始迭代器
 * @return OutputIt 目标范围的结束迭代器
 */
template <typename Iterator, typename OutputIt>
OutputIt copy(Iterator first, Iterator last, OutputIt d_first) {
    if (first == last)
        return d_first;
    return detail::copy(first, last, d_first,
                        bool_constant<is_iterator_v<Iterator>>{});
}

/**
 * @brief 将范围 [first, last) 符合条件的元素复制到 d_first 中
 * @tparam InputIt 源范围迭代器类型
 * @tparam OutputIt 目标范围迭代器类型
 * @tparam UnaryPredicate 元函数类型
 * @param first 源范围起始迭代器
 * @param last 源范围结束迭代器
 * @param d_first 目标范围起始迭代器
 * @param pred 元函数，用于判断元素是否符合条件
 * @return OutputIt 目标范围的结束迭代器
 */
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt copy_if(InputIt first,
                 InputIt last,
                 OutputIt d_first,
                 UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            *d_first++ = *first;
        }
        ++first;
    }
    return d_first;
}

/**
 * @brief 将范围 [first, last) 的n个元素复制到 d_first 中
 * @tparam InputIt 源范围迭代器类型
 * @tparam Size 整数类型，表示要复制的元素数量
 * @tparam OutputIt 目标范围迭代器类型
 * @param first 源范围起始迭代器
 * @param d_first 目标范围起始迭代器
 * @return OutputIt 目标范围的结束迭代器
 */
template <typename InputIt, typename Size, typename OutputIt>
OutputIt copy_n(InputIt first, Size n, OutputIt d_first) {
    if (n <= 0)
        return d_first;
    return copy(first, advance(first, n), d_first);
}
/**
 * @brief 将范围 [first, last) 的元素复制到 d_last 中
 * @tparam BidirIt1 源范围迭代器类型
 * @tparam BidirIt2 目标范围迭代器类型
 * @param first 源范围起始迭代器
 * @param last 源范围结束迭代器
 * @param d_last 目标范围结束迭代器
 * @return BidirIt2 目标范围的结束迭代器
 */
template <typename BidirIt1, typename BidirIt2>
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last) {
    while (first != last) {
        *--d_last = *--last;
    }
    return d_last;
}

}  // namespace stl