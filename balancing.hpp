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

template <typename T, typename Compare>
void RBTree<T, Compare>::fix_insert(Node<T>* k) {
    while (k != root_ && k->parent_->color_ == Color::Red) {
        if (k->parent_ == k->parent_->parent_->left_) {
            Node<T>* uncle = k->parent_->parent_->right_;
            
            if (uncle && uncle->color_ == Color::Red) { // Case 2: Uncle is red
                k->parent_->color_ = Color::Black;
                uncle->color_ = Color::Black;
                k->parent_->parent_->color_ = Color::Red;
                k = k->parent_->parent_;
            } else {
                if (k == k->parent_->right_) { // Case 4: sigsag
                    k = k->parent_;
                    left_rotate(k);
                } // Case 5: line
                k->parent_->color_ = Color::Black; 
                k->parent_->parent_->color_ = Color::Red;
                right_rotate(k->parent_->parent_);
            }
        } else { // k->parent_ != k->parent_->parent_->left_
            Node<T>* uncle = k->parent_->parent_->left_;
            
            if (uncle && uncle->color_ == Color::Red) { // Case 2: Uncle is red
                k->parent_->color_ = Color::Black;
                uncle->color_ = Color::Black;
                k->parent_->parent_->color_ = Color::Red;
                k = k->parent_->parent_;
            } else {
                if (k == k->parent_->left_) { // Case 4: sigsag
                    k = k->parent_;
                    right_rotate(k);
                } // Case 5: line
                k->parent_->color_ = Color::Black;
                k->parent_->parent_->color_ = Color::Red;
                left_rotate(k->parent_->parent_);
            }
        }
    }
    root_->color_ = Color::Black; // case 3 grandpa is root
}

template <typename T, typename Compare>
void RBTree<T, Compare>::fix_delete(Node<T>* x) {
    while (x != root_ && x->color_ == Color::Black) {
        if (x == x->parent_->left_) {
            Node<T>* w = x->parent_->right_;
            
            if (w->color_ == Color::Red) {
                w->color_ = Color::Black;
                x->parent_->color_ = Color::Red;
                left_rotate(x->parent_);
                w = x->parent_->right_;
            }
            
            if ((!w->left_ || w->left_->color_ == Color::Black) &&
                (!w->right_ || w->right_->color_ == Color::Black)) {
                w->color_ = Color::Red;
                x = x->parent_;
            } else {
                if (!w->right_ || w->right_->color_ == Color::Black) {
                    if (w->left_) w->left_->color_ = Color::Black;
                    w->color_ = Color::Red;
                    right_rotate(w);
                    w = x->parent_->right_;
                }
                
                w->color_ = x->parent_->color_;
                x->parent_->color_ = Color::Black;
                if (w->right_) w->right_->color_ = Color::Black;
                left_rotate(x->parent_);
                x = root_;
            }
        } else {
            Node<T>* w = x->parent_->left_;
            
            if (w->color_ == Color::Red) {
                w->color_ = Color::Black;
                x->parent_->color_ = Color::Red;
                right_rotate(x->parent_);
                w = x->parent_->left_;
            }
            
            if ((!w->right_ || w->right_->color_ == Color::Black) &&
                (!w->left_ || w->left_->color_ == Color::Black)) {
                w->color_ = Color::Red;
                x = x->parent_;
            } else {
                if (!w->left_ || w->left_->color_ == Color::Black) {
                    if (w->right_) w->right_->color_ = Color::Black;
                    w->color_ = Color::Red;
                    left_rotate(w);
                    w = x->parent_->left_;
                }
                
                w->color_ = x->parent_->color_;
                x->parent_->color_ = Color::Black;
                if (w->left_) w->left_->color_ = Color::Black;
                right_rotate(x->parent_);
                x = root_;
            }
        }
    }
    x->color_ = Color::Black;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::transplant(Node<T>* u, Node<T>* v) {
    if (u->parent_ == nullptr) {
        root_ = v;
    } else if (u == u->parent_->left_) {
        u->parent_->left_ = v;
    } else {
        u->parent_->right_ = v;
    }
    
    if (v != nullptr) {
        v->parent_ = u->parent_;
    }
}

#endif