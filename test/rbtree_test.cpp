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

// В rbtree_test.cpp
TEST(RBTreeTest, validate_tree_properties) {
    RBTree<int> tree;
    std::vector<int> values = {41, 38, 31, 12, 19, 8, 51, 63, 27, 84, 92, 15};
    
    for (int val : values) {
        tree.insert(val);
        // TODO: Добавить функцию проверки инвариантов КЧ-дерева
        validate_rbtree(tree.get_root());
    }
    
    // Проверяем что все значения найдены
    for (int val : values) {
        EXPECT_TRUE(tree.contains(val)) << "Value " << val << " not found after insertion";
    }
    
    // Проверяем отсутствие лишних значений
    EXPECT_FALSE(tree.contains(999));
    EXPECT_FALSE(tree.contains(0));
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

// Тесты итератора
TEST(RBTreeTest, iterator_begin_end) {
    RBTree<int> tree;
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST(RBTreeTest, iterator_single_element) {
    RBTree<int> tree;
    tree.insert(42);
    
    auto it = tree.begin();
    ASSERT_NE(it, tree.end());
    EXPECT_EQ(*it, 42);
    
    ++it;
    EXPECT_EQ(it, tree.end());
}

TEST(RBTreeTest, iterator_inorder_traversal) {
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
    
    EXPECT_EQ(actual, expected);
}

TEST(RBTreeTest, iterator_const_version) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    
    const RBTree<int>& const_tree = tree;
    std::vector<int> values;
    
    for (auto it = const_tree.begin(); it != const_tree.end(); ++it) {
        values.push_back(*it);
    }
    
    EXPECT_EQ(values, std::vector<int>({5, 10, 15}));
}

TEST(RBTreeTest, iterator_cbegin_cend) {
    RBTree<int> tree;
    tree.insert(8);
    tree.insert(4);
    tree.insert(12);
    
    std::vector<int> values;
    for (auto it = tree.cbegin(); it != tree.cend(); ++it) {
        values.push_back(*it);
    }
    
    EXPECT_EQ(values, std::vector<int>({4, 8, 12}));
}

TEST(RBTreeTest, iterator_bidirectional) {
    RBTree<int> tree;
    tree.insert(50);
    tree.insert(25);
    tree.insert(75);
    
    auto it = tree.begin();
    EXPECT_EQ(*it, 25);
    
    ++it;
    EXPECT_EQ(*it, 50);
    
    ++it;
    EXPECT_EQ(*it, 75);
    
    --it;
    EXPECT_EQ(*it, 50);
    
    --it;
    EXPECT_EQ(*it, 25);
}

TEST(RBTreeTest, iterator_empty_tree) {
    RBTree<int> tree;
    EXPECT_EQ(tree.begin(), tree.end());
    EXPECT_EQ(tree.cbegin(), tree.cend());
}

TEST(RBTreeTest, iterator_post_increment) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    
    auto it = tree.begin();
    auto old_it = it++;
    
    EXPECT_EQ(*old_it, 10);
    EXPECT_EQ(*it, 20);
}

TEST(RBTreeTest, iterator_post_decrement) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    
    auto it = ++tree.begin();
    auto old_it = it--;
    
    EXPECT_EQ(*old_it, 20);
    EXPECT_EQ(*it, 10);
}

// Тесты удаления
TEST(RBTreeTest, erase_leaf_node) {
    RBTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    
    tree.erase(30);
    EXPECT_FALSE(tree.contains(30));
    EXPECT_TRUE(tree.contains(50));
    EXPECT_TRUE(tree.contains(70));
}

TEST(RBTreeTest, erase_node_with_one_child) {
    RBTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    
    tree.erase(30);
    EXPECT_FALSE(tree.contains(30));
    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.contains(50));
    EXPECT_TRUE(tree.contains(70));
}

TEST(RBTreeTest, erase_node_with_two_children) {
    RBTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    
    tree.erase(30);
    EXPECT_FALSE(tree.contains(30));
    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.contains(40));
    EXPECT_TRUE(tree.contains(50));
    EXPECT_TRUE(tree.contains(70));
}

TEST(RBTreeTest, erase_root_node) {
    RBTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    
    tree.erase(50);
    EXPECT_FALSE(tree.contains(50));
    EXPECT_TRUE(tree.contains(30));
    EXPECT_TRUE(tree.contains(70));
    
    Node<int>* root = tree.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->color_, Color::Black);
}

TEST(RBTreeTest, erase_nonexistent_node) {
    RBTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    
    EXPECT_NO_THROW(tree.erase(100));
    EXPECT_TRUE(tree.contains(50));
    EXPECT_TRUE(tree.contains(30));
}

TEST(RBTreeTest, erase_from_empty_tree) {
    RBTree<int> tree;
    EXPECT_NO_THROW(tree.erase(50));
}

TEST(RBTreeTest, erase_maintains_properties) {
    RBTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    tree.erase(30);
    tree.erase(70);
    
    // Проверяем что свойства КЧ-дерева сохранились
    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.contains(40));
    EXPECT_TRUE(tree.contains(50));
    EXPECT_TRUE(tree.contains(60));
    EXPECT_TRUE(tree.contains(80));
    
    Node<int>* root = tree.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->color_, Color::Black);
}

TEST(RBTreeTest, erase_all_nodes) {
    RBTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    
    tree.erase(30);
    tree.erase(50);
    tree.erase(70);
    
    EXPECT_FALSE(tree.contains(30));
    EXPECT_FALSE(tree.contains(50));
    EXPECT_FALSE(tree.contains(70));
    EXPECT_EQ(tree.get_root(), nullptr);
}