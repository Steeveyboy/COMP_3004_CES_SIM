#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QStringList>


class Menu
{
public:
    Menu(QString, QStringList);
    ~Menu();

    QString getName();
    QStringList getListItems();
    int getPos();
    Menu* get(int);

private:
    QString name;
    QStringList listItems;
    int position;

};

#endif // MENU_H
