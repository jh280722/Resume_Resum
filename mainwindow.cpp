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


QPushButton* MainWindow::new_button(QString name, QString str)
{
       QPushButton* button = new QPushButton(str);
       button->setObjectName(name);
       return button;
}

void MainWindow::make_tab(QWidget* Tab){
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
    QString name;
    QWidget *menu=0;
    if(sel==mb[0]){
        name=Kor("기본 정보 ")+QString::number(num[idx]);
        menu=ui->dropmenu0;
    }
    else if(sel==mb[1]){
        name=Kor("인적 사항 ")+QString::number(num[idx]);
        menu=ui->dropmenu1;
    }
    else if(sel==mb[2]){
        name=Kor("자 소 서 ")+QString::number(num[idx]);
        menu=ui->dropmenu2;
    }
    mb[idx]->setText(name);
    disconnect(mb[idx], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    list[idx].push_back(new_button("dm"+QString::number(idx)+"_"+QString::number(num[idx]),Kor("항목추가")));
    mb[idx]=list[idx][num[idx]];
    connect(list[idx][num[idx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    menu->layout()->addWidget(list[idx][num[idx]++]);
    //makeTab(ui->tab);
}

void MainWindow::hide_show(int idx, int flg){
    QWidget* menu=0;
    if(idx==0)
        menu=ui->dropmenu0;
    else if(idx==1)
        menu=ui->dropmenu1;
    else if(idx==2)
        menu=ui->dropmenu2;

    if(flg==0){
        flg=1;
        list[idx].push_back(new_button("dm"+QString::number(idx)+"_"+QString::number(num[idx]),Kor("항목추가")));
        mb[idx]=list[idx][num[idx]];
        connect(list[idx][num[idx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        menu->layout()->addWidget(list[idx][num[idx]++]);
    }
    if(flg==1){
        flg=2;
        for(int i = 0; i < num[idx]; i++)
        {
             list[idx][i]->show();
        }
    }
    else if(flg==2){
        flg=1;
        for(int i = 0; i < num[idx]; i++)
        {
             list[idx][i]->hide();
        }
    }
}

void MainWindow::on_dm0_clicked()
{
    static int flg=0;
    idx=0;
    hide_show(idx,flg);
}

void MainWindow::on_dm1_clicked()
{
    static int flg=0;
    idx=1;
    hide_show(idx,flg);
}

void MainWindow::on_dm2_clicked()
{
    static int flg=0;
    idx=2;
    hide_show(idx,flg);
}

