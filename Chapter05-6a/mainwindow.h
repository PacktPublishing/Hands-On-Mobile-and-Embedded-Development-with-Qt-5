#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSslSocket>

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
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();
    void error(QAbstractSocket::SocketError);
    void readIncomingBytes();
private:
    Ui::MainWindow *ui;
    void startSslSocket();
    void connected();
    void disconnected();
    void readMessage();

    QSslSocket *sslSocket;
    void initCerts();

};

#endif // MAINWINDOW_H
