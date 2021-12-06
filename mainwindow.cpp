#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <string>
#include <sessionRecorder.h>
#include "menu.h"
using namespace std;
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // timer
    countdown = new QTimer(this);

     //1 second updates


    attached = false;
    powerOn = false;
    recorder = new sessionRecorder();
    curTime.setHMS(0, 0, 0, 0);

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
    connect(ui->recordButton, SIGNAL(released()), this, SLOT(recordClicked()));
    connect(ui->checkButton, SIGNAL(released()), this, SLOT(confirmClicked()));
    connect(ui->faultButton, SIGNAL(released()), this, SLOT(faultClicked()));
    connect(ui->batteryButton, SIGNAL(released()), this, SLOT(batClicked()));
    connect(countdown, SIGNAL(timeout()), this, SLOT(updateTimer()));
    connect(ui->attachButton, SIGNAL(released()), this, SLOT(attachClicked()));
    connect(ui->detachButton, SIGNAL(released()), this, SLOT(detachClicked()));

    menu = ui->mainList;
    menu->setVisible(false);

    waveMenu = new Menu("Wave Form Options", {"Alpha", "Beta", "Gamma"});
    frequencyMenu = new Menu("Frequency Options", {"0.5 Hz", "77 Hz", "100 Hz"});
    currentMenu = new Menu("Current Options", {"50", "100", "150", "200", "250", "300", "350", "400", "450", "500"});
    timerMenu = new Menu("Timer Options", {"20 minutes", "40 minutes", "60 minutes"});

}

void MainWindow::batClicked()
{
    QString batterylevel = QString::number(ui->progressBar->value());
    QString batteryText = "Battery: ";
    QString percent = "%";
    ui->batteryLabel->setText(batteryText + batterylevel + percent);
}

void MainWindow::recordClicked(){
    //cout<<"record It"<<endl;
    if(recording){
        recording = false;
    }
    else{
        recording = true;
    }
    //recorder->makeRecord(frequency, powerLevel, waveForm, Duration);
}

void MainWindow::confirmClicked(){

    if(menu->currentRow() < 0){ return; }

    cout<<"confirm It"<<endl;
    if(ui->page->text().toStdString() == "Wavelength"){
        waveform = menu->item(menu->currentRow())->text().toStdString();
        //cout<<waveform<<endl;
        ui->waveSpot->setText(menu->item(menu->currentRow())->text());
    }
    else if(ui->page->text().toStdString() == "Frequency"){
        frequency = menu->item(menu->currentRow())->text().toStdString();
        ui->freqSpot->setText(menu->item(menu->currentRow())->text());
    }
    else if(ui->page->text().toStdString() == "Current"){
        //EDIT CURRENT HERE
          current = menu->item(menu->currentRow())->text().toStdString();
          ui->currentSpot->setText(menu->item(menu->currentRow())->text());
    }
    else if(ui->page->text().toStdString() == "Timer"){
        timer = menu->item(menu->currentRow())->text().toStdString().substr(0,3);
        ui->timerSpot->setText(QString::fromStdString(timer));
        // string output of time
        QTime time;
        QString sixty = "60 ";
        if (ui->timerSpot->text() == sixty)
        {
            printf("60");
            time.setHMS(1, 0, 0, 0);
        }else
        {
            time.setHMS(0, ui->timerSpot->text().toInt(), 0, 0);
        }
        QString timeText = time.toString("hh : mm : ss");
        ui->date_time->setText(timeText);
        curTime = time;
    }

    //cout<<menu->item(menu->currentRow())->text().toStdString()<<"  "<<endl;
}

////This is a helper function to concatinate string. Enjoy!
//string MainWindow::concatStr(string start, string end){int
//    cout<<start<<cout<<
//}

MainWindow::~MainWindow()
{
    delete recorder;
    delete ui;
}


// timer
void MainWindow::updateTimer()
{
   qDebug() <<"Testing frequent update...";
   if(attached == false)
   {
       countdown->stop();
   }else if(current == (string)"701")
   {
       countdown->stop();
       powerClicked();
       ui->powerButton->setEnabled(false);
       QMessageBox::warning(
                   this,
                   tr("CES Machine"),
                   tr("Fault Detected! Shutting Down"));
   }
   curTime = curTime.addSecs(-1);
   QString timeStr = curTime.toString("hh : mm : ss");
   ui->date_time->setText(timeStr);

}



void MainWindow::powerClicked()
{
    QBrush brushWhite(Qt::white);
    QBrush brushBlack(Qt::black);
    QPen penBlack(Qt::black);
    penBlack.setWidth(1);

    if(powerOn == false)
    {
        ui->powerOffView->setVisible(false);
        menu->setVisible(true);
        powerOn = true;
        return;
    }
    if(powerOn == true)
    {
        ui->powerOffView->setVisible(true);
        menu->clear();
        menu->setVisible(false);
        powerOn = false;
        return;int nextIndex = menu->currentRow() + 1;

        if (nextIndex > menu->count() - 1) {
            nextIndex = 0;
        }
        menu->setCurrentRow(nextIndex);
    }

}
void MainWindow::waveLengthClicked()
{
    if(menu != NULL)
    {
        menu->clear();
    }
    ui->page->setText("Wavelength");
    menu = ui->mainList;
    menu->addItems(waveMenu->getListItems());

}



void MainWindow::frequencyClicked()
{
    if(menu != NULL)
    {
        menu->clear();
    }
    ui->page->setText("Frequency");
    menu = ui->mainList;
    menu->addItems(frequencyMenu->getListItems());
}

void MainWindow::currentClicked()
{
    if(menu != NULL)
    {
        menu->clear();
    }
    ui->page->setText("Current");
    menu = ui->mainList;
    menu->addItems(currentMenu->getListItems());
}



void MainWindow::timerClicked()
{
    if(menu != NULL)
    {
        menu->clear();
    }
    menu = ui->mainList;
    ui->page->setText("Timer");
    menu->addItems(timerMenu->getListItems());
}

void MainWindow::incClicked()
{
    int nextIndex = menu->currentRow() - 1;

    if (nextIndex < 0) {
        nextIndex = menu->count() - 1;
    }

    menu->setCurrentRow(nextIndex);
}

void MainWindow::decClicked()
{
    int nextIndex = menu->currentRow() + 1;

    if (nextIndex > menu->count() - 1) {
        nextIndex = 0;
    }

    menu->setCurrentRow(nextIndex);
}

void MainWindow::startClicked()
{
    sessionStartTime = QDateTime::currentDateTime();
    int startSec = QDateTime::currentSecsSinceEpoch();

//    cout<<sessionStartTime.toString().toStdString()<<endl;
    if (attached == true)
    {
        countdown->start(1000);

        //during treatment, check every second to see if electrodes connected, if they ever become disconnected stop timer
        //during treatment, decrement timer every second, also check current for faults every second, also also check battery level
        //if battery level hits 5% give a warning, if it hits 2% give warning and power off
    }
    //string fq, int curr, int dur, string date, string wave


    int endSec = QDateTime::currentSecsSinceEpoch();
    int duration = endSec - startSec;

    if(recording){
        recorder->makeRecord(frequency, current, duration, sessionStartTime.toString().toStdString(), waveform);
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

void MainWindow::faultClicked()
{
    string fault = (string)"701";
    QString fault1 = "701";
    current = fault;
    ui->currentSpot->setText(fault1);
}
