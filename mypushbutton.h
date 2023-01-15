#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public slots:
    void setButText(QString);

public:
    MyPushButton(QWidget *parent = nullptr);
};

#endif // MYPUSHBUTTON_H
