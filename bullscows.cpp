#include "bullscows.h"

BullsCows::BullsCows(QObject *parent) : QObject(parent), times(0)
{
    std::ifstream fin("save");
    int r;
    std::string name;
    while(fin >> r >> name)
        reses.insert({r, name});
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
    if (s.size() != 4){
        ok = false;
        return;
    }

    int val_int;
    val_int = s.toInt(&ok);
    if (ok)
         num_in_line = val_int;
}

void BullsCows::reset() {
    if (!in_game) {
        newNum();
        in_game = true;
        emit output("Число сгенерировано");
        emit changeButText("Сдаться");
        return;
    }
    QString out = "Число: " + QString::number(m_num) + ", Потрачено ходов : " + QString::number(times);
    text = "";
    in_game = false;
    emit output(text + out);
    emit changeButText("Новая игра");
}

QString ResultOut(int bulls, int cows) {
    QString res = QString::number(bulls);
    if (bulls == 0)
        res += " быков ";
    else if (bulls == 1)
        res += " бык   ";
    else
        res += " быка  ";
    res += QString::number(cows);
    if (cows == 0)
        res += " коров ";
    else if (cows == 1)
        res += " корова";
    else
        res += " коровы";
    return res;

}
void BullsCows::save() {
    std::ofstream fout("save");
    for (const auto & x: reses) {
        fout << x.first << " " << x.second << "\n";
    }
    fout.close();
}

void BullsCows::showRes() {
    QMessageBox msg;
    QString str;
    int ii = 1;
    for (const auto & x : reses) {
        str = str + QString::number(ii) + ": " + QString::fromStdString(x.second) + " - " + QString::number(x.first) + "\n";
        ++ii;
    }
    msg.setText(str);
    msg.exec();
}

void BullsCows::getResult() {
    if (!in_game) {
        return;
    }
    ++times;
    emit changeButText("Сдаться");
    if (!check(num_in_line) || !ok){
        --times;
        emit error("Введите четырехзначное число\nс различными цифрами");
        return;
    }
    if (num_in_line == pr_num)
        --times;
    pr_num = num_in_line;
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
        text += QString::number(num_in_line) + "\nВы угадали!! Ходов:" + QString::number(times) + "\n";
        reses.insert({times, QInputDialog::getText(nullptr,tr("Ваше имя"), tr("Ваше имя:"), QLineEdit::Normal).toStdString()});
        if (reses.size() > 5)
            reses.erase(--reses.end());
        save();
        showRes();
        emit output(text);
        emit error("");
        emit changeButText("Новая игра");
        times = 0;
        pr_num = 0;
        text = "";
        in_game = false;
    }
    else {
        if (sizes.size() > 15) {
            text = text.right(text.size() - sizes.front());
            sizes.pop();
        }
        QString add = QString::number(times)+ ". " + QString::number(num_in_line) + " - " + ResultOut(bulls, cows) + "\n";
        sizes.push(add.size());
        text += add;
        emit output(text);
        emit error("");
    }
}
void BullsCows::showTable() {
    showRes();
}
