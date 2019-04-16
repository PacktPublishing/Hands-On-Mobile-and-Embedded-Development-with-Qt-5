#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLocalSocket>
#include <algorithm>
#include <utility>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->insertPlainText("Not running\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startLocalServer()
{
    localServer = new QLocalServer(this);
    if (localServer->listen("localSocketName"))
        ui->textEdit->insertPlainText("QLocalServer listening...\n");

    connect(localServer, &QLocalServer::newConnection, this,
            &MainWindow::newLocalConnection);
}

void MainWindow::newLocalConnection()
{
    remoteSocket = localServer->nextPendingConnection();
    connect(remoteSocket, &QLocalSocket::readyRead,
            this, &MainWindow::readyRead);

    connect(remoteSocket, &QLocalSocket::disconnected,
            this, &MainWindow::disconnected);

    ui->textEdit->insertPlainText( remoteSocket->serverName() +" connected\n");

    remoteSocket->write("Client OK\r\n");
    remoteSocket->flush();
}

void MainWindow::on_pushButton_clicked()
{
    startLocalServer();
}

void MainWindow::readyRead()
{
    if (remoteSocket->bytesAvailable()) {
        QByteArray message = remoteSocket->readAll();
        ui->textEdit->insertPlainText(QString::fromLocal8Bit(message) + "\n");

        remoteSocket->write(message +"\r\n");
    }
}

void MainWindow::disconnected()
{
    ui->textEdit->insertPlainText("Client Disconnected\n");
}

void MainWindow::on_pushButton_2_clicked()
{
    localServer->close();
}
