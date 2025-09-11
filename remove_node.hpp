#ifndef REMOVE_NODE_HPP
#define REMOVE_NODE_HPP

#include "rbtree.h"

template <typename T, typename Compare>
void RBTree<T, Compare>::erase(const T& val_) {
    Node<T>* z = find(val_);
    if (!z) return;

    Node<T>* y = z;
    Node<T>* x = nullptr;
    Color y_original_color = y->color_;

    if (!z->left_) {
        x = z->right_;
        transplant(z, z->right_);
    } else if (!z->right_) {
        x = z->left_;
        transplant(z, z->left_);
    } else {
        y = z->right_;
        while (y->left_) {
            y = y->left_;
        }
        y_original_color = y->color_;
        x = y->right_;

        if (y->parent_ == z) {
            if (x) x->parent_ = y;
        } else {
            transplant(y, y->right_);
            y->right_ = z->right_;
            y->right_->parent_ = y;
        }

        transplant(z, y);
        y->left_ = z->left_;
        y->left_->parent_ = y;
        y->color_ = z->color_;
    }

    delete z;

    if (y_original_color == Color::Black && x) {
        fix_delete(x);
    }
}

#endif