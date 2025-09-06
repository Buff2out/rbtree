#ifndef VISUALIZE_HPP
#define VISUALIZE_HPP

#include "rbtree.h"
#include <iostream>
#include <queue>

template <typename T, typename Compare>
void RBTree<T, Compare>::visualize() const {
    if (!root_) {
        std::cout << "Tree is empty" << std::endl;
        return;
    }

    std::queue<Node<T>*> q;
    q.push(root_);
    int level = 0;
    
    while (!q.empty()) {
        int level_size = q.size();
        std::cout << "Level " << level << ": ";
        
        for (int i = 0; i < level_size; ++i) {
            Node<T>* current = q.front();
            q.pop();
            
            if (current) {
                // Выводим значение и цвет
                std::cout << current->val_ 
                         << (current->color_ == Color::Red ? "(R)" : "(B)");
                
                // Добавляем детей в очередь
                if (current->left_ || current->right_) {
                    q.push(current->left_);
                    q.push(current->right_);
                }
                
                // Разделитель между узлами
                if (i < level_size - 1) std::cout << " - ";
            } else {
                std::cout << "NULL";
            }
        }
        
        std::cout << std::endl;
        level++;
    }
}

#endif