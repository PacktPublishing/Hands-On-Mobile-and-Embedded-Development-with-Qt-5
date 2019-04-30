#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioRecorder>
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
    void listAudioDevices();

private slots:

    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_recordButton_clicked();

    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

private:
    Ui::MainWindow *ui;
    QString stringifyIntList(QList<int>);
    QAudioRecorder *audioRecorder;
    QMediaPlayer *player;
    void playFile();
};

#endif // MAINWINDOW_H
