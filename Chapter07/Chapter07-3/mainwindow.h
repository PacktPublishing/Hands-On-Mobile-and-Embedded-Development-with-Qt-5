#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QWebSocketProtocol>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
     QWebSocketServer *socketServer;
    Ui::MainWindow *ui;
    void initWebsockets();
    QList<QWebSocket *> clientSockets;
    void connectToServer(QUrl url);
    QWebSocket *localSocket;

private slots:
    void closed();
    void newConnection();
    void socketError(QAbstractSocket::SocketError error);
    void textMessageReceived(const QString &msg);
    void binaryReceived(const QByteArray &bMsg);
    void sendText();
    void localClientConnected();
    void serverError(QWebSocketProtocol::CloseCode closeCode);


};

#endif // MAINWINDOW_H
