#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"
#include "data.h"
#include <QFile>
extern Sortation *sortation;

Document::Document(QString name, int srtIdx, bool load):QWidget(){
    setObjectName("document");
    this->name=name;
    this->srtIdx=srtIdx;
    this->active=0;
    docPath=srtPath+QString::number(srtIdx) +"/"+this->name+"/";
    QDir Directory(docPath); // 폴더 지정
    if(!Directory.exists()) // 폴더가 존재하지 않을경우
    {
        Directory.mkdir(AppPath+"/Data"); // 폴더 생성
        Directory.mkdir(srtPath+QString::number(srtIdx)); // 폴더 생성
        Directory.mkdir(docPath); // 폴더 생성
    }
    init_docTab(load);
    qDebug()<<active;
}

Document::~Document(){
    delete this;
}


//문서 만들때 한 번 실행되는 함수
void Document::init_docTab(bool load) {

    //스크롤 영역 위젯 생성
    tab=new DocTab(this,srtIdx);
    tab->setObjectName("doctab");
    //저장, 삭제, 미리보기, 활성화 버튼 생성
    QWidget* Par = new QWidget(tab);
    Par->setObjectName("docMenu");
    QHBoxLayout* HBox = new QHBoxLayout(Par);
    QPushButton* PB;
    PB=new QPushButton(Kor("저장"),Par);
    PB->setObjectName("save");
    connect(PB, SIGNAL(clicked()), this, SLOT(save_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("삭제"),Par);
    PB->setObjectName("delete");
    connect(PB, SIGNAL(clicked()), this, SLOT(delete_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("미리보기"),Par);
    PB->setObjectName("preview");
    connect(PB, SIGNAL(clicked()), this, SLOT(load_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("활성화"),Par);
    PB->setObjectName("active");
    //connect(PB, SIGNAL(clicked()), this, SLOT(active_doc_select()));
    HBox->addWidget(PB);
    Par->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

    tab->VLayout->addWidget(Par);
    tab->VLayout->addWidget(tab->box);

    Par = new QWidget(tab);
    Par->setObjectName("addBoxButton");
    QHBoxLayout* plusButton = new QHBoxLayout(Par);

    plusButton->addStretch();
    PB=new QPushButton(Kor("표 추가"),Par);
    PB->setObjectName("addTable");
    connect(PB, SIGNAL(clicked()), this, SLOT(add_table_box()));

    plusButton->addWidget(PB);
    PB=new QPushButton(Kor("추가"),Par);
    PB->setObjectName("addBox");
    plusButton->addWidget(PB);
    plusButton->setAlignment(Qt::AlignTop);

    tab->VLayout->addWidget(Par);

    switch(srtIdx){ //srt별로 양식 생성
    //connect로 함수들 연결
    case 0:
        make_doc0();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc0()));
        break;
    case 1:
        make_doc1();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc1()));
        break;
    case 2:
        make_doc2();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc2()));
        break;
    case 3:
        make_doc3();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc3()));
        break;
    case 4:
        make_doc4();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc4()));
        break;
    case 5:
        make_doc5();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc5()));
        break;
    case 6:
        make_doc6();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc6()));
        break;
    case 7:
        make_doc7();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc7()));
        break;
    case 8:
        make_doc8();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc8()));
        break;
    }
    if(!load)
        this->save_doc();
}

QVBoxLayout* Document::load_add_box() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QLayout* layout = tab->boxArea;

    add_tool_option(box,boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);

    return boxLayout;
}


void Document::deleteBox() {
    QObject* item = QObject::sender();
    disconnect(item, SIGNAL(triggered()), this, SLOT(deleteBox()));
    delete item->parent()->parent()->parent();
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
    active=!active;
    QObject* sel = QObject::sender();
    QPushButton* activePB = (QPushButton*)sel;
    if (activePB->icon().isNull()) {
        activePB->setIcon(QIcon(":/images/dot.png"));
    }
    else {
        activePB->setIcon(QIcon());
    }
}

bool Document::getActive(){
    return active;
}

void Document::setActive(bool val){
    active=val;
}

int Document::getSrtIdx(){
    return srtIdx;
}

void Document::setSrtIdx(int val){
    srtIdx=val;
}
