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
 * For UI Purposes: All of the below are used for visual purposes witht he QGraphics
 *      MainWindow *ui
        QGraphicsScene *scene
        QGraphicsScene *scene2
        QGraphicsScene *scene3
        QGraphicsEllipseItem * ellipse
        QGraphicsRectItem *rectangle
        QGraphicsRectItem *rectangle2
        QGraphicsRectItem *rectangle3
        QListWidget *menu
 *
 * Menu: 4 menu instances used for user to select therapy settings
        Menu *waveMenu
        Menu *frequencyMenu
        Menu *currentMenu
        Menu *timerMenu

 * Boolean Variables: Mainly used to check if user has already selected a button
 *      bool powerOn
 *      bool attached
        bool recording

 * String Variables: Used to store users selections
 *      string waveform
        string current
        string powerlevel
        string frequency
        string timer

* Battery Data Members: To Track, Set and Display Battery Levels
       int battCount
       QString batlvl

* Record Data Members: Stores values needed for 'records.txt'
        sessionRecorder *recorder
        QDateTime sessionStartTime

*Timer Variables: Stores selected timer value and QTime value
        QTimer *countdown
        int curTimer
        QTime curTime

 *
 *
 * Class Functions:
 *  void powerClicked() -> Turns Device on and off
    Menu Options:
       void waveLengthClicked(); void frequencyClicked(); void currentClicked(); void timerClicked(); void incClicked(); void decClicked(); void confirmClicked();

    Session Functionalities:
       void startClicked(); void attachClicked(); void detachClicked(); void recordClicked();

    Testing Functionalities:
        void faultClicked(); void batClicked(); inactivityTimer()
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
    bool recording = false;
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
    QTimer *inacTimer;


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
    void inactivityTimer();


};
#endif // MAINWINDOW_H
