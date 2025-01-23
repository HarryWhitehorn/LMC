#include "mainwindow.h"
#include "lmc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setMemory(l.getMemory());
    return a.exec();
}