#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QMediaPlayer>


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
    void loadFile(const QString &file);
        QMediaPlayer *mediaPlayer;
        QString stateToString(QAudio::State state);
private slots:
    void metaDataChanged(QString key, QVariant data);
};

#endif // MAINWINDOW_H
