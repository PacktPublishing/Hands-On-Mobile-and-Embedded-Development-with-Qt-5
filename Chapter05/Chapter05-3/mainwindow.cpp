#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QFile>

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>



#define USER "guest@llornkcor.com"
#define PASS "handsonmobileandembedded"
#define URL "ftp://llornkcor.com"

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
    //QtFtp
    ftp = new QFtp(this);
    connect(ftp, SIGNAL(commandFinished(int,bool)),
            this, SLOT(qftpCommandFinished(int,bool)));

    connect(ftp, SIGNAL(stateChanged(int)),
            this, SLOT(stateChanged(int)));

    connect(ftp, SIGNAL(dataTransferProgress(qint64,qint64)),
            this, SLOT(qftpDataTransferProgress(qint64,qint64)));

    QUrl url(URL);
    ftp->connectToHost(url.host(), 21);
    ftp->login(USER, PASS);
}

void MainWindow::on_pushButton_2_clicked()
{
    // QNAM
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);

    QNetworkRequest request;

    QUrl url(URL);
    url.setUserName(USER);
    url.setPassword(PASS);
    url.setPort(21);

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Image Files (*.png *.jpg *.bmp)"));

    if (!filename.isEmpty()) {
        QFile file(filename);
        remoteFile = QFileInfo(file).fileName();
        qDebug() << Q_FUNC_INFO << remoteFile;

        url.setPath(remoteFile);
        request.setUrl(url);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

            QByteArray fileBytes = file.readAll();
            QNetworkReply *networkReply = manager->put(request, fileBytes);

            connect(networkReply, &QNetworkReply::downloadProgress,
                    this, &MainWindow::onDownloadProgress);
            connect(networkReply, &QNetworkReply::downloadProgress,
                    this, &MainWindow::onUploadProgress);

            connect(networkReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
                    [=](QNetworkReply::NetworkError code){
                qDebug() << Q_FUNC_INFO << code << networkReply->errorString();
            });

            connect(networkReply, &QNetworkReply::finished,
                    this, &MainWindow::requestFinished);
        }
    }
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply->error())
        qDebug() << Q_FUNC_INFO << reply->errorString();
    else {
        QList<QByteArray> headerList = reply->rawHeaderList();
        QByteArray responsData = reply->readAll();
    }
}

void MainWindow::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << Q_FUNC_INFO << "bytesReceived" << bytesReceived<< "bytesTotal" << bytesTotal;
}

void MainWindow::networkReplyError(QNetworkReply::NetworkError code)
{
    qDebug() << Q_FUNC_INFO << code << code;
}

void MainWindow::requestFinished()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug() << Q_FUNC_INFO << "bytesSent" << bytesSent<< "bytesTotal" << bytesTotal;
}
void MainWindow::qftpCommandFinished(int i, bool isError)
{
    if (isError)
        qDebug() << Q_FUNC_INFO << i<< "Error" << isError << ftp->errorString();
    else {
        if (ftp->currentCommand() == QFtp::Login)
            ftp->list();
    }
}

void MainWindow::putFtp()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("Image Files (*.png *.jpg *.bmp)"));

    if (!filename.isEmpty()) {
        QFile file(filename);
        remoteFile = QFileInfo(file).fileName();

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray fileBytes = file.readAll();
            ftp->put(fileBytes, remoteFile);
        }
    }
}

void MainWindow::qftpDataTransferProgress(qint64 readBytes, qint64 totalBytes)
{
    qDebug() << Q_FUNC_INFO << "readBytes" << readBytes<< "totalBytes" << totalBytes;
}

void MainWindow::stateChanged(int i)
{
    qDebug() << Q_FUNC_INFO << i;
    if (i == 4)
        putFtp();
}
