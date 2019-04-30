#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkSession>
#include <QNetworkConfigurationManager>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow :  public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *accessMan;
     QNetworkConfigurationManager *configMan;
    QString stateToString(QNetworkSession::State state);
    void printCaps(QNetworkConfigurationManager::Capabilities);

private slots:
    void stateChanged(QNetworkSession::State state);
    void finished(QNetworkReply *reply);
    void opened();
    void updateCompleted();
};

#endif // MAINWINDOW_H
