#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioRecorder>
#include <QMultimedia>
#include <QAudioDeviceInfo>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    audioRecorder(nullptr),
    player(nullptr)
{
    ui->setupUi(this);
    listAudioDevices();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listAudioDevices()
{
    for (const QAudioDeviceInfo &deviceInfo :
         QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
        ui->textEdit->insertPlainText(
                    QString("Device name: %1\n")
                    .arg(deviceInfo.deviceName()));

        ui->textEdit->insertPlainText(
                    "    Supported Codecs: "
                    + deviceInfo.supportedCodecs()
                    .join(", ") + "\n");
        ui->textEdit->insertPlainText(
                    QString("    Supported channel count: %1\n")
                    .arg(stringifyIntList(deviceInfo.supportedChannelCounts())));
        ui->textEdit->insertPlainText(
                    QString("    Supported bit depth b/s: %1\n")
                    .arg(stringifyIntList(deviceInfo.supportedSampleSizes())));
        ui->textEdit->insertPlainText(
                    QString("    Supported sample rates Hz: %1\n")
                    .arg(stringifyIntList(deviceInfo.supportedSampleRates())));
    }
}

void MainWindow::on_playButton_clicked()
{
    if (audioRecorder == nullptr) {
        return;
    }
    qDebug() << Q_FUNC_INFO << audioRecorder->state();
    if (audioRecorder->state() == QMediaRecorder::PausedState) {
        audioRecorder->record();
    } else if (audioRecorder->state() == QMediaRecorder::StoppedState) {
        playFile();
    } else {
        audioRecorder->pause();
    }
}

void MainWindow::on_stopButton_clicked()
{
    qDebug() << Q_FUNC_INFO;
    ui->progressBar->setMaximum(100);
    audioRecorder->stop();
    ui->progressBar->setValue(0);
}

void MainWindow::on_recordButton_clicked()
{
    qDebug() << Q_FUNC_INFO;
    ui->progressBar->setMaximum(0);

    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/pcm");
    //       audioSettings.setChannelCount(2);
    //       audioSettings.setBitRate(16);
    //       audioSettings.setSampleRate(44100);
    audioSettings.setQuality(QMultimedia::NormalQuality);

    audioRecorder = new QAudioRecorder(this);
    connect(audioRecorder, &QMediaRecorder::durationChanged,
            this, &MainWindow::durationChanged);
    connect(audioRecorder, QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            [=](QMediaRecorder::Error error){
                                              ui->textEdit->insertPlainText("QAudioRecorder Error: "
                                                                            + audioRecorder->errorString());
                                             on_stopButton_clicked();
                                             });

    audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());
    audioRecorder->setEncodingSettings(audioSettings);

    QStringList inputs = audioRecorder->audioInputs();

    if (!audioRecorder->setOutputLocation(QUrl::fromLocalFile("record1.wav")))
        ui->textEdit->insertPlainText("Could not set output file location\n");
    else
        audioRecorder->record();
}

QString MainWindow::stringifyIntList(QList<int> list)
{
    QString string;
    for (int i = 0; i < list.count(); i++) {
        string += QString::number(list[i]);
        if (i < list.size() - 1)
            string += ", " ;
    }
    return string;
}

void MainWindow::durationChanged(qint64 duration)
{
    ui->progressBar->setMaximum(duration);
    ui->progressBar->setValue(duration);
    qDebug() << Q_FUNC_INFO << audioRecorder->outputLocation();
}

void MainWindow::playFile()
{
    if (player == nullptr) {
        player = new QMediaPlayer(this);
        connect(player, &QMediaPlayer::positionChanged,
                this, &MainWindow::positionChanged);
        connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
                [=](QMediaPlayer::Error error){
            ui->textEdit->insertPlainText("QMediaPlayer Error: " + player->errorString());
           on_stopButton_clicked();
        });
    }
    player->setMedia(audioRecorder->outputLocation());
    player->setVolume(50);
    ui->progressBar->setMaximum(player->duration());
    player->play();
}

void MainWindow::positionChanged(qint64 position)
{
    ui->progressBar->setValue(position);
}
