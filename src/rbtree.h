#ifndef RBTREE_H
#define RBTREE_H

#include <cstddef>

enum class Color { Red, Black };

struct Node {
    int value;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    explicit Node(int val) 
        : value(val), 
          color(Color::Red),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
};

class RBTree {
public:
    RBTree() : root(nullptr) {}
    ~RBTree() { clear(root); }
    
    void insert(int value);

    [[nodiscard]] Node* get_root() const { return root; }

private:
    Node* root;

    void left_rotate(Node* x);
    void right_rotate(Node* x);
    void fix_insert(Node* k);
    
    // Вспомогательная функция для очистки памяти
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

inline void RBTree::insert(int value) {
    Node* new_node = new Node(value);
    if (!root) {
        root = new_node;
        root->color = Color::Black;
    }
    // TODO: Реализовать полную вставку
}

#endif // RBTREE_H