
#include "qmlsaltsensor.h"
#include <QSaltSensor>

/*!
    \qmltype SaltSensor
    \instantiates QmlSaltSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.[INSERT VERSION HERE]
    \inherits Sensor
    \brief The SaltSensor element reports on fubbleness.

    The SaltSensor element reports on fubbleness.

    This element wraps the QSaltSensor class. Please see the documentation for
    QSaltSensor for details.

    \sa SaltReading
*/

QmlSaltSensor::QmlSaltSensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QSaltSensor(this))
{
}

QmlSaltSensor::~QmlSaltSensor()
{
}

QmlSensorReading *QmlSaltSensor::createReading() const
{
    return new QmlSaltReading(m_sensor);
}

QSensor *QmlSaltSensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype SaltReading
    \instantiates QmlSaltReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.[INSERT VERSION HERE]
    \inherits SensorReading
    \brief The SaltReading element holds the most recent SaltSensor reading.

    The SaltReading element holds the most recent SaltSensor reading.

    This element wraps the QSaltReading class. Please see the documentation for
    QSaltReading for details.

    This element cannot be directly created.
*/

QmlSaltReading::QmlSaltReading(QSaltSensor *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
    , m_prop1(0)
{
}

QmlSaltReading::~QmlSaltReading()
{
}

/*!
    \qmlproperty qreal SaltReading::prop1
    This property holds the fubble of the device.

    Please see QSaltReading::prop1 for information about this property.
*/

qreal QmlSaltReading::prop1() const
{
    return m_prop1;
}

QSensorReading *QmlSaltReading::reading() const
{
    return m_sensor->reading();
}

void QmlSaltReading::readingUpdate()
{
    qreal prop1 = m_sensor->reading()->prop1();
    if (m_prop1 != prop1) {
        m_prop1 = prop1;
        Q_EMIT prop1Changed();
    }
}
