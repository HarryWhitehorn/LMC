#include "mainwindow.h"

MainWindow::MainWindow(Lmc *l, QWidget *parent)
    : QMainWindow(parent)
{
    lmc = l;
    l->setOuput(this);
    l->setInput(this);
    settingsWindow = new SettingsWindow(this);
    connect(settingsWindow, &SettingsWindow::clearOutput, this, &MainWindow::onClearOutputTriggered);
    aboutWindow = new AboutWindow(this);
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
    // MenuBar
    setupMenu();
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
    pcLabel->setToolTip("Program Counter");
    registersGrid->addWidget(pcLabel, 0, 0, 1, 1);
    pcLCD = new QLCDNumber(centralWidget);
    pcLCD->setObjectName("pcLCD");
    pcLCD->setToolTip("Program Counter");
    registersGrid->addWidget(pcLCD, 0, 1, 1, 1);
    //
    accLabel = new QLabel(centralWidget);
    accLabel->setObjectName("accLabel");
    accLabel->setText("Acc");
    accLabel->setToolTip("Accumulator");
    registersGrid->addWidget(accLabel, 1, 0, 1, 1);
    accLCD = new QLCDNumber(centralWidget);
    accLCD->setObjectName("accLCD");
    accLCD->setToolTip("Accumulator");
    registersGrid->addWidget(accLCD, 1, 1, 1, 1);
    //
    irLabel = new QLabel(centralWidget);
    irLabel->setObjectName("irLabel");
    irLabel->setText("IR");
    irLabel->setToolTip("Instruction Register");
    registersGrid->addWidget(irLabel, 2, 0, 1, 1);
    irLCD = new QLCDNumber(centralWidget);
    irLCD->setObjectName("irLCD");
    irLCD->setToolTip("Instruction Register");
    registersGrid->addWidget(irLCD, 2, 1, 1, 1);
    //
    arLabel = new QLabel(centralWidget);
    arLabel->setObjectName("arLabel");
    arLabel->setText("AR");
    arLabel->setToolTip("Address Register");
    registersGrid->addWidget(arLabel, 3, 0, 1, 1);
    arLCD = new QLCDNumber(centralWidget);
    arLCD->setObjectName("arLCD");
    arLCD->setToolTip("Address Register");
    registersGrid->addWidget(arLCD, 3, 1, 1, 1);
    //
    inputSpinBox = new QSpinBox(centralWidget);
    inputSpinBox->setObjectName("inputSpinBox");
    inputSpinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
    inputSpinBox->setMaximum(999);
    inputSpinBox->setMinimum(-999);
    inputSpinBox->setToolTip("Input Value");
    registersGrid->addWidget(inputSpinBox, 4, 0, 1, 1);
    //
    inputButton = new QPushButton(centralWidget);
    inputButton->setObjectName("inputButton");
    inputButton->setText("Enter");
    inputButton->setToolTip("Enter Input");
    connect(inputButton, &QPushButton::clicked, this, &MainWindow::onEnterClicked);
    inputButton->setEnabled(false);
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
        memoryLCDs[i]->setObjectName("lcdM" + std::to_string(i));
        memoryLCDs[i]->setSmallDecimalPoint(false);
        memoryLCDs[i]->setDigitCount(3);
        memoryLCDs[i]->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
        memoryLCDs[i]->setProperty("value", QVariant(i));
        memoryLCDs[i]->setAutoFillBackground(true);
        memoryLCDs[i]->setToolTip("Memory Address " + QString::number(i));
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
}

void MainWindow::setupMenu()
{
    menuBar = new QMenuBar(centralWidget);
    menuBar->setObjectName("menuBar");
    setMenuBar(menuBar);
    // fileMenu
    fileMenu = new QMenu("&File", centralWidget);
    fileMenu->setObjectName("fileMenu");
    menuBar->addMenu(fileMenu);
    //   Open
    openAction = new QAction("Open", centralWidget);
    openAction->setObjectName("openAction");
    fileMenu->addAction(openAction);
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenTriggered);
    //   Save
    saveAction = new QAction("Save", centralWidget);
    saveAction->setObjectName("saveAction");
    fileMenu->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveTriggered);
    //   Exit
    fileMenu->addSeparator();
    exitAction = new QAction("Exit", centralWidget);
    exitAction->setObjectName("exitAction");
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExitTriggered);
    // controlMenu
    controlMenu = new QMenu("&Control", centralWidget);
    controlMenu->setObjectName("controlMenu");
    menuBar->addMenu(controlMenu);
    //   Run
    runAction = new QAction("Run", centralWidget);
    controlMenu->addAction(runAction);
    connect(runAction, &QAction::triggered, this, &MainWindow::onRunTriggered);
    //   Stop
    stopAction = new QAction("Stop", centralWidget);
    controlMenu->addAction(stopAction);
    connect(stopAction, &QAction::triggered, this, &MainWindow::onStopTriggered);
    //   Step
    stepAction = new QAction("Step", centralWidget);
    controlMenu->addAction(stepAction);
    connect(stepAction, &QAction::triggered, this, &MainWindow::onStepTriggered);
    //   Reset
    controlMenu->addSeparator();
    resetAction = new QAction("Reset", centralWidget);
    controlMenu->addAction(resetAction);
    connect(resetAction, &QAction::triggered, this, &MainWindow::onResetTriggered);
    // helpMenu
    helpMenu = new QMenu("&Help", centralWidget);
    helpMenu->setObjectName("helpMenu");
    menuBar->addMenu(helpMenu);
    //   Settings
    settingsAction = new QAction("Settings", centralWidget);
    helpMenu->addAction(settingsAction);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettingsTriggered);
    //   About
    helpMenu->addSeparator();
    aboutAction = new QAction("About", centralWidget);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAboutTriggered);
}

void MainWindow::clearOutput()
{
    outputTextEdit->clear();
}

void MainWindow::setPc(int n)
{
    pcLCD->display(n);
    memoryLCDs[n]->setPalette(settingsWindow->getPcHighlight());
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
    if (lmc->getIr() != IO)
    { // Not IO
        memoryLCDs[n]->setPalette(settingsWindow->getArHighlight());
    }
}

void MainWindow::setMemory(int n, int i)
{
    memoryLCDs[i]->display(n);
    memoryLCDs[i]->setPalette(settingsWindow->defaultPalette);
}

void MainWindow::setMemory(std::array<int, 100> m)
{
    for (int i = 0; i < std::size(m); ++i)
    {
        setMemory(m[i], i);
    }
}

void MainWindow::setIsRunning(bool isRunning)
{
    stepAction->setEnabled(isRunning);
}

void MainWindow::updateValues()
{
    setMemory(lmc->getMemory()); // First to clear all highlights
    setAcc(lmc->getAcc());
    setIr(lmc->getIr());
    setAr(lmc->getAr());
    setPc(lmc->getPc()); // Last to show pc highlight on top
    setIsRunning(lmc->getIsRunning());
}

int MainWindow::read()
{
    inputButton->setEnabled(true);
    stepAction->setEnabled(false);
    QEventLoop loop;
    connect(inputButton, &QPushButton::clicked, &loop, &QEventLoop::quit);
    loop.exec();
    inputButton->setEnabled(false);
    stepAction->setEnabled(true);
    int value = inputSpinBox->value();
    return value;
}

void MainWindow::write(std::string value)
{
    QString v = QString::fromStdString(value);
    write(v);
}

void MainWindow::write(int value)
{
    QString v = QString::number(value);
    write(v);
}

void MainWindow::write(char value)
{
    QString v = QString(value);
    write(v);
}

void MainWindow::write(QString value)
{
    value.append(settingsWindow->getOutputText());
    outputTextEdit->insertPlainText(value);
}

void MainWindow::delay(int msecs)
{
    // https://stackoverflow.com/a/11487434/
    QTime delayTime = QTime::currentTime().addMSecs(msecs);
    while (QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::onOpenTriggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", QCoreApplication::applicationDirPath(), "LMC (compiled) (*.lmc)");
    if (!filename.isEmpty())
    {
        lmc->load(filename.toStdString());
        updateValues();
    }
}

void MainWindow::onSaveTriggered()
{
    // TODO
}

void MainWindow::onExitTriggered()
{
    QCoreApplication::quit();
}

void MainWindow::onRunTriggered()
{
    lmc->setIsRunning(true);
    while (lmc->getIsRunning())
    {
        lmc->step();
        updateValues();
        delay(settingsWindow->getDelay());
    }
}

void MainWindow::onStopTriggered()
{
    lmc->setIsRunning(false);
}

void MainWindow::onStepTriggered()
{
    lmc->step();
    updateValues();
}

void MainWindow::onResetTriggered()
{
    lmc->reset();
    if (settingsWindow->getIsAutoClear())
    {
        clearOutput();
    }
    updateValues();
}

void MainWindow::onEnterClicked()
{
    QString v = QString::number(inputSpinBox->value()); // TODO: give to lmc via InputDevice;
    // TODO: Write/fix this function; Enter is handled in eventloop (not here)
}

void MainWindow::onSettingsTriggered()
{
    settingsWindow->show();
}

void MainWindow::onAboutTriggered()
{
    aboutWindow->show();
}

void MainWindow::onClearOutputTriggered()
{
    clearOutput();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (lmc->getIsRunning())
    {
        lmc->setIsRunning(false);
        while (lmc->getIsRunning())
        {
            event->ignore();
        }
        event->accept();
    }
}