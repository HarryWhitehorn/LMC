#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QScrollBar>
#include <array>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    // Registers
    QGridLayout *registersGrid;
    QSpinBox *inputSpinBox;
    QPushButton *inputButton;
    QLabel *pcLabel;
    QLCDNumber *pcLCD;
    QLabel *accLabel;
    QLCDNumber *accLCD;
    QLabel *irLabel;
    QLCDNumber *irLCD;
    QLabel *arLabel;
    QLCDNumber *arLCD;
    // Memory
    QGridLayout *memoryGrid;
    std::array<QLCDNumber *, 100> memoryLCDs; // LCDs created on init
    // Output
    QGridLayout *outputGrid;
    QLabel *outputLabel;
    QPlainTextEdit *outputTextEdit;
    QScrollBar *outputScrollBar;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPc(int n);
    void setAcc(int n);
    void setIr(int n);
    void setAr(int n);
    void setMemory(int n, int i);
    void setMemory(std::array<int, 100> m);

private:
    void setupUi();
    void setupRegisters();
    void setupMemory();
    void populateMemoryGrid();
    void setupOutput();
};
#endif // MAINWINDOW_H
