#include <cassert>
#include <iostream>
#include <tuple>
#include <typeinfo>
#include <utility>
#include "../include/type_traits/is_same.h"
#include "utility.h"
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

// 测试类型
void test_func() {}

// 测试类
class TestClass {
   public:
    TestClass() {}
    TestClass(const TestClass& other) {
        TEST_TYPE_EQUAL(decltype(other), const TestClass&,
                        "拷贝构造： TestClass(const TestClass& other)");
    }

    TestClass(TestClass&& other) {
        TEST_TYPE_EQUAL(decltype(other), TestClass&&,
                        "移动构造： TestClass(TestClass&& other)");
    }

    TestClass& operator=(const TestClass& other) {
        TEST_TYPE_EQUAL(
            decltype(other), const TestClass&,
            "拷贝赋值： TestClass& operator=(const TestClass& other)");
        return *this;
    }

    TestClass& operator=(TestClass&& other) {
        TEST_TYPE_EQUAL(decltype(other), TestClass&&,
                        "移动赋值： TestClass& operator=(TestClass&& other)");
        return *this;
    }

    ~TestClass() {}
};

// 无移动构造函数和移动赋值
class TestClassNoMove {
   public:
    TestClassNoMove() {}
    TestClassNoMove(const TestClassNoMove& other) {
        TEST_TYPE_EQUAL(
            decltype(other), const TestClassNoMove&,
            "拷贝构造： TestClassNoMove(const TestClassNoMove& other)");
    }

    TestClassNoMove& operator=(const TestClassNoMove& other) {
        TEST_TYPE_EQUAL(decltype(other), const TestClassNoMove&,
                        "拷贝赋值： TestClassNoMove& operator=(const "
                        "TestClassNoMove& other)");
        return *this;
    }
};

// ===================
// move 测试
// ===================
void test_move() {
    std::cout << '\n' << "------------move 测试------------" << std::endl;
    TestClass obj;
    TestClass obj2(move(obj));
    TestClass obj3 = move(obj2);
}

// ===================
// forward 测试
// ===================
void test_forward() {
    std::cout << '\n' << "------------forward 测试------------" << std::endl;
    TestClass obj;
    TestClass obj2(forward<TestClass&>(obj));
    TestClass obj3 = forward<TestClass&>(obj2);
    TestClass obj4(forward<TestClass>(obj3));
    TestClass obj5 = forward<TestClass>(obj4);
}

// ===================
// swap 测试
// ===================
void test_swap() {
    std::cout << '\n' << "------------swap 测试------------" << std::endl;
    TestClass obj1;
    TestClass obj2;
    swap(obj1, obj2);

    // 没有移动构造函数和移动赋值
    TestClassNoMove obj3;
    TestClassNoMove obj4;
    swap(obj3, obj4);
}

// ===================
// pair 测试
// ===================
template <typename T, typename U>
void test_pair_print(pair<T, U> pair, const char* test_name) {
    std::cout << "first: " << pair.first << " second: " << pair.second
              << test_name << std::endl;
}

void test_pair() {
    std::cout << '\n' << "------------pair 测试------------" << std::endl;
    pair<int, int> pair1(1, 2);
    test_pair_print(pair1, "预期： 1 2");

    pair<int, int> pair2 = make_pair(3, 4);
    test_pair_print(pair2, "预期： 3 4");

    pair<int, std::string> pair3 = pair<int, std::string>(5, "c++");
    test_pair_print(pair3, "预期： 5 c++");

    pair<int, std::string> pair4 = make_pair(5, "c++");
    test_pair_print(pair4, "预期： 5 c++");

    TEST_BOOL_EQUAL((pair1 == pair2), false, "pair1 == pair2");
    TEST_BOOL_EQUAL((pair1 != pair2), true, "pair1 != pair2");
    TEST_BOOL_EQUAL((pair1 < pair2), true, "pair1 < pair2");
    TEST_BOOL_EQUAL((pair1 <= pair2), true, "pair1 <= pair2");
    TEST_BOOL_EQUAL((pair1 > pair2), false, "pair1 > pair2");
    TEST_BOOL_EQUAL((pair1 >= pair2), false, "pair1 >= pair2");
    TEST_BOOL_EQUAL((pair1 == pair1), true, "pair1 == pair1");

    pair<int, int> pair5(1, 3);
    pair<int, int> pair6(10, 30);
    pair5.swap(pair6);

    TEST_BOOL_EQUAL((pair5.first == 10 && pair5.second == 30), true,
                    "pair5.first == 10 && pair5.second == 30");

    TEST_BOOL_EQUAL((pair6.first == 1 && pair6.second == 3), true,
                    "pair6.first == 1 && pair6.second == 3");
}

class Adder {
   public:
    int operator()(int a, int b) const { return a + b; }
};

// ===================
// reference_wrapper 测试
// ===================
void test_reference_wrapper() {
    std::cout << '\n'
              << "------------reference_wrapper 测试------------" << std::endl;

    int a = 10;
    int b = 20;
    int c = 30;

    reference_wrapper<int> ref_w01(a);
    ref_w01.get() = 20;
    std::cout << "✅ get() 方法测试通过" << std::endl;
    TEST_BOOL_EQUAL((ref_w01.get() == 20), true, "ref_w01.get() = 20;");

    int& ref_i = ref_w01;
    ref_i = 30;
    std::cout << "✅ operator& 方法测试通过" << std::endl;
    TEST_BOOL_EQUAL((ref_w01.get() == 30), true, "ref = 30");

    reference_wrapper<int> ref_w02(ref_w01);
    ref_w02.get() = 40;
    TEST_BOOL_EQUAL((ref_w01.get() == 40), true, "ref_w02.get() = 40;");
    std::cout << "✅ 拷贝构造测试通过" << std::endl;

    reference_wrapper<int> ref_w03 = ref_w01;
    ref_w03.get() = 50;
    TEST_BOOL_EQUAL((ref_w01.get() == 50), true, "ref_w03.get() = 50;");
    std::cout << "✅ 拷贝赋值测试通过" << std::endl;

    // reference_wrapper并不会真的移动对象，他和拷贝一样
    reference_wrapper<int> ref_w04(stl::move(ref_w01));
    ref_w04.get() = 60;
    TEST_BOOL_EQUAL((ref_w04.get() == 60), true, "ref_w04.get() = 60;");
    std::cout << "✅ 移动构造测试通过" << std::endl;

    reference_wrapper<int> ref_w05 = stl::move(ref_w04);
    ref_w05.get() = 70;
    TEST_BOOL_EQUAL((ref_w05.get() == 70), true, "ref_w05.get() = 70;");
    std::cout << "✅ 移动赋值测试通过" << std::endl;

    reference_wrapper<int> ref_w06 = ref(b);
    ref_w06.get() = 80;
    TEST_BOOL_EQUAL((b == 80), true, "ref_w06.get() = 20;");

    Adder adder;
    reference_wrapper<Adder> ref_w07 = ref(adder);
    TEST_BOOL_EQUAL((ref_w07.get()(10, 50) == 60), true,
                    "ref_w07.get()(10, 50) == 60");
    std::cout << "✅ ref() 方法测试通过" << std::endl;

    reference_wrapper<const int> ref_w08 = cref(c);
    // ref_w08.get() = 30; errer 常量引用不能修改
    TEST_BOOL_EQUAL((ref_w08.get() == 30), true, "ref_w08.get() == 30");
    std::cout << "✅ cref() 方法测试通过" << std::endl;
}

// ===================
// tuple 测试
// ===================
void test_tuple() {
    std::cout << '\n' << "------------tuple 测试------------" << std::endl;
    tuple<int, double, std::string> tuple1;     // 默认构造
    tuple<int, int, int> tuple3(1, 2, 3);       // 拷贝构造
    tuple<int, int, int> tuple4(tuple3);        // 拷贝构造
    tuple<int, int, int> tuple5(move(tuple3));  // 移动构造拷贝赋值
    std::cout << "✅ tuple构造测试通过" << std::endl;

    auto tuple6 = make_tuple(1, 2, 3);
    TEST_BOOL_EQUAL((stl::get<0>(tuple6) == 1), true,
                    "stl::get<0>(tuple6) == 1");
    TEST_BOOL_EQUAL((stl::get<1>(tuple6) == 2), true,
                    "stl::get<1>(tuple6) == 2");
    TEST_BOOL_EQUAL((stl::get<2>(tuple6) == 3), true,
                    "stl::get<2>(tuple6) == 3");
    std::cout << "✅ make_tuple 测试通过" << std::endl;

    stl::get<0>(tuple1) = 10;
    stl::get<1>(tuple1) = 30;
    stl::get<2>(tuple1) = "c++";
    TEST_BOOL_EQUAL((stl::get<0>(tuple1) == 10), true,
                    "stl::get<0>(tuple1) == 20");
    TEST_BOOL_EQUAL((stl::get<1>(tuple1) == 30), true,
                    "stl::get<1>(tuple1) == 30");
    TEST_BOOL_EQUAL((stl::get<2>(tuple1) == "c++"), true,
                    "stl::get<2>(tuple1) == c++");
    std::cout << "✅ get() 方法测试通过" << std::endl;

    TEST_BOOL_EQUAL(((tuple_size<decltype(tuple1)>::value) == 3), true,
                    "tuple_size<decltype(tuple1)>::value == 3");
    std::cout << "✅ tuple_size 测试通过" << std::endl;

    TEST_BOOL_EQUAL((tuple1 == tuple1), true, "tuple1 == tuple1");
    TEST_BOOL_EQUAL((tuple1 != tuple1), false, "tuple1 != tuple1");
    TEST_BOOL_EQUAL((tuple1 < tuple1), false, "tuple1 < tuple1");
    TEST_BOOL_EQUAL((tuple1 <= tuple1), true, "tuple1 <= tuple1");
    TEST_BOOL_EQUAL((tuple1 > tuple1), false, "tuple1 > tuple1");
    TEST_BOOL_EQUAL((tuple1 >= tuple1), true, "tuple1 >= tuple1");

    std::cout << "✅ 运算符测试通过" << std::endl;

    auto tuple7 = tuple6;  // 拷贝构造
    TEST_BOOL_EQUAL((tuple7 == tuple6), true, "tuple7 = tuple6");
    auto tuple8 = move(tuple7);  // 移动构造
    TEST_BOOL_EQUAL((tuple8 != tuple7), false, "tuple8 = move(tuple7)");
    std::cout << "✅ tuple拷贝构造测试通过" << std::endl;

    auto tuple9 = make_tuple(10, 20, 30);
    tuple9.swap(tuple6);
    TEST_BOOL_EQUAL((stl::get<0>(tuple6) == 10), true,
                    "stl::get<0>(tuple6) == 10");
    TEST_BOOL_EQUAL((stl::get<1>(tuple6) == 20), true,
                    "stl::get<1>(tuple6) == 20");
    TEST_BOOL_EQUAL((stl::get<2>(tuple6) == 30), true,
                    "stl::get<2>(tuple6) == 30");
    swap(tuple9, tuple6);
    TEST_BOOL_EQUAL((stl::get<0>(tuple6) == 1), true,
                    "stl::get<0>(tuple6) == 1");
    TEST_BOOL_EQUAL((stl::get<1>(tuple6) == 2), true,
                    "stl::get<1>(tuple6) == 2");
    TEST_BOOL_EQUAL((stl::get<2>(tuple6) == 3), true,
                    "stl::get<2>(tuple6) == 4");
    std::cout << "✅ tuple swap 测试通过" << std::endl;

    auto tuple10 = forward_as_tuple(1, 2, 3);
    using tuple10_type_01 = tuple_element_t<0, decltype(tuple10)>;
    using tuple10_type_02 = tuple_element_t<1, decltype(tuple10)>;
    using tuple10_type_03 = tuple_element_t<2, decltype(tuple10)>;

    TEST_TYPE_EQUAL(tuple10_type_01, int&&,
                    "tuple_element_t<0, decltype(tuple10)> == int&&");
    TEST_TYPE_EQUAL(tuple10_type_02, int&&,
                    "tuple_element_t<1, decltype(tuple10)> == int&&");
    TEST_TYPE_EQUAL(tuple10_type_03, int&&,
                    "tuple_element_t<2, decltype(tuple10)> == int&&");
    TEST_BOOL_EQUAL((stl::get<0>(tuple10) == 1), true,
                    "stl::get<0>(tuple10) == 1");
    TEST_BOOL_EQUAL((stl::get<1>(tuple10) == 2), true,
                    "stl::get<1>(tuple10) == 2");
    TEST_BOOL_EQUAL((stl::get<2>(tuple10) == 3), true,
                    "stl::get<2>(tuple10) == 3");
    std::cout << "✅ forward_as_tuple 测试通过" << std::endl;
}

int main() {
    std::cout << "------------utility 测试------------" << std::endl;
    try {
        test_move();
        test_forward();
        test_swap();
        test_pair();
        test_reference_wrapper();
        test_tuple();
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