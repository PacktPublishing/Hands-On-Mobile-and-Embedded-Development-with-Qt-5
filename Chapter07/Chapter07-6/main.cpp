#include <QCoreApplication>
#include "sensorserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SensorServer server;

    return a.exec();
}
