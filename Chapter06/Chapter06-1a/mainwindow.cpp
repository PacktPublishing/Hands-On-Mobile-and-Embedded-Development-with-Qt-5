#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBluetoothDeviceDiscoveryAgent>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QBluetoothLocalDevice>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::itemDoubleClicked);

    localDevice = new QBluetoothLocalDevice(this);
    localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    ui->label->setText("<b>Local address:</b> " + localDevice->address().toString());

    connect(localDevice, &QBluetoothLocalDevice::pairingDisplayPinCode,
            this, &MainWindow::displayPin);

    connect(localDevice, &QBluetoothLocalDevice::pairingDisplayConfirmation,
            this, &MainWindow::displayConfirmation);

    connect(localDevice, &QBluetoothLocalDevice::pairingFinished,
            this, &MainWindow::pairingFinished);

    connect(localDevice, &QBluetoothLocalDevice::error,
            this, &MainWindow::pairingError);

    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &MainWindow::newDevice);
    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

}

MainWindow::~MainWindow()
{
   // localDevice->setHostMode(QBluetoothLocalDevice::HostMode);
    delete ui;
}

void MainWindow::newDevice(const QBluetoothDeviceInfo &info)
{
    QString label = QString("%1 \t%2").arg(info.name()).arg(info.address().toString());

    QListWidgetItem *item = new QListWidgetItem(label);
    item->setData(Qt::UserRole, info.address().toString());
    QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
    if (pairingStatus == QBluetoothLocalDevice::Unpaired) {
        QFont font;
        font.setBold(true);
        item->setFont(font);
    }
    ui->listWidget->addItem(item);
}

void MainWindow::itemDoubleClicked(const QListWidgetItem *item)
{
     QBluetoothAddress address(item->data(Qt::UserRole).toString());
//     QBluetoothDeviceInfo btInfo(address);
     qDebug() << Q_FUNC_INFO << item->data(Qt::UserRole).toString();
     QMessageBox msgBox;
     msgBox.setText("Bluetooth Pairing.");
     msgBox.setInformativeText("Do you want to pair with device: " + item->data(Qt::UserRole).toString());
     msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Cancel);
     int ret = msgBox.exec();
     if (ret == QMessageBox::Ok) {
         qDebug() << Q_FUNC_INFO << "Pairing...";
         localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
     }
}

void MainWindow::displayPin(const QBluetoothAddress &address, const QString &pin)
{
    qDebug() << Q_FUNC_INFO << address.toString() << pin;
    bool ok;
    QMessageBox msgBox;
    msgBox.setText(pin);
    msgBox.setInformativeText("Enter pin on remote device");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::displayConfirmation(const QBluetoothAddress &address, const QString &pin)
{
    qDebug() << Q_FUNC_INFO << address.toString() << pin;
}

void MainWindow::pairingFinished(const QBluetoothAddress &address, const QBluetoothLocalDevice::Pairing pairing)
{

    qDebug() << Q_FUNC_INFO << address.toString() << pairing;
}

void MainWindow::pairingError(const QBluetoothLocalDevice::Error error)
{

    qDebug() << Q_FUNC_INFO << error;
}


