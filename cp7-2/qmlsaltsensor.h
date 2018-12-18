
#ifndef QMLSALTSENSOR_H
#define QMLSALTSENSOR_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QSaltSensor;

class QmlSaltSensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlSaltSensor(QObject *parent = 0);
    ~QmlSaltSensor();

private:
    QSensor *sensor() const override;
    QmlSensorReading *createReading() const override;

    QSaltSensor *m_sensor;
};

class QmlSaltReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal prop1 READ prop1 NOTIFY prop1Changed)
public:
    explicit QmlSaltReading(QSaltSensor *sensor);
    ~QmlSaltReading();

    qreal prop1() const;

Q_SIGNALS:
    void prop1Changed();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QSaltSensor *m_sensor;
    qreal m_prop1;
};

QT_END_NAMESPACE
#endif
