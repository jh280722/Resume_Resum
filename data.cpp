#include "data.h"

Data::Data(QString type, QString name ,QString value, QString date,QString path){
    this->type=type;
    this->name=name;
    this->value=value;
    this->date=date;
    this->path=path;
}

Data::~Data(){

}
