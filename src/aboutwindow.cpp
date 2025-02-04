#include "aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent)
{
    // window
    setParent(parent);
    setWindowTitle("About");
    setFixedSize(275, 200);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_QuitOnClose);
    // ui
    setupUi();
}

AboutWindow::~AboutWindow()
{
}

void AboutWindow::setupUi()
{
    mainGrid = new QGridLayout(this);
    mainGrid->setObjectName("mainGrid");
    // title
    titleLabel = new QLabel("Little Man Computer");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 20px;");
    mainGrid->addWidget(titleLabel, 0, 0);
    // description
    descriptionLabel = new QLabel("A simple implementation of a <a href=\"https://en.wikipedia.org/wiki/Little_man_computer\">Little Man Computer</a>");
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setTextFormat(Qt::RichText);
    descriptionLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    descriptionLabel->setOpenExternalLinks(true);
    mainGrid->addWidget(descriptionLabel, 1, 0);
    // author
    authorLabel = new QLabel("Author: <a href=\"www.github.com/HarryWhitehorn/\">Harry Whitehorn</a>");
    authorLabel->setAlignment(Qt::AlignCenter);
    authorLabel->setTextFormat(Qt::RichText);
    authorLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    authorLabel->setOpenExternalLinks(true);
    mainGrid->addWidget(authorLabel, 2, 0);
    // version
    versionLabel = new QLabel("Version: 0.1.0");
    versionLabel->setAlignment(Qt::AlignCenter);
    mainGrid->addWidget(versionLabel, 3, 0);
    // license
    licenseLabel = new QLabel("Licence: <a href=\"www.github.com/HarryWhitehorn/lmc/blob/main/LICENSE\">MPL-2.0</a>");
    licenseLabel->setAlignment(Qt::AlignCenter);
    licenseLabel->setTextFormat(Qt::RichText);
    licenseLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    licenseLabel->setOpenExternalLinks(true);
    mainGrid->addWidget(licenseLabel, 4, 0);
    // 
    setLayout(mainGrid);
}
