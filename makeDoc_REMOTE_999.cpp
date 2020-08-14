#include "mainwindow.h"
#include "Document.h"
#include "ui_mainwindow.h"

void Document::make_doc0(){
    QGroupBox* box = new QGroupBox("", this);
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    QVBoxLayout* layout=this->VBox;
    QWidget* nameWidget = new QWidget(box);
    QWidget* ageWidget = new QWidget(box);
    QWidget* addressWidget = new QWidget(box);

    boxLayout->addWidget(nameWidget);
    boxLayout->addWidget(ageWidget);
    boxLayout->addWidget(addressWidget);


    QToolBar *toolbar=new QToolBar(this);
    QToolButton *tool = new QToolButton(toolbar);
    toolbar->addWidget(tool);
    QMenu *pFileMenu=new QMenu(tool);
    QAction *pSlotNewFile = new QAction(Kor("추가"), pFileMenu);
    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
    pSlotNewFile->setStatusTip(Kor("인적사항을 추가합니다."));
    pFileMenu->addAction(pSlotNewFile); // 추가
    tool->setPopupMode(QToolButton::InstantPopup);
    tool->setMenu(pFileMenu);
    tool->setDefaultAction(pSlotNewFile);

    QHBoxLayout* nameLayout = new QHBoxLayout(nameWidget);
    nameLayout->addWidget(new QLabel(Kor("이 름 :")));
    nameLayout->addWidget(new QLineEdit(nameWidget));
    nameLayout->addWidget(toolbar);


    QHBoxLayout* ageLayout = new QHBoxLayout(ageWidget);
    ageLayout->addWidget(new QLabel(Kor("나 이 :")));
    ageLayout->addWidget(new QLineEdit(ageWidget));

    QHBoxLayout* addressLayout = new QHBoxLayout(addressWidget);
    addressLayout->addWidget(new QLabel(Kor("주 소 :")));
    addressLayout->addWidget(new QLineEdit(addressWidget));


    box->setMinimumSize(600,200);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    int n=box->parent()->children().size();
    layout->insertWidget(n-3,box);
}

void Document::make_doc1() {

}

void Document::make_doc2() {

}

void Document::make_doc3() {

}

void Document::make_doc4() {

}

void Document::make_doc5() {

}

void Document::make_doc6() {

}

void Document::make_doc7() {

}

void Document::make_doc8(){

}

void save_doc(){

}

void delete_doc(){

}

void preview_doc(){

}

void active_doc_select(){

}

Document::Document(QWidget* parent):QWidget(parent){
    QScrollArea* SA=new QScrollArea(parent);
    QVBoxLayout* VBox = new QVBoxLayout(parent);
    VBox->addWidget(SA);

    //세로 스크롤바 생성
    SA->setWidgetResizable(1);
    SA->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    SA->setWidget(this);
    this->VBox = new QVBoxLayout();//VBox로 생성
    this->setLayout( this->VBox );
    this->VBox->setAlignment(Qt::AlignTop);
}
Document::~Document(){
}

//문서 만들때 한 번 실행되는 함수
void MainWindow::add_box(QWidget* docTab) {

    //스크롤 영역 위젯 생성
    Document* SAW=new Document(docTab);

    //저장, 삭제, 미리보기, 활성화 버튼 생성
    QWidget* Par = new QWidget(SAW);

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
    Par->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

    SAW->VBox->addWidget(Par);

    Par = new QWidget(SAW);
    QHBoxLayout* plusButton = new QHBoxLayout(Par);
    PB=new QPushButton(Kor("추가"),Par);
    plusButton->addWidget(PB);
    plusButton->setAlignment(Qt::AlignRight);
    SAW->VBox->addWidget(Par);

    switch(srtIdx){ //srt별로 양식 생성
    //connect로 함수들 연결
    case 0:
        SAW->make_doc0();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc0()));
        break;
    case 1:
        SAW->make_doc1();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc1()));
        break;
    case 2:
        SAW->make_doc2();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc2()));
        break;
    case 3:
        SAW->make_doc3();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc3()));
        break;
    case 4:
        SAW->make_doc4();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc4()));
        break;
    case 5:
        SAW->make_doc5();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc5()));
        break;
    case 6:
        SAW->make_doc6();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc6()));
        break;
    case 7:
        SAW->make_doc7();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc7()));
        break;
    case 8:
        SAW->make_doc8();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc8()));
        break;
    }
}
