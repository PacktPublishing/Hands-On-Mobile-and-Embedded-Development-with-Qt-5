#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>

#include <QFile>
#include <QSocketNotifier>
#include <QTextStream>

#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/input.h>

#include <QDebug>

#define BITSLONG (sizeof(long) * 8)
#define LONG_FIELD_SIZE(bits) ((bits / BITSLONG) + 1)
#define BTN_TOUCH 0x14a
#define ABS_MT_POSITION_X 0x35
#define ABS_MT_POSITION_Y 0x36

static inline bool testBit(long bit, const long *array)
{
    return (array[bit / BITSLONG] >> bit % BITSLONG) & 1;
}

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
    ::close(fd);
    delete ui;
}

int MainWindow::doScan(int fd)
{
    QSocketNotifier *notifier
            = new QSocketNotifier(fd, QSocketNotifier::Read, this);

    auto c = connect(notifier,  &QSocketNotifier::activated,
                     [=]( int /*socket*/ ) {

        struct input_event ev;
        unsigned int size;

        size = read(fd, &ev, sizeof(struct input_event));

        if (size < sizeof(struct input_event)) {
            qWarning("expected %u bytes, got %u\n", sizeof(struct input_event), size);
            perror("\nerror reading");
            return EXIT_FAILURE;
        }

        if (ev.type == EV_KEY && ev.code == BTN_TOUCH)
            qWarning("Touchscreen value: %i\n", ev.value);
        if (ev.type == EV_ABS && ev.code == ABS_MT_POSITION_X)
            qWarning("X value: %i\n",  ev.value);
        if (ev.type == EV_ABS && ev.code == ABS_MT_POSITION_Y)
            qWarning("Y value: %i\n",  ev.value);

        return 0;
    });

    return true;
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
         fd = ::open(file.toLocal8Bit().constData(), O_RDONLY);

         if (fd >= 0) {
             if (isTouchDevice(fd)) {
                 doScan(fd);
                 break;
             }
         }
     }
 }

 bool MainWindow::isTouchDevice(int fd)
 {
     unsigned short id[4];
     long bitsKey[LONG_FIELD_SIZE(KEY_CNT)];

     memset(bitsKey, 0, sizeof(bitsKey));

     ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(bitsKey)), bitsKey);

     if (testBit(BTN_TOUCH, bitsKey)) {
         return true;
     }

     return false;
 }

