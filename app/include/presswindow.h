#ifndef COMPRESSWINDOW_H
#define COMPRESSWINDOW_H

#include <QFileDialog>
#include <QLineEdit>

namespace Ui {
    class PressWindow;
}

class PressWindow : public QDialog {
    Q_OBJECT
public:
    PressWindow(QWidget *parent = nullptr);
    ~PressWindow();

    QString getNewFilename () const;
    QString getPathToFile () const;
    QString getDirectory() const;

private slots:
    void onPushOkButton();
    void onPushChooseFileButton();
    void onPushChooseDirectoryButton();

private:
    QString _new_filename;
    QString _path_to_file;
    QString _directory;

    Ui::PressWindow *ui;
};

#endif // CHOOSEFILE_H
