#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMqtt/QMqttClient>

#include <QtMqtt/QMqttSubscription>
#include <QtMqtt/QMqttTopicFilter>

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
    QMqttClient *mqttClient;
    QMqttSubscription *subscription;
    void subscribe();
    void publish();

private slots:
        void errorChanged(QMqttClient::ClientError error);
        void stateChanged(QMqttClient::ClientState state);
        void messageReceived(const QByteArray &message, const QMqttTopicName &topic);

        void subscriptionStateChanged(QMqttSubscription::SubscriptionState state);

};

#endif // MAINWINDOW_H
