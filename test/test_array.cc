#include <iostream>
#include "array.h"
using namespace stl;

int main() {
    array<int, 5> arr1 = {1, 2, 3, 4, 5};
    array<int, 5> arr2 = {1, 2, 3, 4, 5};
    array<int, 5> arr3 = {5, 4, 3, 2, 1};

    std::cout << (arr1 == arr2) << std::endl;  // 输出 1 (true)
    std::cout << (arr1 != arr3) << std::endl;  // 输出 1 (true)
    std::cout << (arr1 < arr3) << std::endl;   // 输出 1 (true)
    std::cout << (arr1 > arr3) << std::endl;   // 输出 0 (false)

    return 0;
}