#ifndef SENSORSERVER_H
#define SENSORSERVER_H

#include <QObject>
#include <QHumiditySensor>
#include <QAmbientTemperatureSensor>

#include <QtMqtt/QMqttClient>
#include "websocketiodevice.h"

class SensorServer : public QObject
{
    Q_OBJECT
public:
    explicit SensorServer(QObject *parent = nullptr);
    ~SensorServer();

signals:

private slots:
    void humidityReadingChanged();
    void temperatureReadingChanged();

    void errorChanged(QMqttClient::ClientError error);
    void stateChanged(QMqttClient::ClientState state);
    void messageReceived(const QByteArray &message, const QMqttTopicName &topic);

    void subscriptionStateChanged(QMqttSubscription::SubscriptionState state);
    void websocketConnected();

private:
    void initSensors();
    void initWebsocket();
    QHumiditySensor *humiditySensor;
    QAmbientTemperatureSensor *temperatureSensor;

    QMqttClient *mqttClient;
    QMqttSubscription *subscription1;
    QMqttSubscription *subscription2;
    void subscribe();
    WebSocketIODevice mDevice;
};

#endif // SENSORSERVER_H
