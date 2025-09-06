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

// Проверка балансировки после вставки (левый поворот)
TEST(RBTreeTest, insert_balance_left_rotate) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30); // Должен вызвать левый поворот
    
    Node<int>* root = tree.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->val_, 20);
    EXPECT_EQ(root->color_, Color::Black);
    
    ASSERT_NE(root->left_, nullptr);
    EXPECT_EQ(root->left_->val_, 10);
    EXPECT_EQ(root->left_->color_, Color::Red);
    
    ASSERT_NE(root->right_, nullptr);
    EXPECT_EQ(root->right_->val_, 30);
    EXPECT_EQ(root->right_->color_, Color::Red);
}

// Проверка балансировки после вставки (правый поворот)
TEST(RBTreeTest, insert_balance_right_rotate) {
    RBTree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10); // Должен вызвать правый поворот
    
    Node<int>* root = tree.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->val_, 20);
    EXPECT_EQ(root->color_, Color::Black);
    
    ASSERT_NE(root->left_, nullptr);
    EXPECT_EQ(root->left_->val_, 10);
    EXPECT_EQ(root->left_->color_, Color::Red);
    
    ASSERT_NE(root->right_, nullptr);
    EXPECT_EQ(root->right_->val_, 30);
    EXPECT_EQ(root->right_->color_, Color::Red);
}

// Проверка перекрашивания (case 1)
TEST(RBTreeTest, insert_recoloring) {
    RBTree<int> tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5); // Должен вызвать перекрашивание
    
    Node<int>* root = tree.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->val_, 20);
    EXPECT_EQ(root->color_, Color::Black);
    
    // Проверяем что перекрашивание сработало
    EXPECT_EQ(root->left_->color_, Color::Black);
    EXPECT_EQ(root->right_->color_, Color::Black);
    EXPECT_EQ(root->left_->left_->color_, Color::Red);
}