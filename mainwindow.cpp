#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <string>
using namespace std;
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curTimer = -1;
    attached = false;

    powerOn = false;

    scene = new QGraphicsScene(this);
    ui->deviceWholeView->setScene(scene);
    QBrush brushGray(Qt::gray);
    QBrush brushDarkGray(Qt::darkGray);
    QBrush brushBlack(Qt::black);
    QPen penBlack(Qt::black);
    penBlack.setWidth(6);
    rectangle = scene->addRect(10, 10, 202, 342, penBlack, brushGray);//wholedevice screen

    scene2 = new QGraphicsScene(this);
    ui->powerOffView->setScene(scene2);
    rectangle2 = scene2->addRect(10,10, 183, 140, penBlack, brushBlack);//device screen

    scene3 = new QGraphicsScene(this);
    ui->userView->setScene(scene3);
    rectangle3 = scene3->addRect(10, 10, 232, 180, penBlack, brushGray);//wholedevice screen


    connect(ui->powerButton, SIGNAL(released()), this, SLOT(powerClicked()));
    connect(ui->waveFormButton, SIGNAL(released()), this, SLOT(waveLengthClicked()));
    connect(ui->frequencyButton, SIGNAL(released()), this, SLOT(frequencyClicked()));
    connect(ui->currentButton, SIGNAL(released()), this, SLOT(currentClicked()));
    connect(ui->timerButton, SIGNAL(released()), this, SLOT(timerClicked()));
    connect(ui->increaseButton, SIGNAL(released()), this, SLOT(incClicked()));
    connect(ui->decreaseButton, SIGNAL(released()), this, SLOT(decClicked()));
    connect(ui->startButton, SIGNAL(released()), this, SLOT(startClicked()));

    menu = ui->mainList;

    waveMenu = new Menu("Wave Form Options", {"Alpha", "Betta", "Gamma"});
    frequencyMenu = new Menu("Frequency Options", {"0.5 Hz", "77 Hz", "100 Hz"});
    currentMenu = new Menu("Current Options", {"Current Options"});
    timerMenu = new Menu("Timer Options", {"20 Minutes", "40 Minutes", "60 Minutes"});

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::powerClicked()
{
    QBrush brushWhite(Qt::white);
    QBrush brushBlack(Qt::black);
    QPen penBlack(Qt::black);
    penBlack.setWidth(1);

    if(powerOn == false)
    {
        cout<<"Entered 1st 4 loop"<<endl;
        rectangle2 = scene2->addRect(10,10, 183, 140, penBlack, brushWhite);
        powerOn = true;
        return;
    }
    if(powerOn == true)
    {
        rectangle2 = scene2->addRect(10,10, 183, 140, penBlack, brushBlack);
        powerOn = false;
        return;int nextIndex = activeQListWidget->currentRow() + 1;

        if (nextIndex > activeQListWidget->count() - 1) {
            nextIndex = 0;
        }

        activeQListWidget->setCurrentRow(nextIndex);
    }


}
void MainWindow::waveLengthClicked()
{
    menu = ui->mainList;
    menu->addItems(waveMenu->getListItems());
}

void MainWindow::frequencyClicked()
{
    menu = ui->mainList;
    menu->addItems(frequencyMenu->getListItems());
}

void MainWindow::currentClicked()
{
    menu = ui->mainList;
    menu->addItems(currentMenu->getListItems());
}

void MainWindow::timerClicked()
{
    menu = ui->mainList;
    menu->addItems(currentMenu->getListItems());
}

void MainWindow::incClicked()
{
    int nextIndex = activeQListWidget->currentRow() - 1;

    if (nextIndex < 0) {
        nextIndex = activeQListWidget->count() - 1;
    }

    activeQListWidget->setCurrentRow(nextIndex);
}

void MainWindow::decClicked()
{
    int nextIndex = activeQListWidget->currentRow() + 1;

    if (nextIndex > activeQListWidget->count() - 1) {
        nextIndex = 0;
    }

    activeQListWidget->setCurrentRow(nextIndex);
}

void MainWindow::startClicked()
{
    if (attached)
    {
        //during treatment, check every second to see if electrodes connected, if they ever become disconnected stop timer
        //during treatment, decrement timer every second, also check current for faults every second, also also check battery level
        //if battery level hits 5% give a warning, if it hits 2% give warning and power off
    }
}

void MainWindow::attachClicked()
{
    attached = true;
}

void MainWindow::detachClicked()
{
    attached = false;
}
