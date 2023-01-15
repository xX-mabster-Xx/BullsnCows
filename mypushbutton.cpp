#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent)
    :QPushButton(parent)
{
    setText("Новая игра");
}

void MyPushButton::setButText(QString s)
{
    setText(s);
}
