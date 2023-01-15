#include "bullscows.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
BullsCows::BullsCows(QObject *parent) : QObject(parent)
{
    newNum();
}

void BullsCows::newNum(){
    srand(time(0));
    int a = 0, b = 0, c = 0, d = 0;
    a = rand() % 9 + 1;
    b = rand() % 9;
    if (b >= a)
        ++b;
    c = rand() % 8;
    if (c >= std::min(a, b))
        ++c;
    if (c >= std::max(a, b))
        ++c;
    d = rand() % 7;
    if (d >= std::min(std::min(a, b), c))
        ++d;
    if (d >= a + b + c - std::min(std::min(a, b), c) - std::max(std::max(a, b), c))
        ++d;
    if (d >= std::max(std::max(a, b), c))
        ++d;
    m_num = a * 1000 + b * 100 + c * 10 + d;
    std::cout << m_num << std::endl;
}

bool check(int n) {
    if (n < 1000)
        return false;
    if (n > 9999)
        return false;
    std::set <int> s;
    s.insert((n)%10);
    s.insert((n/10)%10);
    s.insert((n/100)%10);
    s.insert((n/1000)%10);
    if (s.size() < 4)
        return false;
    return true;
}

void BullsCows::updNum(QString s) {
    int val_int;
    val_int = s.toInt(&ok);
    if (ok)
         num_in_line = val_int;
}
void BullsCows::getResult() {
    if (!ok) {
        emit error("НЕ ЧИСЛО");
        return;
    }
    if (!check(num_in_line)){
        emit error("Введите четырехзначное число\nс различными цифрами");
        return;
    }
    int bulls = 0;
    int cows = 0;
    if ((num_in_line / 1000) == (m_num / 1000))
        ++bulls;
    if ((num_in_line / 100) % 10 == (m_num / 100) % 10)
        ++bulls;
    if ((num_in_line / 10) % 10 == (m_num / 10) % 10)
        ++bulls;
    if (num_in_line % 10 == m_num % 10)
        ++bulls;
    std::set <int> used;
    used.insert((num_in_line / 1000));
    used.insert((num_in_line / 100) % 10);
    used.insert((num_in_line / 10) % 10);
    used.insert(num_in_line % 10);
    used.insert((m_num / 1000));
    used.insert((m_num / 100) % 10);
    used.insert((m_num / 10) % 10);
    used.insert(m_num % 10);
    cows = 8 - used.size() - bulls;
    if (bulls == 4) {
        text += QString::number(num_in_line) + "\nВы угадали!!\n";
        emit output(text);
        text = "";
        newNum();
    }
    else {
        if (text.size() > 34 * 13) {
            text = QString::fromStdString(text.toStdString().substr(44, 1000));
        }
        text += QString::number(num_in_line) + " Быков - " + QString::number(bulls) + "\n         Коров - " + QString::number(cows) + "\n";
        emit output(text);
    }
}
