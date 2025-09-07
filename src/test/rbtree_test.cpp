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

// // Тест визуализации (для отладки)
// TEST(RBTreeTest, visualize_tree) {
//     RBTree<int> tree;
//     tree.insert(50);
//     tree.insert(30);
//     tree.insert(70);
//     tree.insert(20);
//     tree.insert(40);
//     tree.insert(60);
//     tree.insert(80);
    
//     // Просто проверяем что метод вызывается без ошибок
//     EXPECT_NO_THROW(tree.visualize());
    
//     tree.visualize();
// }

// // Тест визуализации пустого дерева
// TEST(RBTreeTest, visualize_empty_tree) {
//     RBTree<int> tree;
//     EXPECT_NO_THROW(tree.visualize());
// }

// Проверка поиска существующего элемента
TEST(RBTreeTest, find_existing) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(25);
    tree.insert(35);
    tree.insert(45);    
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);
    tree.insert(80);

    Node<int>* found = tree.find(20);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->val_, 20);

    found = tree.find(10);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->val_, 10);
    
    found = tree.find(40);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->val_, 40);

    found = tree.find(45);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->val_, 45);

    found = tree.find(50);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->val_, 50);

    found = tree.find(60);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->val_, 60);

    found = tree.find(70);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->val_, 70);

    found = tree.find(80);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->val_, 80);
}

// Проверка поиска несуществующего элемента
TEST(RBTreeTest, find_non_existing) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    
    EXPECT_EQ(tree.find(30), nullptr);
}

// Проверка contains для существующего элемента
TEST(RBTreeTest, contains_existing) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(25);
    tree.insert(35);
    tree.insert(45);    
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);
    tree.insert(80);
    
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.contains(30));
    EXPECT_TRUE(tree.contains(40));
    EXPECT_TRUE(tree.contains(25));
    EXPECT_TRUE(tree.contains(35));
    EXPECT_TRUE(tree.contains(45));
    EXPECT_TRUE(tree.contains(50));
    EXPECT_TRUE(tree.contains(60));
    EXPECT_TRUE(tree.contains(70));
    EXPECT_TRUE(tree.contains(80));
}

// Проверка contains для несуществующего элемента
TEST(RBTreeTest, contains_non_existing) {
    RBTree<int> tree;
    tree.insert(10);
    
    EXPECT_FALSE(tree.contains(20));
    EXPECT_FALSE(tree.contains(5));
}

// Проверка find в пустом дереве
TEST(RBTreeTest, find_empty_tree) {
    RBTree<int> tree;
    EXPECT_EQ(tree.find(10), nullptr);
}

// Проверка contains в пустом дереве
TEST(RBTreeTest, contains_empty_tree) {
    RBTree<int> tree;
    EXPECT_FALSE(tree.contains(10));
}