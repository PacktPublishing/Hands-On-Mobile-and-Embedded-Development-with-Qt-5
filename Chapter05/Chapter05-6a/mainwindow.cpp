#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>

#include <QSslSocket>
#include <QSslKey>
#include <QSsl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //  startSslSocket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCerts()
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
    sslSocket->setPrivateKey(sslKey);

    QSslCertificate sslCert(cert);
    sslSocket->addCaCertificate(sslCert);
    sslSocket->setLocalCertificate(sslCert);
}

void MainWindow::startSslSocket()
{
    sslSocket = new QSslSocket(this);
    initCerts();
    connect(sslSocket, &QSslSocket::connected,
            this, &MainWindow::connected);

    connect(sslSocket, &QSslSocket::disconnected,
            this, &MainWindow::disconnected);

    connect(sslSocket, &QSslSocket::readyRead, this, &MainWindow::readIncomingBytes);

    connect(sslSocket,
            QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors),
            [=](const QList<QSslError> &errors){
        for (QSslError error : errors) {
            sslSocket->ignoreSslErrors();

            ui->textEdit->insertPlainText(error.errorString() + "\n");
        }
    });
    connect(sslSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(error(QAbstractSocket::SocketError)));

    connect(sslSocket, &QSslSocket::readyRead,
            this, &MainWindow::readMessage);

    sslSocket->connectToHostEncrypted("localhost", 4472);

}

void MainWindow::readMessage()
{
    if (sslSocket->bytesAvailable()) {
        QByteArray msg = sslSocket->readAll();
        ui->textEdit->insertPlainText(QString::fromLocal8Bit(msg) + "\n");
    }
}

void MainWindow::disconnected()
{
    ui->textEdit->insertPlainText("Disconnected\n");
}

void MainWindow::connected()
{
    ui->textEdit->insertPlainText("Connected\n");
}

void MainWindow::on_pushButton_2_clicked()
{
    //connect
    startSslSocket();
}

void MainWindow::on_pushButton_clicked()
{
    // send
    sslSocket->write(ui->lineEdit->text().toUtf8() +"\r\n");
}

void MainWindow::on_pushButton_3_clicked()
{
    // disconnect
    //sslSocket->disconnectFromServer();
}

void MainWindow::error(QAbstractSocket::SocketError)
{
    ui->textEdit->insertPlainText("Error: "+ sslSocket->errorString() +"\n");
}

void MainWindow::readIncomingBytes()
{
    ui->textEdit->insertPlainText(sslSocket->readAll() +"\n");
}
