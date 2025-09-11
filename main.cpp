#include "rbtree.h"

int main () {
    RBTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    std::vector<int> expected = {20, 30, 40, 50, 60, 70, 80};
    std::vector<int> actual;
    
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        actual.push_back(*it);
    }
    return 0;
}