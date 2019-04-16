#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_AcceptTouchEvents, true);
  //  qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    switch(event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchCancel:
    case QEvent::TouchEnd:
    case QEvent::TouchUpdate:
        qWarning("Touch event %d", event->type());
        break;
    default:
        break;
    };
    return QMainWindow::eventFilter(obj, event);
}

bool MainWindow::event(QEvent *ev)
{
  switch (ev->type()) {
    case QEvent::TouchBegin:
      qWarning("TouchBegin event %d", ev->type());
        break;
    case QEvent::TouchEnd:
      qWarning("TouchEnd event %d", ev->type());
        break;
    case QEvent::TouchUpdate:
      qWarning("TouchUpdate event %d", ev->type());
        break;
    };
  return false;
}
