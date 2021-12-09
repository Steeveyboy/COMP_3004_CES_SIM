#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <string>
#include <sessionRecorder.h>
#include "menu.h"
#include <stdio.h>
#include <unistd.h>
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
    inacTimer = new QTimer(this);

     //1 second updates

    battCount = 0;
    attached = false;
    powerOn = false;
    recorder = new sessionRecorder();
    curTime.setHMS(0, 0, 0, 0);
    batlvl = "100";
    recording = false;


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
    connect(inacTimer, SIGNAL(timeout()), this, SLOT(inactivityTimer()));

    menu = ui->mainList;
    menu->setVisible(false);
    ui->page->setVisible(false);
    ui->waveLabel->setVisible(false);
    ui->waveSpot->setVisible(false);
    ui->freqLabel->setVisible(false);
    ui->freqSpot->setVisible(false);
    ui->currentLabel->setVisible(false);
    ui->currentSpot->setVisible(false);
    ui->timerLabel->setVisible(false);
    ui->timerSpot->setVisible(false);
    ui->lowBatteryLabel->setVisible(false);
    ui->timerView->setVisible(false);
    ui->date_time->setVisible(false);
    ui->attIco->setVisible(true);

    waveMenu = new Menu("Wave Form Options", {"Alpha", "Beta", "Gamma"});
    frequencyMenu = new Menu("Frequency Options", {"0.5-Hz", "77-Hz", "100-Hz"});
    currentMenu = new Menu("Current Options", {"50", "100", "150", "200", "250", "300", "350", "400", "450", "500"});
    timerMenu = new Menu("Timer Options", {"20 minutes", "40 minutes", "60 minutes"});


}

void MainWindow::batClicked()
{
    QString batterylevel = QString::number(ui->progressBar->value());
    batlvl = batterylevel;
    QString batteryText = "Battery: ";
    QString percent = "%";
    ui->batteryLabel->setText(batteryText + batterylevel + percent);
    if(batterylevel == '5')
    {
        ui->lowBatteryLabel->setVisible(true);
        cout<<"BATERY AT: "<<endl;
        //QTimer::singleShot(5000, ui->lowBatteryLabel, &QLabel::hide);
        //sleep(5);
        //ui->lowBatteryLabel->setVisible(false);
    }
    else if(batterylevel == '2')
    {
        ui->lowBatteryLabel->setVisible(true);
        powerClicked();

    }
    else
    {
        ui->lowBatteryLabel->setVisible(false);
    }


}

void MainWindow::recordClicked(){
    //cout<<"record It"<<endl;
    if(recording){
        recording = false;
        ui->recordLabel->setText("Recording: Off");
    }
    else{
        recording = true;
        ui->recordLabel->setText("Recording: On");
    }
    //recorder->makeRecord(frequency, powerLevel, waveForm, Duration);
}

void MainWindow::confirmClicked(){

    if(menu->currentRow() < 0){ return; }

    //cout<<"confirm It"<<endl;
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
       ui->date_time->lower();
       ui->timerView->lower();


       /*For testing purposes, the proper length of time for the inactivity timer has been commented out
        * and replaced with a 5 minute interval. The 1800000 line is the actual interval if the inactivity
        * timer was being called for 30 minutes of inactivity
        */
       //inacTimer->start(1800000);
       inacTimer->start(300000);

   }else if(current == (string)"701")
   {
       countdown->stop();
       recordSession();
       powerClicked();
       ui->powerButton->setEnabled(false);
       QMessageBox::warning(
                   this,
                   tr("CES Machine"),
                   tr("Fault Detected! Shutting Down"));
       ui->date_time->lower();
       ui->timerView->lower();

   }
   if(batlvl == '5')
   {
       cout<<"Warning: BATTERY LOW 5%"<<endl;
       ui->lowBatteryLabel->setVisible(true);
       ui->lowBatteryLabel->raise();


   }
   if(batlvl == '2')
   {
       cout<<"Warning: Battery at 2%"<<endl;
       ui->lowBatteryLabel->setVisible(true);
       QTimer::singleShot(5000, ui->lowBatteryLabel, &QLabel::hide);
       countdown->stop();
       ui->date_time->lower();
       ui->timerView->lower();
       powerClicked();
       recordSession();
   }

   if(battCount < 9)
   {
       battCount++;
   }else
   {
       battCount = 0;
       int batterylevel = batlvl.toInt();
       batterylevel--;
       batlvl = QString::number(batterylevel);
       QString batteryText = "Battery: ";
       QString percent = "%";
       ui->batteryLabel->setText(batteryText + batlvl + percent);
   }

   curTime = curTime.addSecs(-1);
   QString timeStr = curTime.toString("hh : mm : ss");
   ui->date_time->setText(timeStr);

   if(curTime.minute() == 0)
   {
       countdown->stop();
       recordSession();
       //record if recording

       /*For testing purposes, the proper length of time for the inactivity timer has been commented out
        * and replaced with a 5 minute interval. The 1800000 line is the actual interval if the inactivity
        * timer was being called for 30 minutes of inactivity
        */
       //inacTimer->start(1800000);
       inacTimer->start(300000);

       ui->date_time->lower();
       ui->timerView->lower();

       curTimer = 0;
       recording = false;
       curTime.setHMS(0, 0, 0, 0);
       waveform = (string)"";
       ui->waveSpot->setText("");
       current = (string)"";
       ui->currentSpot->setText("");
       powerlevel = (string)"";
       frequency = (string)"";
       ui->freqSpot->setText("");
       timer = (string)"";
       ui->timerSpot->setText("");
       battCount = 0;
   }

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
        ui->page->setVisible(true);
        ui->waveLabel->setVisible(true);
        ui->waveSpot->setVisible(true);
        ui->freqLabel->setVisible(true);
        ui->freqSpot->setVisible(true);
        ui->attIco->setVisible(true);
        ui->currentLabel->setVisible(true);
        ui->currentSpot->setVisible(true);
        ui->timerLabel->setVisible(true);
        ui->timerSpot->setVisible(true);
        ui->timerView->setVisible(true);
        ui->date_time->setVisible(true);
        menu->setVisible(true);
        powerOn = true;
        return;
    }
    if(powerOn == true)
    {
        ui->powerOffView->setVisible(true);
        ui->page->setVisible(false);
        ui->waveLabel->setVisible(false);
        ui->waveSpot->setVisible(false);
        ui->freqLabel->setVisible(false);
        ui->freqSpot->setVisible(false);
        ui->attIco->setVisible(true);
        ui->currentLabel->setVisible(false);
        ui->currentSpot->setVisible(false);
        ui->timerLabel->setVisible(false);
        ui->timerSpot->setVisible(false);
        ui->timerView->setVisible(false);
        ui->date_time->setVisible(false);
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
    startSecond = QDateTime::currentSecsSinceEpoch();

    if (attached == true)
    {
        ui->timerView->raise();
        ui->date_time->raise();
        countdown->start(1000);
        inacTimer->stop();
    }

}

void MainWindow::recordSession(){

    QString format = "dddd/MM/dd-HH:mm:ss";
    int endSec = QDateTime::currentSecsSinceEpoch();
    int duration = endSec - startSecond;

    if(recording){
        //cout<<sessionStartTime.toString(format).toStdString()<<"    "<<current<<"   "<<waveform<<"  "<<frequency<<endl;
        recorder->makeRecord(frequency, current, duration, sessionStartTime.toString(format).toStdString(), waveform);
    }
}

void MainWindow::attachClicked()
{
    attached = true;
    ui->attachButton->setEnabled(false);
    ui->detachButton->setEnabled(true);
    ui->attIco->raise();
}

void MainWindow::detachClicked()
{
    attached = false;
    ui->attachButton->setEnabled(true);
    ui->detachButton->setEnabled(false);
    ui->attIco->lower();
}

void MainWindow::faultClicked()
{
    string fault = (string)"701";
    QString fault1 = "701";
    current = fault;
    ui->currentSpot->setText(fault1);
}

void MainWindow::inactivityTimer()
{
    countdown->stop();
    recordSession();
    ui->date_time->lower();
    ui->timerView->lower();
    curTimer = 0;
    recording = false;
    curTime.setHMS(0, 0, 0, 0);
    waveform = (string)"";
    ui->waveSpot->setText("");
    current = (string)"";
    ui->currentSpot->setText("");
    powerlevel = (string)"";
    frequency = (string)"";
    ui->freqSpot->setText("");
    timer = (string)"";
    ui->timerSpot->setText("");
    battCount = 0;
    powerClicked();
}
