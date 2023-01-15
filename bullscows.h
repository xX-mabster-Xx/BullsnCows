#ifndef BULLSCOWS_H
#define BULLSCOWS_H

#include <QObject>

class BullsCows : public QObject
{
    Q_OBJECT
    int m_num;
    int num_in_line;
    bool ok;
    QString text;
public:
    explicit BullsCows(QObject *parent = nullptr);
    void newNum();

public slots:
    void updNum(QString);
    void getResult();
signals:
    void output(QString);
    void error(QString);
};

#endif // BULLSCOWS_H
