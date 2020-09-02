#include "mainwindow.h"
#include "doctab.h"
#include "sortation.h"
#include "ui_mainwindow.h"

extern Sortation *sortation;

//class Widget : public QWidget{
//    Q_OBJECT

//public:
//    Widget(QWidget *parent = nullptr);
//    ~Widget();
//    void moussMoveEvent(QMouseEvent *ev);
//    bool eventFilter(QObject *obj,QEvent *ev);
//    void leaveEvent(QEvent *);
//    void enterEvent(QEvent *event) override;
//};

//void Widget:: enterEvent(QEvent *event){

//}

DocTab::DocTab(QWidget* parent, int srtIdx):QWidget(parent){
    //setObjectName("doctab");
    this->SA=new QScrollArea(parent);
    QVBoxLayout* VBox = new QVBoxLayout(parent);
    VBox->addWidget(SA);

    //技肺 胶农费官 积己
    SA->setWidgetResizable(1);
    SA->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

    SA->setWidget(this);
    this->VBox = new QVBoxLayout();//VBox肺 积己
    this->setLayout( this->VBox );

    this->srtIdx=srtIdx;
}

DocTab::~DocTab(){
    delete this->VBox;
    delete this->SA;
    delete this;
}


