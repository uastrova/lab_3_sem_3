//
// Created by User on 22.12.2024.
//

#include "KnapsackParametersWindow.h"
#include "KnapsackItemsWindow.h" // Подключаем новый класс для ввода вещей
#include <QMessageBox>
#include <QString>

KnapsackParametersWindow::KnapsackParametersWindow(QWidget *parent)
        : QWidget(parent)
{
    // Установка заголовка окна
    setWindowTitle("Проблема рюкзака");

    // Создание элементов интерфейса
    QLabel *label = new QLabel("Введите параметры рюкзака:", this);
    itemCountLineEdit = new QLineEdit(this);
    capacityLineEdit = new QLineEdit(this);

    // Установка плейсхолдеров для полей ввода
    itemCountLineEdit->setPlaceholderText("Количество вещей (до 10)");
    capacityLineEdit->setPlaceholderText("Вместимость рюкзака");

    QPushButton *confirmButton = new QPushButton("Подтвердить", this);

    // Установка вертикального компоновщика
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(itemCountLineEdit);
    layout->addWidget(capacityLineEdit);
    layout->addWidget(confirmButton);

    // Подключение сигнала к слоту
    connect(confirmButton, &QPushButton::clicked, this, &KnapsackParametersWindow::onConfirmButtonClicked);
}

void KnapsackParametersWindow::onConfirmButtonClicked()
{
    // Получение количества вещей и вместимости рюкзака
    bool itemCountOk, capacityOk;
    int itemCount = itemCountLineEdit->text().toInt(&itemCountOk);
    int capacity = capacityLineEdit->text().toInt(&capacityOk);

    // Проверка корректности введенных значений
    if (!itemCountOk || !capacityOk || itemCount <= 0 || itemCount > 10 || capacity <= 0) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные значения.");
        return;
    }

    // Открытие окна для ввода данных о вещах
    KnapsackItemsWindow *itemsWindow = new KnapsackItemsWindow(itemCount, capacity);
    itemsWindow->setAttribute(Qt::WA_DeleteOnClose); // Удалить окно при закрытии
    itemsWindow->show();

    // Закрытие текущего окна
    this->close();
}