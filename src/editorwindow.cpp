#include "editorwindow.h"

EditorWindow::EditorWindow(QWidget *parent)
{
    // window
    setParent(parent);
    setWindowTitle("Editor");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_QuitOnClose);
    // ui
    resize(600, 600);
    setupUi();
    setupMenu();
}

EditorWindow::~EditorWindow()
{
}

void EditorWindow::setText(const QString &text)
{
    textEdit->setText(text);
}

void EditorWindow::setTextFromFile(const std::string path)
{
    QString text;
    std::string line;
    std::ifstream file;
    file.open(path);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            text.append(line);
            text.append("\n");
        }
    }
    setText(text);
}

QString EditorWindow::toPlainText()
{
    return textEdit->toPlainText();
}

void EditorWindow::onOpenTriggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", QCoreApplication::applicationDirPath(), "LMC (raw) (*.txt)");
    if (!filename.isEmpty())
    {
        setTextFromFile(filename.toStdString());
    }
}

void EditorWindow::onSaveTriggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save File", QCoreApplication::applicationDirPath(), "LMC (compiled) (*.lmc);;LMC (plaintext) (*.txt)");
    if (!filename.isEmpty())
    {
        if (filename.endsWith(".lmc", Qt::CaseInsensitive))
        {
            // Compile from String
            QByteArray editorBA = toPlainText().toLocal8Bit();
            char *editorString = editorBA.data();
            compileFromString(editorString);
            // Write to file
            QByteArray dataBA = filename.toLocal8Bit();
            char *dataString = dataBA.data();
            instructionsToFile(dataString);
            // clear
            freeParser();
        }
        else if (filename.endsWith(".txt", Qt::CaseInsensitive))
        {
            // Write to file
            std::ofstream file;
            file.open(filename.toStdString());
            if (file.is_open())
            {
                file << toPlainText().toStdString();
            }
        }
        else
        {
            // TODO error handling
        }
    }
    else
    {
        // TODO error handling
    }
}

void EditorWindow::onCloseTriggered()
{
    this->hide();
}

void EditorWindow::setupUi()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    // grid
    mainGrid = new QGridLayout(centralWidget);
    //  text
    textEdit = new QTextEdit(centralWidget);
    mainGrid->addWidget(textEdit, 0, 0);
    highlighter = new LmcHighlighter(textEdit->document());
    //  load button
    loadButton = new QPushButton("Load", centralWidget);
    connect(loadButton, &QPushButton::clicked, this, &EditorWindow::onLoadClicked);
    mainGrid->addWidget(loadButton, 1, 0);
}

void EditorWindow::setupMenu()
{
    menuBar = new QMenuBar(centralWidget);
    setMenuBar(menuBar);
    // file
    fileMenu = new QMenu("&File", centralWidget);
    menuBar->addMenu(fileMenu);
    //  open
    openAction = new QAction("&Open", centralWidget);
    fileMenu->addAction(openAction);
    connect(openAction, &QAction::triggered, this, &EditorWindow::onOpenTriggered);
    //  save
    saveAction = new QAction("&Save", centralWidget);
    fileMenu->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &EditorWindow::onSaveTriggered);
    //  close
    fileMenu->addSeparator();
    closeAction = new QAction("&Close", centralWidget);
    fileMenu->addAction(closeAction);
    connect(closeAction, &QAction::triggered, this, &EditorWindow::onCloseTriggered);
}

void EditorWindow::onLoadClicked()
{
    emit load();
    hide();
}