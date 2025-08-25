#pragma once
#include <cstdint>

namespace stl {

namespace detail {
void mecopy_small(void* dest, const void* src, size_t size) {
    char* dest_byte8 = static_cast<char*>(dest);
    const char* src_byte8 = static_cast<const char*>(src);

    switch (size) {
        case 1:
            *dest_byte8 = *src_byte8;
            return;
        case 2:
            *reinterpret_cast<uint16_t*>(dest_byte8) =
                *reinterpret_cast<const uint16_t*>(src_byte8);
            return;
        case 4:
            *reinterpret_cast<uint32_t*>(dest_byte8) =
                *reinterpret_cast<const uint32_t*>(src_byte8);
            return;
        case 8:
            *reinterpret_cast<uint64_t*>(dest_byte8) =
                *reinterpret_cast<const uint64_t*>(src_byte8);
            return;
        default:
            if (size >= 16) {
                *reinterpret_cast<uint64_t*>(dest_byte8) =
                    *reinterpret_cast<const uint64_t*>(src_byte8);
                *reinterpret_cast<uint64_t*>(dest_byte8 + size - 8) =
                    *reinterpret_cast<const uint64_t*>(src_byte8 + size - 8);
                return;
            } else {
                for (size_t i = 0; i < size; ++i) {
                    dest_byte8[i] = src_byte8[i];
                }
            }
    }
}

void mecopy_forward(void* dest, const void* src, size_t size) {
    char* dest_byte8 = static_cast<char*>(dest);
    const char* src_byte8 = static_cast<const char*>(src);

    while (size > 0 && (reinterpret_cast<uintptr_t>(dest_byte8) & 7) != 0) {
        *dest_byte8++ = *src_byte8++;
        --size;
    }

    while (size >= 64) {
        uint64_t* dest_byte64 = reinterpret_cast<uint64_t*>(dest_byte8);
        const uint64_t* src_byte64 =
            reinterpret_cast<const uint64_t*>(src_byte8);

        dest_byte64[0] = src_byte64[0];
        dest_byte64[1] = src_byte64[1];
        dest_byte64[2] = src_byte64[2];
        dest_byte64[3] = src_byte64[3];
        dest_byte64[4] = src_byte64[4];
        dest_byte64[5] = src_byte64[5];
        dest_byte64[6] = src_byte64[6];
        dest_byte64[7] = src_byte64[7];

        dest_byte8 += 64;
        src_byte8 += 64;
        size -= 64;
    }

    while (size >= 8) {
        *reinterpret_cast<uint64_t*>(dest_byte8) =
            *reinterpret_cast<const uint64_t*>(src_byte8);
        dest_byte8 += 8;
        src_byte8 += 8;
        size -= 8;
    }

    while (size > 0) {
        *dest_byte8++ = *src_byte8++;
        --size;
    }
}

void mecopy_backward(void* dest, const void* src, size_t size) {
    char* dest_byte8 = static_cast<char*>(dest) + size;
    const char* src_byte8 = static_cast<const char*>(src) + size;

    while (size > 0 && (reinterpret_cast<uintptr_t>(dest_byte8) & 7) != 0) {
        *--dest_byte8 = *--src_byte8;
        --size;
    }

    while (size >= 64) {
        dest_byte8 -= 64;
        src_byte8 -= 64;

        uint64_t* dest_byte64 = reinterpret_cast<uint64_t*>(dest_byte8);
        const uint64_t* src_byte64 =
            reinterpret_cast<const uint64_t*>(src_byte8);

        dest_byte64[7] = src_byte64[7];
        dest_byte64[6] = src_byte64[6];
        dest_byte64[5] = src_byte64[5];
        dest_byte64[4] = src_byte64[4];
        dest_byte64[3] = src_byte64[3];
        dest_byte64[2] = src_byte64[2];
        dest_byte64[1] = src_byte64[1];
        dest_byte64[0] = src_byte64[0];

        size -= 64;
    }

    while (size >= 8) {
        dest_byte8 -= 8;
        src_byte8 -= 8;
        *reinterpret_cast<uint64_t*>(dest_byte8) =
            *reinterpret_cast<const uint64_t*>(src_byte8);
        size -= 8;
    }
    while (size > 0) {
        *--dest_byte8 = *--src_byte8;
        --size;
    }
}

void* mecopy(void* dest, const void* src, size_t size) {
    if (size <= 32) {
        mecopy_small(dest, src, size);
        return dest;
    }

    uintptr_t dest_addr = reinterpret_cast<uintptr_t>(dest);
    uintptr_t src_addr = reinterpret_cast<uintptr_t>(src);

    if (dest_addr < src_addr) {
        mecopy_forward(dest, src, size);
    } else if (dest_addr > src_addr + size || src_addr > dest_addr + size) {
        mecopy_forward(dest, src, size);
    } else {
        mecopy_backward(dest, src, size);
    }
    return dest;
}

}  // namespace detail

/**
 * @brief 内存拷贝
 * @param dest 目标地址
 * @param src 源地址
 * @param size 拷贝大小
 */
void* mecopy(void* dest, const void* src, size_t size) {
    if (dest == src || size == 0)
        return dest;
    return detail::mecopy(dest, src, size);
}

}  // namespace stl