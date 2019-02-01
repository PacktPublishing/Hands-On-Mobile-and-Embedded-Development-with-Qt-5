#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkConfiguration>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow
{
    ui->setupUi(this);
    accessMan = new QNetworkAccessManager(this);
    QObject::connect(accessMan, &QNetworkAccessManager::finished,
                     this, &MainWindow::finished);
qWarning() << "network accessible" << accessMan->networkAccessible();
    configMan = new QNetworkConfigurationManager(this);
    connect(configMan, &QNetworkConfigurationManager::updateCompleted,
            this, &MainWindow::updateCompleted);
qWarning() << "isOnline?" << configMan->isOnline();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stateChanged(QNetworkSession::State state)
{
    qDebug() << Q_FUNC_INFO << stateToString(state);
}

QString MainWindow::stateToString(QNetworkSession::State state)
{
    switch (state) {
    case QNetworkSession::NotAvailable:
        return QStringLiteral("NotAvailable");
        break;
    case QNetworkSession::Connected:
        return QStringLiteral("Connected");
        break;
    case QNetworkSession::Connecting:
        return QStringLiteral("Connecting");
        break;
    case QNetworkSession::Closing:
        return QStringLiteral("Closing");
        break;
    case QNetworkSession::Disconnected:
        return QStringLiteral("Disconnected");
        break;
    case QNetworkSession::Roaming:
        return QStringLiteral("NotAvailable");
        break;
    default:
        break;
    };
    return "Invalid";
}

void MainWindow::printCaps(QNetworkConfigurationManager::Capabilities caps)
{
    if (caps.testFlag(QNetworkConfigurationManager::CanStartAndStopInterfaces))
            qWarning() << "CanStartAndStopInterfaces";
    if (caps.testFlag(QNetworkConfigurationManager::DirectConnectionRouting))
            qWarning() << "DirectConnectionRouting";
    if (caps.testFlag(QNetworkConfigurationManager::SystemSessionSupport))
            qWarning() << "SystemSessionSupport";
    if (caps.testFlag(QNetworkConfigurationManager::ApplicationLevelRoaming))
            qWarning() << "ApplicationLevelRoaming";
    if (caps.testFlag(QNetworkConfigurationManager::ForcedRoaming))
            qWarning() << "ForcedRoaming";
    if (caps.testFlag(QNetworkConfigurationManager::DataStatistics))
            qWarning() << "DataStatistics";
    if (caps.testFlag(QNetworkConfigurationManager::NetworkSessionRequired))
            qWarning() << "NetworkSessionRequired";
    if (caps.testFlag(QNetworkConfigurationManager::CanStartAndStopInterfaces))
            qWarning() << "CanStartAndStopInterfaces";
}

void MainWindow::finished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
        qWarning() << Q_FUNC_INFO;//<< reply->readAll();
    else
        qWarning() << Q_FUNC_INFO << reply->errorString();
}

void MainWindow::opened()
{
    qWarning() << Q_FUNC_INFO;
    QNetworkRequest request(QUrl("http://llornkcor.com"));

    accessMan->get(request);
}

void MainWindow::updateCompleted()
{
    qWarning() << "isOnline?" << configMan->isOnline();
    qWarning() << "network accessible" << accessMan->networkAccessible();

    printCaps(configMan->capabilities());

    QNetworkConfiguration configuration = accessMan->configuration();

    qWarning() << configuration.name() << configuration.state();
    qDebug() <<"activeConfiguration"<< accessMan->activeConfiguration().name();
    qDebug() <<"defaultConfiguration"<< configMan->defaultConfiguration().name();

    QNetworkSession *session = new QNetworkSession(configuration, this);

    qWarning() << stateToString(session->state());
    connect(session, &QNetworkSession::stateChanged, this, &MainWindow::stateChanged);

    if (configuration.state().testFlag(QNetworkConfiguration::Active)) {
        opened();
    } else {
        qWarning() << "opening";
     //   session->open();
    }
}
