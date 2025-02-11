#pragma once
#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class AboutWindow : public QWidget
{
    Q_OBJECT
public:
    AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

private:
    QGridLayout *mainGrid;
    QLabel *titleLabel;
    QLabel *descriptionLabel;
    QLabel *authorLabel;
    QLabel *versionLabel;
    QLabel *licenseLabel;
    void setupUi();
};

#endif // ABOUTWINDOW_H