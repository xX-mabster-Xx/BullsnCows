#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "bullscows.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    BullsCows game(&w);
    QPushButton button("ОК", &w);
    button.setGeometry(80, 30, 30, 30);
    QLabel label("Угадайте число!\nКорова - есть совпадающие цифры\nБык - есть цифры на своих местах", &w);
    QLabel errLabel(&w);
    QLineEdit line(&w);
    w.setGeometry(500, 500, 330, 590);
    line.setGeometry(10, 30, 60, 30);
    label.setGeometry(10, 70, 600, 500);
    errLabel.setGeometry(120, 30, 200, 30);
    errLabel.setWordWrap(true);
    QObject::connect(&button, SIGNAL(clicked()), &game, SLOT(getResult()));
    QObject::connect(&line, SIGNAL(textChanged(QString)), &game, SLOT(updNum(QString)));
    QObject::connect(&game, SIGNAL(output(QString)), &label, SLOT(setText(QString)));
    QObject::connect(&game, SIGNAL(error(QString)), &errLabel, SLOT(setText(QString)));

    w.show();
    return a.exec();
}
