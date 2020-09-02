#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QWidget>
#include <QDate>
class Data
{
public:
    //type 0 box 1 text, 2 textarea, 3 image, 4 date, 5 dropdown
    Data(QString type="null", QString name="null" ,QString value="null", QString date="null",QString path="null");
    ~Data();
    QString type;
    QString name;
    QString value;
    QString date;
    QString path;
};

#endif // DATA_H
