//
// Created by User on 21.12.2024.
//

#ifndef LAB3_MAINWINDOW_H
#define LAB3_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSubsequenceButtonClicked();
    void onKnapsackButtonClicked();

private:
    QLabel *label;
    QPushButton *subsequenceButton;
    QPushButton *knapsackButton;
};


#endif //LAB3_MAINWINDOW_H
