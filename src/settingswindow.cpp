#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
{
    // window
    setParent(parent);
    setWindowTitle("Settings");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_QuitOnClose);
    // ui
    setupUi();
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::setupUi()
{
    mainGrid = new QGridLayout(this);
    mainGrid->setObjectName("mainGrid");
    // delay
    setupDelay();
    // output
    setupOutput();
    // palette
    setupPalette();
    setupHighlightDialog();
}

void SettingsWindow::setupDelay()
{
    delayGroupBox = new QGroupBox("Delay", this);
    delayGrid = new QGridLayout(delayGroupBox);
    delaySpinBox = new QSpinBox(this);
    delaySpinBox->setRange(0, MAX_DELAY);  // range
    delaySpinBox->setValue(DELAY_TIME);    // default
    delaySpinBox->setSuffix(" ms");        // suffix
    delaySpinBox->setSingleStep(MIN_STEP); // step
    delaySpinBox->setToolTip("Delay in msecs between F.D.E cycles when running the program. Use zero for no delay.");
    delayGrid->addWidget(delaySpinBox, 0, 0, 1, 1);
    delayGroupBox->setLayout(delayGrid);
    mainGrid->addWidget(delayGroupBox, 0, 0, 1, 1);
}

void SettingsWindow::setupOutput()
{
    outputGroupBox = new QGroupBox("Output", this);
    outputGrid = new QGridLayout(outputGroupBox);
    // Append
    //   CheckBox
    outputAppendCheckBox = new QCheckBox("Append", this);
    outputAppendCheckBox->setChecked(true);
    outputAppendCheckBox->setToolTip("Automatically append lmc output with following string. Use '\\n' for newline.");
    connect(outputAppendCheckBox, &QCheckBox::checkStateChanged, this, &SettingsWindow::onOutputAppendCheckBoxChanged);
    outputGrid->addWidget(outputAppendCheckBox, 0, 0, 1, 1);
    //   Text
    outputAppendText = new QLineEdit(this);
    outputAppendText->setText("\\n");
    outputAppendText->setPlaceholderText("Append text");
    outputAppendText->setToolTip("Text to append to lmc output. Use '\\n' for newline.");
    outputGrid->addWidget(outputAppendText, 0, 1, 1, 1);
    // Clear
    //   CheckBox
    outputClearCheckBox = new QCheckBox("Auto Clear", this);
    outputClearCheckBox->setToolTip("Automatically clear output text after each run / on reset.");
    outputGrid->addWidget(outputClearCheckBox, 1, 0, 1, 1);
    //   Button
    outputClearButton = new QPushButton("Clear Now", this);
    outputClearButton->setToolTip("Clear output text now.");
    connect(outputClearButton, &QPushButton::pressed, this, &SettingsWindow::onOutputClearButtonPressed);
    outputGrid->addWidget(outputClearButton, 1, 1, 1, 1);
    //
    outputGroupBox->setLayout(outputGrid);
    mainGrid->addWidget(outputGroupBox, 0, 1, 1, 1);
}

void SettingsWindow::setupPalette()
{
    paletteGroupBox = new QGroupBox("Palette", this);
    paletteGrid = new QGridLayout(paletteGroupBox);
    // pc
    pcHighlight.setColor(QPalette::Window, QColor(255, 0, 0));
    //   CheckBox
    palettePcCheckBox = new QCheckBox("PC Highlight", this);
    palettePcCheckBox->setChecked(true);
    palettePcCheckBox->setToolTip("Highlight address in memory referenced by the PC Register with this color.");
    connect(palettePcCheckBox, &QCheckBox::checkStateChanged, this, &SettingsWindow::onPalettePcCheckBoxChanged);
    paletteGrid->addWidget(palettePcCheckBox, 0, 0, 1, 1);
    //    Button
    palettePcButton = new QPushButton("Color", this);
    palettePcButton->setToolTip("Select color for PC highlight.");
    setButtonColor(palettePcButton, pcHighlight.color(QPalette::Window));
    connect(palettePcButton, &QPushButton::pressed, this, &SettingsWindow::onPalettePcButtonPressed);
    paletteGrid->addWidget(palettePcButton, 0, 1, 1, 1);
    // ar
    arHighlight.setColor(QPalette::Window, QColor(0, 255, 0));
    //   CheckBox
    paletteArCheckBox = new QCheckBox("AR Highlight", this);
    paletteArCheckBox->setChecked(true);
    paletteArCheckBox->setToolTip("Highlight address in memory referenced by the Address Register with this color.");
    connect(paletteArCheckBox, &QCheckBox::checkStateChanged, this, &SettingsWindow::onPaletteArCheckBoxChanged);
    paletteGrid->addWidget(paletteArCheckBox, 1, 0, 1, 1);
    //    Button
    paletteArButton = new QPushButton("Color", this);
    paletteArButton->setAutoFillBackground(true);
    paletteArButton->setToolTip("Select color for AR highlight.");
    setButtonColor(paletteArButton, arHighlight.color(QPalette::Window));
    connect(paletteArButton, &QPushButton::pressed, this, &SettingsWindow::onPaletteArButtonPressed);
    paletteGrid->addWidget(paletteArButton, 1, 1, 1, 1);
    //
    paletteGroupBox->setLayout(paletteGrid);
    mainGrid->addWidget(paletteGroupBox, 1, 0, 1, 2);
}

void SettingsWindow::setupHighlightDialog()
{
    highlightColorDialog = new QColorDialog(this);
}

int SettingsWindow::getDelay()
{
    return delaySpinBox->value();
}

QString SettingsWindow::getOutputText()
{
    if (outputAppendCheckBox->isChecked())
    {
        return outputAppendText->text().replace("\\n", "\n");
    }
    return "";
}

QPalette SettingsWindow::getPcHighlight()
{
    if (palettePcCheckBox->isChecked())
    {
        return pcHighlight;
    }
    return defaultPalette;
}

QPalette SettingsWindow::getArHighlight()
{
    if (paletteArCheckBox->isChecked())
    {
        return arHighlight;
    }
    return defaultPalette;
}

bool SettingsWindow::getIsAutoClear()
{
    return outputClearCheckBox->isChecked();
}

void SettingsWindow::onOutputAppendCheckBoxChanged(int state)
{
    if (state == Qt::Checked)
    {
        outputAppendText->setEnabled(true);
    }
    else
    {
        outputAppendText->setEnabled(false);
    }
}

void SettingsWindow::onOutputClearButtonPressed()
{
    emit clearOutput();
}

void SettingsWindow::onPalettePcCheckBoxChanged(int state)
{
    if (state == Qt::Checked)
    {
        palettePcButton->setEnabled(true);
    }
    else
    {
        palettePcButton->setEnabled(false);
    }
}

void SettingsWindow::onPaletteArCheckBoxChanged(int state)
{
    if (state == Qt::Checked)
    {
        paletteArButton->setEnabled(true);
    }
    else
    {
        paletteArButton->setEnabled(false);
    }
}

void SettingsWindow::onPalettePcButtonPressed()
{
    QColor color = highlightColorDialog->getColor();
    if (color.isValid())
    {
        pcHighlight.setColor(QPalette::Window, color);
        setButtonColor(palettePcButton, color);
    }
}

void SettingsWindow::onPaletteArButtonPressed()
{
    QColor color = highlightColorDialog->getColor();
    if (color.isValid())
    {
        arHighlight.setColor(QPalette::Window, color);
        setButtonColor(paletteArButton, color);
    }
}

void SettingsWindow::setButtonColor(QPushButton *button, QColor color)
{
    if (color.isValid())
    {
        QString style = QString("background-color: %1").arg(color.name());
        button->setStyleSheet(style);
    }
}
