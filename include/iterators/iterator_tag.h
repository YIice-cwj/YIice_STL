#pragma once
namespace stl {
namespace iterator_tag {

/**
 * @brief 输入迭代器
 */
struct input_iterator_tag {};

/**
 * @brief 输出迭代器
 */
struct output_iterator_tag {};

/**
 * @brief 前向迭代器
 */
struct forward_iterator_tag : input_iterator_tag {};

/**
 * @brief 双向迭代器
 */
struct bidirectional_iterator_tag : forward_iterator_tag {};

/**
 * @brief 随机访问迭代器
 */
struct random_access_iterator_tag : bidirectional_iterator_tag {};

}  // namespace iterator_tag
}  // namespace stl