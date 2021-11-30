#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QBrush brushGray(Qt::gray);
    QBrush brushDarkGray(Qt::darkGray);
    QPen penBlack(Qt::black);
    penBlack.setWidth(6);

    rectangle = scene->addRect(10, 10, 202, 272, penBlack, brushGray);
}

MainWindow::~MainWindow()
{
    delete ui;
}

