#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <libevdev-1.0/libevdev/libevdev.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void scanInputDevices();
    bool isTouchDevice(int fd);
    int doScan(int fd);
    int fd;
    struct libevdev *dev = NULL;
//private slots:
//    void activated(int);
};

#endif // MAINWINDOW_H
