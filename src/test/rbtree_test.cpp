#include "../rbtree.h"
#include <gtest/gtest.h>

// Проверка вставки одного элемента
TEST(RBTreeTest, insert_single) {
    RBTree tree;
    tree.insert(10);
    
    Node* root = tree.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->color, Color::Black); // Корень всегда чёрный
}

// Проверка вставки двух элементов (простой случай)
TEST(RBTreeTest, insert_two_nodes) {
    RBTree tree;
    tree.insert(10);
    tree.insert(20);
    
    Node* root = tree.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->color, Color::Black);
    
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->value, 20);
    EXPECT_EQ(root->right->color, Color::Red); // Новый узел красный
}

// Проверка дубликатов (по заданию не требуется, но для TDD)
TEST(RBTreeTest, insert_duplicate) {
    RBTree tree;
    tree.insert(10);
    tree.insert(10); // Дубликат
    
    // В стандартном КЧ-дереве дубликаты не разрешены
    // Проверяем, что количество узлов не увеличилось
    EXPECT_EQ(tree.get_root()->value, 10);
    EXPECT_EQ(tree.get_root()->left, nullptr);
    EXPECT_EQ(tree.get_root()->right, nullptr);
}