#ifndef BALANCING_HPP
#define BALANCING_HPP

#include "rbtree.h"

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

#endif