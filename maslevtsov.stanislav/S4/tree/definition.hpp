#ifndef TREE_DEFINITION_HPP
#define TREE_DEFINITION_HPP

#include "declaration.hpp"
#include <utility>

template< class Key, class T, class Compare >
maslevtsov::Tree< Key, T, Compare >::Tree():
  dummy_root_(new Node{value_type(), value_type(), nullptr, nullptr, nullptr, nullptr, true}),
  size_(0),
  compare_(Compare())
{}

template< class Key, class T, class Compare >
maslevtsov::Tree< Key, T, Compare >::Tree(const Tree& rhs):
  Tree()
{
  for (auto it = rhs.cbegin(); it != rhs.cend(); ++it) {
    insert(std::make_pair(it->first, it->second));
  }
}

template< class Key, class T, class Compare >
maslevtsov::Tree< Key, T, Compare >::Tree(Tree&& rhs) noexcept:
  dummy_root_(std::exchange(rhs.dummy_root_, nullptr)),
  size_(std::exchange(rhs.size_, 0))
{}

template< class Key, class T, class Compare >
maslevtsov::Tree< Key, T, Compare >::~Tree()
{
  clear();
  delete dummy_root_;
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::Tree& maslevtsov::Tree< Key, T, Compare >::operator=(const Tree& rhs)
{
  if (dummy_root_ != rhs.dummy_root_) {
    Tree< Key, T, Compare > copied_rhs(rhs);
    swap(copied_rhs);
  }
  return *this;
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::Tree& maslevtsov::Tree< Key, T, Compare >::operator=(Tree&& rhs) noexcept
{
  if (dummy_root_ != rhs.dummy_root_) {
    Tree< Key, T, Compare > moved_rhs(std::move(rhs));
    swap(moved_rhs);
  }
  return *this;
}

template< class Key, class T, class Compare >
T& maslevtsov::Tree< Key, T, Compare >::operator[](const Key& key)
{
  return insert(std::make_pair(key, T())).first->second;
}

template< class Key, class T, class Compare >
T& maslevtsov::Tree< Key, T, Compare >::operator[](Key&& key)
{
  return insert(std::make_pair(std::move(key), T())).first->second;
}

template< class Key, class T, class Compare >
T& maslevtsov::Tree< Key, T, Compare >::at(const Key& key)
{
  iterator it = find(key);
  if (it != end()) {
    return it->second;
  }
  throw std::out_of_range("invalid key");
}

template< class Key, class T, class Compare >
const T& maslevtsov::Tree< Key, T, Compare >::at(const Key& key) const
{
  const_iterator it = find(key);
  if (it != cend()) {
    return it->second;
  }
  throw std::out_of_range("invalid key");
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::iterator maslevtsov::Tree< Key, T, Compare >::begin()
{
  return {const_iterator::get_min_node(dummy_root_->left), true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator maslevtsov::Tree< Key, T, Compare >::begin() const
{
  return {const_iterator::get_min_node(dummy_root_->left), true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator
  maslevtsov::Tree< Key, T, Compare >::cbegin() const noexcept
{
  return {const_iterator::get_min_node(dummy_root_->left), true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::iterator maslevtsov::Tree< Key, T, Compare >::end()
{
  return {dummy_root_, true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator maslevtsov::Tree< Key, T, Compare >::end() const
{
  return {dummy_root_, true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator maslevtsov::Tree< Key, T, Compare >::cend() const noexcept
{
  return {dummy_root_, true};
}

template< class Key, class T, class Compare >
bool maslevtsov::Tree< Key, T, Compare >::empty() const noexcept
{
  return size_ == 0;
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::size_type maslevtsov::Tree< Key, T, Compare >::size() const noexcept
{
  return size_;
}

template< class Key, class T, class Compare >
void maslevtsov::Tree< Key, T, Compare >::clear() noexcept
{
  clear_subtree(dummy_root_->left);
  dummy_root_->left = nullptr;
}

template< class Key, class T, class Compare >
std::pair< typename maslevtsov::Tree< Key, T, Compare >::iterator, bool >
  maslevtsov::Tree< Key, T, Compare >::insert(const value_type& value)
{
  if (empty()) {
    Node* n = new Node{value, value, dummy_root_, nullptr, nullptr, nullptr, true};
    dummy_root_->left = n;
    ++size_;
    return {iterator(n, true), true};
  }
  auto result = find_impl(value.first);
  if (result.second) {
    return result;
  }
  return result;
}

template< class Key, class T, class Compare >
void maslevtsov::Tree< Key, T, Compare >::swap(Tree& other) noexcept
{
  std::swap(dummy_root_, other.dummy_root_);
  std::swap(size_, other.size_);
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::size_type
  maslevtsov::Tree< Key, T, Compare >::count(const Key& key) const noexcept
{
  if (find(key) != cend()) {
    return 1;
  }
  return 0;
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::iterator
  maslevtsov::Tree< Key, T, Compare >::find(const Key& key) noexcept
{
  auto result = find_impl(key);
  if (result.second) {
    return iterator(result.first.node_, result.first.is_first_);
  }
  return end();
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator
  maslevtsov::Tree< Key, T, Compare >::find(const Key& key) const noexcept
{
  auto result = find_impl(key);
  if (result.second) {
    return const_iterator(result.first.node_, result.first.is_first_);
  }
  return cend();
}

template< class Key, class T, class Compare >
std::pair< typename maslevtsov::Tree< Key, T, Compare >::iterator,
  typename maslevtsov::Tree< Key, T, Compare >::iterator >
  maslevtsov::Tree< Key, T, Compare >::equal_range(const Key& key)
{
  iterator first_it = find_impl(key).first;
  iterator second_it = first_it;
  if (second_it != end()) {
    ++second_it;
  }
  return std::make_pair(first_it, second_it);
}

template< class Key, class T, class Compare >
std::pair< typename maslevtsov::Tree< Key, T, Compare >::const_iterator,
  typename maslevtsov::Tree< Key, T, Compare >::const_iterator >
  maslevtsov::Tree< Key, T, Compare >::equal_range(const Key& key) const
{
  iterator it = find_impl(key).first;
  const_iterator first_it = const_iterator(it.node_, it.is_first_);
  const_iterator second_it = first_it;
  if (second_it != cend()) {
    ++second_it;
  }
  return std::make_pair(first_it, second_it);
}

template< class Key, class T, class Compare >
void maslevtsov::Tree< Key, T, Compare >::clear_subtree(Node* node) noexcept
{
  if (!node) {
    return;
  }
  clear_subtree(node->left);
  clear_subtree(node->middle);
  clear_subtree(node->right);
  delete node;
}

template< class Key, class T, class Compare >
std::pair< typename maslevtsov::Tree< Key, T, Compare >::iterator, bool >
  maslevtsov::Tree< Key, T, Compare >::find_impl(const Key& key) const noexcept
{
  if (empty()) {
    return {iterator(dummy_root_, true), true};
  }
  Node* current = dummy_root_->left;
  Node* greater = nullptr;
  bool greater_is_first = true;
  while (current) {
    if (!compare_(key, current->data1.first) && !compare_(current->data1.first, key)) {
      return std::make_pair(iterator(current, true), true);
    }
    if (!current->is_two && !compare_(key, current->data2.first) && !compare_(current->data2.first, key)) {
      return std::make_pair(iterator(current, false), true);
    }
    if (compare_(key, current->data1.first)) {
      greater = current;
      greater_is_first = true;
      current = current->left;
    } else if (!current->is_two && compare_(key, current->data2.first)) {
      greater = current;
      greater_is_first = false;
      current = current->middle;
    } else {
      current = current->right;
    }
  }
  if (greater) {
    return std::make_pair(iterator(greater, greater_is_first), false);
  } else {
    return std::make_pair(iterator(dummy_root_, true), false);
  }
}

#endif
