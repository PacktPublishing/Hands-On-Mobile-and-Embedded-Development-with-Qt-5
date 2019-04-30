#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaResource>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QFile>
#include <QAudioFormat>
#include <QAudioOutput>

#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mediaPlayer = new QMediaPlayer(this);
    const QString dir;
    const QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open WAV file"), dir, "*.wav");
    if (fileNames.count()) {
        loadFile(fileNames.front());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(const QString &file)
{
    connect(mediaPlayer, SIGNAL(metaDataChanged(QString,QVariant)),
            this, SLOT(metaDataChanged(QString,QVariant)));

     mediaPlayer->setMedia(QUrl::fromLocalFile(file));

     QObject::connect(mediaPlayer, &QMediaPlayer::metaDataAvailableChanged, [&](bool available){
         if (available) {
             qDebug() << "AudioCodec" << mediaPlayer->metaData("AudioCodec").toString();
             qDebug() << "AudioBitRate" <<  mediaPlayer->metaData("AudioBitRate").toInt();
             qDebug() << "ChannelCount" <<  mediaPlayer->metaData("ChannelCount").toInt();
             qDebug() << "SampleRate" <<  mediaPlayer->metaData("SampleRate").toInt();
             qDebug() << "Resolution" <<  mediaPlayer->metaData("Resolution").toSize();
             qDebug() << "container-format" <<  mediaPlayer->metaData("container-format").toSize();

             }
         });

    QFile *sourceFile = new QFile();
    sourceFile->setFileName(file);
    sourceFile->open(QIODevice::ReadOnly);

    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    QAudioOutput *audio;

    QAudioDeviceInfo deviceInfo = QAudioDeviceInfo::defaultOutputDevice();

    if (!deviceInfo.isFormatSupported(format)) {
        format = deviceInfo.nearestFormat(format);
        qWarning() << "Audio format not supported by backend, cannot play audio.";
    }
    audio = new QAudioOutput(deviceInfo, format, this);
    connect(audio, &QAudioOutput::stateChanged, [=] (QAudio::State state) {
        qDebug() << Q_FUNC_INFO << "state" << state;
        ui->textEdit->insertPlainText(stateToString(state) + "\n");
        if (state == QAudio::StoppedState) {
            if (audio->error() != QAudio::NoError) {
                qDebug() << Q_FUNC_INFO << audio->error();
            }
        }
    });
    audio->setVolume(.50);
    audio->start(sourceFile);
}

void MainWindow::metaDataChanged(QString key, QVariant data)
{
    qDebug() << "metadata changed: " + key +" "+ data.toString();
    ui->textEdit->insertPlainText(key +" "+data.toString() +"\n");
}

QString MainWindow::stateToString(QAudio::State state)
{
    QString stateString;
    switch (state) {
    case QAudio::SuspendedState:
        stateString = "QAudio::SuspendedState";
        break;
    case QAudio::ActiveState:
        stateString = "QAudio::ActiveState";
        break;
    case QAudio::StoppedState:
        stateString = "QAudio::StoppedState";
        break;
    case QAudio::IdleState:
        stateString = "QAudio::IdleState";
        break;
    case QAudio::InterruptedState:
        stateString = "QAudio::InterruptedState";
        break;
    };
    return stateString;
}

