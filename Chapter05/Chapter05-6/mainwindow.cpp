#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mysslserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sslServer = new MySslServer();
    if (sslServer->listen(QHostAddress::Any, 4472)) {
        ui->textEdit->insertPlainText("Listening on port 4472\n");
    } else {
        ui->textEdit->insertPlainText("NOT Listening\n");
    }
    connect(sslServer, &MySslServer::messageOutput,
            this, &MainWindow::writeToScreen);
}

MainWindow::~MainWindow()
{
    delete sslServer;
    delete ui;
}

void MainWindow::writeToScreen(const QString &message)
{
    ui->textEdit->insertPlainText(message +"\n");
}
