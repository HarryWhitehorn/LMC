#pragma once
#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QMenuBar>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include "lmcHighlighter.h"
extern "C"
{
#include "compile.h"
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT
public:
    EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

    void setText(const QString &text);
    void setTextFromFile(const std::string path);
    QString toPlainText();

private slots:
    void onLoadClicked();
    // menu
    void onOpenTriggered();
    void onSaveTriggered();
    void onCloseTriggered();

signals:
    void load();

private:
    QWidget *centralWidget;
    QGridLayout *mainGrid;
    QTextEdit *textEdit;
    LmcHighlighter *highlighter;
    QPushButton *loadButton;
    // Menu
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *closeAction;

    void setupUi();
    void setupMenu();
};

#endif // EDITORWINDOW_H