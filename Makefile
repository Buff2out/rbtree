# Компилятор и флаги
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -g -O0 -I./src -I/usr/include
CPPMAIN = -std=c++20 -g -O0 -I./src -I/usr/include

# Директории
SRC_DIR = src
TEST_DIR = src/test
BUILD_DIR = build
TEST_BUILD_DIR = $(BUILD_DIR)/test

# Исходные файлы
RBTREE_SRC = $(SRC_DIR)/rbtree.h
TEST_SRC = $(TEST_DIR)/rbtree_test.cpp
MAIN_SRC = src/main.cpp

# Исполняемые файлы
TEST_EXEC = $(TEST_BUILD_DIR)/rbtree_test
MAIN_EXEC = $(TEST_BUILD_DIR)/rbtree_main

# Google Test флаги
GTEST_LIBS = -lgtest -lgtest_main -lpthread

# Цели по умолчанию
all: build test

# Создание директорий
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BUILD_DIR): $(BUILD_DIR)
	mkdir -p $(TEST_BUILD_DIR)

# Сборка тестов
build: $(TEST_EXEC)

$(TEST_EXEC): $(RBTREE_SRC) $(TEST_SRC) | $(TEST_BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_EXEC) $(GTEST_LIBS)

# Запуск тестов
test: build
	$(TEST_EXEC)

main:
	$(CXX) $(CPPMAIN) $(MAIN_SRC) -o $(MAIN_EXEC) -lpthread

# Запуск с valgrind для проверки утечек памяти
valgrind: build
	valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $(TEST_EXEC)

# Очистка
clean:
	rm -rf $(BUILD_DIR)

# Пересборка
rebuild: clean all

.PHONY: all build test valgrind clean rebuild