#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QWidget>
#include <QDate>
class Data
{
public:
    //type 0 box 1 text, 2 textarea, 3 image, 4 date, 5 dropdown, 6 period
    Data(QString type="", QString name="" ,int valueLine=1, QString value="", QString date="",QString path="", QString stdate="",QString eddate="");
    ~Data();
    QString type;
    QString name;
    int valueLine;
    QString value;
    QString date;
    QString stdate;
    QString eddate;
    QString path;
};

#endif // DATA_H
