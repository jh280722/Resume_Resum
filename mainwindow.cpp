#include "mainwindow.h"
#include "ui_MainWindow.h"

QString name;
int kor,eng,math;
int total,avg;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int w=ui->label_pic->width();
    int h=ui->label_pic->height();
    QPixmap pix(":/img/tmp.jpg");
    ui->label_pic->setPixmap(pix);
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}


QPushButton* MainWindow::newButton(QString name, QString str)
{
       QPushButton* button = new QPushButton(str);
       button->setObjectName(name);
       return button;
}

void MainWindow::on_dm_clicked()
{
    static bool flg=0;
    if(flg==0){
        flg=1;
        QList<QPushButton*> list;
        list.push_back(newButton("dm1",Kor("인적사항 1")));
        list.push_back(newButton("dm2",Kor("인적사항 2")));
        for(int i=0;i<list.size();i++)
           ui->dropmenu->layout()->addWidget(list[i]);
    }
    else{
        flg=0;
        int sz=ui->dropmenu->layout()->count();
        for(int i = 0; i < sz; i++)
          {
              QWidget *button;
              button = ui->dropmenu->layout()->takeAt(0)->widget();
              delete button;
          }
    }
}
