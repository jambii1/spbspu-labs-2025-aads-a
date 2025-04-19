#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

namespace maslevtsov {
  template< class T >
  struct TreeNode
  {
    T data1_;
    T data2_;
    TreeNode* parent_;
    TreeNode* left_;
    TreeNode* middle_;
    TreeNode* right_;
    bool is_two;
  };
}

#endif
