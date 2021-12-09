#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QStringList>
/* Class Purpose: Offers options to user to select for each setting of the therapy session
 *
 * Data Members:
 *  QString name;
    QStringList listItems;
    int position
 *
 * Class Functions:
 * Getters for list names, list items, list position, menu itself
 */

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
