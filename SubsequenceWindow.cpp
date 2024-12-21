//
// Created by User on 21.12.2024.
//

#include "SubsequenceWindow.h"
#include "InputSequenceWindow.h"

SubsequenceWindow::SubsequenceWindow(QWidget *parent)
        : QWidget(parent)
{
    // Установка заголовка окна
    setWindowTitle("Поиск подпоследовательностей");

    // Создание элементов интерфейса
    label = new QLabel("Выберите способ ввода последовательности:", this);
    manualInputButton = new QPushButton("Ввести последовательность вручную", this);
    generateSequenceButton = new QPushButton("Сгенерировать последовательность", this);

    // Установка вертикального компоновщика
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(manualInputButton);
    layout->addWidget(generateSequenceButton);

    // Подключение сигналов к слотам
    connect(manualInputButton, &QPushButton::clicked, this, &SubsequenceWindow::onManualInputButtonClicked);
    connect(generateSequenceButton, &QPushButton::clicked, this, &SubsequenceWindow::onGenerateSequenceButtonClicked);
}

void SubsequenceWindow::onManualInputButtonClicked()
{
    // Закрытие текущего окна
    this->close();

    // Открытие окна для ввода последовательности
    InputSequenceWindow *inputWindow = new InputSequenceWindow();
    inputWindow->setAttribute(Qt::WA_DeleteOnClose); // Удалить окно при закрытии
    inputWindow->show();
}

void SubsequenceWindow::onGenerateSequenceButtonClicked()
{
    // Закрытие текущего окна
    this->close();

    // Здесь можно добавить код для обработки нажатия кнопки "Сгенерировать последовательность"
    label->setText("Вы выбрали генерацию последовательности.");
}