#include "mainwindow.h"
#include "lmc.h"
#include "consoleio.cpp"

#include <QApplication>

Lmc* lmcDemo(){
    InputDevice *in = new ConsoleInput();
    OutputDevice *out = new ConsoleOutput();
    Lmc *l = new Lmc(in, out, true);
    l->load();
    l->printStatus();
    // l.main();
    return l;
}

int main(int argc, char *argv[])
{
    Lmc *l = lmcDemo();
    // return 0;
    QApplication a(argc, argv);
    MainWindow w(l);
    w.updateValues();
    w.show();
    // w.setMemory(l.getMemory());
    return a.exec();
}