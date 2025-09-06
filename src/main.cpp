#include "rbtree.h"

int main () {
    RBTree tree;
    tree.insert(10);
    tree.insert(20);
    
    Node* root = tree.get_root();
}