#include "rbtree.h"

int main () {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    
    Node<int>* root = tree.get_root();
}