#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "presswindow.h"
#include "ui_presswindow.h"
#include <iostream>
#include <QThread>
#include <QDir>

#include "HuffmanArchiver.h"
#include "CLI.h"
#include <cstdlib>
#include <fstream>


enum OPERATION_TYPE {
    COMPRESS,
    DECOMPRESS
};

class MyThread : public QThread {
public:
    MyThread(QString path_to_file, QString directory,
             QString new_filename, OPERATION_TYPE type) :
        _path_to_file(path_to_file.toStdString()), _directory(directory.toStdString()),
        _new_filename(new_filename.toStdString()), _type(type) {}

    void run () {
        HuffmanArchiver ha;

        QString prefix = "..";
        for (int i = 0; i < QDir::currentPath().count('/') - 1; ++i)
            prefix.append("/..");

        std::string filename = prefix.toStdString() + _directory + "/" + _new_filename;

        std::ifstream ifs(_path_to_file, std::ifstream::binary);
        std::ofstream ofs(filename, std::ofstream::binary);

        if (_type == OPERATION_TYPE::COMPRESS)
            ha.compress(ifs,ofs);
        else
            ha.decompress(ifs,ofs);
    }

private:
    std::string _path_to_file;
    std::string _directory;
    std::string _new_filename;
    OPERATION_TYPE _type;
};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->zip->hide();
    ui->unzip->hide();
    ui->zipDone->hide();
    ui->unzipDone->hide();

    connect(ui->compressButton, &QPushButton::clicked, this, &MainWindow::onPushCompressButton);
    connect(ui->decompressButton, &QPushButton::clicked, this, &MainWindow::onPushDecompressButton);
    connect(ui->quitButton, &QPushButton::clicked, this, &MainWindow::onPushQuitButton);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onPushQuitButton() {
    this->close();
}

void MainWindow::onPushCompressButton() {
    ui->zipDone->hide();
    PressWindow compress_window;
    compress_window.setModal(true);
    compress_window.exec();

    MyThread* thread = new MyThread(compress_window.getPathToFile(), compress_window.getDirectory(),
                    compress_window.getNewFilename(), OPERATION_TYPE::COMPRESS);

    connect(thread, SIGNAL(started()), this, SLOT(drawZip()));
    connect(thread, SIGNAL(finished()), this, SLOT(drawZipDone()));

    thread->start();
}

void MainWindow::onPushDecompressButton() {
    PressWindow decompress_window;
    decompress_window.exec();

    MyThread* thread = new MyThread(decompress_window.getPathToFile(), decompress_window.getDirectory(),
                    decompress_window.getNewFilename(), OPERATION_TYPE::DECOMPRESS);

    connect(thread, SIGNAL(started()), this, SLOT(drawUnzip()));
    connect(thread, SIGNAL(finished()), this, SLOT(drawUnzipDone()));

    thread->start();
}

void MainWindow::drawZip() {
    ui->zip->show();
}

void MainWindow::drawZipDone() {
    ui->zip->hide();
    ui->zipDone->show();
}

void MainWindow::drawUnzip() {
    ui->unzip->show();
}

void MainWindow::drawUnzipDone() {
    ui->unzip->hide();
    ui->unzipDone->show();
}
