//
// Created by User on 24.12.2024.
//

#ifndef LAB3_GENERATEDSEQUENCEWINDOW_H
#define LAB3_GENERATEDSEQUENCEWINDOW_H


#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

class GeneratedSequenceWindow : public QWidget
{
Q_OBJECT

public:
    GeneratedSequenceWindow(const std::string &sequence, QWidget *parent = nullptr);

private slots:
    void onSubsequencesButtonClicked();

private:
    QLabel *sequenceLabel; // Для отображения сгенерированной последовательности
};


#endif //LAB3_GENERATEDSEQUENCEWINDOW_H
