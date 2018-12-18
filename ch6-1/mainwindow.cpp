#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

#include <QtBluetooth/QLowEnergyAdvertisingData>
#include <QtBluetooth/QLowEnergyAdvertisingParameters>
#include <QtBluetooth/QLowEnergyCharacteristic>
#include <QtBluetooth/QLowEnergyCharacteristicData>
#include <QtBluetooth/QLowEnergyDescriptorData>
#include <QtBluetooth/QLowEnergyService>
#include <QtBluetooth/QLowEnergyServiceData>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBle()
{
    controller = QLowEnergyController::createPeripheral(this);
    connect(controller, QOverload<QLowEnergyController::Error>::of(&QLowEnergyController::error), this, &MainWindow::controllerError);
    connect(controller, &QLowEnergyController::stateChanged, this, &MainWindow::controllerStateChanged);

    QLowEnergyAdvertisingData leAdd;
    leAdd.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);
    leAdd.setLocalName("SensorServer");

    QList<QBluetoothUuid> servicesList;
    servicesList.append(QBluetoothUuid::EnvironmentalSensing);
    leAdd.setServices(servicesList);

    QLowEnergyCharacteristicData chData;
    chData.setUuid(QBluetoothUuid::TemperatureMeasurement);
    chData.setValue(QByteArray(2,0));
    chData.setProperties(QLowEnergyCharacteristic::Notify);
    const QLowEnergyDescriptorData descriptorData(QBluetoothUuid::ClientCharacteristicConfiguration, QByteArray(2, 0));
    chData.addDescriptor(descriptorData);

    QLowEnergyServiceData serviceData;
    serviceData.setUuid(QBluetoothUuid::Temperature);
    serviceData.setType(QLowEnergyServiceData::ServiceTypePrimary);
    serviceData.addCharacteristic(chData);
    QLowEnergyService *service = controller->addService(serviceData);
    QLowEnergyCharacteristic characteristic = service->characteristic(QBluetoothUuid::TemperatureMeasurement);

    quint8 temperature = 35;

    QByteArray currentTempValue;
    currentTempValue.append(char(0));
    currentTempValue.append(char(temperature));
    service->writeCharacteristic(characteristic, currentTempValue);

    controller->startAdvertising(QLowEnergyAdvertisingParameters(), leAdd, leAdd);

}

void MainWindow::controllerError(QLowEnergyController::Error newError)
{
    qWarning() << Q_FUNC_INFO << newError;
    ui->textEdit->insertPlainText(errorToString(newError));
}

void MainWindow::controllerStateChanged(QLowEnergyController::ControllerState newState)
{
    qWarning() << Q_FUNC_INFO << newState;
}

QString MainWindow::errorToString(QLowEnergyController::Error errorValue)
{
    QString ret(QStringLiteral("No error"));
    switch(errorValue) {
    case QLowEnergyController::NoError:
        break;
    case QLowEnergyController::UnknownError:
        ret = "UnknownError";
        break;

    case QLowEnergyController::UnknownRemoteDeviceError:
        ret = "UnknownRemoteDeviceError";
        break;

    case QLowEnergyController::NetworkError:
        ret = "NetworkError";
        break;

    case QLowEnergyController::InvalidBluetoothAdapterError:
        ret = "InvalidBluetoothAdapterError";
        break;
    case QLowEnergyController::ConnectionError:
        ret = "ConnectionError";
        break;
    case QLowEnergyController::AdvertisingError:
        ret = "AdvertisingError";
        break;
    case QLowEnergyController::RemoteHostClosedError:
        ret = "RemoteHostClosedError";
        break;
    };
    return ret;
}