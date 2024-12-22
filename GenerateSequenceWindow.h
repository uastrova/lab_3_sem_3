//
// Created by User on 22.12.2024.
//

#ifndef LAB3_GENERATESEQUENCEWINDOW_H
#define LAB3_GENERATESEQUENCEWINDOW_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class GenerateSequenceWindow : public QWidget
{
Q_OBJECT

public:
    GenerateSequenceWindow(QWidget *parent = nullptr);

private slots:
    void onConfirmButtonClicked();

private:
    QLineEdit *lengthLineEdit; // Поле для ввода длины последовательности
    QLineEdit *minLengthLineEdit; // Поле для ввода минимальной длины
    QLineEdit *maxLengthLineEdit; // Поле для ввода максимальной длины
    QLabel *label;
};



#endif //LAB3_GENERATESEQUENCEWINDOW_H
