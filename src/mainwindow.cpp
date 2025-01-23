#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi()
{
    if (objectName().isEmpty())
        setObjectName("MainWindow");
    resize(800, 600);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setObjectName("gridLayout");
    // Registers
    setupRegisters();
    // Memory
    setupMemory();
    // Output
    setupOutput();
    //
    setCentralWidget(centralWidget);
}

void MainWindow::setupRegisters()
{
    registersGrid = new QGridLayout(centralWidget);
    registersGrid->setObjectName("registersGrid");
    gridLayout->addLayout(registersGrid, 0, 0, 1, 1);
    //
    pcLabel = new QLabel(centralWidget);
    pcLabel->setObjectName("pcLabel");
    pcLabel->setText("PC");
    registersGrid->addWidget(pcLabel, 0, 0, 1, 1);
    pcLCD = new QLCDNumber(centralWidget);
    pcLCD->setObjectName("pcLCD");
    registersGrid->addWidget(pcLCD, 0, 1, 1, 1);
    //
    accLabel = new QLabel(centralWidget);
    accLabel->setObjectName("accLabel");
    accLabel->setText("Acc");
    registersGrid->addWidget(accLabel, 1, 0, 1, 1);
    accLCD = new QLCDNumber(centralWidget);
    accLCD->setObjectName("accLCD");
    registersGrid->addWidget(accLCD, 1, 1, 1, 1);
    //
    irLabel = new QLabel(centralWidget);
    irLabel->setObjectName("irLabel");
    irLabel->setText("IR");
    registersGrid->addWidget(irLabel, 2, 0, 1, 1);
    irLCD = new QLCDNumber(centralWidget);
    irLCD->setObjectName("irLCD");
    registersGrid->addWidget(irLCD, 2, 1, 1, 1);
    //
    arLabel = new QLabel(centralWidget);
    arLabel->setObjectName("arLabel");
    arLabel->setText("AR");
    registersGrid->addWidget(arLabel, 3, 0, 1, 1);
    arLCD = new QLCDNumber(centralWidget);
    arLCD->setObjectName("arLCD");
    registersGrid->addWidget(arLCD, 3, 1, 1, 1);
    //
    inputSpinBox = new QSpinBox(centralWidget);
    inputSpinBox->setObjectName("inputSpinBox");
    inputSpinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
    inputSpinBox->setMaximum(999);
    registersGrid->addWidget(inputSpinBox, 4, 0, 1, 1);
    //
    inputButton = new QPushButton(centralWidget);
    inputButton->setObjectName("inputButton");
    inputButton->setText("Enter");
    registersGrid->addWidget(inputButton, 4, 1, 1, 1);
}

void MainWindow::setupMemory()
{
    memoryGrid = new QGridLayout(centralWidget);
    memoryGrid->setObjectName("memoryGrid");
    gridLayout->addLayout(memoryGrid, 0, 1, 1, 1);
    //
    populateMemoryGrid();
}

void MainWindow::populateMemoryGrid()
{
    for (int i = 0; i < std::size(memoryLCDs); ++i)
    {
        memoryLCDs[i] = new QLCDNumber(centralWidget);
        memoryLCDs[i]->setObjectName("lcdM"+std::to_string(i));
        memoryLCDs[i]->setSmallDecimalPoint(false);
        memoryLCDs[i]->setDigitCount(3);
        memoryLCDs[i]->setSegmentStyle(QLCDNumber::SegmentStyle::Filled);
        memoryLCDs[i]->setProperty("value", QVariant(i));
        memoryGrid->addWidget(memoryLCDs[i], i / 10, i % 10, 1, 1);
    }
}

void MainWindow::setupOutput()
{
    outputGrid = new QGridLayout(centralWidget);
    outputGrid->setObjectName("outputGrid");
    gridLayout->addLayout(outputGrid, 1, 0, 1, 2);
    //
    outputLabel = new QLabel(centralWidget);
    outputLabel->setObjectName("outputLabel");
    outputLabel->setText("Output");
    outputGrid->addWidget(outputLabel, 0, 0, 1, 2);
    //
    outputTextEdit = new QPlainTextEdit(centralWidget);
    outputTextEdit->setObjectName("outputTextEdit");
    outputTextEdit->setReadOnly(true);
    outputGrid->addWidget(outputTextEdit, 1, 0, 1, 1);
    //
    outputScrollBar = new QScrollBar(centralWidget);
    outputScrollBar->setObjectName("outputScrollBar");
    outputGrid->addWidget(outputScrollBar, 1, 1, 1, 1);
}

void MainWindow::setPc(int n)
{
    pcLCD->display(n);
}

void MainWindow::setAcc(int n)
{
    accLCD->display(n);
}

void MainWindow::setIr(int n)
{
    irLCD->display(n);
}

void MainWindow::setAr(int n)
{
    arLCD->display(n);
}

void MainWindow::setMemory(int n, int i)
{
    memoryLCDs[i]->display(n);
}

void MainWindow::setMemory(std::array<int, 100> m)
{
    for (int i = 0; i < std::size(m); ++i)
    {
        setMemory(m[i], i);
    }
}