#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsVideoItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);

    QGraphicsVideoItem *item = new QGraphicsVideoItem;
    player->setVideoOutput(item);
    graphicsView->scene()->addItem(item);
    graphicsView->show();

    player->setMedia(QUrl("qrc://hellowindow.m4v"));
    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}
