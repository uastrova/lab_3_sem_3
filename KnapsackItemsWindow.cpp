//
// Created by User on 22.12.2024.
//

#include "KnapsackItemsWindow.h"
#include <QMessageBox>
#include <QString>
#include "KnapSackProblem.h" // Подключите вашу функцию решения задачи о рюкзаке

KnapsackItemsWindow::KnapsackItemsWindow(int itemCount, int capacity, QWidget *parent)
        : QWidget(parent), itemCount(itemCount), capacity(capacity)
{
    // Установка заголовка окна
    setWindowTitle("Ввод данных о вещах");

    // Создание компоновщика
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создание полей для ввода веса и стоимости
    weightLineEdits = new QLineEdit*[itemCount];
    valueLineEdits = new QLineEdit*[itemCount];

    for (int i = 0; i < itemCount; ++i) {
        QLabel *label = new QLabel("Вещь " + QString::number(i + 1), this);
        weightLineEdits[i] = new QLineEdit(this);
        valueLineEdits[i] = new QLineEdit(this);

        // Установка плейсхолдеров
        weightLineEdits[i]->setPlaceholderText("Вес");
        valueLineEdits[i]->setPlaceholderText("Стоимость");

        // Добавление элементов в компоновщик
        layout->addWidget(label);
        layout->addWidget(weightLineEdits[i]);
        layout->addWidget(valueLineEdits[i]);
    }

    QPushButton *confirmButton = new QPushButton("Подтвердить", this);
    layout->addWidget(confirmButton);

    // Подключение сигнала к слоту
    connect(confirmButton, &QPushButton::clicked, this, &KnapsackItemsWindow::onConfirmButtonClicked);
}

void KnapsackItemsWindow::onConfirmButtonClicked()
{
    // Считывание данных о вещах
    items.clear();
    for (int i = 0; i < itemCount; ++i) {
        bool weightOk, valueOk;
        int weight = weightLineEdits[i]->text().toInt(&weightOk);
        int value = valueLineEdits[i]->text().toInt(&valueOk);

        // Проверка корректности введенных значений
        if (!weightOk || !valueOk || weight <= 0 || value <= 0) {
            QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные значения для всех вещей.");
            return;
        }

        // Создание объекта Item и добавление его в вектор
        Item item(weight, value);
        items.push_back(item);
    }

    // Вызов функции решения задачи о рюкзаке
    KnapsackProblemSolving(items, capacity);

    // Закрытие окна после подтверждения
    this->close();
}