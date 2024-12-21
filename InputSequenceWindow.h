//
// Created by User on 21.12.2024.
//

#ifndef LAB3_INPUTSEQUENCEWINDOW_H
#define LAB3_INPUTSEQUENCEWINDOW_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class InputSequenceWindow : public QWidget
{
Q_OBJECT

public:
    InputSequenceWindow(QWidget *parent = nullptr);

private slots:
    void onConfirmButtonClicked();

private:
    QLineEdit *inputLineEdit; // Поле для ввода последовательности
    QLineEdit *minLengthLineEdit; // Поле для ввода минимальной длины
    QLineEdit *maxLengthLineEdit; // Поле для ввода максимальной длины
    QLabel *label;
};


#endif //LAB3_INPUTSEQUENCEWINDOW_H
