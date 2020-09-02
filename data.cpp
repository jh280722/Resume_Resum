#include "data.h"

Data::Data(QString type, QString name ,int valueLine, QString value, QString date,QString path){
    this->type=type;
    this->name=name;
    this->value=value;
    this->valueLine=valueLine;
    this->date=date;
    this->path=path;
}

Data::~Data(){

}
