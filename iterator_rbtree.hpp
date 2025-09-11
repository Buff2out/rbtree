#ifndef ITERATOR_RBTREE_HPP
#define ITERATOR_RBTREE_HPP

#include "rbtree.h"

template <typename T, typename Compare>
class RBTree<T, Compare>::iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    explicit iterator(Node<T>* node = nullptr) : current_(node) {}

    reference operator*() const { return current_->val_; }
    pointer operator->() const { return &current_->val_; }

    iterator& operator++() {
        if (!current_) return *this;
        
        if (current_->right_) {
            current_ = current_->right_;
            while (current_->left_) {
                current_ = current_->left_;
            }
        } else {
            Node<T>* parent = current_->parent_;
            while (parent && current_ == parent->right_) {
                current_ = parent;
                parent = parent->parent_;
            }
            current_ = parent;
        }
        return *this;
    }

    iterator operator++(int) {
        iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    iterator& operator--() {
        if (!current_) return *this;
        
        if (current_->left_) {
            current_ = current_->left_;
            while (current_->right_) {
                current_ = current_->right_;
            }
        } else {
            Node<T>* parent = current_->parent_;
            while (parent && current_ == parent->left_) {
                current_ = parent;
                parent = parent->parent_;
            }
            current_ = parent;
        }
        return *this;
    }

    iterator operator--(int) {
        iterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const iterator& other) const { return current_ == other.current_; }
    bool operator!=(const iterator& other) const { return current_ != other.current_; }

private:
    Node<T>* current_;
};

template <typename T, typename Compare>
class RBTree<T, Compare>::const_iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    explicit const_iterator(const Node<T>* node = nullptr) : current_(node) {}

    const_iterator(const iterator& it) : current_(it.current_) {}

    reference operator*() const { return current_->val_; }
    pointer operator->() const { return &current_->val_; }

    const_iterator& operator++() {
        if (!current_) return *this;
        
        if (current_->right_) {
            current_ = current_->right_;
            while (current_->left_) {
                current_ = current_->left_;
            }
        } else {
            const Node<T>* parent = current_->parent_;
            while (parent && current_ == parent->right_) {
                current_ = parent;
                parent = parent->parent_;
            }
            current_ = parent;
        }
        return *this;
    }

    const_iterator operator++(int) {
        const_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    const_iterator& operator--() {
        if (!current_) return *this;
        
        if (current_->left_) {
            current_ = current_->left_;
            while (current_->right_) {
                current_ = current_->right_;
            }
        } else {
            const Node<T>* parent = current_->parent_;
            while (parent && current_ == parent->left_) {
                current_ = parent;
                parent = parent->parent_;
            }
            current_ = parent;
        }
        return *this;
    }

    const_iterator operator--(int) {
        const_iterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const const_iterator& other) const { return current_ == other.current_; }
    bool operator!=(const const_iterator& other) const { return current_ != other.current_; }

private:
    const Node<T>* current_;
};

template <typename T, typename Compare>
typename RBTree<T, Compare>::iterator RBTree<T, Compare>::begin() {
    Node<T>* node = root_;
    while (node && node->left_) {
        node = node->left_;
    }
    return iterator(node);
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::iterator RBTree<T, Compare>::end() {
    return iterator(nullptr);
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::const_iterator RBTree<T, Compare>::begin() const {
    const Node<T>* node = root_;
    while (node && node->left_) {
        node = node->left_;
    }
    return const_iterator(node);
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::const_iterator RBTree<T, Compare>::end() const {
    return const_iterator(nullptr);
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::const_iterator RBTree<T, Compare>::cbegin() const {
    return begin();
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::const_iterator RBTree<T, Compare>::cend() const {
    return end();
}

#endif