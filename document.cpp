#include "mainwindow.h"
#include "Document.h"
#include "sortation.h"
#include "ui_mainwindow.h"

extern Sortation *sortation;

Document::Document(QWidget*parent, int srtIdx):QWidget(parent){
    //setObjectName("doc");
    this->srtIdx=srtIdx;
    add_box();
}

Document::~Document(){
    delete this->PBS;
    delete this->tab;
    delete this;
}

//문서 만들때 한 번 실행되는 함수
void Document::add_box() {

    //스크롤 영역 위젯 생성
    tab=new DocTab(this,srtIdx);
    //저장, 삭제, 미리보기, 활성화 버튼 생성
    QWidget* Par = new QWidget(tab);

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

    tab->VBox->addWidget(Par);

    Par = new QWidget(tab);
    QHBoxLayout* plusButton = new QHBoxLayout(Par);
    PB=new QPushButton(Kor("추가"),Par);
    plusButton->addWidget(PB);
    plusButton->setAlignment(Qt::AlignRight);
    tab->VBox->addWidget(Par);

    switch(srtIdx){ //srt별로 양식 생성
    //connect로 함수들 연결
    case 0:
        tab->make_doc0();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc0()));
        break;
    case 1:
        tab->make_doc1();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc1()));
        break;
    case 2:
        tab->make_doc2();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc2()));
        break;
    case 3:
        tab->make_doc3();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc3()));
        break;
    case 4:
        tab->make_doc4();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc4()));
        break;
    case 5:
        tab->make_doc5();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc5()));
        break;
    case 6:
        tab->make_doc6();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc6()));
        break;
    case 7:
        tab->make_doc7();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc7()));
        break;
    case 8:
        tab->make_doc8();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc8()));
        break;
    }
}

void Document::save_doc(){

}

void Document::delete_doc(){
    sortation->srtIdx=srtIdx;
    for(auto it : sortation->docList[srtIdx]){
        if(it==this){
            delete(it->PBS);
            sortation->docList[srtIdx].removeOne(it);
            break;
        }
    }
    sortation->delete_tab(srtIdx);
}

void Document::preview_doc(){

}

void Document::active_doc_select(){

}

