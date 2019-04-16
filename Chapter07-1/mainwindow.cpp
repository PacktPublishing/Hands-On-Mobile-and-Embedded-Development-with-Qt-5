#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSensors>
#include <QDebug>
#include <QLightFilter>

class LightFilter : public QLightFilter
{
public:
    bool filter(QLightReading *reading)
    {
        int lux = 0;
        int averageLux = 0;
        if (averagingList.count() <= 4) {
            averagingList.append(reading->lux());
        } else {
            for (int i = 0; i < averagingList.count(); i++) {
                lux += averagingList.at(i);
            }
            averageLux = lux / (averagingList.count());
            reading->setLux(averageLux);
            averagingList.append(averageLux);
            return true; // store the reading in the sensor
        }
        return false;
    };
    QList<int> averagingList;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSensors();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSensors()
{
    for (const QByteArray &type : QSensor::sensorTypes()) {
        ui->textEdit->insertPlainText("Found type "+type +"\n");
        const QByteArray &identifier = QSensor::defaultSensorForType(type);
        ui->textEdit->insertPlainText("    Found identifier "+identifier+"\n");
        QSensor* sensor = new QSensor(type, this);
        sensor->setIdentifier(identifier);
        if (!sensor->connectToBackend()) {
            ui->textEdit->insertPlainText(  "Couldn't connect to " + identifier);
        } else {
            connect(sensor, &QSensor::readingChanged, this, &MainWindow::readingChanged);
            if (type == QByteArray("QLightSensor")) {
                qWarning() << "add filter";
                LightFilter *filter = new LightFilter();
                  sensor->addFilter(filter);
            }
            if (!sensor->isActive())
                sensor->start();
        }
    }
}

void MainWindow::readingChanged()
{
    QSensor *sensor = qobject_cast<QSensor *>(sender());

    QSensorReading *reading = sensor->reading();

    qDebug() << Q_FUNC_INFO << reading->value(0);

    QString values;
    for (int i = 0; i < reading->valueCount(); i++) {
        values += QString::number(reading->value(i).toReal()) + " ";
    }
    ui->textEdit->insertPlainText(sensor->type() +" " + sensor->identifier() + " "+ values + "\n");
}

