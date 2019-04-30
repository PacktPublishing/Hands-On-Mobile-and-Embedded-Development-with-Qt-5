#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCameraInfo>
#include <QMediaRecorder>
#include <QCameraImageCapture>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    ui->textEdit->insertPlainText(cameras.at(0).deviceName() + "\n");
    camera = new QCamera(cameras.at(0));

    connect(camera, &QCamera::statusChanged, [=] (QCamera::Status status) {
        ui->textEdit->insertPlainText(QString("Status changed %1").arg(status) + "\n");
    });
    cameraImageCapture = new QCameraImageCapture(camera, this);

    viewFinder = new QCameraViewfinder(this);
    camera->setViewfinder(viewFinder);
    ui->camLayout->addWidget(viewFinder);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stillCaptureButton_clicked()
{
    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    QImageEncoderSettings imageSettings;
    imageSettings.setCodec("image/png");
    cameraImageCapture->setEncodingSettings(imageSettings);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->searchAndLock();

    cameraImageCapture->capture("filename.png");
    camera->unlock();
}

void MainWindow::on_videoCaptureButton_clicked()
{
}

void MainWindow::on_cameraButton_clicked()
{
    camera->start();
}
