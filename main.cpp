#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "bullscows.h"
#include "mypushbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    BullsCows game(&w);
    QPushButton button("Угадать", &w);
    MyPushButton button2(&w);
    button.setGeometry(80, 30, 70, 30);
    button2.setGeometry(160, 30, 70, 30);
    QLabel label("Угадайте число!\nКорова - есть совпадающие цифры\nБык - есть цифры на своих местах", &w);
    QLabel errLabel(&w);
    QLineEdit line(&w);
    QPushButton table(&w);
    table.setGeometry(80, 70, 70, 30);
    table.setText("Таблица результатов");
    w.setGeometry(500, 500, 330, 590);
    line.setGeometry(10, 30, 60, 30);
    label.setGeometry(10, 100, 600, 500);
    errLabel.setGeometry(10, 70, 200, 30);
    errLabel.setWordWrap(true);
    QObject::connect(&button, SIGNAL(clicked()), &game, SLOT(getResult()));
    QObject::connect(&line, SIGNAL(textChanged(QString)), &game, SLOT(updNum(QString)));
    QObject::connect(&game, SIGNAL(output(QString)), &label, SLOT(setText(QString)));
    QObject::connect(&game, SIGNAL(error(QString)), &errLabel, SLOT(setText(QString)));
    QObject::connect(&button2, SIGNAL(clicked()), &game, SLOT(reset()));
    QObject::connect(&game, SIGNAL(changeButText(QString)), &button2, SLOT(setButText(QString)));
    QObject::connect(&table, SIGNAL(clicked()), &game, SLOT(showTable()));
    w.show();
    return a.exec();
}
