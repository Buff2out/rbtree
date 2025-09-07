#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "rbtree.h"

template <typename T, typename Compare>
Node<T>* RBTree<T, Compare>::find(const T& val_) const {
    Node<T>* curr = root_;
    while (curr) {
        if (comp_(val_, curr->val_)) {
            curr = curr->left_;
        } else if (comp_(curr->val_, val_)) {
            curr = curr->right_;
        } else {
            return curr;
        }
    }
    return nullptr;
}

template <typename T, typename Compare>
bool RBTree<T, Compare>::contains(const T& val_) const {
    return find(val_) != nullptr;
}

#endif