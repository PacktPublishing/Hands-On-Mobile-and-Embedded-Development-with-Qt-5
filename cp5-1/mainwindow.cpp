#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
doRequest();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doRequest()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.example.com"));

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);

    manager->get(request);
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply->error())
        ui->textEdit->insertPlainText( reply->errorString());
    else {
        QList<QByteArray> headerList = reply->rawHeaderList();
        ui->textEdit->insertPlainText(headerList.join("\n") +"\n");
        QByteArray responsData = reply->readAll();
        ui->textEdit->insertHtml(responsData);
    }
}

//            if (reply->rawHeader(head).contains("json")) {
//                QJsonDocument json = QJsonDocument::fromJson(response_data);
//                qWarning(json);
//            }

