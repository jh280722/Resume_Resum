#include "mainwindow.h"
#include "ui_mainwindow.h"

QString name;
int kor,eng,math;
int total,avg;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    num[0]=num[1]=num[2]=0;
//    int w=ui->label_pic->width();
//    int h=ui->label_pic->height();
//    QPixmap pix(":/img/tmp.jpg");
//    ui->label_pic->setPixmap(pix);
//    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
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

void MainWindow::makeTab(QWidget* Tab){
    QWidget *widget = Tab;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    widget->setLayout(layout);

    QGroupBox *box = new QGroupBox(Kor("기본 정보"), widget);
    QVBoxLayout *boxLayout = new QVBoxLayout(box);
    layout->addWidget(box);

    QWidget* nameWidget = new QWidget(box);
    QWidget* ageWidget = new QWidget(box);
    QWidget* addressWidget = new QWidget(box);

    boxLayout->addWidget(nameWidget);
    boxLayout->addWidget(ageWidget);
    boxLayout->addWidget(addressWidget);

    QHBoxLayout *nameLayout = new QHBoxLayout(nameWidget);
    nameLayout->addWidget(new QLabel(Kor("이 름 :")));
    nameLayout->addWidget(new QLineEdit(nameWidget));


    QHBoxLayout *ageLayout = new QHBoxLayout(ageWidget);
    ageLayout->addWidget(new QLabel(Kor("나 이 :")));
    ageLayout->addWidget(new QLineEdit(ageWidget));

    QHBoxLayout *addressLayout = new QHBoxLayout(addressWidget);
    addressLayout->addWidget(new QLabel(Kor("주 소 :")));
    addressLayout->addWidget(new QLineEdit(addressWidget));


    QWidget* validateWidget = new QWidget(widget);
    QHBoxLayout *validateLayout = new QHBoxLayout(validateWidget);
    validateLayout->addWidget(new QPushButton(Kor("확 인"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("리 셋"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("취 소"), validateWidget));

    layout->addWidget(validateWidget);
}

void MainWindow::on_plus_clicked(){
    QObject *sel=QObject::sender();
    if(sel==mb[0]){
        mb[0]->setText(Kor("기본정보")+QString::number(num[0]));
        disconnect(mb[0], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        list[0].push_back(newButton("dm0_"+QString::number(num[0]),Kor("항목추가")));
        mb[0]=list[0][num[0]];
        connect(list[0][num[0]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        ui->dropmenu0->layout()->addWidget(list[0][num[0]++]);

        makeTab(ui->tab);
    }
    else if(sel==mb[1]){
        mb[1]->setText(Kor("인적사항")+QString::number(num[1]));
        disconnect(mb[1], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        list[1].push_back(newButton("dm0_"+QString::number(num[1]),Kor("항목추가")));
        mb[1]=list[1][num[1]];
        connect(list[1][num[1]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        ui->dropmenu1->layout()->addWidget(list[1][num[1]++]);
    }
    else if(sel==mb[2]){
        mb[2]->setText(Kor("자기소개서")+QString::number(num[2]));
        disconnect(mb[2], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        list[2].push_back(newButton("dm0_"+QString::number(num[2]),Kor("항목추가")));
        mb[2]=list[2][num[2]];
        connect(list[2][num[2]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        ui->dropmenu2->layout()->addWidget(list[2][num[2]++]);
    }
}
void MainWindow::on_dm0_clicked()
{
    static int flg=0;
    if(flg==0){
        flg=1;
        list[0].push_back(newButton("dm0_"+QString::number(num[0]),Kor("항목추가")));
        mb[0]=list[0][num[0]];
        connect(list[0][num[0]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        ui->dropmenu0->layout()->addWidget(list[0][num[0]++]);
    }
    if(flg==1){
        flg=2;
        for(int i = 0; i < num[0]; i++)
        {
             list[0][i]->show();
        }
    }
    else if(flg==2){
        flg=1;
        for(int i = 0; i < num[0]; i++)
        {
             list[0][i]->hide();
        }
    }
}

void MainWindow::on_dm1_clicked()
{
    static int flg=0;
    if(flg==0){
        flg=1;
        list[1].push_back(newButton("dm1_"+QString::number(num[1]),Kor("항목추가")));
        mb[1]=list[1][num[1]];
        connect(list[1][num[1]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        ui->dropmenu1->layout()->addWidget(list[1][num[1]++]);
    }
    if(flg==1){
        flg=2;
        for(int i = 0; i < num[1]; i++)
        {
             list[1][i]->show();
        }
    }
    else if(flg==2){
        flg=1;
        for(int i = 0; i < num[1]; i++)
        {
             list[1][i]->hide();
        }
    }
}

void MainWindow::on_dm2_clicked()
{
    static int flg=0;
    if(flg==0){
        flg=1;
        list[2].push_back(newButton("dm2_"+QString::number(num[2]),Kor("항목추가")));
        mb[2]=list[2][num[2]];
        connect(list[2][num[2]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        ui->dropmenu2->layout()->addWidget(list[2][num[2]++]);
    }
    if(flg==1){
        flg=2;
        for(int i = 0; i < num[2]; i++)
        {
             list[2][i]->show();
        }
    }
    else if(flg==2){
        flg=1;
        for(int i = 0; i < num[2]; i++)
        {
             list[2][i]->hide();
        }
    }
}

