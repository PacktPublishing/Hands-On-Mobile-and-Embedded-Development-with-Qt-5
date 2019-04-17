#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

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
    QString attributeToString(QGeoPositionInfo::Attribute);
    QString methodsToString(QGeoPositionInfoSource::PositioningMethods);
private slots:
    void positionUpdated(const QGeoPositionInfo &update);
};

#endif // MAINWINDOW_H
