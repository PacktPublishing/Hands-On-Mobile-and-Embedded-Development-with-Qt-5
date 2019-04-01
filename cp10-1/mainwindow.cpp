#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QTableView>
#include <QStringListModel>
#include <QSqlField>
#include <QSqlRecord>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createDatabase()
{
    QString dbname = "MAEPQTdb";
    // QString databaseType = "QSQLITE";
    QString databaseType = "QMYSQL";

    QSqlDatabase db = QSqlDatabase::addDatabase(databaseType);
    if (databaseType == "QSQLITE") {
        db.setDatabaseName("mobileembedded.sql");
    }
    qDebug() << Q_FUNC_INFO << __LINE__;

    if (databaseType == "QMYSQL") {
        db.setHostName("10.0.0.243");
        db.setUserName("lpotter");
        db.setPassword("password");
    }

    bool ok = db.open();
    if (!ok) {
        qDebug() << Q_FUNC_INFO << "could not open database" << db.lastError().text();
    } else {
        if (databaseType == "QMYSQL") {
            QSqlQuery query(db);
            bool sr;

            sr = query.exec("CREATE DATABASE IF NOT EXISTS " + dbname);
            if (!sr) {
                qDebug() << __LINE__<< "Database Error" << query.lastError().text();
                return;
            }
            sr = query.exec("USE " + dbname);
        }
        createTables();
    }
}

void MainWindow::createTables()
{
    qDebug() << Q_FUNC_INFO << __LINE__;
    QSqlDatabase db = QSqlDatabase::database("MAEPQTdb");
    QSqlQuery q("", db);
    if (!q.exec("drop table Mobile;"))
        qDebug() << q.lastError();
    if (!q.exec("drop table Embedded;"))
        qDebug() << q.lastError();
    if (!q.exec("create table Mobile (id int primary key, Device varchar(20), Model varchar(20), Version varchar(20));"))
        qDebug() << q.lastError();
    if (!q.exec("insert into Mobile values (0, 'iPhone', '6SE', '12.1.2');"))
        qDebug() << q.lastError();
    if (!q.exec("insert into Mobile values (1, 'Moto', 'XT1710-09', '2');"))
        qDebug() << q.lastError();

    if (!q.exec("create table Embedded (id int primary key, Device varchar(20), Model varchar(20), Version varchar(20));"))
        qDebug() << q.lastError();
    if (!q.exec("insert into Mobile values (3, 'rpi', '1', '1');"))
        qDebug() << q.lastError();
    if (!q.exec("insert into Mobile values (4, 'rpi', '2', '2');"))
        qDebug() << q.lastError();
    if (!q.exec("insert into Mobile values (5, 'rpi', '3', '3');"))
        qDebug() << q.lastError();
}

void MainWindow::readTables()
{
    qDebug() << Q_FUNC_INFO << __LINE__;

    QSqlDatabase db = QSqlDatabase::database("MAEPQTdb");
    QSqlQuery query("SELECT * FROM Mobile", db);
    int rowCount = 0;
    while (query.next()) {

        QSqlRecord record = query.record();

        QSqlField idField = record.field("id");
        QSqlField deviceField = record.field("device");
        QSqlField modelField = record.field("model");
        QSqlField versionField = record.field("version");

        qDebug() << Q_FUNC_INFO
                 << modelField.name()
                 << modelField.tableName()
                 << modelField.value();

        QString id = query.value(0).toString();
        QString device = query.value(1).toString();
        QString model = query.value(2).toString();
        QString version = query.value(3).toString();

        ui->tableWidget->setRowCount(rowCount + 1);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(id));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(device));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(model));
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(version));
        rowCount++;
    }
    qDebug() << __LINE__<< "Database Error" << query.lastError().text();

}

void MainWindow::on_pushButton_clicked()
{
    readTables();
}
