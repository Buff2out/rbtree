# Компилятор и флаги
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -g -O0 -I./src
GTEST_LIBS = -lgtest -lgtest_main -lpthread

# Директории
SRC_DIR = src
TEST_DIR = src/test
BUILD_DIR = build
TEST_BUILD_DIR = $(BUILD_DIR)/test

# Исходные файлы
HEADERS = $(SRC_DIR)/rbtree.h $(SRC_DIR)/balancing.hpp $(SRC_DIR)/insert.hpp $(SRC_DIR)/operators.hpp
TEST_SRC = $(TEST_DIR)/rbtree_test.cpp
MAIN_SRC = $(SRC_DIR)/main.cpp

# Исполняемые файлы
TEST_EXEC = $(TEST_BUILD_DIR)/rbtree_test
MAIN_EXEC = $(TEST_BUILD_DIR)/rbtree_main

# Цели по умолчанию
all: test

# Создание директорий
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BUILD_DIR): $(BUILD_DIR)
	mkdir -p $(TEST_BUILD_DIR)

# Сборка тестов
$(TEST_EXEC): $(TEST_SRC) $(HEADERS) | $(TEST_BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_EXEC) $(GTEST_LIBS)

# Запуск тестов
test: $(TEST_EXEC)
	$(TEST_EXEC)

# Сборка main
$(MAIN_EXEC): $(MAIN_SRC) $(HEADERS) | $(TEST_BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(MAIN_SRC) -o $(MAIN_EXEC) $(GTEST_LIBS)

main: $(MAIN_EXEC)

# Запуск с valgrind для проверки утечек памяти
valgrind: $(TEST_EXEC)
	valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $(TEST_EXEC)

# Очистка
clean:
	rm -rf $(BUILD_DIR)

# Пересборка
rebuild: clean all

.PHONY: all test main valgrind clean rebuild