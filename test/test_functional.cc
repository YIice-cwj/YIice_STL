#include <cassert>
#include <iostream>
#include "functional.h"
#define TEST_TYPE_EQUAL(type1, type2, test_name)                               \
    do {                                                                       \
        bool result = is_same<type1, type2>::value;                            \
        std::cout << "[" << (result ? " 通过 " : " 失败 ") << "]  "            \
                  << test_name << std::endl;                                   \
        if (!result) {                                                         \
            std::cout << "  预期: " << typeid(type2).name() << std::endl;      \
            std::cout << "  实际:      " << typeid(type1).name() << std::endl; \
        }                                                                      \
        assert(result);                                                        \
    } while (false)

#define TEST_BOOL_EQUAL(bool_type1, bool_type2, test_name)          \
    do {                                                            \
        std::cout << std::boolalpha;                                \
        bool result = (bool_type1 == bool_type2);                   \
        std::cout << "[" << (result ? " 通过 " : " 失败 ") << "]  " \
                  << test_name << std::endl;                        \
        if (!result) {                                              \
            std::cout << "  预期: " << bool_type2 << std::endl;     \
            std::cout << "  实际: " << bool_type1 << std::endl;     \
        }                                                           \
        assert(result);                                             \
    } while (false)

int main() {
    std::cout << "------------functional 测试------------" << std::endl;
    try {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "全部通过! ✅" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "测试失败!: " << e.what() << " ❌" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        return 1;
    }
    return 0;
}