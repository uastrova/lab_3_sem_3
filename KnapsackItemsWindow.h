//
// Created by User on 22.12.2024.
//

#ifndef LAB3_KNAPSACKITEMSWINDOW_H
#define LAB3_KNAPSACKITEMSWINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <vector>
#include "KnapSackProblem.h" // Подключите ваш класс Item

class KnapsackItemsWindow : public QWidget
{
Q_OBJECT

public:
    KnapsackItemsWindow(int itemCount, int capacity, QWidget *parent = nullptr);

private slots:
    void onConfirmButtonClicked();

private:
    std::vector<Item> items; // Вектор для хранения вещей
    int itemCount;           // Количество вещей
    QLineEdit **weightLineEdits; // Массив полей для ввода веса
    QLineEdit **valueLineEdits;  // Массив полей для ввода стоимости
    int capacity;            // Вместимость рюкзака
};


#endif //LAB3_KNAPSACKITEMSWINDOW_H
