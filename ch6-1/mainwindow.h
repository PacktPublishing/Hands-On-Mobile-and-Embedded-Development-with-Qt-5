#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtBluetooth/QLowEnergyController>

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
    void setupBle();

    QLowEnergyController *controller;
    QString errorToString(QLowEnergyController::Error errorValue);

private slots:
    void controllerError(QLowEnergyController::Error newError);
    void controllerStateChanged(QLowEnergyController::ControllerState newState);
};

#endif // MAINWINDOW_H
