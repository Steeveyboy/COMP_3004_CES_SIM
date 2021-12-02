#include "menu.h"


Menu::Menu(QString n, QStringList list) {

    name = n;
    listItems = list;
}

Menu::~Menu()
{
    //delete menu;
}

QStringList Menu::getListItems(){
    return listItems;
}

QString Menu::getName()
{
    return name;
}

int Menu::getPos()
{
    return position;
}
