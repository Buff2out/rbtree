#include "rbtree.h"

int main () {
    RBTree<int> tree;
    
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();
    
    tree.insert(10);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();

    tree.insert(30);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();

    tree.insert(20);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();

    tree.insert(40);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();

    tree.insert(25);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();

    tree.insert(35);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();

    tree.insert(45);    
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();
    
    tree.insert(50);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();

    tree.insert(60);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();

    tree.insert(70);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();

    tree.insert(80);
    std::cout << "RBTree visualization:" << std::endl;
    tree.visualize();


    
    return 0;
}