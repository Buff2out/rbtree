#include "rbtree.h"

int main () {
    RBTree<int> tree;
    
    // Вставляем тестовые данные
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(45);
    
    // Визуализируем дерево
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();
    
    return 0;
}