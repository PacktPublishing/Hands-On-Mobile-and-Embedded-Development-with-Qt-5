#include "mysslserver.h"

#include <QFile>
#include <QSslKey>
#include <QSsl>

MySslServer::MySslServer(QObject *parent)
    : QTcpServer(parent)
{
    server = new QSslSocket(this);
    initCerts();
}

void MySslServer::initCerts()
{
    QByteArray key;
    QByteArray cert;

    QString keyPath = QFileDialog::getOpenFileName(0, tr("Open Key File"),
                                                   QDir::homePath(), "Key file (*.key)");

    if (!keyPath.isEmpty()) {
        QFile keyFile(keyPath);
        if (keyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            key = keyFile.readAll();
            keyFile.close();
        }
    }

    QString certPath = QFileDialog::getOpenFileName(0, tr("Open cert File"),
                                                    QDir::homePath(), "Cert file (*.cert)");

    if (!certPath.isEmpty()) {
        QFile certFile(certPath);
        if (certFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            cert = certFile.readAll();
            certFile.close();
        }
    }

    QSslKey sslKey(key, QSsl::Rsa, QSsl::Pem,QSsl::PrivateKey,"localhost");
    server->setPrivateKey(sslKey);

    QSslCertificate sslCert(cert);
    server->addCaCertificate(sslCert);
    server->setLocalCertificate(sslCert);
}

void MySslServer::incomingConnection(qintptr sd)
{
    if (server->setSocketDescriptor(sd)) {
        addPendingConnection(server);
        connect(server, &QSslSocket::connected,
                this, &MySslServer::connected);

        connect(server, &QSslSocket::disconnected,
                this, &MySslServer::disconnected);

        connect(server, &QSslSocket::encrypted,
                this, &MySslServer::socketEncrypted);

        connect(server, &QSslSocket::modeChanged,
                this, &MySslServer::modeChanged);

        connect(server, &QSslSocket::stateChanged,
                this, &MySslServer::stateChanged);

        connect(server, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(error(QAbstractSocket::SocketError)));
        connect(server,
                QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors),
                [=](const QList<QSslError> &errors){
            for (QSslError error : errors) {
                server->ignoreSslErrors();
                emit messageOutput(error.errorString());
            }
        });

        server->startServerEncryption();
        this->addPendingConnection(server);

    } else {
        delete server;
    }
}

void MySslServer::socketEncrypted()
{
    emit messageOutput("Encryption OK");
    connect(server, SIGNAL(readyRead()),
              this, SLOT(readSocket()));
    // entered encrypted mode, time to write secure transmissions
}

void MySslServer::modeChanged(QSslSocket::SslMode mode)
{
    QString message;
    switch (mode) {
    case QSslSocket::UnencryptedMode:
        message = "UnencryptedMode";
        break;
    case QSslSocket::SslClientMode:
        message = "SslClientMode";
        break;
    case QSslSocket::SslServerMode:
        message = "SslServerMode";
        break;
    };
    emit messageOutput(message);
}

void MySslServer::stateChanged(QAbstractSocket::SocketState socketState)
{
    QString message;
    switch (socketState) {
    case QAbstractSocket::UnconnectedState:
        message = "UnconnectedState";
        break;
    case QAbstractSocket::HostLookupState:
        message = "HostLookupState";
        break;
    case QAbstractSocket::ConnectingState:
        message = "ConnectingState";
        break;
    case QAbstractSocket::ConnectedState:
        message = "ConnectedState";
        break;
    case QAbstractSocket::BoundState:
        message = "BoundState";
        break;
    case QAbstractSocket::ClosingState:
        message = "ClosingState";
        break;
    case QAbstractSocket::ListeningState:
        message = "ListeningState";
        break;
    }
    emit messageOutput(message);
}

void MySslServer::error(QAbstractSocket::SocketError)
{
    emit messageOutput("Error: "+ server->errorString());
}

void MySslServer::readSocket()
{
     emit messageOutput(server->readAll());
}

void MySslServer::disconnected()
{
    emit messageOutput("Disconnected\n");
}

void MySslServer::connected()
{
    emit messageOutput("Connected\n");
}
