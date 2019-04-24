#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList geoSources =  QGeoSatelliteInfoSource::availableSources();
    if (!geoSources.isEmpty()) {

        source = QGeoSatelliteInfoSource::createSource(geoSources.at(0), this);

        if (source) {
            source->setUpdateInterval(3000);
            connect(source, &QGeoSatelliteInfoSource::satellitesInViewUpdated,
                    this, &MainWindow::satellitesInViewUpdated);
            connect(source, &QGeoSatelliteInfoSource::satellitesInUseUpdated,
                    this, &MainWindow::satellitesInUseUpdated);
            connect(source, QOverload<QGeoSatelliteInfoSource::Error>::of(&QGeoSatelliteInfoSource::error),
                    this, &MainWindow::error);
        }
        source->startUpdates();
    } else {
        ui->textEdit->insertPlainText("No QGeoSatelliteInfoSource available");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::error(QGeoSatelliteInfoSource::Error /*error*/)
{
    ui->textEdit->insertPlainText("Error\n");
}

void MainWindow::satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &infos)
{
    QString msg;
    if (infos.count() > 0) {
        msg.append("Number of satellites in view: " + QString::number(infos.count()) + "\n");

        foreach (const QGeoSatelliteInfo &info, infos) {
            msg.append("    satelliteIdentifier"  + QString::number(info.satelliteIdentifier())
                       + " signalStrength " + QString::number(info.signalStrength())
                       + (info.hasAttribute(QGeoSatelliteInfo::Elevation) ? " Elevation " + QString::number(info.attribute(QGeoSatelliteInfo::Elevation)) : "")
                       + (info.hasAttribute(QGeoSatelliteInfo::Elevation) ? " Azimuth " + QString::number(info.attribute(QGeoSatelliteInfo::Azimuth)) : "") + "\n");
        }
        ui->textEdit->insertPlainText(msg);
    }
}

void MainWindow::satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &infos)
{
    QString msg;
    if (infos.count() > 0) {
        msg.append("Number of satellites in view: " + QString::number(infos.count()) + "\n");

        foreach (const QGeoSatelliteInfo &info, infos) {

            msg.append("    satelliteIdentifier"  + QString::number(info.satelliteIdentifier())
                       + " signalStrength " + QString::number(info.signalStrength())
                       + (info.hasAttribute(QGeoSatelliteInfo::Elevation) ? " Elevation " + QString::number(info.attribute(QGeoSatelliteInfo::Elevation)) : "")
                       + (info.hasAttribute(QGeoSatelliteInfo::Elevation) ? " Azimuth " + QString::number(info.attribute(QGeoSatelliteInfo::Azimuth)) : "") + "\n");
        }
        ui->textEdit->insertPlainText(msg);
        ui->textEdit->ensureCursorVisible();
    }
}
