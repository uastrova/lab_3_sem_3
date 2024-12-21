#include <iostream>
#include <Qt>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QApplication>
#include "tests.h"

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Выбор задачи");
    w.resize(500, 400); // Установка размера окна
    w.show();
    return a.exec();
}