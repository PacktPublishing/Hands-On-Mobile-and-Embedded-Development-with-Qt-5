#include "mysslserver.h"

MySslServer::MySslServer()
{

}

void MySslServer::incomingConnection(qintptr sd)
{
    QSslSocket *server = new QSslSocket(this);
    if (server->setSocketDescriptor(sd)) {
        addPendingConnection(server);
        connect(server, &QSslSocket::encrypted, this, &MySslServer::socketEncrypted);
        server->startServerEncryption();
    } else {
        delete server;
    }
}

void MySslServer::socketEncrypted()
{
}
