#include "presswindow.h"
#include "ui_presswindow.h"
#include <iostream>
#include <QString>
#include <QTextBrowser>

// --------------------- PRESS WINDOW ------------------

PressWindow::PressWindow(QWidget *parent) : QDialog(parent), ui(new Ui::PressWindow) {
    ui->setupUi(this);


    connect(ui->ChooseFileButton, &QPushButton::clicked, this, &PressWindow::onPushChooseFileButton);
    connect(ui->ChooseDirectoryButton, &QPushButton::clicked, this, &PressWindow::onPushChooseDirectoryButton);
    connect(ui->OkButton, &QPushButton::clicked, this, &PressWindow::onPushOkButton);
}

PressWindow::~PressWindow() {
    delete ui;
}

QString PressWindow::getNewFilename() const {
    return _new_filename;
}

QString PressWindow::getPathToFile() const {
    return _path_to_file;
}

QString PressWindow::getDirectory() const {
    return _directory;
}

void PressWindow::onPushChooseFileButton() {
    QString file = QFileDialog::getOpenFileName(this, "Select file", "/home");
    ui->browseFilePath->setText(file);
}

void PressWindow::onPushChooseDirectoryButton() {
    QString directory = QFileDialog::getExistingDirectory(this, "Select directory", "/home");
    ui->browseDirectory->setText(directory);
}

void PressWindow::onPushOkButton() {
    _new_filename = ui->FileNameEditor->text();
    _path_to_file = ui->browseFilePath->toPlainText();
    _directory = ui->browseDirectory->toPlainText();
    this->hide();
}
