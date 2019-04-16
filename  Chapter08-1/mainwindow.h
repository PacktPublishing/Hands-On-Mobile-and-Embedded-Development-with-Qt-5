#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtPositioning/QGeoSatelliteInfoSource>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGeoSatelliteInfoSource *source;

private slots:
    void error(QGeoSatelliteInfoSource::Error);
    void satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &infos);
    void satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &infos);

};

#endif // MAINWINDOW_H
