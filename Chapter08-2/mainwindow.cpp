#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGeoPositionInfoSource>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGeoPositionInfoSource *geoSource = QGeoPositionInfoSource::createDefaultSource(this);
    if (geoSource) {
        ui->textEdit->insertPlainText(methodsToString(geoSource->supportedPositioningMethods()) + "\n");

        geoSource->setUpdateInterval(3000);
        connect(geoSource, &QGeoPositionInfoSource::positionUpdated,
                this, &MainWindow::positionUpdated);
        geoSource->startUpdates();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::positionUpdated(const QGeoPositionInfo &positionInfo)
{
    QGeoCoordinate coords = positionInfo.coordinate();
    QString msg;

    ui->textEdit->insertPlainText(positionInfo.timestamp().toString() + "\n");

    for (int i = 0; i < 6; i++) {
        if (positionInfo.hasAttribute(static_cast<QGeoPositionInfo::Attribute>(i)))
            ui->textEdit->insertPlainText("    " + attributeToString(static_cast<QGeoPositionInfo::Attribute>(i)) + " "+
                                          QString::number(positionInfo.attribute(static_cast<QGeoPositionInfo::Attribute>(i))) + "\n");
    }
    ui->textEdit->insertPlainText(QString("    Latitude %1\n").arg(coords.latitude()));
    ui->textEdit->insertPlainText(QString("    Longitude %1\n").arg(coords.longitude()));
    if (coords.type() == QGeoCoordinate::Coordinate3D)
        ui->textEdit->insertPlainText(QString("    Altitude %1\n").arg(coords.altitude()));

    ui->textEdit->ensureCursorVisible();
}

QString MainWindow::attributeToString(QGeoPositionInfo::Attribute attribute)
{
    switch (attribute) {
    case QGeoPositionInfo::Direction:
        return QStringLiteral("Direction");
        break;
    case QGeoPositionInfo::GroundSpeed:
        return QStringLiteral("GroundSpeed");
        break;
    case QGeoPositionInfo::VerticalSpeed:
        return QStringLiteral("VerticalSpeed");
        break;
    case QGeoPositionInfo::MagneticVariation:
        return QStringLiteral("MagneticVariation");
        break;
    case QGeoPositionInfo::HorizontalAccuracy:
        return QStringLiteral("HorizontalAccuracy");
        break;
    case QGeoPositionInfo::VerticalAccuracy:
        return QStringLiteral("VerticalAccuracy");
        break;
    };
    return QString();
}

QString MainWindow::methodsToString(QGeoPositionInfoSource::PositioningMethods method)
{
    switch (method) {
    case QGeoPositionInfoSource::NoPositioningMethods:
        return QStringLiteral("No Positioning Methods");
        break;
    case QGeoPositionInfoSource::SatellitePositioningMethods:
        return QStringLiteral("Satellite Positioning Methods");
        break;
    case QGeoPositionInfoSource::NonSatellitePositioningMethods:
        return QStringLiteral("Non Satellite Positioning Methods");
        break;
    case QGeoPositionInfoSource::AllPositioningMethods:
        return QStringLiteral("All Positioning Methods");
        break;
    };
    return QString();
}

