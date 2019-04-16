#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->textEdit->insertPlainText("Not connected\n");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startLocalSocket()
{
    lSocket = new QLocalSocket(this);
    connect(lSocket, &QLocalSocket::connected,
            this, &MainWindow::connected);

    connect(lSocket, &QLocalSocket::disconnected,
            this, &MainWindow::disconnected);

    connect(lSocket, QOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error),
        [=](QLocalSocket::LocalSocketError socketError){


    });

    connect(lSocket, &QLocalSocket::readyRead,
            this, &MainWindow::readMessage);

    lSocket->connectToServer("localSocketName");

}

void MainWindow::readMessage()
{
    if (lSocket->bytesAvailable()) {
        QByteArray msg = lSocket->readAll();
        qDebug() << Q_FUNC_INFO << msg;

        ui->textEdit->insertPlainText(QString::fromLocal8Bit(msg) + "\n");

    }
}

void MainWindow::disconnected()
{
    ui->textEdit->insertPlainText("Disconnected\n");
}

void MainWindow::connected()
{
    ui->pushButton->setEnabled(true);

    ui->textEdit->insertPlainText("Connected\n");
}


void MainWindow::on_pushButton_2_clicked()
{
    //connect
    startLocalSocket();
}

void MainWindow::on_pushButton_clicked()
{
    // send
    lSocket->write(ui->lineEdit->text().toUtf8() +"\r\n");
}

void MainWindow::on_pushButton_3_clicked()
{
    // disconnect
    lSocket->disconnectFromServer();
}
