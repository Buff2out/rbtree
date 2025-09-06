#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "rbtree.h"

template <typename T, typename Compare>
RBTree<T, Compare>& RBTree<T, Compare>::operator=(const RBTree& other) {
    if (this != &other) {
        RBTree temp(other);
        std::swap(root_, temp.root_);
        comp_ = other.comp_;
    }
    return *this;
}

template <typename T, typename Compare>
RBTree<T, Compare>& RBTree<T, Compare>::operator=(RBTree&& other) noexcept {
    if (this != &other) {
        clear(root_);
        root_ = other.root_;
        comp_ = std::move(other.comp_);
        other.root_ = nullptr;
    }
    return *this;
}

#endif