#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>

#include <QFile>
#include <QSocketNotifier>

#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

//#define BTN_TOUCH 0x14a


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fd(-1)
{
    ui->setupUi(this);
    scanInputDevices();
}

MainWindow::~MainWindow()
{
    libevdev_free(dev);
    delete ui;
}

void MainWindow::scanInputDevices()
{
    QDir inputDir = QDir("/dev/input");
    QStringList filters;
    filters << "event*";

    QStringList eventFiles = inputDir.entryList(filters, QDir::System);
    char name[256];

    for (QString file : eventFiles) {
        file.prepend("/dev/input/");
        fd = ::open(file.toLocal8Bit().constData(), O_RDONLY|O_NONBLOCK);

        if (fd >= 0) {
            if (isTouchDevice(fd)) {
                doScan(fd);
                break;
            } else {
                ::close(fd);
            }
        }
    }
}

bool MainWindow::isTouchDevice(int fd)
{
    int rc = 1;
    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        qWarning("Failed to init libevdev (%s)\n", strerror(-rc));
        return false;
    }
    if (libevdev_has_event_code(dev, EV_KEY, BTN_TOUCH)) {
        qWarning("Device: %s\n", libevdev_get_name(dev));
        return true;
    }
    libevdev_free(dev);
    return false;
}

int MainWindow::doScan(int fd)
{
    QSocketNotifier *notifier
            = new QSocketNotifier(fd, QSocketNotifier::Read, this);
    auto c = connect(notifier,  &QSocketNotifier::activated,
                     [=]( int /*socket*/ ) {
        int rc = -1;
        do {
            struct input_event ev;

            rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);

            if (rc == LIBEVDEV_READ_STATUS_SYNC) {
                while (rc == LIBEVDEV_READ_STATUS_SYNC) {
                    rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_SYNC, &ev);
                }
            } else if (rc == LIBEVDEV_READ_STATUS_SUCCESS) {
                if ((ev.type == EV_KEY && ev.code == BTN_TOUCH) ||
                        (ev.type == EV_ABS && ev.code == ABS_MT_POSITION_X) ||
                        (ev.type == EV_ABS && ev.code == ABS_MT_POSITION_Y)) {
                    qWarning("%s value: %i\n", libevdev_event_code_get_name(ev.type, ev.code), ev.value);
                }
            }
        } while (rc == 1 || rc == 0 || rc == -EAGAIN);
        return 0;
    });

    return 0;
}
