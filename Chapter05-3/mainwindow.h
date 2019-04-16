#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>

#include <qftp.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void replyFinished(QNetworkReply *reply);

    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void networkReplyError(QNetworkReply::NetworkError code);
    void requestFinished();
    void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);

    void qftpDataTransferProgress(qint64,qint64);
   void stateChanged(int);

private:
    void putFtp();
    Ui::MainWindow *ui;
    QString remoteFile;
    QFtp *ftp ;
};

#endif // MAINWINDOW_H
