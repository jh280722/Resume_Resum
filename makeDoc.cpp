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

    connect(pSlotNewFile, SIGNAL(triggered()), this, SLOT(make_doc0()));

   // pFileMenu = tool->menu()->addMenu(Kor("파일"));
    pFileMenu->addAction(pSlotNewFile); // 추가

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
    layout->addWidget(box);

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
}
Document::~Document(){
}

//문서 만들때 한 번 실행되는 함수
void MainWindow::add_box(QWidget* docTab) {

    //스크롤 영역 위젯 생성
    Document* SAW=new Document(docTab);

    //저장, 삭제, 미리보기, 활성화 버튼 생성
    QWidget* Par = new QWidget(docTab);

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

    switch(srtIdx){ //srt별로 양식 생성
    //connect로 함수들 연결
    case 0:
        SAW->make_doc0();
        break;
//    case 1:
//        make_doc1(SAW, VBox2);
//        break;
//    case 2:
//        make_doc2(SAW, VBox2);
//        break;
//    case 3:
//        make_doc3(SAW, VBox2);
//        break;
//    case 4:
//        make_doc4(SAW, VBox2);
//        break;
//    case 5:
//        make_doc5(SAW, VBox2);
//        break;
//    case 6:
//        make_doc6(SAW, VBox2);
//        break;
//    case 7:
//        make_doc7(SAW, VBox2);
//        break;
//    case 8:
//        make_doc8(SAW, VBox2);
//        break;
    }
    //가로 스페이서 생성
    QSpacerItem* VS= new QSpacerItem(500,500);
    //SAW->VBox->addItem(VS);
}
