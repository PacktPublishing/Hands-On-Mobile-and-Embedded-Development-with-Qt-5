
#include <qsaltsensor.h>
#include "qsaltsensor_p.h"

QT_BEGIN_NAMESPACE

IMPLEMENT_READING(QSaltReading)

/*!
    \class QSaltReading
    \ingroup sensors_reading
    \inmodule QtSensors
    \since 5.12

    \brief The QSaltReading class holds readings from the [X] sensor.

    [Fill this out]

    \section2 QSaltReading Units

    [Fill this out]
*/

/*!
    \property QSaltReading::myprop
    \brief [what does it hold?]

    [What are the units?]
    \sa {QSaltReading Units}
*/

qreal QSaltReading::myprop() const
{
    return d->myprop;
}

/*!
    Sets [what?] to \a myprop.
*/
void QSaltReading::setMyprop(qreal myprop)
{
    d->myprop = myprop;
}

// =====================================================================

/*!
    \class QSaltFilter
    \ingroup sensors_filter
    \inmodule QtSensors
    \since 5.[INSERT VERSION HERE]

    \brief The QSaltFilter class is a convenience wrapper around QSensorFilter.

    The only difference is that the filter() method features a pointer to QSaltReading
    instead of QSensorReading.
*/

/*!
    \fn QSaltFilter::filter(QSaltReading *reading)

    Called when \a reading changes. Returns false to prevent the reading from propagating.

    \sa QSensorFilter::filter()
*/

bool QSaltFilter::filter(QSensorReading *reading)
{
    return filter(static_cast<QSaltReading*>(reading));
}

char const * const QSaltSensor::type("QSaltSensor");

/*!
    \class QSaltSensor
    \ingroup sensors_type
    \inmodule QtSensors
    \since 5.[INSERT VERSION HERE]

    \brief The QSaltSensor class is a convenience wrapper around QSensor.

    The only behavioural difference is that this class sets the type properly.

    This class also features a reading() function that returns a QSaltReading instead of a QSensorReading.

    For details about how the sensor works, see \l QSaltReading.

    \sa QSaltReading
*/

/*!
    Construct the sensor as a child of \a parent.
*/
QSaltSensor::QSaltSensor(QObject *parent)
    : QSensor(QSaltSensor::type, parent)
{
}

/*!
    Destroy the sensor. Stops the sensor if it has not already been stopped.
*/
QSaltSensor::~QSaltSensor()
{
}

/*!
    \fn QSaltSensor::reading() const

    Returns the reading class for this sensor.

    \sa QSensor::reading()
*/

QSaltReading *QSaltSensor::reading() const
{
    return static_cast<QSaltReading*>(QSensor::reading());
}

#include "moc_qsaltsensor.cpp"
QT_END_NAMESPACE
