#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MySslServer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void writeToScreen(const QString &message);
private:
    Ui::MainWindow *ui;
    MySslServer *sslServer;
};

#endif // MAINWINDOW_H
