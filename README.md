# YIICE_STL

## 简介

基于 `c++14` 标准实现的 yiice_stl 库, 这是我的第一个 `c++`项目, 用于学习 `c++`标准库中的萃取器, 替换失败并非错误`SFINAE(Substitution Failure Is Not An Error)` ,容器, 算法, 迭代器等, 以及一些 `c++14` 新特性, 里面我添加了详细的注释中文注释, 方便大家学习, 有什么 `bug` 或者建议, 欢迎大家提出, 一起进步.

## STL 目录

#### **类型萃取器 `type_traits`：**

- **[整型常量](include/type_traits/integral_constant.h)** `integral_constant`

- **[移除 const](include/type_traits/remove_const.h)** `remove_const`

- **[移除 volatile](include/type_traits/remove_volatile.h)** `remove_volatile`

- **[移除 cv](include/type_traits/remove_cv.h)** `remove_cv`

- **[移除引用](include/type_traits/remove_reference.h)** `remove_reference`

- **[移除一维指针](include/type_traits/remove_pointer.h)** `remove_pointer`

- **[移除所有维度的指针](include/type_traits/remove_all_pointer.h)** `remove_all_pointer`

- **[移除一维数组维度](include/type_traits/remove_extent.h)** `remove_extent`

- **[移除所有数组维度](include/type_traits/remove_all_extent.h)** `remove_all_extent`

- **[添加 const](include/type_traits/add_const.h)** `add_const`

- **[添加 volatile](include/type_traits/add_volatile.h)** `add_volatile`

- **[添加 cv](include/type_traits/add_cv.h)** `add_cv`

- **[添加指针](include/type_traits/add_pointer.h)** `add_pointer`

- **[添加左引用](include/type_traits/add_lvalue_reference.h)** `add_lvalue_reference`

- **[添加右引用](include/type_traits/add_rvalue_reference.h)** `add_rvalue_reference`

- **[检查是否为指针](include/type_traits/is_pointer.h)** `is_pointer`

- **[检查是否为引用](include/type_traits/is_reference.h)** `is_reference`

- **[检查是否为左值引用](include/type_traits/is_lvalue_reference.h)** `is_lvalue_reference`

- **[检查是否为右值引用](include/type_traits/is_rvalue_reference.h)** `is_rvalue_reference`

- **[检查是否为 const](include/type_traits/is_const.h)** `is_const`

- **[检查是否为 volatile](include/type_traits/is_volatile.h)** `is_volatile`

- **[检查是否为 cv](include/type_traits/is_cv.h)** `is_cv`

- **[检查是否为函数](include/type_traits/is_function.h)** `is_function`

- **[检查是否为 void](include/type_traits/is_void.h)** `is_void`

- **[检查是否为数组](include/type_traits/is_array.h)** `is_array`

- **[检查是否为整型](include/type_traits/is_integral.h)** `is_integral`

- **[检查是否为浮点型](include/type_traits/is_floating_point.h)** `is_floating_point`

- **[检查是否成员指针](include/type_traits/is_member_pointer.h)** `is_member_pointer`

- **[检查是否为成员函数指针](include/type_traits/is_member_function_pointer.h)** `is_member_function_pointer`

- **[检查是否为成员对象指针](include/type_traits/is_member_object_pointer.h)** `is_member_object_pointer`

- **[检查是否可以拷贝](include/type_traits/is_copyable.h)** `is_copyable

- **[检查是否可以移动](include/type_traits/is_movable.h)** `is_movable

- **[检查是否为平凡类型](include/type_traits/is_trivial.h)** `is_trivial`

- **[检查是否可平凡拷贝](include/type_traits/is_trivially_copyable.h)** `is_trivially_copyable`

- **[检查是否可平凡移动](include/type_traits/is_trivially_movable.h)** `is_trivially_movable`

- **[检查是否为类](include/type_traits/is_class.h)** `is_class`

- **[检查是否为联合体](include/type_traits/is_union.h)** `is_union`

- **[检查是否为枚举](include/type_traits/is_enum.h)** `is_enum`

- **[检查是否为引用包装器](include/type_traits/is_reference_wrapper.h)** `is_reference_wrapper`

- **[检查是否为无符号](include/type_traits/is_unsigned.h)** `is_unsigned`

- **[检查是否为有符号](include/type_traits/is_signed.h)** `is_signed`

- **[检查是否为可构造](include/type_traits/is_constructible.h)** `is_constructible`

- **[检查是否可无异常构造](include/type_traits/is_nothrow_constructible.h)** `is_nothrow_constructible`

- **[检查是否可默认构造](include/type_traits/is_default_constructible.h)** `is_default_constructible`

- **[检查是否可拷贝构造](include/type_traits/is_copy_constructible.h)** `is_copy_constructible`

- **[检查是否可无异常拷贝构造](include/type_traits/is_nothrow_copy_constructible.h)** `is_nothrow_copy_constructible`

- **[检查是否可移动构造](include/type_traits/is_move_constructible.h)** `is_move_constructible`

- **[检查是否可无异常移动构造](include/type_traits/is_nothrow_move_constructible.h)** `is_nothrow_move_constructible`

- **[检查是否可平凡的默认构造](include/type_traits/is_trivially_default_constructible.h)** `is_trivially_default_constructible `

- **[检查是否可平凡构造](include/type_traits/is_trivially_constructible.h)** `is_trivially_constructible`

- **[检查是否可平凡拷贝构造](include/type_traits/is_trivially_copy_constructible.h)** `is_trivially_copy_constructible`

- **[检查是否可平凡移动构造](include/type_traits/is_trivially_move_constructible.h)** `is_trivially_move_constructible`

- **[检查是否可析构](include/type_traits/is_destructible.h)** `is_destructible`

- **[检查是否可无异常析构](include/type_traits/is_nothrow_destructible.h)** `is_nothrow_destructible`

- **[检查是否可赋值](include/type_traits/is_assignable.h)** `is_assignable`

- **[检查是否可无异常赋值](include/type_traits/is_nothrow_assignable.h)** `is_nothrow_assignable`

- **[检查是否可拷贝赋值](include/type_traits/is_copy_assignable.h)** `is_copy_assignable`

- **[检查是否可无异常拷贝赋值](include/type_traits/is_nothrow_copy_assignable.h)** `is_nothrow_copy_assignable`

- **[检查是否可移动赋值](include/type_traits/is_move_assignable.h)** `is_move_assignable`

- **[检查是否可无异常移动赋值](include/type_traits/is_nothrow_move_assignable.h)** `is_nothrow_move_assignable`

- **[检查是否可平凡赋值](include/type_traits/is_trivially_assignable.h)** `is_trivially_assignable`

- **[检查是否可平凡拷贝赋值](include/type_traits/is_trivially_copy_assignable.h)** `is_trivially_copy_assignable`

- **[检查是否可平凡移动赋值](include/type_traits/is_trivially_move_assignable.h)** `is_trivially_move_assignable`

- **[类型转换可行性检查](include/type_traits/is_convertible.h)** `is_convertible`

- **[检查是否为类型相等](include/type_traits/is_same.h)** `is_same`

- **[所有类型为 void](include/type_traits/void_t.h)** `void_t`

- **[启用检查](include/type_traits/enable_if.h)** `enable_if`

- **[条件检查](include/type_traits/conditional.h)** `conditional`

- **[衰减类型](include/type_traits/decay.h)** `decay`

#### **工具函数 `utility`：**

- **[交换](include/utility/swap.h)** `swap`

- **[移动语义](include/utility/move.h)** `move`

- **[最大值](include/utility/max.h)** `max`

- **[最小值](include/utility/min.h)** `min`

- **[未求值语义](include/utility/declval.h)** `declval`

- **[完美转发](include/utility/forward.h)** `forward`

- **[引用包装器](include/utility/reference_wrapper.h)** `reference_wrapper`

- **[元组](include/utility/tuple.h)** `tuple`

- **[一对](include/utility/pair.h)** `pair`

#### **内存工具 `memory`：**

- **[独享指针](include/memory/unique_ptr.h)** `unique_ptr`

- **[共享指针](include/memory/shared_ptr.h)** `shared_ptr`

- **[弱指针](include/memory/weak_ptr.h)** `weak_ptr`

- **[地址取值](include/memory/addressof.h)** `addressof`

- **[默认删除器](include/memory/default_delete.h)** `default_delete`

- **[启用共享指针](include/memory/enable_shared_from_this.h)** `enable_shared_from_this`

- **[分配器](include/memory/allocator.h)** `allocator`

- **[内存拷贝](include/memory/copy.h)** `copy`

- **[内存移动](include/memory/move.h)** `move`

- **[内存填充](include/memory/fill.h)** `fill`

#### **迭代器 `iterators`：**

- **[迭代器](include/iterators/iterator.h)** `iterator`

- **[反向迭代器](include/iterators/reverse_iterator.h)** `reverse_iterator`

- **[流迭代器](include/iterators/stream_iterator.h)** `stream_iterator`

#### **容器 `containers`：**

- **[字符串](include/string.h)** `string`

- **[字符串视图](include/string_view.h)** `string_view`

- **[数组](include/array.h)** `array`

- **[向量](include/vector.h)** `vector`

- **[单向链表](include/forward_list.h)** `forward_list`

- **[链表](include/list.h)** `list`

- **[双端队列](include/deque.h)** `deque`

- **[栈](include/stack.h)** `stack`

- **[队列](include/queue.h)** `queue`

- **[优先队列](include/priority_queue.h)** `priority_queue`

- **[平衡二叉树](include/binary_tree.h)** `binary_tree`

- **[B 树](include/b_tree.h)** `b_tree`

- **[B+ 树](include/b_plus_tree.h)** `b_plus_tree`

- **[红黑树](include/red_black_tree.h)** `red_black_tree`

- **[哈希表](include/hash_table.h)** `hash_table`

- **[有序哈希表](include/multihash_table.h)** `multihash_table`

- **[集合](include/set.h)** `set`

- **[无序集合](include/unordered_set.h)** `unordered_set`

- **[映射](include/map.h)** `map`

- **[无序映射](include/unordered_map.h)** `unordered_map`

#### **算法 `algorithms`：**

#### **函数 `functional`：**

- **[函数对象](include/functional/function.h)** `function`

- **[函数绑定](include/functional/bind.h)** `bind`

- **[加法](include/functional/plus.h)** `plus`

- **[减法](include/functional/minus.h)** `minus`

- **[乘法](include/functional/multiplies.h)** `multiplies`

- **[除法](include/functional/divides.h)** `divides`

- **[取模](include/functional/modulus.h)** `modulus`

- **[取反](include/functional/negate.h)** `negate`

- **[逻辑与](include/functional/logical_and.h)** `logical_and`

- **[逻辑或](include/functional/logical_or.h)** `logical_or`

- **[逻辑非](include/functional/logical_not.h)** `logical_not`

- **[相等](include/functional/equal_to.h)** `equal_to`

- **[不相等](include/functional/not_equal_to.h)** `not_equal_to`

- **[小于](include/functional/less.h)** `less`

- **[小于等于](include/functional/less_equal.h)** `less_equal`

- **[大于](include/functional/greater.h)** `greater`

- **[大于等于](include/functional/greater_equal.h)** `greater_equal`

## 支持

- **支持的编译器：`GCC`、`Clang`、`MSVC` 等**

- **编译器版本：最低版本 `C++14`, 建议使用 `C++14` 及以上版本的编译器**

- **操作系统：`Windows`、`Linux`、`macOS` 等**

## 依赖

- **无需额外的第三方库依赖**
- **仅需标准 `C++14` 支持**

## 编译和构建

- **使用 CMake 进行构建**

## 许可证

本项目采用 MIT 许可证

## 贡献

如果您有任何建议或想要贡献代码，请随时提交 Pull Request 或创建 Issue
