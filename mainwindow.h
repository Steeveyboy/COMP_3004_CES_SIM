#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QListWidget>
#include <QtCore>
#include <QtGui>
#include <QSpinBox>
#include <QListWidget>
#include <QGraphicsView>
#include <QTime>
#include <QStatusBar>
#include <QVector>
#include <QtGlobal>

//Include statements for other header files go here


/* Class purpose: The mainwindow is the main control class for the whole program
 *
 * Data Members:
 *
 *
 * Class Functions:
 *
 *
 */

#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    QListWidget *menu;
    bool powerOn;


private slots:
    void powerClicked();
    void waveLengthClicked();
    void frequencyClicked();
    void currentClicked();


};
#endif // MAINWINDOW_H
