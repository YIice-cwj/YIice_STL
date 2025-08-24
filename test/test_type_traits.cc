#include <cassert>
#include <iostream>
#include <type_traits>
#include "type_traits.h"
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
using namespace stl;

// 测试联合体
union TestUnion {
    int a;
    float b;
};

// 测试枚举
enum TestEnum { A, B, C };

// 测试基类
class TestBase {
   public:
    virtual void test_func() {}
};

// 测试派生类
class TestDerived : public TestBase {
   public:
    void test_func() override {}
};

// 测试类
class TestClass {
   public:
    int test_member;

    TestClass() {}

    TestClass(int) {}

    TestClass(int, int) {}

    void test_func() {}

    void test_func(int) {}

    void test_func(int, int) {}
};

// 无默认构造函数类
class TestNoDefaultConstructor {
   public:
    TestNoDefaultConstructor(int) {}
};

// 无拷贝构造函数类
class TestNoCopyConstructor {
   public:
    TestNoCopyConstructor() {}
    TestNoCopyConstructor(const TestNoCopyConstructor&) = delete;
};

// 无移动构造函数类
class TestNoMoveConstructor {
   public:
    TestNoMoveConstructor() {}
    TestNoMoveConstructor(TestNoMoveConstructor&&) = delete;
};

// 无拷贝赋值函数类
class TestNoCopyAssignment {
   public:
    TestNoCopyAssignment() {}
    TestNoCopyAssignment& operator=(const TestNoCopyAssignment&) = delete;
};

// 无移动赋值函数类
class TestNoMoveAssignment {
   public:
    TestNoMoveAssignment() {}
    TestNoMoveAssignment& operator=(TestNoMoveAssignment&&) = delete;
};

// 不可交换类
class TestNoSwap {
   public:
    TestNoSwap() {}
    TestNoSwap(const TestNoSwap&) = delete;
    TestNoSwap(TestNoSwap&&) = delete;
    TestNoSwap& operator=(const TestNoSwap&) = delete;
    TestNoSwap& operator=(TestNoSwap&&) = delete;
    void swap(TestNoSwap&) = delete;  // 没有swap函数
};

// 异常交换类
class TestSwapThrow {
   public:
    TestSwapThrow() {}
    TestSwapThrow(const TestSwapThrow&) noexcept(false);
    TestSwapThrow(TestSwapThrow&&) noexcept(false);
    TestSwapThrow& operator=(const TestSwapThrow&) noexcept(false);
    TestSwapThrow& operator=(TestSwapThrow&&) noexcept(false);
    void swap(TestSwapThrow&) noexcept(false) {}
};

// 测试构造类(有异常)
class TestConstructorThrow {
   public:
    TestConstructorThrow() noexcept(false) {}
    TestConstructorThrow(int) noexcept(false) {}
    TestConstructorThrow(int, int) noexcept(false) {}
    TestConstructorThrow(TestConstructorThrow&&) noexcept(false) {}
    TestConstructorThrow(const TestConstructorThrow&) noexcept(false) {}
    ~TestConstructorThrow() {}
};

// 测试构造类(无异常)
class TestConstructorNothrow {
   public:
    TestConstructorNothrow() noexcept {}
    TestConstructorNothrow(int) noexcept {}
    TestConstructorNothrow(int, int) noexcept {}
    TestConstructorNothrow(TestConstructorNothrow&&) noexcept {}
    TestConstructorNothrow(const TestConstructorNothrow&) noexcept {}
};

// 测试赋值类(有异常)
class TestAssignmentThrow {
   public:
    TestAssignmentThrow() noexcept(false) {}

    TestAssignmentThrow(int) noexcept(false) {}

    TestAssignmentThrow(const TestAssignmentThrow&) noexcept(false) {}

    TestAssignmentThrow(TestAssignmentThrow&&) noexcept(false) {}

    TestAssignmentThrow& operator=(const TestAssignmentThrow&) noexcept(false) {
        return *this;
    }
    TestAssignmentThrow& operator=(TestAssignmentThrow&&) noexcept(false) {
        return *this;
    }
};

// 测试赋值类(无异常)
class TestAssignmentNothrow {
   public:
    TestAssignmentNothrow() noexcept {}

    TestAssignmentNothrow(int) noexcept {}

    TestAssignmentNothrow(const TestAssignmentNothrow&) noexcept {}

    TestAssignmentNothrow(TestAssignmentNothrow&&) noexcept {}

    TestAssignmentNothrow& operator=(const TestAssignmentNothrow&) noexcept {
        return *this;
    }
    TestAssignmentNothrow& operator=(TestAssignmentNothrow&&) noexcept {
        return *this;
    }
};

// 测试析构类(有异常)
class TestDestructorThrow {
   public:
    ~TestDestructorThrow() noexcept(false) {}
};

// 测试析构类(无异常)
class TestDestructorNothrow {
   public:
    ~TestDestructorNothrow() noexcept {}
};

// 测试函数
void test_func() {}

// ==============================
// void_t 测试
// ===============================
void test_void_t() {
    std::cout << '\n' << "------------void_t 测试------------" << std::endl;
    TEST_TYPE_EQUAL(void_t<int>, void, "void_t<int> ---> void");
    TEST_TYPE_EQUAL(void_t<int&>, void, "void_t<int&> ---> void");
    TEST_TYPE_EQUAL(void_t<int&&>, void, "void_t<int&&> ---> void");
    TEST_TYPE_EQUAL(void_t<int*>, void, "void_t<int*> ---> void");
    TEST_TYPE_EQUAL(void_t<const int>, void, "void_t<const int> ---> void");
    TEST_TYPE_EQUAL(void_t<const volatile int>, void,
                    "void_t<const volatile int> ---> void");
    TEST_TYPE_EQUAL(void_t<int[10]>, void, "void_t<int[10]> ---> void");
    TEST_TYPE_EQUAL(void_t<int[]>, void, "void_t<int[]> ---> void");
    TEST_TYPE_EQUAL(void_t<decltype(test_func)>, void,
                    "void_t<decltype(test_func)> ---> void");
    TEST_TYPE_EQUAL(void_t<TestClass>, void, "void_t<TestClass> ---> void");
    TEST_TYPE_EQUAL(void_t<int (*)()>, void,
                    "void_t<int (*)()TestClass> ---> void");
}

// ==============================
// decay 测试
// ===============================
void test_decay() {
    std::cout << '\n' << "------------decay 测试------------" << std::endl;
    TEST_TYPE_EQUAL(decay<int>::type, int, "decay<int> ---> int");
    TEST_TYPE_EQUAL(decay<int&>::type, int, "decay<int&> ---> int");
    TEST_TYPE_EQUAL(decay<int&&>::type, int, "decay<int&&> ---> int");
    TEST_TYPE_EQUAL(decay<int*>::type, int*, "decay<int*> ---> int*");
    TEST_TYPE_EQUAL(decay<const int>::type, int, "decay<const int> ---> int");
    TEST_TYPE_EQUAL(decay<const volatile int>::type, int,
                    "decay<const volatile int> ---> int");
    TEST_TYPE_EQUAL(decay<int[10]>::type, int*, "decay<int[10]> ---> int*");
    TEST_TYPE_EQUAL(decay<int[]>::type, int*, "decay<int[]> ---> int*");
    TEST_TYPE_EQUAL(decay<decltype(test_func)>::type, void (*)(),
                    "decay<decltype(test_func)> ---> void (*)()");
    TEST_TYPE_EQUAL(decay<const int>::type, int, "decay<const int> ---> int");
    TEST_TYPE_EQUAL(decay<const int&>::type, int, "decay<const int&> ---> int");
    TEST_TYPE_EQUAL(decay<const int&&>::type, int,
                    "decay<const int&&> ---> int");
    TEST_TYPE_EQUAL(decay<const int*>::type, const int*,
                    "decay<const int*> ---> const int*");
    TEST_TYPE_EQUAL(decay<const int[10]>::type, const int*,
                    "decay<const int[10]> ---> const int*");
    TEST_TYPE_EQUAL(decay<const int[]>::type, const int*,
                    "decay<const int[]> ---> const int*");
}

// ===============================
// add_const 测试
// ===============================
void test_add_const() {
    std::cout << '\n' << "------------add_const 测试------------" << std::endl;
    TEST_TYPE_EQUAL(add_const<int>::type, const int,
                    "add_const<int> ---> const int");
    TEST_TYPE_EQUAL(add_const<double>::type, const double,
                    "add_const<double> ---> const double");

    TEST_TYPE_EQUAL(add_const<const int>::type, const int,
                    "add_const<const int> ---> const int");
    TEST_TYPE_EQUAL(add_const<const double>::type, const double,
                    "add_const<const double> ---> const double");

    TEST_TYPE_EQUAL(add_const<int&>::type, int&, "add_const<int&> ---> int&");
    TEST_TYPE_EQUAL(add_const<int&&>::type, int&&,
                    "add_const<int&&> ---> int&&");

    TEST_TYPE_EQUAL(add_const<int*>::type, int* const,
                    "add_const<int*> ---> int* const");
    TEST_TYPE_EQUAL(add_const<const int*>::type, const int* const,
                    "add_const<const int*> ---> const int* const");

    TEST_TYPE_EQUAL(add_const<volatile int>::type, const volatile int,
                    "add_const<const volatile int> ---> const volatile int");

    TEST_TYPE_EQUAL(add_const<void>::type, void, "add_const<void> ---> void");
    TEST_TYPE_EQUAL(add_const<void*>::type, void* const,
                    "add_const<void*> ---> void* const");
    TEST_TYPE_EQUAL(add_const<const void*>::type, const void* const,
                    "add_const<const void*> ---> const void* const");

    TEST_TYPE_EQUAL(add_const<int[10]>::type, int[10],
                    "add_const<int[10]> ---> int[10]>");
    TEST_TYPE_EQUAL(add_const<int[]>::type, int[],
                    "add_const<int[]> ---> int[]>");
}

// ===============================
// add_volatile 测试
// ===============================
void test_add_volatile() {
    std::cout << '\n'
              << "------------add_volatile 测试------------" << std::endl;
    TEST_TYPE_EQUAL(add_volatile<int>::type, volatile int,
                    "add_volatile<int> ---> volatile int");
    TEST_TYPE_EQUAL(add_volatile<double>::type, volatile double,
                    "add_volatile<double> ---> volatile double");

    TEST_TYPE_EQUAL(add_volatile<const int>::type, const volatile int,
                    "add_volatile<const int> ---> const volatile int");
    TEST_TYPE_EQUAL(add_volatile<const double>::type, const volatile double,
                    "add_volatile<const double> ---> const volatile double");

    TEST_TYPE_EQUAL(add_volatile<int&>::type, int&,
                    "add_volatile<int&> ---> int&");
    TEST_TYPE_EQUAL(add_volatile<int&&>::type, int&&,
                    "add_volatile<int&&> ---> int&&");

    TEST_TYPE_EQUAL(add_volatile<int*>::type, int* volatile,
                    "add_volatile<int*> ---> int* volatile");
    TEST_TYPE_EQUAL(add_volatile<const int*>::type, const int* volatile,
                    "add_volatile<const int*> ---> const int* volatile");

    TEST_TYPE_EQUAL(add_volatile<volatile int>::type, volatile int,
                    "add_volatile<volatile int> ---> volatile int");

    TEST_TYPE_EQUAL(add_volatile<void>::type, void,
                    "add_volatile<void> ---> void");
    TEST_TYPE_EQUAL(add_volatile<void*>::type, void* volatile,
                    "add_volatile<void*> ---> void* volatile");
    TEST_TYPE_EQUAL(add_volatile<const void*>::type, const void* volatile,
                    "add_volatile<const void*> ---> const void* volatile");

    TEST_TYPE_EQUAL(add_volatile<int[10]>::type, int[10],
                    "add_volatile<int[10]> ---> int[10]");
    TEST_TYPE_EQUAL(add_volatile<int[]>::type, int[],
                    "add_volatile<int[]> ---> int[]>");
}

// ===============================
// add_cv 测试
// ===============================
void test_add_cv() {
    std::cout << '\n' << "------------add_cv 测试------------" << std::endl;
    TEST_TYPE_EQUAL(add_cv<int>::type, const volatile int,
                    "add_cv<int> ---> const volatile int");
    TEST_TYPE_EQUAL(add_cv<double>::type, const volatile double,
                    "add_cv<double> ---> const volatile double");

    TEST_TYPE_EQUAL(add_cv<const int>::type, const volatile int,
                    "add_cv<const int> ---> const volatile int");
    TEST_TYPE_EQUAL(add_cv<const double>::type, const volatile double,
                    "add_cv<const double> ---> const volatile double");

    TEST_TYPE_EQUAL(add_cv<int&>::type, int&, "add_cv<int&> ---> int&");
    TEST_TYPE_EQUAL(add_cv<int&&>::type, int&&, "add_cv<int&&> ---> int&&");

    TEST_TYPE_EQUAL(add_cv<int*>::type, int* const volatile,
                    "add_cv<int*> ---> int* const volatile");
    TEST_TYPE_EQUAL(add_cv<const int*>::type, const int* const volatile,
                    "add_cv<const int*> ---> const int* const volatile");

    TEST_TYPE_EQUAL(add_cv<volatile int>::type, const volatile int,
                    "add_cv<volatile int> ---> const volatile int");

    TEST_TYPE_EQUAL(add_cv<void>::type, void, "add_cv<void> --> void");
    TEST_TYPE_EQUAL(add_cv<void*>::type, void* const volatile,
                    "add_cv<void*> ---> void* const volatile");
    TEST_TYPE_EQUAL(add_cv<const void*>::type, const void* const volatile,
                    "add_cv<const void*> ---> const void* const volatile");

    TEST_TYPE_EQUAL(add_cv<int[10]>::type, int[10],
                    "add_cv<int[10]> ---> int[10]");
    TEST_TYPE_EQUAL(add_cv<int[]>::type, int[], "add_cv<int[]> ---> int[]>");
}

// ===============================
// test_add_lvalue_reference 测试
// ===============================
void test_add_lvalue_reference() {
    std::cout << '\n'
              << "------------add_lvalue_reference 测试------------"
              << std::endl;
    TEST_TYPE_EQUAL(add_lvalue_reference<int>::type, int&,
                    "add_lvalue_reference<int> ---> int&");
    TEST_TYPE_EQUAL(add_lvalue_reference<int&>::type, int&,
                    "add_lvalue_reference<int&> ---> int&");
    TEST_TYPE_EQUAL(add_lvalue_reference<int&&>::type, int&,
                    "add_lvalue_reference<int&&> ---> int&");

    TEST_TYPE_EQUAL(add_lvalue_reference<int*>::type, int*&,
                    "add_lvalue_reference<int*> ---> int*&");
    TEST_TYPE_EQUAL(add_lvalue_reference<const int*>::type, const int*&,
                    "add_lvalue_reference<const int*> ---> const int*&");

    TEST_TYPE_EQUAL(add_lvalue_reference<void>::type, void,
                    "add_lvalue_reference<void> ---> void");
    TEST_TYPE_EQUAL(add_lvalue_reference<void*>::type, void*&,
                    "add_lvalue_reference<void*> ---> void*&");
    TEST_TYPE_EQUAL(add_lvalue_reference<const void*>::type, const void*&,
                    "add_lvalue_reference<const void*> ---> const void*&");

    TEST_TYPE_EQUAL(add_lvalue_reference<int[10]>::type, int[10],
                    "add_lvalue_reference<int[10]> ---> int[10]");
    TEST_TYPE_EQUAL(add_lvalue_reference<int[]>::type, int[],
                    "add_lvalue_reference<int[]> ---> int[]");
}

// ===============================
// test_add_rvalue_reference 测试
// ===============================
void test_add_rvalue_reference() {
    std::cout << '\n'
              << "------------add_rvalue_reference 测试------------"
              << std::endl;
    TEST_TYPE_EQUAL(add_rvalue_reference<int>::type, int&&,
                    "add_rvalue_reference<int> ---> int&&");
    TEST_TYPE_EQUAL(add_rvalue_reference<int&>::type, int&,
                    "add_rvalue_reference<int&> ---> int&");
    TEST_TYPE_EQUAL(add_rvalue_reference<int&&>::type, int&&,
                    "add_rvalue_reference<int&&> ---> int&&");

    TEST_TYPE_EQUAL(add_rvalue_reference<int*>::type, int*&&,
                    "add_rvalue_reference<int*> ---> int*&&");
    TEST_TYPE_EQUAL(add_rvalue_reference<const int*>::type, const int*&&,
                    "add_rvalue_reference<const int*> ---> const int*&&");

    TEST_TYPE_EQUAL(add_rvalue_reference<void>::type, void,
                    "add_rvalue_reference<void> ---> void");
    TEST_TYPE_EQUAL(add_rvalue_reference<void*>::type, void*&&,
                    "add_rvalue_reference<void*> --> void*&&");
    TEST_TYPE_EQUAL(add_rvalue_reference<const void*>::type, const void*&&,
                    "add_rvalue_reference<const void*> ---> const void*&&");

    TEST_TYPE_EQUAL(add_rvalue_reference<int[10]>::type, int[10],
                    "add_rvalue_reference<int[10]> ---> int[10]");
    TEST_TYPE_EQUAL(add_rvalue_reference<int[]>::type, int[],
                    "add_rvalue_reference<int[]> ---> int[]");
}

// ===============================
// test_add_pointer 测试
// ===============================
void test_add_pointer() {
    std::cout << '\n'
              << "------------add_pointer 测试------------" << std::endl;
    TEST_TYPE_EQUAL(add_pointer<int>::type, int*, "add_pointer<int> ---> int*");
    TEST_TYPE_EQUAL(add_pointer<int&>::type, int*,
                    "add_pointer<int&> ---> int*");
    TEST_TYPE_EQUAL(add_pointer<int&&>::type, int*,
                    "add_pointer<int&&> ---> int*");

    TEST_TYPE_EQUAL(add_pointer<int*>::type, int*,
                    "add_pointer<int*> ---> int*");
    TEST_TYPE_EQUAL(add_pointer<const int*>::type, const int*,
                    "add_pointer<const int*> ---> const int*");

    TEST_TYPE_EQUAL(add_pointer<void>::type, void*,
                    "add_pointer<void> ---> void*");
    TEST_TYPE_EQUAL(add_pointer<void*>::type, void*,
                    "add_pointer<void*> ---> void*");
    TEST_TYPE_EQUAL(add_pointer<const void*>::type, const void*,
                    "add_pointer<const void*> ---> const void*");

    TEST_TYPE_EQUAL(add_pointer<decltype(test_func)>::type, void (*)(),
                    "add_pointer<decltype(test_func)> ---> void (*)()");

    TEST_TYPE_EQUAL(add_pointer<int[10]>::type, int (*)[10],
                    "add_pointer<int[10]> ---> int (*)[10]");
    TEST_TYPE_EQUAL(add_pointer<int[]>::type, int (*)[],
                    "add_pointer<int[]> ---> int (*)[]");
}

// ===============================
// test_remove_const 测试
// ===============================
void test_remove_const() {
    std::cout << '\n'
              << "------------test_remove_const 测试------------" << std::endl;
    TEST_TYPE_EQUAL(remove_const<const int>::type, int,
                    "remove_const<const int> ---> int");
    TEST_TYPE_EQUAL(remove_const<const volatile int>::type, volatile int,
                    "remove_const<const volatile int> ---> volatile int");
    TEST_TYPE_EQUAL(remove_const<int>::type, int, "remove_const<int> ---> int");

    TEST_TYPE_EQUAL(remove_const<const int*>::type, const int*,
                    "remove_const<const int*> ---> const int*");
    TEST_TYPE_EQUAL(remove_const<int* const>::type, int*,
                    "remove_const<int* const> ---> int*");
    TEST_TYPE_EQUAL(remove_const<int*>::type, int*,
                    "remove_const<int*> ---> int*");
}

// ===============================
// test_remove_volatile 测试
// ===============================
void test_remove_volatile() {
    std::cout << '\n'
              << "------------test_remove_volatile 测试------------"
              << std::endl;
    TEST_TYPE_EQUAL(remove_volatile<const volatile int>::type, const int,
                    "remove_volatile<const volatile int> ---> const int");
    TEST_TYPE_EQUAL(remove_volatile<volatile int>::type, int,
                    "remove_volatile<volatile int> ---> int");
    TEST_TYPE_EQUAL(remove_volatile<int>::type, int,
                    "remove_volatile<int> ---> int");

    TEST_TYPE_EQUAL(remove_volatile<const int* volatile>::type, const int*,
                    "remove_volatile<const int* volatile> ---> const int* ");
    TEST_TYPE_EQUAL(remove_volatile<int* volatile>::type, int*,
                    "remove_volatile<int* volatile> ---> int*");
    TEST_TYPE_EQUAL(
        remove_volatile<int*>::type, int*, "remove_volatile<int*> ---> int*"

    );
}

// ===============================
// test_remove_cv 测试
// ===============================
void test_remove_cv() {
    std::cout << '\n'
              << "------------test_remove_cv 测试------------" << std::endl;
    TEST_TYPE_EQUAL(remove_cv<const volatile int>::type, int,
                    "remove_cv<const volatile int> ---> int");
    TEST_TYPE_EQUAL(remove_cv<int>::type, int, "remove_cv<int> ---> int");

    TEST_TYPE_EQUAL(remove_cv<const int*>::type, const int*,
                    "remove_cv<const int*> ---> const int*");
    TEST_TYPE_EQUAL(remove_cv<int* const>::type, int*,
                    "remove_cv<int* const> ---> int*");
    TEST_TYPE_EQUAL(remove_cv<int*>::type, int*, "remove_cv<int*> ---> int*");
}

// ===============================
// test_remove_reference 测试
// ===============================
void test_remove_reference() {
    std::cout << '\n'
              << "------------test_remove_reference 测试------------"
              << std::endl;
    TEST_TYPE_EQUAL(remove_reference<int>::type, int,
                    "remove_reference<int> ---> int");
    TEST_TYPE_EQUAL(remove_reference<int&>::type, int,
                    "remove_reference<int&> ---> int");
    TEST_TYPE_EQUAL(remove_reference<int&&>::type, int,
                    "remove_reference<int&&> ---> int");
}

// ===============================
// test_remove_pointer 测试
// ===============================
void test_remove_pointer() {
    std::cout << '\n'
              << "------------test_remove_pointer 测试------------"
              << std::endl;
    TEST_TYPE_EQUAL(remove_pointer<int>::type, int,
                    "remove_pointer<int> ---> int");
    TEST_TYPE_EQUAL(remove_pointer<int*>::type, int,
                    "remove_pointer<int*> ---> int");
    TEST_TYPE_EQUAL(remove_pointer<int**>::type, int*,
                    "remove_pointer<int**> ---> int*");
    TEST_TYPE_EQUAL(remove_pointer<int (**)[10]>::type, int (*)[10],
                    "remove_pointer<int(**)[10]> ---> int(*)[10]");
    TEST_TYPE_EQUAL(remove_pointer<int (*)[10]>::type, int[10],
                    "remove_pointer<int(*)[10]> ---> int[10]");
    TEST_TYPE_EQUAL(remove_pointer<int (*)[]>::type, int[],
                    "remove_pointer<int (*)[]> ---> int[]");
}

// ===============================
// test_remove_all_pointers 测试
// ===============================
void test_remove_all_pointers() {
    std::cout << '\n'
              << "------------test_remove_all_pointers 测试------------"
              << std::endl;
    TEST_TYPE_EQUAL(remove_all_pointers<int>::type, int,
                    "remove_all_pointers<int> ---> int");
    TEST_TYPE_EQUAL(remove_all_pointers<int*>::type, int,
                    "remove_all_pointers<int*> ---> int");
    TEST_TYPE_EQUAL(remove_all_pointers<int**>::type, int,
                    "remove_all_pointers<int**> ---> int");
    TEST_TYPE_EQUAL(remove_all_pointers<int (**)[10][10]>::type, int[10][10],
                    "remove_all_pointers<int (**)[10][10]> ---> int[10][10]");
    TEST_TYPE_EQUAL(
        remove_all_pointers<int (***)[10][10][10]>::type, int[10][10][10],
        "remove_all_pointers<int (***)[10][10][10]> ---> int[10][10][10]");
    TEST_TYPE_EQUAL(remove_all_pointers<int (*)[]>::type, int[],
                    "remove_all_pointers<int(*)[]> ---> int[]");
}

// ===============================
// test_remove_extent 测试
// ===============================
void test_remove_extent() {
    std::cout << '\n'
              << "------------test_remove_extent 测试------------" << std::endl;
    TEST_TYPE_EQUAL(remove_extent<int>::type, int,
                    "remove_extent<int> ---> int");
    TEST_TYPE_EQUAL(remove_extent<int[10]>::type, int,
                    "remove_extent<int[10]> ---> int");
    TEST_TYPE_EQUAL(remove_extent<int[10][10]>::type, int[10],
                    "remove_extent<int[10][10]> ---> int[10]");
    TEST_TYPE_EQUAL(remove_extent<int (*)[10]>::type, int (*)[10],
                    "remove_extent<int(*)[10]> ---> int(*)[10]");
    TEST_TYPE_EQUAL(remove_extent<int (*)[10][10]>::type, int (*)[10][10],
                    "remove_extent<int(*)[10][10]> ---> int(*)[10][10]");
    TEST_TYPE_EQUAL(remove_extent<int[][10][10]>::type, int[10][10],
                    "remove_extent<int[][10][10]> ---> int[10][10]");
}

// ===============================
// test_remove_all_extents 测试
// ===============================
void test_remove_all_extents() {
    std::cout << '\n'
              << "------------test_remove_all_extents 测试------------"
              << std::endl;
    TEST_TYPE_EQUAL(remove_all_extents<int>::type, int,
                    "remove_all_extents<int> ---> int");
    TEST_TYPE_EQUAL(remove_all_extents<int[10]>::type, int,
                    "remove_all_extents<int[10]> ---> int");
    TEST_TYPE_EQUAL(remove_all_extents<int[10][10]>::type, int,
                    "remove_all_extents<int[10][10]> ---> int");
    TEST_TYPE_EQUAL(remove_all_extents<int (*)[10][10]>::type, int (*)[10][10],
                    "remove_all_extents<int (*)[10][10]> ---> int(*)[10][10]");
    TEST_TYPE_EQUAL(
        remove_all_extents<int (*)[][10][10]>::type, int (*)[][10][10],
        "remove_all_extents<int (*)[][10][10]> ---> int(*)[][10][10]");
    TEST_TYPE_EQUAL(remove_all_extents<int[][10][10]>::type, int,
                    "remove_all_extents<int[][10][10]> ---> int");
}

// ===============================
// test_is_const 测试
// ===============================
void test_is_const() {
    std::cout << '\n'
              << "------------test_is_const 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_const<const volatile int>::value, true,
                    "is_const<const volatile int> : true");
    TEST_BOOL_EQUAL(is_const<const int>::value, true,
                    "is_const<const int> : true");
    TEST_BOOL_EQUAL(is_const<int>::value, false, " is_const<int> : false");

    TEST_BOOL_EQUAL(is_const<int* const>::value, true,
                    "is_const< int* const> : true");
    TEST_BOOL_EQUAL(is_const<const int* const>::value, true,
                    "is_const<const int* const> : true");
    TEST_BOOL_EQUAL(is_const<int*>::value, false, " is_const<int*> : false");
    TEST_BOOL_EQUAL(is_const<const int**>::value, false,
                    " is_const<const int**> : false");
}

// ===============================
// test_is_volatile 测试
// ===============================
void test_is_volatile() {
    std::cout << '\n'
              << "------------test_is_volatile 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_volatile<const volatile int>::value, true,
                    "is_volatile<const volatile int> : true");
    TEST_BOOL_EQUAL(is_volatile<volatile int>::value, true,
                    " is_volatile<volatile int> : true");
    TEST_BOOL_EQUAL(is_volatile<int>::value, false,
                    " is_volatile<int> : false");
    TEST_BOOL_EQUAL(is_volatile<const int>::value, false,
                    " is_volatile<const int> : false");

    TEST_BOOL_EQUAL(is_volatile<int* volatile>::value, true,
                    "is_volatile< int* volatile> : true");
    TEST_BOOL_EQUAL(is_volatile<const int* volatile>::value, true,
                    "is_volatile<const int* volatile> : true");
    TEST_BOOL_EQUAL(is_volatile<int*>::value, false,
                    " is_volatile<int*> : false");
    TEST_BOOL_EQUAL(is_volatile<const int**>::value, false,
                    " is_volatile<const int**> : false");
}

// ===============================
// test_is_cv 测试
// ===============================
void test_is_cv() {
    std::cout << '\n' << "------------test_is_cv 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_cv<const volatile int>::value, true,
                    "is_cv<const volatile int> : true");
    TEST_BOOL_EQUAL(is_cv<const int>::value, false,
                    " is_cv<const int> : false");
    TEST_BOOL_EQUAL(is_cv<int>::value, false, " is_cv<int> : false");
    TEST_BOOL_EQUAL(is_cv<int*>::value, false, " is_cv<int*> : false");
    TEST_BOOL_EQUAL(is_cv<const int**>::value, false,
                    " is_cv<const int**> : false");
    TEST_BOOL_EQUAL(is_cv<int* const>::value, false,
                    "is_cv<int* const> : false");
    TEST_BOOL_EQUAL(is_cv<int* const volatile>::value, true,
                    " is_cv<int* const volatile> : true");
}

// ===============================
// test_is_lvalue_reference 测试
// ===============================
void test_is_lvalue_reference() {
    std::cout << '\n'
              << "------------test_is_lvalue_reference 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_lvalue_reference<int&>::value, true,
                    "is_lvalue_reference<int&> : true");
    TEST_BOOL_EQUAL(is_lvalue_reference<int&&>::value, false,
                    " is_lvalue_reference<int&&> : false");
    TEST_BOOL_EQUAL(is_lvalue_reference<int>::value, false,
                    " is_lvalue_reference<int> : false");
    TEST_BOOL_EQUAL(is_lvalue_reference<const int&>::value, true,
                    "is_lvalue_reference<const int&> : true");
    TEST_BOOL_EQUAL(is_lvalue_reference<int* const&>::value, true,
                    "is_lvalue_reference<int* const&> : true");
    TEST_BOOL_EQUAL(is_lvalue_reference<int*&>::value, true,
                    "is_lvalue_reference<int*&> : true");
}

// ===============================
// test_is_rvalue_reference 测试
// ===============================
void test_is_rvalue_reference() {
    std::cout << '\n'
              << "------------test_is_rvalue_reference 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_rvalue_reference<int&&>::value, true,
                    "is_rvalue_reference<int&&> : true");
    TEST_BOOL_EQUAL(is_rvalue_reference<int&>::value, false,
                    "is_rvalue_reference<int&> : false");
    TEST_BOOL_EQUAL(is_rvalue_reference<int>::value, false,
                    "is_rvalue_reference<int> : false");
    TEST_BOOL_EQUAL(is_rvalue_reference<const int&&>::value, true,
                    "is_rvalue_reference<const int&&> : true");
    TEST_BOOL_EQUAL(is_rvalue_reference<int* const&&>::value, true,
                    "is_rvalue_reference<int* const&&> : true");
    TEST_BOOL_EQUAL(is_rvalue_reference<int*&>::value, false,
                    "is_rvalue_reference<int*&> : false");
}

// ===============================
// test_is_reference 测试
// ===============================
void test_is_reference() {
    std::cout << '\n'
              << "------------test_is_reference 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_reference<int&>::value, true,
                    "is_reference<int&> : true");
    TEST_BOOL_EQUAL(is_reference<int&&>::value, true,
                    "is_reference<int&&> : true");
    TEST_BOOL_EQUAL(is_reference<int>::value, false,
                    "is_reference<int> : false");
    TEST_BOOL_EQUAL(is_reference<const int&>::value, true,
                    "is_reference<const int&> : true");
    TEST_BOOL_EQUAL(is_reference<int* const&>::value, true,
                    "is_reference<int* const&> : true");
    TEST_BOOL_EQUAL(is_reference<int*&>::value, true,
                    "is_reference<int*&> : true");
    TEST_BOOL_EQUAL(is_reference<int*&&>::value, true,
                    "is_reference<int*&&> : true");
}

// ===============================
// test_is_pointer 测试
// ===============================
void test_is_pointer() {
    std::cout << '\n'
              << "------------test_is_pointer 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_pointer<int*>::value, true, "is_pointer<int*> : true");
    TEST_BOOL_EQUAL(is_pointer<int&>::value, false, "is_pointer<int&> : false");
    TEST_BOOL_EQUAL(is_pointer<int>::value, false, "is_pointer<int> : false");
    TEST_BOOL_EQUAL(is_pointer<const int*>::value, true,
                    "is_pointer<const int*> : true");
    TEST_BOOL_EQUAL(is_pointer<int (*)[5]>::value, true,
                    "is_pointer<int (*)[5]> : true");
    TEST_BOOL_EQUAL(is_pointer<int (*)[]>::value, true,
                    "is_pointer<int (*)[]> : true");
    TEST_BOOL_EQUAL(is_pointer<int (*)()>::value, true,
                    "is_pointer<int (*)()> : true");
}

// ===============================
// test_is_array 测试
// ===============================
void test_is_null_pointer() {
    std::cout << '\n'
              << "------------test_is_null_pointer 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_null_pointer<int*>::value, false,
                    "is_null_pointer<int*> : false");
    TEST_BOOL_EQUAL(is_null_pointer<int&>::value, false,
                    "is_null_pointer<int&> : false");
    TEST_BOOL_EQUAL(is_null_pointer<int>::value, false,
                    "is_null_pointer<int> : false");
    TEST_BOOL_EQUAL(is_null_pointer<const int*>::value, false,
                    "is_null_pointer<const int*> : false");
    TEST_BOOL_EQUAL(is_null_pointer<int (*)[5]>::value, false,
                    "is_null_pointer<int (*)[5]> : false");
    TEST_BOOL_EQUAL(is_null_pointer<int (*)[]>::value, false,
                    "is_null_pointer<int (*)[]> : false");
    TEST_BOOL_EQUAL(is_null_pointer<int (*)()>::value, false,
                    "is_null_pointer<int (*)()> : false");
    TEST_BOOL_EQUAL(is_null_pointer<decltype(nullptr)>::value, true,
                    "is_null_pointer<decltype(nullptr)> : true");
    TEST_BOOL_EQUAL(is_null_pointer<std::nullptr_t>::value, true,
                    "is_null_pointer<nullptr_t> : true");
    TEST_BOOL_EQUAL(is_null_pointer<decltype(NULL)>::value, true,
                    "is_null_pointer<decltype(NULL)> : true");
}

// ===============================
// test_is_array 测试
// ===============================
void test_is_array() {
    std::cout << '\n'
              << "------------test_is_array 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_array<int[5]>::value, true, "is_array<int[5]> : true");
    TEST_BOOL_EQUAL(is_array<int[5][4]>::value, true,
                    "is_array<int[5][4]> : true");
    TEST_BOOL_EQUAL(is_array<int[]>::value, true, "is_array<int[]> : true");
    TEST_BOOL_EQUAL(is_array<int>::value, false, "is_array<int> : false");
    TEST_BOOL_EQUAL(is_array<const int[5]>::value, true,
                    "is_array<const int[5]> : true");
    TEST_BOOL_EQUAL(is_array<int (*)[5]>::value, false,
                    "is_array<int (*)[5]> : false");
    TEST_BOOL_EQUAL(is_array<int (*)[]>::value, false,
                    "is_array<int (*)[]> : false");
}

// ===============================
// test_is_function 测试
// ===============================
void test_is_function() {
    std::cout << '\n'
              << "------------test_is_function 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_function<int(int)>::value, true,
                    "is_function<int(int)> : true");
    TEST_BOOL_EQUAL(is_function<int (*)()>::value, false,
                    "is_function<int (*)()> : false");
    TEST_BOOL_EQUAL(is_function<decltype(test_func)>::value, true,
                    "is_function<decltype(test_func)> : true");
    TEST_BOOL_EQUAL(is_function<int>::value, false, "is_function<int> : false");
    TEST_BOOL_EQUAL(is_function<int[5]>::value, false,
                    "is_function<int[5]> : false");
}

// ===============================
// test_is_integral 测试
// ===============================
void test_is_integral() {
    std::cout << '\n'
              << "------------test_is_integral 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_integral<int>::value, true, "is_integral<int> : true");
    TEST_BOOL_EQUAL(is_integral<char>::value, true, "is_integral<char> : true");
    TEST_BOOL_EQUAL(is_integral<long>::value, true, "is_integral<long> : true");
    TEST_BOOL_EQUAL(is_integral<bool>::value, true, "is_integral<bool> : true");
    TEST_BOOL_EQUAL(is_integral<double>::value, false,
                    "is_integral<double> : false");
    TEST_BOOL_EQUAL(is_integral<int&>::value, false,
                    "is_integral<int&> : false");
}

// ===============================
// test_is_floating_point 测试
// ===============================
void test_is_floating_point() {
    std::cout << '\n'
              << "------------test_is_floating_point 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_floating_point<float>::value, true,
                    "is_floating_point<float> : true");
    TEST_BOOL_EQUAL(is_floating_point<double>::value, true,
                    "is_floating_point<double> : true");
    TEST_BOOL_EQUAL(is_floating_point<double&>::value, false,
                    "is_floating_point<double&> : false");
    TEST_BOOL_EQUAL(is_floating_point<long double>::value, true,
                    "is_floating_point<long double> : true");
    TEST_BOOL_EQUAL(is_floating_point<int>::value, false,
                    "is_floating_point<int> : false");
    TEST_BOOL_EQUAL(is_floating_point<int&>::value, false,
                    "is_floating_point<int&> : false");
    TEST_BOOL_EQUAL(is_floating_point<char>::value, false,
                    "is_floating_point<char> : false");
}

// ===============================
// test_is_class 测试
// ===============================
void test_is_class() {
    std::cout << '\n'
              << "------------test_is_class 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_class<int>::value, false, "is_class<int> : false");
    TEST_BOOL_EQUAL(is_class<std::string>::value, true,
                    "is_class<std::string> : true");
    TEST_BOOL_EQUAL(is_class<TestClass>::value, true,
                    "is_class<TestClass> : true");
    TEST_BOOL_EQUAL(is_class<int&>::value, false, "is_class<int&> : false");
    TEST_BOOL_EQUAL(is_class<int*>::value, false, "is_class<int*> : false");
    TEST_BOOL_EQUAL(is_class<int[5]>::value, false, "is_class<int[5]> : false");
}

// ===============================
// test_is_union 测试
// ===============================
void test_is_union() {
    std::cout << '\n'
              << "------------test_is_union 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_union<int>::value, false, "is_union<int> : false");
    TEST_BOOL_EQUAL(is_union<TestClass>::value, false,
                    "is_union<TestClass> : false");
    TEST_BOOL_EQUAL(is_union<TestUnion>::value, true,
                    "is_union<TestUnion> : true");
    TEST_BOOL_EQUAL(is_union<int&>::value, false, "is_union<int&> : false");
}

// ===============================
// test_is_enum 测试
// ===============================
void test_is_enum() {
    std::cout << '\n'
              << "------------test_is_enum 测试------------" << std::endl;
    TEST_BOOL_EQUAL(is_enum<int>::value, false, "is_enum<int> : false");
    TEST_BOOL_EQUAL(is_enum<double>::value, false, "is_enum<double> : false");
    TEST_BOOL_EQUAL(is_enum<TestClass>::value, false,
                    "is_enum<TestClass> : false");
    TEST_BOOL_EQUAL(is_enum<TestEnum>::value, true, "is_enum<TestEnum> : true");
    TEST_BOOL_EQUAL(is_enum<int&>::value, false, "is_enum<int&> : false");
}

// ===============================
// test_is_reference_wrapper 测试
// ===============================
void test_is_reference_wrapper() {
    std::cout << '\n'
              << "------------test_is_reference_wrapper 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_reference_wrapper<int>::value, false,
                    "is_reference_wrapper<int> : false");
    TEST_BOOL_EQUAL(is_reference_wrapper<int&>::value, false,
                    "is_reference_wrapper<int&> : false");
    TEST_BOOL_EQUAL(is_reference_wrapper<reference_wrapper<int>>::value, true,
                    "is_reference_wrapper<reference_wrapper<int>> : true");
    TEST_BOOL_EQUAL(is_reference_wrapper<reference_wrapper<int&>>::value, true,
                    "is_reference_wrapper<reference_wrapper<int&>> : true");
    TEST_BOOL_EQUAL(
        is_reference_wrapper<reference_wrapper<const int>>::value, true,
        "is_reference_wrapper<reference_wrapper<const int>> : true");
    TEST_BOOL_EQUAL(
        is_reference_wrapper<reference_wrapper<decltype(test_func)>>::value,
        true,
        "is_reference_wrapper<reference_wrapper<decltype(test_func)>> : true");
}

// ===============================
// test_is_member_pointer 测试
// ===============================
void test_is_member_pointer() {
    std::cout << '\n'
              << "------------test_is_member_pointer 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_member_pointer<int>::value, false,
                    "is_member_pointer<int> : false");
    TEST_BOOL_EQUAL(is_member_pointer<int&>::value, false,
                    "is_member_pointer<int&> : false");
    TEST_BOOL_EQUAL(is_member_pointer<int (*)()>::value, false,
                    "is_member_pointer<int(*)()> : false");
    TEST_BOOL_EQUAL(is_member_pointer<int (TestClass::*)()>::value, true,
                    "is_member_pointer<int(TestClass::*)()> : true");
    TEST_BOOL_EQUAL(is_member_pointer<int(TestClass::*)>::value, true,
                    "is_member_pointer<int(TestClass::*)> : true");
}

// ===============================
// test_is_member_object_pointer 测试
// ===============================
void test_is_menber_object_pointer() {
    std::cout << '\n'
              << "------------test_is_member_object_pointer 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_member_object_pointer<int>::value, false,
                    "is_member_object_pointer<int> : false");
    TEST_BOOL_EQUAL(is_member_object_pointer<int&>::value, false,
                    "is_member_object_pointer<int&> : false");
    TEST_BOOL_EQUAL(is_member_object_pointer<int (*)()>::value, false,
                    "is_member_object_pointer<int(*)()> : false");
    TEST_BOOL_EQUAL(is_member_object_pointer<int (TestClass::*)()>::value,
                    false,
                    "is_member_object_pointer<int(TestClass::*)()> : false");
    TEST_BOOL_EQUAL(is_member_object_pointer<int(TestClass::*)>::value, true,
                    "is_member_object_pointer<int(TestClass::*)> : true");
}

// ===============================
// test_is_member_function_pointer 测试
// ===============================
void test_is_member_function_pointer() {
    std::cout << '\n'
              << "------------test_member_function_pointer 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_member_function_pointer<int>::value, false,
                    "is_member_function_pointer<int> : false");
    TEST_BOOL_EQUAL(is_member_function_pointer<int&>::value, false,
                    "is_member_function_pointer<int&> : false");
    TEST_BOOL_EQUAL(is_member_function_pointer<int (*)()>::value, false,
                    "is_member_function_pointer<int(*)()> : false");
    TEST_BOOL_EQUAL(is_member_function_pointer<int (TestClass::*)()>::value,
                    true,
                    "is_member_function_pointer<int(TestClass::*)()> : true");
    TEST_BOOL_EQUAL(is_member_function_pointer<int (TestClass::*)(int)>::value,
                    true,
                    "is_member_function_pointer<int (TestClass::*)(int): true");
    TEST_BOOL_EQUAL(is_member_function_pointer<int(TestClass::*)>::value, false,
                    "is_member_function_pointer<int(TestClass::*)> : false");
}

// ===============================
// test_is_constructible 测试
// ===============================
void test_is_constructible() {
    std::cout << '\n'
              << "------------test_is_constructible 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_constructible<int>::value, true,
                    "is_constructible<int> : true");
    TEST_BOOL_EQUAL(is_constructible<int&>::value, false,
                    "is_constructible<int&> : false");
    TEST_BOOL_EQUAL(is_constructible<int (*)()>::value, true,
                    "is_constructible<int(*)()> : true");

    TEST_BOOL_EQUAL((is_constructible<TestClass, int>::value), true,
                    "is_constructible<TestClass, int> : true");
    TEST_BOOL_EQUAL((is_constructible<TestClass, int&>::value), true,
                    "is_constructible<TestClass, int&> : true");
    TEST_BOOL_EQUAL((is_constructible<TestClass, int (*)()>::value), false,
                    "is_constructible<TestClass, int(*)()> : false");
}
// ======================================
// test_is_default_constructible 测试
// ======================================
void test_is_default_constructible() {
    std::cout << '\n'
              << "------------test_is_default_constructible 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_default_constructible<int>::value, true,
                    "is_default_constructible<int> : true");
    TEST_BOOL_EQUAL(is_default_constructible<int&>::value, false,
                    "is_default_constructible<int&> : false");
    TEST_BOOL_EQUAL(is_default_constructible<int (*)()>::value, true,
                    "is_default_constructible<int(*)()> : true");

    TEST_BOOL_EQUAL((is_default_constructible<TestClass>::value), true,
                    "is_default_constructible<TestClass> : true");

    TEST_BOOL_EQUAL(
        (is_default_constructible<TestNoDefaultConstructor>::value), false,
        "is_default_constructible<TestNoDefaultConstructor> : false");
}

// ======================================
// test_is_copy_constructible 测试
// ======================================
void test_is_copy_constructible() {
    std::cout << '\n'
              << "------------test_is_copy_constructible 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_copy_constructible<int>::value, true,
                    "is_copy_constructible<int> : true");
    TEST_BOOL_EQUAL(is_copy_constructible<int&>::value, true,
                    "is_copy_constructible<int&> : true");
    TEST_BOOL_EQUAL(is_copy_constructible<int (*)()>::value, true,
                    "is_copy_constructible<int(*)()> : true");

    TEST_BOOL_EQUAL((is_copy_constructible<TestClass>::value), true,
                    "is_copy_constructible<TestClass> : true");
    TEST_BOOL_EQUAL((is_copy_constructible<TestNoCopyConstructor>::value),
                    false,
                    "is_copy_constructible<TestNoCopyConstructor> : false");
}

// ======================================
// test_is_move_constructible 测试
// ======================================
void test_is_move_constructible() {
    std::cout << '\n'
              << "------------test_is_move_constructible 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_move_constructible<int>::value, true,
                    "is_move_constructible<int> : true");
    TEST_BOOL_EQUAL(is_move_constructible<int&>::value, true,
                    "is_move_constructible<int&> : true");
    TEST_BOOL_EQUAL(is_move_constructible<int (*)()>::value, true,
                    "is_move_constructible<int(*)()> : true");

    TEST_BOOL_EQUAL((is_move_constructible<TestClass>::value), true,
                    "is_move_constructible<TestClass> : true");
    TEST_BOOL_EQUAL((is_move_constructible<TestNoMoveConstructor>::value),
                    false,
                    "is_move_constructible<TestNoMoveConstructor> : false");
}

// ======================================
// test_is_nothrow_constructible 测试
// ======================================
void test_is_nothrow_constructible() {
    std::cout << '\n'
              << "------------test_is_nothrow_constructible 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL(is_nothrow_constructible<int>::value, true,
                    "is_nothrow_constructible<int> : true");
    TEST_BOOL_EQUAL(is_nothrow_constructible<int&>::value, false,
                    "is_nothrow_constructible<int&> : false");
    TEST_BOOL_EQUAL(is_nothrow_constructible<int (*)()>::value, true,
                    "is_nothrow_constructible<int(*)()> : true");

    TEST_BOOL_EQUAL((is_nothrow_constructible<TestClass>::value), false,
                    "is_nothrow_constructible<TestClass> : false");
    TEST_BOOL_EQUAL((is_nothrow_constructible<TestConstructorNothrow>::value),
                    true,
                    "is_nothrow_constructible<TestConstructorNothrow> : true");
    TEST_BOOL_EQUAL((is_nothrow_constructible<TestConstructorThrow>::value),
                    false,
                    "is_nothrow_constructible<TestConstructorThrow> : false");
}

// ======================================
// test_is_nothrow_copy_constructible 测试
// ======================================
void test_is_nothrow_copy_constructible() {
    std::cout
        << '\n'
        << "------------test_is_nothrow_copy_constructible 测试------------"
        << std::endl;
    TEST_BOOL_EQUAL(is_nothrow_copy_constructible<int>::value, true,
                    "is_nothrow_copy_constructible<int> : true");
    TEST_BOOL_EQUAL(is_nothrow_copy_constructible<int&>::value, true,
                    "is_nothrow_copy_constructible<int&> : true");
    TEST_BOOL_EQUAL(is_nothrow_copy_constructible<int (*)()>::value, true,
                    "is_nothrow_copy_constructible<int(*)()> : true");

    TEST_BOOL_EQUAL((is_nothrow_copy_constructible<TestClass>::value), true,
                    "is_nothrow_copy_constructible<TestClass> : true");
    TEST_BOOL_EQUAL(
        (is_nothrow_copy_constructible<TestConstructorNothrow>::value), true,
        "is_nothrow_copy_constructible<TestConstructorNothrow> : true");

    TEST_BOOL_EQUAL(
        (is_nothrow_copy_constructible<TestConstructorThrow>::value), false,
        "is_nothrow_copy_constructible<TestConstructorThrow> : false");
}

// =============================================
// test_is_nothrow_move_constructible 测试
// =============================================
void test_is_nothrow_move_constructible() {
    std::cout
        << '\n'
        << "------------test_is_nothrow_move_constructible 测试------------"
        << std::endl;
    TEST_BOOL_EQUAL(is_nothrow_move_constructible<int>::value, true,
                    "is_nothrow_move_constructible<int> : true");
    TEST_BOOL_EQUAL(is_nothrow_move_constructible<int&>::value, true,
                    "is_nothrow_move_constructible<int&> : true");
    TEST_BOOL_EQUAL(is_nothrow_move_constructible<int (*)()>::value, true,
                    "is_nothrow_move_constructible<int(*)()> : true");

    TEST_BOOL_EQUAL((is_nothrow_move_constructible<TestClass>::value), true,
                    "is_nothrow_move_constructible<TestClass> : true");
    TEST_BOOL_EQUAL(
        (is_nothrow_move_constructible<TestConstructorNothrow>::value), true,
        "is_nothrow_move_constructible<TestConstructorNothrow> : true");

    TEST_BOOL_EQUAL(
        (is_nothrow_move_constructible<TestConstructorThrow>::value), false,
        "is_nothrow_move_constructible<TestConstructorThrow> : false");
}

// ============================================
// test_is_assignable 测试
// =============================================
void test_is_assignable() {
    std::cout << '\n'
              << "------------test_is_assignable 测试------------" << std::endl;
    TEST_BOOL_EQUAL((is_assignable<int, int>::value), false,
                    "is_assignable<int, int> : false");
    TEST_BOOL_EQUAL((is_assignable<int&, int>::value), true,
                    "is_assignable<int&, int> : true");
    TEST_BOOL_EQUAL((is_assignable<int, int (*)()>::value), false,
                    "is_assignable<int, int(*)()> : false");
    TEST_BOOL_EQUAL((is_assignable<TestClass&, TestClass>::value), true,
                    "is_assignable<TestClass, TestClass> : true");
    TEST_BOOL_EQUAL((is_assignable<TestClass, TestClass>::value), true,
                    "is_assignable<TestClass, TestClass> : true");
}

// =============================================
// test_is_copy_assignable 测试
// =============================================
void test_is_copy_assignable() {
    std::cout << '\n'
              << "------------test_is_copy_assignable 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL((is_copy_assignable<int>::value), true,
                    "is_copy_assignable<int> : true");
    TEST_BOOL_EQUAL((is_copy_assignable<int&>::value), true,
                    "is_copy_assignable<int&> : true");
    TEST_BOOL_EQUAL((is_copy_assignable<int (*)()>::value), true,
                    "is_copy_assignable<int(*)()> : true");
    TEST_BOOL_EQUAL((is_copy_assignable<TestClass>::value), true,
                    "is_copy_assignable<TestClass> : true");
    TEST_BOOL_EQUAL((is_copy_assignable<TestNoCopyAssignment>::value), false,
                    "is_copy_assignable<TestCopyAssign> : false");
}

// =============================================
// test_is_move_assignable 测试
// =============================================
void test_is_move_assignable() {
    std::cout << '\n'
              << "------------test_is_move_assignable 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL((is_move_assignable<int>::value), true,
                    "is_move_assignable<int> : true");
    TEST_BOOL_EQUAL((is_move_assignable<int&>::value), true,
                    "is_move_assignable<int&> : true");
    TEST_BOOL_EQUAL((is_move_assignable<int (*)()>::value), true,
                    "is_move_assignable<int(*)()> : true");
    TEST_BOOL_EQUAL((is_move_assignable<TestClass>::value), true,
                    "is_move_assignable<TestClass> : true");
    TEST_BOOL_EQUAL((is_move_assignable<TestNoMoveAssignment>::value), false,
                    "is_move_assignable<TestMoveAssign> : false");
}

// =============================================
// test_is_nothrow_assignable 测试
// =============================================
void test_is_nothrow_assignable() {
    std::cout << '\n'

              << "------------test_is_nothrow_assignable 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL((is_nothrow_assignable<int, int>::value), false,
                    "is_nothrow_assignable<int, int> : false");
    TEST_BOOL_EQUAL((is_nothrow_assignable<int&, int>::value), true,
                    "is_nothrow_assignable<int&, int> : true");
    TEST_BOOL_EQUAL((is_nothrow_assignable<int, int (*)()>::value), false,
                    "is_nothrow_assignable<int, int(*)()> : false");
    TEST_BOOL_EQUAL((is_nothrow_assignable<TestClass&, TestClass>::value), true,
                    "is_nothrow_assignable<TestClass, TestClass> : true");
    TEST_BOOL_EQUAL((is_nothrow_assignable<TestClass, TestClass>::value), true,
                    "is_nothrow_assignable<TestClass, TestClass> : true");
    TEST_BOOL_EQUAL((is_nothrow_assignable<TestAssignmentNothrow&,
                                           TestAssignmentNothrow>::value),
                    true,
                    "is_nothrow_assignable<TestAssignmentNothrow&, "
                    "TestAssignmentNothrow> : true");
}

// =============================================
// test_is_nothrow_copy_assignable 测试
// =============================================
void test_is_nothrow_copy_assignable() {
    std::cout << '\n'
              << "------------test_is_nothrow_copy_assignable 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL((is_nothrow_copy_assignable<int>::value), true,
                    "is_nothrow_copy_assignable<int> : true");
    TEST_BOOL_EQUAL((is_nothrow_copy_assignable<int&>::value), true,
                    "is_nothrow_copy_assignable<int&> : true");
    TEST_BOOL_EQUAL((is_nothrow_copy_assignable<int (*)()>::value), true,
                    "is_nothrow_copy_assignable<int(*)()> : true");
    TEST_BOOL_EQUAL((is_nothrow_copy_assignable<TestClass>::value), true,
                    "is_nothrow_copy_assignable<TestClass> : true");
    TEST_BOOL_EQUAL((is_nothrow_copy_assignable<TestAssignmentNothrow>::value),
                    true,
                    "is_nothrow_copy_assignable<TestAssignmentNothrow> : true");
    TEST_BOOL_EQUAL(
        (is_nothrow_copy_assignable<TestAssignmentNothrow&>::value), true,
        "is_nothrow_copy_assignable<TestAssignmentNothrow&> : true");
}

// =============================================
// test_is_nothrow_move_assignable 测试
// =============================================
void test_is_nothrow_move_assignable() {
    std::cout << '\n'
              << "------------test_is_nothrow_move_assignable 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL((is_nothrow_move_assignable<int>::value), true,
                    "is_nothrow_move_assignable<int> : true");
    TEST_BOOL_EQUAL((is_nothrow_move_assignable<int&>::value), true,
                    "is_nothrow_move_assignable<int&> : true");
    TEST_BOOL_EQUAL((is_nothrow_move_assignable<int (*)()>::value), true,

                    "is_nothrow_move_assignable<int(*)()> : true");
    TEST_BOOL_EQUAL((is_nothrow_move_assignable<TestClass>::value), true,
                    "is_nothrow_move_assignable<TestClass> : true");
    TEST_BOOL_EQUAL((is_nothrow_move_assignable<TestAssignmentNothrow>::value),
                    true,
                    "is_nothrow_move_assignable<TestAssignmentNothrow> : true");
    TEST_BOOL_EQUAL(
        (is_nothrow_move_assignable<TestAssignmentNothrow&>::value), true,
        "is_nothrow_move_assignable<TestAssignmentNothrow&> : true");
}

// =============================================
// test_is_swappable 测试
// =============================================
void test_is_swappable() {
    std::cout << '\n'
              << "------------test_is_swappable 测试------------" << std::endl;
    TEST_BOOL_EQUAL((is_swappable<int>::value), true,
                    "is_swappable<int> : true");
    TEST_BOOL_EQUAL((is_swappable<int&>::value), true,
                    "is_swappable<int&> : true");
    TEST_BOOL_EQUAL((is_swappable<int (*)()>::value), true,
                    "is_swappable<int(*)()> : true");
    TEST_BOOL_EQUAL((is_swappable<TestClass>::value), true,
                    "is_swappable<TestClass> : true");
    TEST_BOOL_EQUAL((is_swappable<TestAssignmentNothrow>::value), true,
                    "is_swappable<TestAssignmentNothrow> : true");
    TEST_BOOL_EQUAL((is_swappable<TestAssignmentNothrow&>::value), true,
                    "is_swappable<TestAssignmentNothrow&> : true");
    TEST_BOOL_EQUAL((is_swappable<TestNoSwap>::value), false,
                    "is_nothrow_swappable<TestNoSwap> : false");
    TEST_BOOL_EQUAL((is_swappable<TestSwapThrow>::value), true,
                    "is_swappable<TestSwapThrow> : true");
}

// =============================================
// test_is_nothrow_swappable 测试
// =============================================
void test_is_nothrow_swappable() {
    std::cout << '\n'
              << "------------test_is_nothrow_swappable 测试------------"
              << std::endl;
    TEST_BOOL_EQUAL((is_nothrow_swappable<int>::value), true,
                    "is_nothrow_swappable<int> : true");
    TEST_BOOL_EQUAL((is_nothrow_swappable<int&>::value), true,
                    "is_nothrow_swappable<int&> : true");
    TEST_BOOL_EQUAL((is_nothrow_swappable<int (*)()>::value), true,
                    "is_nothrow_swappable<int(*)()> : true");
    TEST_BOOL_EQUAL((is_nothrow_swappable<TestClass>::value), true,
                    "is_nothrow_swappable<TestClass> : true");
    TEST_BOOL_EQUAL((is_nothrow_swappable<TestAssignmentNothrow>::value), true,
                    "is_nothrow_swappable<TestAssignmentNothrow> : true");
    TEST_BOOL_EQUAL((is_nothrow_swappable<TestAssignmentNothrow&>::value), true,
                    "is_nothrow_swappable<TestAssignmentNothrow&> : true");
    TEST_BOOL_EQUAL((is_nothrow_swappable<int[10]>::value), true,
                    "is_nothrow_swappable<int[10]> : true");
    TEST_BOOL_EQUAL((is_nothrow_swappable<TestNoSwap>::value), false,
                    "is_nothrow_swappable<TestNoSwap> : false");
    TEST_BOOL_EQUAL((is_nothrow_swappable<TestSwapThrow>::value), false,
                    "is_nothrow_swappable<TestSwapThrow> : false");
}

int main() {
    std::cout << "------------type traits 测试------------..." << std::endl;
    try {
        // test_void_t();
        // test_decay();
        // test_add_const();
        // test_add_volatile();
        // test_add_cv();
        // test_add_lvalue_reference();
        // test_add_rvalue_reference();
        // test_add_pointer();
        // test_remove_const();
        // test_remove_volatile();
        // test_remove_cv();
        // test_remove_reference();
        // test_remove_pointer();
        // test_remove_all_pointers();
        // test_remove_extent();
        // test_remove_all_extents();
        // test_is_const();
        // test_is_volatile();
        // test_is_cv();
        // test_is_lvalue_reference();
        // test_is_rvalue_reference();
        // test_is_reference();
        // test_is_pointer();
        // test_is_null_pointer();
        // test_is_array();
        // test_is_function();
        // test_is_integral();
        // test_is_floating_point();
        // test_is_class();
        // test_is_union();
        // test_is_enum();
        // test_is_reference_wrapper();
        // test_is_member_pointer();
        // test_is_menber_object_pointer();
        // test_is_member_function_pointer();
        // test_is_constructible();
        // test_is_default_constructible();
        // test_is_copy_constructible();
        // test_is_move_constructible();
        // test_is_nothrow_constructible();
        // test_is_nothrow_copy_constructible();
        // test_is_nothrow_move_constructible();
        // test_is_assignable();
        // test_is_copy_assignable();
        // test_is_move_assignable();
        // test_is_nothrow_assignable();
        // test_is_nothrow_copy_assignable();
        // test_is_nothrow_move_assignable();
        // test_is_swappable();
        // test_is_nothrow_swappable();
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