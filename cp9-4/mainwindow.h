#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

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

    void on_stillCaptureButton_clicked();

    void on_videoCaptureButton_clicked();

    void on_cameraButton_clicked();

private:
    Ui::MainWindow *ui;
    QCameraViewfinder *viewFinder;
     QCameraImageCapture *cameraImageCapture;
     QCamera *camera;

};

#endif // MAINWINDOW_H
