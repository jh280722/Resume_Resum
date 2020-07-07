#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    num[0] = num[1] = num[2] = 0;
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

void MainWindow::make_tab(QWidget* Tab) {
    QWidget* widget = Tab;
    QVBoxLayout* layout = new QVBoxLayout(widget);

    widget->setLayout(layout);

    QGroupBox* box = new QGroupBox(Kor("기본 정보"), widget);
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    layout->addWidget(box);

    QWidget* nameWidget = new QWidget(box);
    QWidget* ageWidget = new QWidget(box);
    QWidget* addressWidget = new QWidget(box);

    boxLayout->addWidget(nameWidget);
    boxLayout->addWidget(ageWidget);
    boxLayout->addWidget(addressWidget);

    QHBoxLayout* nameLayout = new QHBoxLayout(nameWidget);
    nameLayout->addWidget(new QLabel(Kor("이 름 :")));
    nameLayout->addWidget(new QLineEdit(nameWidget));


    QHBoxLayout* ageLayout = new QHBoxLayout(ageWidget);
    ageLayout->addWidget(new QLabel(Kor("나 이 :")));
    ageLayout->addWidget(new QLineEdit(ageWidget));

    QHBoxLayout* addressLayout = new QHBoxLayout(addressWidget);
    addressLayout->addWidget(new QLabel(Kor("주 소 :")));
    addressLayout->addWidget(new QLineEdit(addressWidget));


    QWidget* validateWidget = new QWidget(widget);
    QHBoxLayout* validateLayout = new QHBoxLayout(validateWidget);
    validateLayout->addWidget(new QPushButton(Kor("확 인"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("리 셋"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("취 소"), validateWidget));
    layout->addWidget(validateWidget);
}


void MainWindow::on_plus_clicked() {
    QObject* sel = QObject::sender();
    QString name;
    QWidget* menu = 0;
    if (sel == mb[0]) {
        TopicIdx = 0;
        name = Kor("기본 정보 ") + QString::number(num[TopicIdx]);
        menu = ui->dropmenu0;
    }
    else if (sel == mb[1]) {
        TopicIdx = 1;
        name = Kor("인적 사항 ") + QString::number(num[TopicIdx]);
        menu = ui->dropmenu1;
    }
    else if (sel == mb[2]) {
        TopicIdx = 2;
        name = Kor("자 소 서 ") + QString::number(num[TopicIdx]);
        menu = ui->dropmenu2;
    }
    mb[TopicIdx]->setText(name);
    disconnect(mb[TopicIdx], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    PBList[TopicIdx].push_back(new_button("dm" + QString::number(TopicIdx) + "_" + QString::number(num[TopicIdx]), Kor("항목추가")));
    mb[TopicIdx] = PBList[TopicIdx][num[TopicIdx]];
    menu->layout()->addWidget(PBList[TopicIdx][num[TopicIdx]]);
    QWidget* new_tab = new QWidget;
    make_tab(new_tab);
    TList[TopicIdx].push_back(new_tab);
    connect(PBList[TopicIdx][num[TopicIdx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    connect(PBList[TopicIdx][num[TopicIdx]++], SIGNAL(clicked()), this, SLOT(connect_subTopic()));
}

void MainWindow::hide_show(int TopicIdx, int& flg) {
    QWidget* menu = 0;
    if (TopicIdx == 0)
        menu = ui->dropmenu0;
    else if (TopicIdx == 1)
        menu = ui->dropmenu1;
    else if (TopicIdx == 2)
        menu = ui->dropmenu2;

    if (flg == 0) {
        flg = 2;
        PBList[TopicIdx].push_back(new_button("dm" + QString::number(TopicIdx) + "_" + QString::number(num[TopicIdx]),
            Kor("항목추가")));
        mb[TopicIdx] = PBList[TopicIdx][num[TopicIdx]];
        menu->layout()->addWidget(PBList[TopicIdx][num[TopicIdx]]);

        connect(PBList[TopicIdx][num[TopicIdx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        connect(PBList[TopicIdx][num[TopicIdx]++], SIGNAL(clicked()), this, SLOT(connect_subTopic()));
        ui->Tb1->setTabsClosable(true);
        connect(ui->Tb1, SIGNAL(tabCloseRequested(int)), this, SLOT(on_Tb1_deleteTab(int)));
    }
    else if (flg == 1) {
        flg = 2;
        for (int i = 0; i < num[TopicIdx]; i++)
        {
            PBList[TopicIdx][i]->show();
        }
    }
    else if (flg == 2) {
        flg = 1;
        for (int i = 0; i < num[TopicIdx]; i++)
        {
            PBList[TopicIdx][i]->hide();
        }
    }
}

void MainWindow::connect_subTopic() {
    QObject* sel = QObject::sender();
    bool existList = false;
    int tmpIdx = -1;
    int subTopicIdx = -1;


    for (int i = 0; i < PBList[0].size(); ++i) {
        if (PBList[0][i] == sel) {
            TopicIdx = 0;
            subTopicIdx = i;
        }
    }
    for (int i = 0; i < PBList[1].size(); ++i) {
        if (PBList[1][i] == sel) {
            TopicIdx = 1;
            subTopicIdx = i;
        }
    }
    for (int i = 0; i < PBList[2].size(); ++i) {
        if (PBList[2][i] == sel) {
            TopicIdx = 2;
            subTopicIdx = i;
        }
    }
    for (int i = 0; i < ui->Tb1->count(); ++i) {
        if (PBList[TopicIdx][subTopicIdx]->text() == ui->Tb1->tabText(i)) {
            existList = true;
            tmpIdx = i;
            break;
        }
    }



    if (existList) {
        ui->Tb1->setCurrentIndex(tmpIdx);
    }
    else {
        mbt = PBList[TopicIdx][subTopicIdx];
        on_Tb1_addTab(subTopicIdx);
        // connect(mbt,SIGNAL(clicked()),this,SLOT(on_Tb1_addTab()));
        ui->Tb1->setCurrentIndex(ui->Tb1->count() - 1);
    }

}

void MainWindow::on_Tb1_deleteTab(int idx) {
    ui->Tb1->removeTab(idx);

    //   disconnect(mbt,SIGNAL(clicked()),this,SLOT(connect_subTopic()));
    //   disconnect( mbt,SIGNAL(clicked()),this,SLOT(on_Tb1_addTab()));
}
void MainWindow::on_Tb1_addTab(int subTopicIdx) {
    QWidget* new_tab = TList[TopicIdx][subTopicIdx];
    ui->Tb1->addTab(new_tab, mbt->text());
    //ui->Tb1->show();

    if (ui->Tb1->indexOf(new_tab) != -1) {
        // disconnect( mbt,SIGNAL(clicked()),this,SLOT(on_Tb1_addTab()));
        // connect( mbt,SIGNAL(clicked()),this,SLOT(on_Tb1_addTab()));
         //ui->Tb1->removeTab(ui->Tb1->indexOf(new_tab));
    }
}


void MainWindow::on_dm0_clicked()
{
    static int flg = 0;
    TopicIdx = 0;
    hide_show(TopicIdx, flg);
}

void MainWindow::on_dm1_clicked()
{
    static int flg = 0;
    TopicIdx = 1;
    hide_show(TopicIdx, flg);
}

void MainWindow::on_dm2_clicked()
{
    static int flg = 0;
    TopicIdx = 2;
    hide_show(TopicIdx, flg);
}
