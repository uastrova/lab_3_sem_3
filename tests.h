//
// Created by User on 17.12.2024.
//

#ifndef LAB3_TESTS_H
#define LAB3_TESTS_H

#include <iostream>
#include <cassert>
#include "RBTree.h"
#include "KnapsackProblem.h"
#include "RBTree.h"
#include "MostFrequent.h"
#include "HashTable.h"
#include "Generator.h"
#include "Dictionary.h"
#include <iterator>

void testInsertAndSearch() {
    RedBlackTree<int, std::string> tree;
    tree.insert(10, "Data1");
    tree.insert(20, "Data2");
    tree.insert(5, "Data3");
    tree.insert(15, "Data4");
    tree.insert(25, "Data5");

    assert(tree.find(10)->key == 10);
    assert(tree.find(20)->key == 20);
    assert(tree.find(5)->key == 5);
    assert(tree.find(15)->key == 15);
    assert(tree.find(25)->key == 25);

    assert(tree.find(30) == tree.getNil());
}

void testRemove() {
    RedBlackTree<int, std::string> tree;
    tree.insert(10, "Data1");
    tree.insert(20, "Data2");
    tree.insert(5, "Data3");

    tree.remove(20);
    assert(tree.find(20) == tree.getNil());

    tree.remove(10);
    assert(tree.find(10) == tree.getNil());

    tree.remove(5);
    assert(tree.find(5) == tree.getNil());
}

void testKnapsack1()
{
    std::vector<Item> items;
    Item item1(10, 60);
    Item item2(20, 100);
    Item item3(30,120);
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    int capacity = 50;
    int result = KnapsackProblemSolving(items, capacity);
    assert(result == 220);
}

void testKnapsack2()
{
    std::vector<Item> items;
    Item item1(5, 10);
    Item item2(5, 10);
    Item item3(5, 10);
    Item item4(10, 30);
    Item item5(15,45);
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    items.push_back(item4);
    items.push_back(item5);
    int capacity = 20;
    int result = KnapsackProblemSolving(items, capacity);
    assert(result == 55);
}

void testKnapsack3()
{
    std::vector<Item> items;
    Item item1(60, 100);
    Item item2(10, 20);
    Item item3(20, 50);
    Item item4(30, 60);
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    items.push_back(item4);
    int capacity = 50;
    int result = KnapsackProblemSolving(items, capacity);
    assert(result == 110);
}

void testKnapsack4()
{
    std::vector<Item> items;
    Item item1(1, 10);
    Item item2(2, 20);
    Item item3(3, 30);
    Item item4(4, 40);
    Item item5(5, 50);
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    items.push_back(item4);
    items.push_back(item5);
    int capacity = 15;
    int result = KnapsackProblemSolving(items, capacity);
    assert(result == 150);
}

void testKnapsack5()
{
    std::vector<Item> items;
    Item item1(10, 60);
    Item item2(20, 100);
    Item item3(30,120);
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    int capacity = 25;
    int result = KnapsackProblemSolving(items, capacity);
    assert(result == 100);
}

void testKnapsack6()
{
    std::vector<Item> items;
    Item item1(10, 10);
    Item item2(10, 20);
    Item item3(10, 30);
    Item item4(10, 40);
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    items.push_back(item4);
    int capacity = 20;
    int result = KnapsackProblemSolving(items, capacity);
    assert(result == 70);
}

void testKnapsack7()
{
    std::vector<Item> items;
    Item item1(1, 1);
    Item item2(2, 2);
    Item item3(3, 3);
    Item item4(4, 4);
    Item item5(5, 5);
    Item item6(6, 6);
    Item item7(7, 7);
    Item item8(8, 8);
    Item item9(9, 9);
    Item item10(10, 10);
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    items.push_back(item4);
    items.push_back(item5);
    items.push_back(item6);
    items.push_back(item7);
    items.push_back(item8);
    items.push_back(item9);
    items.push_back(item10);
    int capacity = 15;
    int result = KnapsackProblemSolving(items, capacity);
    assert(result == 15);
}







struct TestStruct {
    int *value_;
    TestStruct() : value_(new int(0)) {}
    TestStruct(int value) : value_(new int(value)) {}
    TestStruct(const TestStruct &other) : value_(new int(*other.value_)) {}
    TestStruct(TestStruct &&other) : value_(other.value_) {
        other.value_ = nullptr;
    }

    TestStruct &operator=(const TestStruct &other) {
        if (this == &other) {
            return *this;
        }
        delete value_;
        value_ = new int(*other.value_);
        return *this;
    }

    TestStruct &operator=(TestStruct &&other) {
        if (this == &other) {
            return *this;
        }
        delete value_;
        value_ = other.value_;
        other.value_ = nullptr;
        return *this;
    }
    TestStruct &operator=(int value) {
        delete value_;
        value_ = new int(value);
        return *this;
    }
    ~TestStruct() {
        delete value_;
    }

    int operator*() {
        return *value_;
    }
};

void testDefaultConstructor() {
    THashTable<int, TestStruct> table;
    assert(table.size() == 0);
    assert(table.capacity() == 0);

}

void testParameterizedConstructor() {
    THashTable<int, TestStruct> table(10);
    assert(table.size() == 0);
    assert(table.capacity() == 10);

}

void testInsert() {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    assert(table.size() == 2);
    assert(table.capacity() == 10);
    assert(*(*(table.find(1))).value_ == 1);
    assert(*(*(table.find(2))).value_ == 2);

}

void testRemoveExistingKey() {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    table.insert(3, 3);

    table.remove(1);
    assert(table.size() == 2);
    assert(table.find(1) == table.end());

    table.remove(2);
    assert(table.size() == 1);
    assert(table.find(2) == table.end());

}

void testContains() {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    assert(table.contains(1));
    assert(table.contains(2));
    assert(!table.contains(3));

}

void testSizeAndCapacity() {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    assert(table.size() == 2);
    assert(table.capacity() == 10);

}

void testClear() {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    table.clear();
    assert(table.size() == 0);
    assert(table.capacity() == 0);

}

void testResize() {
    THashTable<int, TestStruct> table(2);
    table.insert(1, 1);
    table.insert(2, 2);
    table.insert(3, 3);
    assert(table.size() == 3);
    assert(table.capacity() == 4);

}

void testIterator() {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    auto it = table.begin();
    assert((*it).key_ == 1);
    assert(*((*it).value_) == 1);
    ++it;
    assert((*it).key_ == 2);
    assert(*((*it).value_) == 2);

}

void testFind() {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    auto it = table.find(1);
    assert((*it).key_ == 1);
    assert(*((*it).value_) == 1);

}

void testOperatorBracket() {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    assert(*(table[1]) == 1);
    assert(*(table[2]) == 2);

}

void testCopyAssignment() {
    THashTable<int, TestStruct> hashTable;
    hashTable.insert(-1, 1);
    hashTable.insert(-2, 2);

    THashTable<int, TestStruct> anotherHashTable;
    anotherHashTable = hashTable;

    assert(anotherHashTable.size() == 2);
    assert(*(anotherHashTable[-1]) == 1);
    assert(*(anotherHashTable[-2]) == 2);

}

void testMoveAssignment() {
    THashTable<int, TestStruct> hashTable;
    hashTable.insert(-1, 1);
    hashTable.insert(-2, 2);

    THashTable<int, TestStruct> anotherHashTable;
    anotherHashTable = std::move(hashTable);

    assert(anotherHashTable.size() == 2);
    assert(*(anotherHashTable[-1]) == 1);
    assert(*(anotherHashTable[-2]) == 2);
}



void startTests()
{
    testInsertAndSearch();
    testRemove();
    testKnapsack1();
    testKnapsack2();
    testKnapsack3();
    testKnapsack4();
    testKnapsack5();
    testKnapsack6();
    testKnapsack7();
    testDefaultConstructor();
    testParameterizedConstructor();
    testInsert();
    testRemoveExistingKey();
    testContains();
    testSizeAndCapacity();
    testClear();
    testResize();
    testIterator();
    testFind();
    testOperatorBracket();
    testCopyAssignment();
    testMoveAssignment();
}

void testFrequentSubsequences(int count, int lmin, int lmax)
{
    std::string seq = GenerateSequence(count);
    Dictionary<std::string, int> result = theMostFrequentSubsequences(seq, lmin, lmax);
    for (auto it = result.begin(); it != result.end(); ++it) {
        // Декомпозиция текущей пары
        std::pair<std::string, int> entry = *it;
        const std::string &subsequence = entry.first; // Подстрока
        int expectedCount = entry.second;            // Ожидаемое количество

        // Пропускаем пустую строку


        if (subsequence.empty()) {
            //std::cerr << "Ошибка: Обнаружена пустая подстрока в словаре. Пропускаем проверку.\n";
            continue;
        }
        // Подсчет количества вхождений подстроки в строку seq
        int actualCount = 0;
        size_t pos = seq.find(subsequence, 0); // Начинаем поиск с начала строки
        while (pos != std::string::npos) {
            ++actualCount;
            pos = seq.find(subsequence, pos + 1); // Продолжаем поиск
        }

        // Используем assert для проверки фактического количества
        assert(actualCount == expectedCount &&
               "Количество вхождений подстроки не совпадает с ожидаемым значением.");
    }
}


#endif //LAB3_TESTS_H
