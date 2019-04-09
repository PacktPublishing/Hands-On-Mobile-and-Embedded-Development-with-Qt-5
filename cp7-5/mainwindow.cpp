#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttTopicName>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mqttClient = new QMqttClient(this);
    mqttClient->setHostname("broker.hivemq.com");
    mqttClient->setPort(1883);

    connect(mqttClient, &QMqttClient::errorChanged, this, &MainWindow::errorChanged);
    connect(mqttClient, &QMqttClient::stateChanged, this, &MainWindow::stateChanged);

    connect(mqttClient, &QMqttClient::messageReceived, this, &MainWindow::messageReceived);

    connect(mqttClient, &QMqttClient::pingResponseReceived, this, [this]() {
        qDebug() << Q_FUNC_INFO;
    });

    mqttClient->connectToHost();
}

MainWindow::~MainWindow()
{
    mqttClient->disconnect();
    delete ui;
}


void MainWindow::errorChanged(QMqttClient::ClientError error)
{
    qDebug() << Q_FUNC_INFO << error;
    ui->textEdit->insertPlainText("Error ");
    switch(error) {
    case QMqttClient::NoError:
        ui->textEdit->insertPlainText("NoError");
        break;

    case QMqttClient::InvalidProtocolVersion:
        ui->textEdit->insertPlainText("InvalidProtocolVersion");
        break;

    case QMqttClient::IdRejected:
        ui->textEdit->insertPlainText("IdRejected");
        break;

    case QMqttClient::ServerUnavailable:
        ui->textEdit->insertPlainText("ServerUnavailable");
        break;

    case QMqttClient::BadUsernameOrPassword:
        ui->textEdit->insertPlainText("BadUsernameOrPassword");
        break;

    case QMqttClient::NotAuthorized:
        ui->textEdit->insertPlainText("NotAuthorized");
        break;

    case QMqttClient::TransportInvalid:
        ui->textEdit->insertPlainText("TransportInvalid");
        break;

    case QMqttClient::ProtocolViolation:
        ui->textEdit->insertPlainText("ProtocolViolation");
        break;

    case QMqttClient::UnknownError:
        ui->textEdit->insertPlainText("UnknownError");
        break;

            case QMqttClient::Mqtt5SpecificError:
            ui->textEdit->insertPlainText("Mqtt5SpecificError");
            break;

    };
    ui->textEdit->insertPlainText("\n");
}

void MainWindow::stateChanged(QMqttClient::ClientState state)
{
    switch(state) {
    case QMqttClient::Connecting:
        ui->textEdit->insertPlainText("Connecting...");
        qDebug() << "Connecting...";
        break;
    case QMqttClient::Connected:
        ui->textEdit->insertPlainText("Connected");
        qDebug() << "Connected.";
        subscribe();
        break;
    case QMqttClient::Disconnected:
        ui->textEdit->insertPlainText("Disconnected");
        qDebug() << "Disconnected.";
        break;
    }
    ui->textEdit->insertPlainText("\n");

}

void MainWindow::messageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << Q_FUNC_INFO  << topic << message;
    ui->textEdit->insertPlainText(topic.name() + " " + message);
    ui->textEdit->insertPlainText("\n");

}

void MainWindow::subscribe()
{
    qDebug() << Q_FUNC_INFO;
    QMqttTopicFilter topicName("Qt");
    subscription = mqttClient->subscribe(topicName, 0);
    connect(subscription, &QMqttSubscription::stateChanged, this, &MainWindow::subscriptionStateChanged);

    publish();
}

void MainWindow::publish()
{
    qDebug() << Q_FUNC_INFO;
    QMqttTopicName topicName("Qt");
    QByteArray topicMessage("Everywhere!");
    mqttClient->publish(topicName, topicMessage);
}

void MainWindow::subscriptionStateChanged(QMqttSubscription::SubscriptionState state)
{
    switch (state) {
    case QMqttSubscription::Unsubscribed:
        ui->textEdit->insertPlainText("Unsubscribed");
        qDebug() << "Unsubscribed";
        break;
    case QMqttSubscription::SubscriptionPending:
        ui->textEdit->insertPlainText("SubscriptionPending");
        qDebug() << "SubscriptionPending";
        break;
    case QMqttSubscription::Subscribed:
        ui->textEdit->insertPlainText("Subscribed");
        qDebug() << "Subscribed";
        break;
    case QMqttSubscription::UnsubscriptionPending:
        ui->textEdit->insertPlainText("UnsubscriptionPending");
        qDebug() << "UnsubscriptionPending";
        break;
    case QMqttSubscription::Error:
        ui->textEdit->insertPlainText("Error");
        qDebug() << "Error";a
        break;
    };
    ui->textEdit->insertPlainText("\n");

}
