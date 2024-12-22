//
// Created by User on 22.12.2024.
//

#include "GenerateSequenceWindow.h"

#include <QMessageBox>
#include <QString>
#include "MostFrequent.h"
#include "Generator.h"

GenerateSequenceWindow::GenerateSequenceWindow(QWidget *parent)
        : QWidget(parent)
{
    // Установка заголовка окна
    setWindowTitle("Генерация последовательности");

    // Создание элементов интерфейса
    label = new QLabel("Введите параметры для генерации последовательности:", this);
    lengthLineEdit = new QLineEdit(this);
    minLengthLineEdit = new QLineEdit(this);
    maxLengthLineEdit = new QLineEdit(this);

    // Установка плейсхолдеров для полей ввода
    lengthLineEdit->setPlaceholderText("Длина последовательности");
    minLengthLineEdit->setPlaceholderText("Минимальная длина подпоследовательности");
    maxLengthLineEdit->setPlaceholderText("Максимальная длина подпоследовательности");

    QPushButton *confirmButton = new QPushButton("Подтвердить", this);

    // Установка вертикального компоновщика
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(lengthLineEdit);
    layout->addWidget(minLengthLineEdit);
    layout->addWidget(maxLengthLineEdit);
    layout->addWidget(confirmButton);

    // Подключение сигнала к слоту
    connect(confirmButton, &QPushButton::clicked, this, &GenerateSequenceWindow::onConfirmButtonClicked);
}

void GenerateSequenceWindow::onConfirmButtonClicked()
{
    // Получение длины последовательности
    bool lengthOk, minOk, maxOk;
    int length = lengthLineEdit->text().toInt(&lengthOk);
    int lmin = minLengthLineEdit->text().toInt(&minOk);
    int lmax = maxLengthLineEdit->text().toInt(&maxOk);

    // Проверка корректности введенных значений
    if (!lengthOk || !minOk || !maxOk || length <= 0 || lmin < 0 || lmax < 0 || lmin > lmax) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные значения.");
        return;
    }

    // Генерация последовательности
    std::string generatedSequence = GenerateSequence(length);

    // Вызов функции с сгенерированной последовательностью и длинами
    FindingTheMostFrequentSubsequence(generatedSequence, lmin, lmax);

    // Закрытие окна после подтверждения
    this->close();
}