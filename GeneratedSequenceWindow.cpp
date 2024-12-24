//
// Created by User on 24.12.2024.
//

#include "GeneratedSequenceWindow.h"
#include <QFont>

GeneratedSequenceWindow::GeneratedSequenceWindow(const std::string &sequence, QWidget *parent)
        : QWidget(parent)
{
    // Установка заголовка окна
    setWindowTitle("Исходная последовательность");

    // Создание элементов интерфейса
    sequenceLabel = new QLabel(QString::fromStdString(sequence), this);
    QPushButton *subsequencesButton = new QPushButton("Подпоследовательности", this);

    // Установка вертикального компоновщика
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(sequenceLabel);
    layout->addWidget(subsequencesButton);

    // Подключение сигнала к слоту
    connect(subsequencesButton, &QPushButton::clicked, this, &GeneratedSequenceWindow::onSubsequencesButtonClicked);
}

void GeneratedSequenceWindow::onSubsequencesButtonClicked()
{
    // Открытие файла с подпоследовательностями
    QString filePath = "C:/c++Programs/lab_3_sem_3/outputSequences.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}
