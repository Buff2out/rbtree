#ifndef VISUALIZE_HPP
#define VISUALIZE_HPP

#include "rbtree.h"
#include <iostream>
#include <string>

template <typename T>
static void visualize_helper(const Node<T>* node, const std::string& prefix, bool is_left) {
    if (!node) return;

    if (node->right_) {
        visualize_helper(node->right_, prefix + (is_left ? "│   " : "    "), false);
    }

    std::cout << prefix 
              << (is_left ? "└── " : "┌── ")
              << node->val_ 
              << "(" 
              << (node->color_ == Color::Red ? "R" : "B")
              << ")\n";

    if (node->left_) {
        visualize_helper(node->left_, prefix + (is_left ? "    " : "│   "), true);
    }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::visualize() const {
    if (!root_) {
        std::cout << "<empty tree>\n";
        return;
    }
    visualize_helper(root_, "", true);
    std::cout << std::endl;
}

#endif