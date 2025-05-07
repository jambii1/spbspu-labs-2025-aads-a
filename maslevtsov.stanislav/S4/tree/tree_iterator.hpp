#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iterator>
#include <type_traits>
#include "tree_node.hpp"

namespace maslevtsov {
  template< class T, bool is_const >
  class TreeIterator final: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    template< class Key, class Type, class Compare >
    friend class Tree;

    TreeIterator();
    TreeIterator(const TreeIterator& rhs) noexcept = default;
    ~TreeIterator() = default;
    TreeIterator& operator=(const TreeIterator& rhs) noexcept = default;

    TreeIterator& operator++();
    TreeIterator& operator++(int);
    TreeIterator& operator--();
    TreeIterator& operator--(int);

    typename std::conditional< is_const, const T&, T& >::type operator*() const;
    typename std::conditional< is_const, const T*, T* >::type operator->() const;

    bool operator==(const TreeIterator& rhs) const;
    bool operator!=(const TreeIterator& rhs) const;

  private:
    TreeNode< T >* node_;
    bool is_first_;

    TreeIterator(TreeNode< T >* node, bool is_first_);
    static TreeNode< T >* get_min_node(TreeNode< T >* node);
    static TreeNode< T >* get_max_node(TreeNode< T >* node);
  };

  template< class T, bool is_const >
  TreeIterator< T, is_const >::TreeIterator():
    node_(nullptr)
  {}

  template< class T, bool is_const >
  typename TreeIterator< T, is_const >::TreeIterator& TreeIterator< T, is_const >::operator++()
  {
    if (!(node_->is_two) && is_first_) {
      TreeNode< T >* min_node = get_min_node(node_->middle);
      if (!min_node) {
        is_first_ = false;
      } else {
        node_ = min_node;
      }
      return *this;
    }
    TreeNode< T >* min_node = get_min_node(node_->right);
    if (!min_node) {
      if (node_->parent) {
        while (node_->parent && node_->parent->right == node_) {
          node_ = node_->parent;
        }
        if (node_->parent && node_->parent->middle == node_) {
          node_ = node_->parent;
          is_first_ = false;
          return *this;
        } else if (node_->parent) {
          node_ = node_->parent;
        }
      }
    } else {
      node_ = min_node;
    }
    is_first_ = true;
    return *this;
  }

  template< class T, bool is_const >
  typename TreeIterator< T, is_const >::TreeIterator& TreeIterator< T, is_const >::operator++(int)
  {
    TreeIterator< T, is_const > result(*this);
    ++(*this);
    return result;
  }

  template< class T, bool is_const >
  typename TreeIterator< T, is_const >::TreeIterator& TreeIterator< T, is_const >::operator--()
  {
    if (!(node_->is_two) && !is_first_) {
      TreeNode< T >* max_node = get_max_node(node_->middle);
      if (!max_node) {
        is_first_ = true;
      } else {
        node_ = max_node;
      }
      return *this;
    }
    TreeNode< T >* max_node = get_max_node(node_->left);
    if (!max_node) {
      if (node_->parent) {
        while (node_->parent && node_->parent->left == node_) {
          node_ = node_->parent;
        }
        if (node_->parent && node_->parent->middle == node_) {
          node_ = node_->parent;
          is_first_ = true;
          return *this;
        } else if (node_->parent) {
          node_ = node_->parent;
        }
      }
    } else {
      node_ = max_node;
    }
    is_first_ = false;
    return *this;
  }

  template< class T, bool is_const >
  typename TreeIterator< T, is_const >::TreeIterator& TreeIterator< T, is_const >::operator--(int)
  {
    TreeIterator< T, is_const > result(*this);
    --(*this);
    return result;
  }

  template< class T, bool is_const >
  typename std::conditional< is_const, const T&, T& >::type TreeIterator< T, is_const >::operator*() const
  {
    return is_first_ ? node_->data1 : node_->data2;
  }

  template< class T, bool is_const >
  typename std::conditional< is_const, const T*, T* >::type TreeIterator< T, is_const >::operator->() const
  {
    return is_first_ ? std::addressof(node_->data1) : std::addressof(node_->data2);
  }

  template< class T, bool is_const >
  bool TreeIterator< T, is_const >::operator==(const TreeIterator& rhs) const
  {
    return node_ == rhs.node_ && (!node_ || is_first_ == rhs.is_first_);
  }

  template< class T, bool is_const >
  bool TreeIterator< T, is_const >::operator!=(const TreeIterator& rhs) const
  {
    return !(*this == rhs);
  }

  template< class T, bool is_const >
  TreeIterator< T, is_const >::TreeIterator(TreeNode< T >* node, bool is_first):
    node_(node),
    is_first_(is_first)
  {}

  template< class T, bool is_const >
  TreeNode< T >* TreeIterator< T, is_const >::get_min_node(TreeNode< T >* node)
  {
    TreeNode< T >* result = node;
    while (result && result->left) {
      result = result->left;
    }
    return result;
  }

  template< class T, bool is_const >
  TreeNode< T >* TreeIterator< T, is_const >::get_max_node(TreeNode< T >* node)
  {
    TreeNode< T >* result = node;
    while (result && result->right) {
      result = result->right;
    }
    return result;
  }
}

#endif
