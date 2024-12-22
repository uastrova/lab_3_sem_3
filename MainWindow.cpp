//
// Created by User on 21.12.2024.
//

#include "MainWindow.h"
#include "SubsequenceWindow.h" // Подключаем новый класс
#include "KnapsackParametersWindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    // Установка центрального виджета
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создание элементов интерфейса
    label = new QLabel("Выберите задачу", this);
    subsequenceButton = new QPushButton("Поиск подпоследовательностей", this);
    knapsackButton = new QPushButton("Проблема рюкзака", this);

    // Установка вертикального компоновщика
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(label);
    layout->addWidget(subsequenceButton);
    layout->addWidget(knapsackButton);

    // Подключение сигналов к слотам
    connect(subsequenceButton, &QPushButton::clicked, this, &MainWindow::onSubsequenceButtonClicked);
    connect(knapsackButton, &QPushButton::clicked, this, &MainWindow::onKnapsackButtonClicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onSubsequenceButtonClicked()
{
    // Закрытие текущего окна
    this->close();

    // Открытие нового окна для поиска подпоследовательностей
    SubsequenceWindow *subsequenceWindow = new SubsequenceWindow();
    subsequenceWindow->setAttribute(Qt::WA_DeleteOnClose); // Удалить окно при закрытии
    subsequenceWindow->show();
}

void MainWindow::onKnapsackButtonClicked()
{
    // Закрытие текущего окна
    this->close();

    // Открытие окна для ввода параметров рюкзака
    KnapsackParametersWindow *knapsackParamsWindow = new KnapsackParametersWindow();
    knapsackParamsWindow->setAttribute(Qt::WA_DeleteOnClose); // Удалить окно при закрытии
    knapsackParamsWindow->show(); // Показать новое окно
}