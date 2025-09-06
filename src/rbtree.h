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
    void insert(const T& val_);
    [[nodiscard]] Node<T>* get_root() const { return root_; }

private:
    Node<T>* root_;
    Compare comp_;

    void left__rotate(Node<T>* x);
    void right_rotate(Node<T>* x);
    void fix_insert(Node<T>* k);
    void clear(Node<T>* node);
};

template <typename T, typename Compare>
void RBTree<T, Compare>::clear(Node<T>* node) {
    if (node) {
        clear(node->left_);
        clear(node->right_);
        delete node;
    }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::insert(const T& val_) {
    Node<T>* new_node = new Node<T>(val_);
    if (!root_) {
        root_ = new_node;
        root_->color_ = Color::Black;
        return;
    }
    Node<T>* curr = root_;
    Node<T>* parent_ = nullptr;
    // Поиск места для вставки
    while (curr) {
        parent_ = curr;
        if (comp_(val_, curr->val_)) {
            curr = curr->left_;
        } else if (comp_(curr->val_, val_)) {
            curr = curr->right_;
        } else {
            delete new_node;
            return;
        }
    }
    new_node->parent_ = parent_;
    if (comp_(val_, parent_->val_)) {
        parent_->left_ = new_node;
    } else {
        parent_->right_ = new_node;
    }
    // TODO: Реализовать полную вставку с компаратором
}

#endif // RBTREE_H