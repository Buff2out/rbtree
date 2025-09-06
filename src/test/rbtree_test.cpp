#include "../rbtree.h"
#include <gtest/gtest.h>

// Проверка вставки одного элемента
TEST(RBTreeTest, insert_single) {
    RBTree<int> tree;
    tree.insert(10);
    
    Node<int>* root = tree.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->val_, 10);
    EXPECT_EQ(root->color_, Color::Black); // Корень всегда чёрный
}

// Проверка вставки двух элементов (простой случай)
TEST(RBTreeTest, insert_two_nodes) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    
    Node<int>* root = tree.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->val_, 10);
    EXPECT_EQ(root->color_, Color::Black);
    
    ASSERT_NE(root->right_, nullptr);
    EXPECT_EQ(root->right_->val_, 20);
    EXPECT_EQ(root->right_->color_, Color::Red); // Новый узел красный
}

// Проверка дубликатов (по заданию не требуется, но для TDD)
TEST(RBTreeTest, insert_duplicate) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(10); // Дубликат
    
    // В стандартном КЧ-дереве дубликаты не разрешены
    // Проверяем, что количество узлов не увеличилось
    EXPECT_EQ(tree.get_root()->val_, 10);
    EXPECT_EQ(tree.get_root()->left_, nullptr);
    EXPECT_EQ(tree.get_root()->right_, nullptr);
}