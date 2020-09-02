#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QWidget>
#include <QDate>
using namespace std;
class Data
{
public:
    //type 0 box 1 text, 2 textarea, 3 image, 4 date, 5 dropdown
    Data(int type, string name ,string value, string date="",string path="");
    ~Data();
    int type;
    string name;
    string value;
    string date;
    string path;
};

#endif // DATA_H
