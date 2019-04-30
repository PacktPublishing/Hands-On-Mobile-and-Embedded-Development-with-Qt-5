#include "sensorserver.h"
#include <QtSensors>
#include <QDebug>

#include <QtMqtt/QMqttTopicName>
#include <QtMqtt/QMqttSubscription>
#include <QtMqtt/QMqttTopicFilter>

SensorServer::SensorServer(QObject *parent)
    : QObject(parent),
      humiditySensor(new QHumiditySensor(this)),
      temperatureSensor(new QAmbientTemperatureSensor(this))
{
    initSensors();
    initWebsocket();
}

SensorServer::~SensorServer()
{
    mqttClient->disconnect();
}

void SensorServer::initWebsocket()
{
    mDevice.setUrl(QUrl("broker.hivemq.com:8000"));
    mDevice.setProtocol("mqttv3.1");

    connect(&mDevice, &WebSocketIODevice::socketConnected, this, &SensorServer::websocketConnected);
}

void SensorServer::websocketConnected()
{
    mqttClient = new QMqttClient(this);
    mqttClient->setProtocolVersion(QMqttClient::MQTT_3_1);
    mqttClient->setTransport(&mDevice, QMqttClient::IODevice);

    connect(mqttClient, &QMqttClient::errorChanged,
            this, &SensorServer::errorChanged);

    connect(mqttClient, &QMqttClient::stateChanged,
            this, &SensorServer::stateChanged);

    connect(mqttClient, &QMqttClient::messageReceived,
            this, &SensorServer::messageReceived);


    mqttClient->connectToHost();

}

void SensorServer::initSensors()
{
    if (!humiditySensor->connectToBackend()) {
        qWarning() << "Could not connect to humidity backend";
    } else {
        humiditySensor->setProperty("alwaysOn",true);
        connect(humiditySensor,SIGNAL(readingChanged()),
                this, SLOT(humidityReadingChanged()));
    }
    if (!temperatureSensor->connectToBackend()) {
        qWarning() << "Could not connect to humidity backend";
    } else {
        temperatureSensor->setProperty("alwaysOn",true);
        connect(temperatureSensor,SIGNAL(readingChanged()),
                this, SLOT(temperatureReadingChanged()));
    }
}

void SensorServer::humidityReadingChanged()
{
    qDebug() << Q_FUNC_INFO << __LINE__;
    QHumidityReading *humidityReading = humiditySensor->reading();
    QByteArray data;
    data.setNum(humidityReading->relativeHumidity());

    QMqttTopicName topicName("Humidity");
    QByteArray topicMessage(data);
    mqttClient->publish(topicName, topicMessage);
}

void SensorServer::temperatureReadingChanged()
{
    qDebug() << Q_FUNC_INFO << __LINE__;
    QAmbientTemperatureReading *tempReading = temperatureSensor->reading();
    QByteArray data;
    data.setNum(tempReading->temperature());

    QMqttTopicName topicName("Temperature");
    QByteArray topicMessage(data);
    mqttClient->publish(topicName, topicMessage);
}


void SensorServer::errorChanged(QMqttClient::
                                ClientError error)
{
    qDebug() << Q_FUNC_INFO << error;
    switch(error) {
    case QMqttClient::NoError:
        break;

    case QMqttClient::InvalidProtocolVersion:
        break;

    case QMqttClient::IdRejected:
        break;

    case QMqttClient::ServerUnavailable:
        break;

    case QMqttClient::BadUsernameOrPassword:
        break;

    case QMqttClient::NotAuthorized:
        break;

    case QMqttClient::TransportInvalid:
        break;

    case QMqttClient::ProtocolViolation:
        break;

    case QMqttClient::UnknownError:
        break;
    case QMqttClient::Mqtt5SpecificError:
        qDebug() << "Error";
    break;
    };
}

void SensorServer::stateChanged(QMqttClient::ClientState state)
{
    switch(state) {
    case QMqttClient::Connecting:
        qDebug() << "Connecting...";
        break;
    case QMqttClient::Connected:
        qDebug() << "Connected.";
        humiditySensor->start();
        temperatureSensor->start();
        subscribe();
        break;
    case QMqttClient::Disconnected:
        qDebug() << "Disconnected.";
        break;
    }
}

void SensorServer::messageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << Q_FUNC_INFO  << topic << message;
}

void SensorServer::subscribe()
{
    qDebug() << Q_FUNC_INFO;
    QMqttTopicFilter topicName("Humidity");
    subscription1 = mqttClient->subscribe(topicName, 0);

    connect(subscription1, &QMqttSubscription::stateChanged,
            this, &SensorServer::subscriptionStateChanged);


    QMqttTopicFilter topicName2("Temperature");
    subscription2 = mqttClient->subscribe(topicName, 0);
    connect(subscription1, &QMqttSubscription::stateChanged,
            this, &SensorServer::subscriptionStateChanged);

}

void SensorServer::subscriptionStateChanged(QMqttSubscription::SubscriptionState state)
{
    switch (state) {
    case QMqttSubscription::Unsubscribed:
        qDebug() << "Unsubscribed";
        break;
    case QMqttSubscription::SubscriptionPending:
        qDebug() << "SubscriptionPending";
        break;
    case QMqttSubscription::Subscribed:
        qDebug() << "Subscribed";
        break;
    case QMqttSubscription::UnsubscriptionPending:
        qDebug() << "UnsubscriptionPending";
        break;
    case QMqttSubscription::Error:
        qDebug() << "Error";
        break;
    };
}
