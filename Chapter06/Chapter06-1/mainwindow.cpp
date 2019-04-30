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
#include <QtCore/qloggingcategory.h>
#include <QBluetoothLocalDevice>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QBluetoothLocalDevice *localDevice = new QBluetoothLocalDevice(this);

    if (!localDevice->isValid()) {
        ui->textEdit->insertPlainText("No Bluetooth adapter found\n");
        return;
    }

    ui->textEdit->insertPlainText("Bluetooth adapter:\n    " + localDevice->name() +" "+ localDevice->address().toString() +"\n");

    QString hostModeString;
    switch (localDevice->hostMode()) {
    case QBluetoothLocalDevice::HostPoweredOff:
        hostModeString = "HostPoweredOff";
        break;
    case QBluetoothLocalDevice::HostConnectable:
        hostModeString = "HostConnectable";
        break;
    case   QBluetoothLocalDevice::HostDiscoverable:
        hostModeString = "HostDiscoverable";
        break;
    case QBluetoothLocalDevice::HostDiscoverableLimitedInquiry:
        hostModeString = "HostDiscoverableLimitedInquiry";
        break;
    }
    ui->textEdit->insertPlainText(hostModeString +"\n");
    if (localDevice->hostMode() != QBluetoothLocalDevice::HostPoweredOff)
        setupBle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBle()
{
    QLowEnergyAdvertisingData leAdd;
    leAdd.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);
    leAdd.setLocalName("SensorServer");
    leAdd.setIncludePowerLevel(true);

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

    controller = QLowEnergyController::createPeripheral();
    connect(controller, QOverload<QLowEnergyController::Error>::of(&QLowEnergyController::error), this, &MainWindow::controllerError);
    connect(controller, &QLowEnergyController::stateChanged, this, &MainWindow::controllerStateChanged);

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
    ui->textEdit->insertPlainText(errorToString(newError) +"\n");
}

void MainWindow::controllerStateChanged(QLowEnergyController::ControllerState newState)
{
    qWarning() << Q_FUNC_INFO << newState;
    QString stateString;
    switch (newState) {
    case  QLowEnergyController::UnconnectedState:
        stateString =  "UnconnectedState";
        break;
    case QLowEnergyController::ConnectingState:
        stateString = "ConnectingState";
        break;
    case QLowEnergyController::ConnectedState:
        stateString = "ConnectedState";
        break;
    case QLowEnergyController::DiscoveringState:
        stateString = "DiscoveringState";
        break;
    case QLowEnergyController::DiscoveredState:
        stateString = "DiscoveredState";
        break;
    case QLowEnergyController::ClosingState:
        stateString = "ClosingState";
        break;
    case QLowEnergyController::AdvertisingState:
        stateString = "AdvertisingState";
        break;

    }
    ui->textEdit->insertPlainText(stateString +"\n");
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
