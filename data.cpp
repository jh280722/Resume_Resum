#include "data.h"

Data::Data(int type, string name ,string value, string date,string path){
    this->type=type;
    this->name=name;
    this->value=value;
    this->date=date;
    this->path=path;
}

Data::~Data(){

}
