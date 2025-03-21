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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <array>
#include "lmc.h"
#include "abstractio.h"
#include "editorWindow.h"
#include "settingswindow.h"
#include "aboutwindow.h"
extern "C" {
    #include "compile.h"
}


class MainWindow : public QMainWindow, InputDevice, OutputDevice
{
    Q_OBJECT

public:
    Lmc *lmc;
    // UI
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
    std::array<QLCDNumber*, 100> memoryLCDs; // LCDs created on init
    // Output
    QGridLayout *outputGrid;
    QLabel *outputLabel;
    QPlainTextEdit *outputTextEdit;
    // Menu
    QMenuBar *menuBar;
        // FileMenu
    QMenu *fileMenu;
    QAction *openAction;
    // QAction *saveAction;
    QAction *exitAction; 
        // ControlMenu
    QMenu *controlMenu;
    QAction *runAction;
    QAction *stopAction;
    QAction *stepAction;
    QAction *resetAction;
        // EditorMenu
    QMenu *editorMenu;
    QAction *editorAction;
    EditorWindow *editorWindow;
        // SettingsMenu
    QMenu *settingsMenu;
    QAction *settingsAction;
    SettingsWindow *settingsWindow;
        // HelpMenu
    QMenu *helpMenu;
    QAction *docsAction;
    QAction *aboutAction;
    AboutWindow *aboutWindow;

    MainWindow(Lmc *l, QWidget *parent = nullptr);
    ~MainWindow();

    void setPc(int n);
    void setAcc(int n);
    void setIr(int n);
    void setAr(int n);
    void setMemory(int n, int i);
    void setMemory(std::array<int, 100> m);
    void setIsRunning(bool isRunning);
    void updateValues();
    // InputDevice
    int read() override;
    // OutputDevice
    void write(std::string value) override;
    void write(int value) override;
    void write(char value) override;
    void write(QString value);

    void delay(int msecs=DELAY_TIME);

private slots:
    void onEditorTriggered();
    void onOpenTriggered();
    void onSaveTriggered();
    void onExitTriggered();
    void onRunTriggered();
    void onStopTriggered();
    void onStepTriggered();
    void onResetTriggered();
    void onEnterClicked();
    void onSettingsTriggered();
    void onDocsTriggered();
    void onAboutTriggered();
    // Editor Window
    void onEditorLoadTriggered();
    // Settings Window
    void onClearOutputTriggered();
    // Misc
    void closeEvent(QCloseEvent *event) override;

private:
    void setupUi();
    void setupRegisters();
    void setupMemory();
    void populateMemoryGrid();
    void setupOutput();
    void setupMenu();
    void clearOutput();
    void resetLmc();
};
#endif // MAINWINDOW_H
