#ifndef MYSSLSERVER_H
#define MYSSLSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QSslSocket>

class MySslServer : public QTcpServer
{
public:
    MySslServer();
protected:
    void incomingConnection(qintptr handle) override;

private slots:
    void socketEncrypted();

};

#endif // MYSSLSERVER_H