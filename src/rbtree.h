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

    void left_rotate(Node<T>* up_to_leftdown);
    void right_rotate(Node<T>* up_to_rightdown);
    void fix_insert(Node<T>* k);
    void clear(Node<T>* node);
    void transplant(Node<T>* u, Node<T>* v);
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
void RBTree<T, Compare>::left_rotate(Node<T>* up_to_leftdown) { // 6-7 свапов указателей
    Node<T>* downright_to_up = up_to_leftdown->right_;
    up_to_leftdown->right_ = downright_to_up->left_;
    if (nullptr != downright_to_up->left_) { // если у правого есть левый потомок
        downright_to_up->left_->parent_ = up_to_leftdown;
    }
    downright_to_up->parent_ = up_to_leftdown->parent_;
    if (nullptr == up_to_leftdown->parent_) { // если верхний - корень
        root_ = downright_to_up;
    } else if (up_to_leftdown == up_to_leftdown->parent_->left_) { // если не корень, меняем 
        up_to_leftdown->parent_->left_ = downright_to_up;
    } else {
        up_to_leftdown->parent_->right_ = downright_to_up;
    }
    downright_to_up->left_ = up_to_leftdown;
    up_to_leftdown->parent_ = downright_to_up;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::right_rotate(Node<T>* up_to_rightdown) { // 6-7 свапов указателей
    Node<T>* downleft_to_up = up_to_rightdown->left_;
    up_to_rightdown->left_ = downleft_to_up->right_;
    if (nullptr != downleft_to_up->right_) { // если у правого есть левый потомок
        downleft_to_up->right_->parent_ = up_to_rightdown;
    }
    downleft_to_up->parent_ = up_to_rightdown->parent_;
    if (nullptr == up_to_rightdown->parent_) { // если верхний - корень
        root_ = downleft_to_up;
    } else if (up_to_rightdown == up_to_rightdown->parent_->right_) { // если не корень, меняем 
        up_to_rightdown->parent_->right_ = downleft_to_up;
    } else {
        up_to_rightdown->parent_->left_ = downleft_to_up;
    }
    downleft_to_up->right_ = up_to_rightdown;
    up_to_rightdown->parent_ = downleft_to_up;
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