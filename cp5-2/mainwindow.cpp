#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QUrlQuery>
#include <QHttpPart>
#include <QHttpMultiPart>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    on_lineEdit_returnPressed();
    // send file
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(serverUrl));

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());

    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray fileBytes = file.readAll();
            manager->put(request, fileBytes);
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    on_lineEdit_returnPressed();
    // send form
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl url(serverUrl);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery formData;
    formData.addQueryItem("login", "me");
    formData.addQueryItem("password", "123");
    formData.addQueryItem("submit", "Send");
    url.setQuery(formData);
    request.setUrl(url);

    manager->get(request);
}

void MainWindow::on_lineEdit_returnPressed()
{
    // url changed
     serverUrl = ui->lineEdit->text();
}

void MainWindow::on_pushButton_3_clicked()
{
    // post
    on_lineEdit_returnPressed();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl url(serverUrl);

    QByteArray postData;
    postData.append("?login=me&password=123&submit=Send+data");
    manager->post(request, postData);
}

void MainWindow::on_pushButton_4_clicked()
{
    // multipart

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl url(serverUrl);


    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());

    if (filename.isEmpty())
        return;

    QFile *file = new QFile(filename);
    if (file->open(QIODevice::ReadOnly)) {

        QByteArray fileBytes = file->readAll();


        QHttpMultiPart *multiPart =
                new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                           QVariant("form-data; name=\"filename\""));
        textPart.setBody(filename.toLocal8Bit());


        QHttpPart filePart;
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                           QVariant("form-data; name=\"file\""));

        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/zip"));

        filePart.setBodyDevice(file);

        file->setParent(multiPart);

        multiPart->append(textPart);
        multiPart->append(filePart);

        manager->put(request, multiPart);

    }

}
