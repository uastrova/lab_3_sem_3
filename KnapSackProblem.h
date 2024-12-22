//
// Created by User on 17.12.2024.
//

#ifndef LAB3_KNAPSACKPROBLEM_H
#define LAB3_KNAPSACKPROBLEM_H

#ifndef LAB3_KNAPSACK_PROBLEM
#define LAB3_KNAPSACK_PROBLEM

#include <fstream>
#include <vector>
#include "RBTree.h"

struct Item {
    int weight;
    int value;
    Item(int weight_, int value_)
    {
        weight = weight_;
        value = value_;
    }
    double valuePerWeight() const {
        return static_cast<double>(value) / weight;
    }
};


struct State {
    int currentWeight;
    int currentValue;
    std::vector<int> usedItems;

    // Для сравнения состояний в красно-черном дереве
    bool operator<(const State& other) const {
        if (currentWeight != other.currentWeight)
            return currentWeight < other.currentWeight;
        return currentValue < other.currentValue;
    }


    // Оператор равенства для сравнения состояний
    bool operator==(const State& other) const {
        return currentWeight == other.currentWeight &&
               currentValue == other.currentValue &&
               usedItems == other.usedItems;
    }
};


class KnapsackSolver {
private:
    int capacity; // Максимальная грузоподъемность рюкзака
    std::vector<Item> items;
    RedBlackTree<State, int> stateTree; // Хранение уникальных состояний
    int maxValue; // Максимальная стоимость, найденная до сих пор
    State bestState; // Оптимальное состояние

    // Поиск в глубину для генерации всех возможных состояний рюкзака
    void dfs(State state) {
        // Если превышен вес рюкзака, выходим
        if (state.currentWeight > capacity) return;

        // Проверяем и обновляем максимальное значение
        if (state.currentValue > maxValue) {
            maxValue = state.currentValue;
            bestState = state; // Сохраняем лучшее состояние
        }

        // Добавляем состояние в дерево (если оно уникально)
        if (stateTree.find(state) != stateTree.getNil()) return; // Уникальность
        stateTree.insert(state, state.currentValue);

        // Пробуем добавить каждый предмет
        for (int i = 0; i < items.size(); ++i) {
            if (std::find(state.usedItems.begin(), state.usedItems.end(), i) != state.usedItems.end())
                continue; // Пропускаем уже использованные предметы

            State nextState = state;
            nextState.currentWeight += items[i].weight;
            nextState.currentValue += items[i].value;
            nextState.usedItems.push_back(i);
            dfs(nextState); // Рекурсивно углубляемся
        }
    }

public:
    KnapsackSolver(int capacity, const std::vector<Item>& items)
            : capacity(capacity), items(items), maxValue(0) {
        // Сортируем предметы по ценности на единицу веса
        std::sort(this->items.begin(), this->items.end(), [](const Item& a, const Item& b) {
            return a.valuePerWeight() > b.valuePerWeight();
        });
    }

    int solve() {
        State initialState = {0, 0, {}};
        dfs(initialState);
        return maxValue;
    }

    // Метод для записи результата в файл
    void writeResultToFile(const std::string& filePath) {
        std::ofstream outputFile(filePath);
        if (!outputFile) {
            throw std::runtime_error("Не удалось открыть файл для записи результата.");
        }

        // Записываем общее значение и вес
        outputFile << "Max Value: " << maxValue << "\n";
        outputFile << "Total Weight: " << bestState.currentWeight << "\n";

        // Записываем список предметов
        outputFile << "Items in the knapsack:\n";
        for (int index : bestState.usedItems) {
            const Item& item = items[index];
            outputFile << "Item " << index + 1
                       << " (Weight: " << item.weight
                       << ", Value: " << item.value << ")\n";
        }

        outputFile.close();
    }
};

inline int KnapsackProblemSolving(const std::vector<Item>& items, int capacity) {
    std::string outputFilePath = "C://c++Programs//lab_3_sem_3//knapsack-output.txt";
    KnapsackSolver solver(capacity, items);
    int maxValue = solver.solve();
    solver.writeResultToFile(outputFilePath); // Записываем результат в файл
    return maxValue;
}


#endif //LAB3_KNAPSACK_PROBLEM


#endif //LAB3_KNAPSACKPROBLEM_H
