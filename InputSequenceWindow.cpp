//
// Created by User on 21.12.2024.
//

#include "InputSequenceWindow.h"
#include "MostFrequent.h"

#include <QMessageBox>
#include <QMessageBox>
#include <QString>
#include <stdexcept>

InputSequenceWindow::InputSequenceWindow(QWidget *parent)
        : QWidget(parent)
{
    // Установка заголовка окна
    setWindowTitle("Ввод последовательности");

    // Создание элементов интерфейса
    label = new QLabel("Введите последовательность:", this);
    inputLineEdit = new QLineEdit(this);
    minLengthLineEdit = new QLineEdit(this);
    maxLengthLineEdit = new QLineEdit(this);

    // Установка плейсхолдеров для полей ввода
    minLengthLineEdit->setPlaceholderText("Минимальная длина");
    maxLengthLineEdit->setPlaceholderText("Максимальная длина");

    QPushButton *confirmButton = new QPushButton("Подтвердить", this);

    // Установка вертикального компоновщика
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(inputLineEdit);
    layout->addWidget(minLengthLineEdit);
    layout->addWidget(maxLengthLineEdit);
    layout->addWidget(confirmButton);

    // Подключение сигнала к слоту
    connect(confirmButton, &QPushButton::clicked, this, &InputSequenceWindow::onConfirmButtonClicked);
}

void InputSequenceWindow::onConfirmButtonClicked()
{
    // Получение введенной последовательности
    std::string input = inputLineEdit->text().toStdString();

    // Получение минимальной и максимальной длины
    bool minOk, maxOk;
    int lmin = minLengthLineEdit->text().toInt(&minOk);
    int lmax = maxLengthLineEdit->text().toInt(&maxOk);

    // Проверка корректности введенных значений
    if (!minOk || !maxOk || lmin < 0 || lmax < 0 || lmin > lmax) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные значения для минимальной и максимальной длины.");
        return;
    }

    // Вызов функции с введенной последовательностью и длинами
    FindingTheMostFrequentSubsequence(input, lmin, lmax);

    // Закрытие окна после подтверждения
    this->close();
}
