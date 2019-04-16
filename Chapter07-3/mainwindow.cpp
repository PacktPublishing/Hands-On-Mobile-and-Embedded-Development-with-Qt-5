#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QAbstractSocket>
#include <QtNetwork>
#include <QWebSocketProtocol>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    localSocket(new QWebSocket)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::sendText);

#ifndef Q_OS_WASM
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)
                && !address.isLinkLocal()) {
            qDebug() << address.toString();
            ui->textEdit->insertPlainText(address.toString() + "\n");
        }
    }
#endif
    initWebsockets();
}

MainWindow::~MainWindow()
{
    socketServer->close();
    delete ui;
    delete localSocket;
}

void MainWindow::initWebsockets()
{
    socketServer = new QWebSocketServer("MobileSocketServer", QWebSocketServer::NonSecureMode, this);

    connect(socketServer, &QWebSocketServer::newConnection, this, &MainWindow::newConnection);
    connect(socketServer, &QWebSocketServer::closed, this, &MainWindow::closed);
    connect(socketServer, &QWebSocketServer::serverError, this, &MainWindow::serverError);

    if (socketServer->listen(QHostAddress::Any,1234))
        ui->textEdit->insertPlainText("Listening...\n");
}

void MainWindow::closed()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::newConnection()
{
    qDebug() << Q_FUNC_INFO;
    QWebSocket *socket = socketServer->nextPendingConnection();

    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &MainWindow::socketError);

    connect(socket, &QWebSocket::textMessageReceived, this, &MainWindow::textMessageReceived);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &MainWindow::binaryReceived);

    clientSockets.append(socket);
    //  connect(socket, &QWebSocket::disconnected, this, &MainWindow::socketDisconnected);

}

void MainWindow::socketError(QAbstractSocket::SocketError error)
{
    qDebug() << "WebSocket error" << error;
}

void MainWindow::textMessageReceived(const QString &msg)
{
      QWebSocket *senderSocket = qobject_cast<QWebSocket *>(sender());
      QString str(senderSocket->peerAddress().toString() + " " +msg + "\n");
      ui->textEdit->insertPlainText(str);
}

void MainWindow::binaryReceived(const QByteArray &/*bMsg*/)
{
  //    QWebSocket *senderSocket = qobject_cast<QWebSocket *>(sender());

}

void MainWindow::sendText()
{
    const QString outgoingMessage = ui->lineEdit->text();

        if (outgoingMessage.left(7) == QStringLiteral("Connect")) {
            connectToServer(QUrl(outgoingMessage.section(' ',1,1)));
        return;
    }
      for (QWebSocket *cSocket : qAsConst(clientSockets)) {
          cSocket->sendTextMessage(outgoingMessage);
      }
      ui->lineEdit->clear();
}

void MainWindow::connectToServer(const QUrl url)
{
    if (socketServer->isListening())
        socketServer->close();

    qDebug() << Q_FUNC_INFO << url;
    connect(localSocket, &QWebSocket::connected,
            this, &MainWindow::localClientConnected);
    connect(localSocket, &QWebSocket::disconnected,
            this, &MainWindow::closed);
    localSocket->open(url);
}

void MainWindow::localClientConnected()
{
    qDebug() << Q_FUNC_INFO << __LINE__;
    clientSockets.append(localSocket);

    connect(localSocket, &QWebSocket::textMessageReceived,
            this, &MainWindow::textMessageReceived);
}

void MainWindow::serverError(QWebSocketProtocol::CloseCode closeCode)
{
    qDebug() << Q_FUNC_INFO << closeCode;
}
