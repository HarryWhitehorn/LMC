#pragma once
#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QColorDialog>
#include <QPushButton>
#include <string>

const int MAX_DELAY = 10000;
const int DELAY_TIME = 200;
const int MIN_STEP = 10;

class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    const QPalette defaultPalette = QPalette(QPalette::Window, QColor(255, 255, 255));

    // getters
    int getDelay();
    QString getOutputText();
    QPalette getPcHighlight();
    QPalette getArHighlight();
    bool getIsAutoClear();
    bool getIsAutoscroll();

signals:
    void clearOutput();

private slots:
    void onOutputAppendCheckBoxChanged(int state);
    void onOutputClearButtonPressed();
    void onPalettePcCheckBoxChanged(int state);
    void onPaletteArCheckBoxChanged(int state);
    void onPalettePcButtonPressed();
    void onPaletteArButtonPressed();

private:
    QGridLayout *mainGrid;
    // Delay
    QGroupBox *delayGroupBox;
    QGridLayout *delayGrid;
    QSpinBox *delaySpinBox;
    // Output
    QGroupBox *outputGroupBox;
    QGridLayout *outputGrid;
    QCheckBox *outputAppendCheckBox;
    QLineEdit *outputAppendText;
    QCheckBox *outputClearCheckBox;
    QPushButton *outputClearButton;
    QCheckBox *outputAutoscrollCheckBox;
    // Palette
    QColorDialog *highlightColorDialog;
    QGroupBox *paletteGroupBox;
    QGridLayout *paletteGrid;
    void setButtonColor(QPushButton *button, QColor color);
    //      PC
    QPalette pcHighlight;
    QCheckBox *palettePcCheckBox;
    QPushButton *palettePcButton;
    //      AR
    QPalette arHighlight;
    QCheckBox *paletteArCheckBox;
    QPushButton *paletteArButton;

    void setupUi();
    void setupDelay();
    void setupOutput();
    void setupPalette();
    void setupHighlightDialog();
};

#endif // SETTINGSWINDOW_H