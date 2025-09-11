#ifndef VALIDATE_HPP
#define VALIDATE_HPP

#include "rbtree.h"
#include <cassert>

template <typename T>
int validate_rbtree_internal(Node<T>* node, int black_count, int current_black) {
    if (!node) return current_black;
    
    // Check: Красный узел не может иметь красных детей
    if (node->color_ == Color::Red) {
        assert(!node->left_ || node->left_->color_ == Color::Black);
        assert(!node->right_ || node->right_->color_ == Color::Black);
    }
    
    int left_black = validate_rbtree_internal(node->left_, black_count, 
                                   current_black + (node->color_ == Color::Black ? 1 : 0));
    int right_black = validate_rbtree_internal(node->right_, black_count, 
                                    current_black + (node->color_ == Color::Black ? 1 : 0));
    
    // Check: Все пути имеют одинаковое количество черных узлов
    assert(left_black == right_black);
    
    return left_black;
}

template <typename T>
void validate_rbtree(Node<T>* root) {
    if (!root) return;
    
    // Check: Корень всегда черный
    assert(root->color_ == Color::Black);
    
    int black_count = 0;
    Node<T>* node = root;
    while (node) {
        black_count += (node->color_ == Color::Black ? 1 : 0);
        node = node->left_;
    }
    
    validate_rbtree_internal(root, black_count, 0);
}

#endif