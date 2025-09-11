#ifndef INSERT_HPP
#define INSERT_HPP

#include "rbtree.h"

template <typename T, typename Compare>
void RBTree<T, Compare>::insert(const T& val) {
    Node<T>* new_node = new Node<T>(val);
    if (!root_) {
        root_ = new_node;
        root_->color_ = Color::Black;
        return;
    }
    Node<T>* curr = root_;
    Node<T>* parent_ = nullptr;
    // Поиск родителя
    while (curr) {
        parent_ = curr;
        if (comp_(val, curr->val_)) {
            curr = curr->left_;
        } else if (comp_(curr->val_, val)) {
            curr = curr->right_;
        } else {
            delete new_node;
            return;
        }
    }
    new_node->parent_ = parent_;
    if (comp_(val, parent_->val_)) {
        parent_->left_ = new_node;
    } else {
        parent_->right_ = new_node;
    }
    
    fix_insert(new_node);
}

#endif