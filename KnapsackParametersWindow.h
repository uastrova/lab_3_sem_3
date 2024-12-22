//
// Created by User on 22.12.2024.
//

#ifndef LAB3_KNAPSACKPARAMETERSWINDOW_H
#define LAB3_KNAPSACKPARAMETERSWINDOW_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class KnapsackParametersWindow : public QWidget
{
Q_OBJECT

public:
    KnapsackParametersWindow(QWidget *parent = nullptr);

private slots:
    void onConfirmButtonClicked();

private:
    QLineEdit *itemCountLineEdit; // Поле для ввода количества вещей
    QLineEdit *capacityLineEdit;   // Поле для ввода вместимости рюкзака
};

#endif //LAB3_KNAPSACKPARAMETERSWINDOW_H
