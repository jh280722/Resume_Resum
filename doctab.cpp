#include "mainwindow.h"
#include "doctab.h"
#include "sortation.h"
#include "ui_mainwindow.h"

extern Sortation *sortation;

DocTab::DocTab(QWidget* parent, int srtIdx):QWidget(parent){
    setObjectName("doctab");
    this->SA=new QScrollArea(parent);
    QVBoxLayout* VBox = new QVBoxLayout(parent);
    VBox->addWidget(SA);
    //技肺 胶农费官 积己
    SA->setWidgetResizable(1);
    SA->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

    SA->setWidget(this);
    this->VLayout = new QVBoxLayout();//VBox肺 积己
    this->setLayout( this->VLayout );

    this->srtIdx=srtIdx;
    this->SA->setObjectName("SA");
    this->VLayout->setObjectName("VLayout");
    this->box=new QWidget(this);
    this->box->setObjectName("boxAreaWidget");
    this->boxArea=new QVBoxLayout(box);
    this->boxArea->setObjectName("boxAreaLayout");
    boxArea->setAlignment(Qt::AlignTop);
    box->setLayout(boxArea);
}

DocTab::~DocTab(){
}


