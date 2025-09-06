#ifndef RBTREE_H
#define RBTREE_H

#include <cstddef>
#include <functional>

enum class Color { Red, Black };

template <typename T>
struct Node {
    T val_;
    Color color_;
    Node<T>* left_;
    Node<T>* right_;
    Node<T>* parent_;

    explicit Node(const T& val) 
        : val_(val), 
          color_(Color::Red),
          left_(nullptr),
          right_(nullptr),
          parent_(nullptr) {}
};

template <typename T, typename Compare = std::less<T>>
class RBTree {
public:
    RBTree() : root_(nullptr), comp_(Compare()) {}
    ~RBTree() { clear(root_); }
    RBTree(const RBTree& other);
    RBTree(RBTree&& other) noexcept;
    RBTree& operator=(const RBTree& other);
    RBTree& operator=(RBTree&& other) noexcept;
    void insert(const T& val_);
    [[nodiscard]] Node<T>* get_root() const { return root_; }

private:
    Node<T>* root_;
    Compare comp_;

    void left_rotate(Node<T>* up_to_leftdown);
    void right_rotate(Node<T>* up_to_rightdown);
    void fix_insert(Node<T>* k);
    void clear(Node<T>* node);
    void transplant(Node<T>* u, Node<T>* v);
};

template <typename T, typename Compare>
RBTree<T, Compare>::RBTree(const RBTree& other)
    : root_(nullptr), comp_(other.comp_) {
    if (other.root_) {
        root_ = copy_subtree(other.root_, nullptr);
    }
}

template <typename T, typename Compare>
Node<T>* copy_subtree(Node<T>* node, Node<T>* parent) {
    if (!node) return nullptr;
    Node<T>* new_node = new Node<T>(node->val_);
    new_node->color_ = node->color_;
    new_node->parent_ = parent;
    new_node->left_ = copy_subtree(node->left_, new_node);
    new_node->right_ = copy_subtree(node->right_, new_node);
    return new_node;
}

template <typename T, typename Compare>
RBTree<T, Compare>::RBTree(RBTree&& other) noexcept
    : root_(other.root_), comp_(std::move(other.comp_)) {
    other.root_ = nullptr;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::clear(Node<T>* node) {
    if (node) {
        clear(node->left_);
        clear(node->right_);
        delete node;
    }
}

#include "operators.hpp"

#include "balancing.hpp"

#include "insert.hpp"

#endif // RBTREE_H