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
#include <string>

#include <QTimer>

//Include statements for other header files go here
#include "menu.h"

/* Class purpose: The mainwindow is the main control class for the whole program
 *
 * Data Members:
 *-int curTimer: the current timer for the treatment
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
   void slotFunction();


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

    sessionRecorder *recorder;

    string waveform;
    int current = 50;
//    string duration;
    string powerlevel;
    string frequency;
    string timer;
    QDateTime sessionStartTime;

    QTimer *timer;


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


};
#endif // MAINWINDOW_H
