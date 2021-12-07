#ifndef MAINWINDOW_H
#define MAINWINDOW_H
using namespace std;
#include <QMainWindow>
#include <QGraphicsScene>
#include <QListWidget>
#include <QtCore>
#include <QtGui>
#include <QSpinBox>
#include <QGraphicsView>
#include <QTime>
#include <QStatusBar>
#include <QVector>
#include <QtGlobal>
#include <sessionRecorder.h>
#include <QTimer>
#include <string>

//Include statements for other header files go here
#include "menu.h"

/* Class purpose: The mainwindow is the main control class for the whole program
 *
 * Data Members:
 *
 *
 * Class Functions:
 *
 *
 */


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
   void updateTimer();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsEllipseItem * ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsRectItem *rectangle2;
    QGraphicsRectItem *rectangle3;
    Menu *waveMenu;
    Menu *frequencyMenu;
    Menu *currentMenu;
    Menu *timerMenu;
    QListWidget *menu;
    bool powerOn;
    int curTimer;
    bool attached;
    bool recording;
    QTime curTime;
    int battCount;

    sessionRecorder *recorder;

    string waveform;
    string current;
//    string duration;
    string powerlevel;
    string frequency;
    string timer;
    QDateTime sessionStartTime;
    QString batlvl;
    QTimer *countdown;


private slots:
    void powerClicked();
    void waveLengthClicked();
    void frequencyClicked();
    void currentClicked();
    void timerClicked();
    void incClicked();
    void decClicked();
    void startClicked();
    void attachClicked();
    void detachClicked();
    void recordClicked();
    void confirmClicked();
    void faultClicked();
    void batClicked();


};
#endif // MAINWINDOW_H
