
#ifndef QSALTSENSOR_H
#define QSALTSENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QSaltReadingPrivate;

class Q_SENSORS_EXPORT QSaltReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal myprop READ myprop)
    DECLARE_READING(QSaltReading)
public:
    qreal myprop() const;
    void setMyprop(qreal myprop);
};

class Q_SENSORS_EXPORT QSaltFilter : public QSensorFilter
{
public:
    virtual bool filter(QSaltReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QSaltSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QSaltSensor(QObject *parent = 0);
    ~QSaltSensor();
    QSaltReading *reading() const;
    static char const * const type;

private:
    Q_DISABLE_COPY(QSaltSensor)
};

QT_END_NAMESPACE

#endif
