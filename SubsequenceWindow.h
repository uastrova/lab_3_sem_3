//
// Created by User on 21.12.2024.
//

#ifndef LAB3_SUBSEQUENCEWINDOW_H
#define LAB3_SUBSEQUENCEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class SubsequenceWindow : public QWidget
{
Q_OBJECT

public:
    SubsequenceWindow(QWidget *parent = nullptr);

private slots:
    void onManualInputButtonClicked();
    void onGenerateSequenceButtonClicked();

private:
    QLabel *label;
    QPushButton *manualInputButton;
    QPushButton *generateSequenceButton;
};


#endif //LAB3_SUBSEQUENCEWINDOW_H
