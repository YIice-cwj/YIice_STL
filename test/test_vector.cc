#include <chrono>
#include <iostream>
#include <vector>
#include "vector.h"

size_t construct_count = 0;
size_t destructor_count = 0;

class test_vector {
   public:
    int data;
    char padding[10];
    test_vector() : data(0) { ++construct_count; }

    test_vector(int value) : data(value) { ++construct_count; }

    test_vector(const test_vector& other) : data(other.data) {
        ++construct_count;
    }

    test_vector(test_vector&& other) noexcept : data(stl::move(other.data)) {
        ++construct_count;
    }

    test_vector& operator=(const test_vector& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    test_vector& operator=(test_vector&& other) noexcept {
        if (this != &other) {
            data = stl::move(other.data);
        }
        return *this;
    }

    ~test_vector() { ++destructor_count; }
};

void print_vector(const stl::vector<test_vector>& vec,
                  const std::string& name) {
    std::cout << name << ": ";
    for (const auto& elem : vec) {
        std::cout << elem.data << " ";
    }
    std::cout << std::endl;
}

void test_constructor() {
    stl::vector<test_vector> vec1;  // 默认构造函数

    stl::vector<test_vector> vec2(2);  // 带初始大小的构造函数

    stl::vector<test_vector> vec3(2, 42);  // 指定大小和初始值

    stl::vector<test_vector> vec4(vec3);  // 拷贝构造函数

    stl::vector<test_vector> vec5(stl::move(vec4));  // 移动构造函数
    print_vector(vec5, "vec5");
    print_vector(vec4, "vec4");

    stl::vector<test_vector> vec6{1, 2, 3, 4, 5};  // 初始化列表构造函数
    print_vector(vec6, "vec6");

    stl::vector<test_vector> vec7(vec6.begin(), vec6.end());  // 迭代器构造
    print_vector(vec7, "vec7");
}

void test_assign() {
    stl::vector<test_vector> vec1{1, 2, 3, 4, 5, 6};

    stl::vector<test_vector> vec2;
    vec2 = vec1;  // 拷贝赋值
    print_vector(vec2, "vec2");

    stl::vector<test_vector> vec3;
    vec3 = stl::move(vec2);  // 移动赋值
    print_vector(vec3, "vec3");
}

void test_iterator() {
    std::cout << '\n'
              << std::string(25, '-') << "test_iterator" << std::string(25, '-')
              << std::endl;
    stl::vector<test_vector> vec{1, 2, 3, 4, 5};
    print_vector(vec, "vec");

    std::cout << "使用迭代器遍历元素: ";
    for (const auto& elem : vec) {
        std::cout << elem.data << " ";
    }

    std::cout << std::endl;

    std::cout << "使用反向迭代器遍历元素: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << it->data << " ";
    }
    std::cout << std::endl;

    std::cout << "使用常量迭代器遍历元素: ";
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        std::cout << it->data << " ";
    }
    std::cout << std::endl;

    auto c_it = vec.cbegin();
    // c_it->data = 100;  // 修改第一个元素

    std::cout << "使用常量反向迭代器遍历元素: ";
    for (auto it = vec.crbegin(); it != vec.crend(); ++it) {
        std::cout << it->data << " ";
    }
    auto cr_it = vec.crbegin();
    // cr_it->data = 100;  // 修改第一个元素

    std::cout << std::endl;
}

void test_push_pop() {
    std::cout << '\n'
              << std::string(25, '-') << "test_push_pop" << std::string(25, '-')
              << std::endl;
    stl::vector<test_vector> vec;
    std::cout << "使用push_back添加元素: ";
    vec.push_back(test_vector(1));
    vec.push_back(test_vector(2));
    vec.push_back(test_vector(3));
    print_vector(vec, "vec");

    std::cout << "\n使用pop_back移除最后一个元素: ";
    vec.pop_back();
    print_vector(vec, "vec");
}

void test_insert() {
    std::cout << '\n'
              << std::string(25, '-') << "test_insert" << std::string(25, '-')
              << std::endl;
    stl::vector<test_vector> vec{1, 2, 3, 4, 5};
    print_vector(vec, "vec");

    std::cout << "\n在位置2插入单个元素42: ";

    vec.insert(vec.begin() + 1, test_vector(42));
    print_vector(vec, "vec");

    std::cout << "\n在位置2插入多个元素: ";
    auto it = vec.insert(vec.begin() + 1, 3, test_vector(99));
    print_vector(vec, "vec");
    for (size_t i = 0; i < 3; ++i)
        std::cout << "新插入元素: " << (it + i)->data << " \n";

    std::cout << "\n在位置2插入一个范围: ";
    stl::vector<test_vector> vec2{6, 7, 8, 9};
    it = vec.insert(vec.begin() + 1, vec2.begin(), vec2.end());
    print_vector(vec, "vec");
    for (size_t i = 0; i < vec2.size(); ++i)
        std::cout << "新插入元素: " << (it + i)->data << " \n";

    std::cout << "\n在位置2插入一个初始化列表: ";
    it = vec.insert(vec.begin() + 1, {10, 11, 12});
    print_vector(vec, "vec");
    for (size_t i = 0; i < 3; ++i)
        std::cout << "新插入元素: " << (it + i)->data << " \n";
}

void test_swap() {
    std::cout << '\n'
              << std::string(25, '-') << "test_swap" << std::string(25, '-')
              << std::endl;
    stl::vector<test_vector> vec1{1, 2, 3};
    stl::vector<test_vector> vec2{4, 5, 6};

    std::cout << "交换前:" << std::endl;
    print_vector(vec1, "vec1");
    print_vector(vec2, "vec2");

    vec1.swap(vec2);

    std::cout << "交换后:" << std::endl;
    print_vector(vec1, "vec1");
    print_vector(vec2, "vec2");
}

void test_clear() {
    std::cout << '\n'
              << std::string(25, '-') << "test_clear" << std::string(25, '-')
              << std::endl;
    stl::vector<test_vector> vec{1, 2, 3, 4, 5};
    print_vector(vec, "vec");

    vec.clear();
    std::cout << "清空后:" << std::endl;
    print_vector(vec, "vec");
}

void test_capacity() {
    std::cout << '\n'
              << std::string(25, '-') << "test_capacity" << std::string(25, '-')
              << std::endl;
    stl::vector<test_vector> vec{1, 2, 3, 4, 5};
    print_vector(vec, "vec");

    std::cout << "当前容量: " << vec.capacity() << std::endl;

    vec.reserve(10);
    std::cout << "扩展后容量: " << vec.capacity() << std::endl;

    vec.resize(3);
    std::cout << "调整后容量: " << vec.capacity() << std::endl;

    vec.shrink_to_fit();
    std::cout << "收缩后容量: " << vec.capacity() << std::endl;
}

void test_time() {
    std::cout << '\n'
              << std::string(25, '-') << "test_time" << std::string(25, '-')
              << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    constexpr long long N = 100000000;
    stl::vector<test_vector> vec;
    for (int i = 0; i < N; ++i) {
        vec.push_back(test_vector(i));
    }
    for (int i = 0; i < N; ++i) {
        vec.pop_back();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "YIice_STL 耗时: " << duration.count() << " 毫秒" << std::endl;
}

int main() {
    test_constructor();
    test_assign();
    test_iterator();
    test_push_pop();
    test_insert();
    test_swap();
    test_clear();
    test_capacity();
    test_time();
    std::cout << "总构造次数: " << construct_count << std::endl;
    std::cout << "总析构次数: " << destructor_count << std::endl;
    return 0;
}