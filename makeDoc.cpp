#include "mainwindow.h"
#include "ui_mainwindow.h"

void make_doc0(QWidget* docTab, QVBoxLayout* layout){
    QGroupBox* box = new QGroupBox(Kor("기본 정보"), docTab);
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
}

void make_doc1(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc2(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc3(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc4(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc5(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc6(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc7(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc8(QWidget* docTab, QVBoxLayout* layout){

}

void save_doc(){

}

void delete_doc(){

}

void preview_doc(){

}

void active_doc_select(){

}

//문서 만들때 한 번 실행되는 함수
void MainWindow::add_box(QWidget* docTab) {
    //저장, 삭제 미리보기, 활성화 버튼 생성

    QScrollArea* SA=new QScrollArea();
    SA->setWidget(docTab);
    SA->setWidgetResizable(true);
    SA->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

    QVBoxLayout* VBox = new QVBoxLayout(SA);

    docTab->setLayout(VBox);
    QWidget* Par = new QWidget(SA);
    QHBoxLayout* HBox = new QHBoxLayout(Par);
    QPushButton* PB;
    PB=new QPushButton(Kor("저장"),Par);
    connect(PB, SIGNAL(clicked()), this, SLOT(save_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("삭제"),Par);
    connect(PB, SIGNAL(clicked()), this, SLOT(delete_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("미리보기"),Par);
    connect(PB, SIGNAL(clicked()), this, SLOT(preview_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("활성화"),Par);
    connect(PB, SIGNAL(clicked()), this, SLOT(active_doc_select()));
    HBox->addWidget(PB);
    VBox->addWidget(Par);
    Par->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    switch(srtIdx){
    //connect로 함수들 연결
    case 0:
        make_doc0(SA, VBox);
        make_doc0(SA, VBox);
        break;
    case 1:
        make_doc1(docTab, VBox);
        break;
    case 2:
        make_doc2(docTab, VBox);
        break;
    case 3:
        make_doc3(docTab, VBox);
        break;
    case 4:
        make_doc4(docTab, VBox);
        break;
    case 5:
        make_doc5(docTab, VBox);
        break;
    case 6:
        make_doc6(docTab, VBox);
        break;
    case 7:
        make_doc7(docTab, VBox);
        break;
    case 8:
        make_doc8(docTab, VBox);
        break;
    }
}
