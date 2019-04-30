#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

void MainWindow::on_pushButtonStrings_clicked()
{
    for (int i = 0; i < 20; i++) {
      qDebug() << i;
    }

    QString a("crab");
    QString b("Apple");

    qDebug() << a << b;
}

void MainWindow::on_pushButtonCrash_clicked()
{
    int crash = 21 / 0;
}
