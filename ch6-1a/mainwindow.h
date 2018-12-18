#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceInfo>
#include <QListWidgetItem>

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
     QBluetoothLocalDevice *localDevice;
private slots:
    void newDevice(const QBluetoothDeviceInfo &info);
    void itemDoubleClicked(const QListWidgetItem *item);

    void displayPin(const QBluetoothAddress &address, const QString &str);
    void displayConfirmation(const QBluetoothAddress &address, const QString &str);
    void pairingFinished(const QBluetoothAddress &address, const QBluetoothLocalDevice::Pairing paring);
    void pairingError(const QBluetoothLocalDevice::Error error);
};

#endif // MAINWINDOW_H
