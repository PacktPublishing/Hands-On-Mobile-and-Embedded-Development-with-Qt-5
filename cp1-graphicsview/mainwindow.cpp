#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsSimpleTextItem>

#include "textgraphic.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(gScene);

    gScene->setSceneRect(-50, -50, 120, 120);

    QPen pen = QPen(Qt::red);
    gScene->addRect(gScene->sceneRect(), pen);

    TextGraphic *text = new TextGraphic(QStringLiteral("Qt Mobile!"));
    gScene->addItem(text);
    text->setFlag(QGraphicsItem::ItemIsMovable);
}

MainWindow::~MainWindow()
{
    delete ui;
}
