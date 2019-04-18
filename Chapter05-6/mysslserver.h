#ifndef MYSSLSERVER_H
#define MYSSLSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QSslSocket>
#include <QFile>
#include <QFileDialog>

class MySslServer : public QTcpServer
{
    Q_OBJECT
public:
    MySslServer(QObject *parent = 0);
signals:
    void messageOutput(const QString &message);
protected:
    void incomingConnection(qintptr handle) override;
    QSslSocket *server;
    void initCerts();

private slots:
    void socketEncrypted();
    void modeChanged(QSslSocket::SslMode mode);
    void stateChanged(QAbstractSocket::SocketState socketState);
    void error(QAbstractSocket::SocketError);
    void readSocket();
    void connected();
    void disconnected();
};

#endif // MYSSLSERVER_H
