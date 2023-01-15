#ifndef BULLSCOWS_H
#define BULLSCOWS_H

#include <QObject>
#include <queue>
#include <map>
#include <string>
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>

class BullsCows : public QObject
{
    Q_OBJECT
    int m_num;
    int num_in_line;
    int times;
    int pr_num = 0;
    bool ok;
    bool in_game = false;
    std::queue <int> sizes;
    std::multimap <int, std::string> reses;
    QString text;
    void showRes();
public:
    explicit BullsCows(QObject *parent = nullptr);
    void newNum();
    void save();

public slots:
    void updNum(QString);
    void getResult();
    void reset();
    void showTable();
signals:
    void output(QString);
    void error(QString);
    void changeButText(QString);
};

#endif // BULLSCOWS_H
