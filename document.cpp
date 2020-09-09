#include "mainwindow.h"
#include "Document.h"
#include "sortation.h"
#include "ui_mainwindow.h"
#include "data.h"
extern Sortation *sortation;

class Widget : public QWidget{

public:
    Widget(QWidget *parent=nullptr): QWidget(parent){
        this->installEventFilter(this);
    };
protected:
    bool eventFilter(QObject *obj,QEvent *ev) override{
        QPushButton * delButton= obj->findChild<QPushButton*>("delButton");
        this->show();
        if(ev->type()==QEvent::Enter){
            delButton->setFlat(0);
            return false;
        }
        else if(ev->type()==QEvent::Leave){
            delButton->setFlat(1);
            return true;
        }

    }
    //    void mouseDoubleClickEvent(QMouseEvent *ev) override{

    //    }
};

//class DoubleClickedWidget : public QWidget{

//public:
//    DoubleClickedWidget(QWidget *parent=nullptr): QWidget(parent){
//        this->installEventFilter(this);
//    };
//    signals:
//    void doubleClicked();
//protected:
//    void mouseDoubleClickEvent(QMouseEvent *) {
//        emit doubleClicked();
//    }

//};


Document::Document(QString name, int srtIdx):QWidget(){
    setObjectName("document");
    this->name=name;
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
    connect(PB, SIGNAL(clicked()), this, SLOT(active_doc_select()));
    HBox->addWidget(PB);
    Par->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

    tab->VLayout->addWidget(Par);
    tab->VLayout->addWidget(tab->box);

    Par = new QWidget(tab);
    Par->setObjectName("addBoxButton");
    QHBoxLayout* plusButton = new QHBoxLayout(Par);
    PB=new QPushButton(Kor("추가"),Par);
    PB->setObjectName("addBox");
    plusButton->addStretch();
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
}

QVBoxLayout* Document::load_add_box() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;
    QWidget* toolWidget = new QWidget(box);

    QWidget* tmp=new QWidget();
    Widget* nameWidget = new Widget(tmp);
    Widget* ageWidget = new Widget(tmp);
    Widget* addressWidget = new Widget(tmp);

    QToolButton* tool = new QToolButton(toolWidget);
    QHBoxLayout* toolLayout = new QHBoxLayout(toolWidget);
    QMenu* Menu = new QMenu();
    QMenu* InputMenu = new QMenu();
    toolLayout->addStretch();
    toolLayout->addWidget(tool, Qt::AlignRight);
    //tool->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QAction* TBAAdd = new QAction(Kor("추가"), tool);
    TBAAdd->setStatusTip(Kor("인적사항을 추가합니다."));
    QAction* TBADelete = new QAction(Kor("삭제"), tool);
    TBADelete->setStatusTip(Kor("인적사항을 삭제합니다."));
    connect(TBADelete, SIGNAL(triggered()), this, SLOT(deleteBox()));


    QAction* TBAAddText = new QAction(Kor("텍스트"), boxLayout);
    connect(TBAAddText, SIGNAL(triggered()), this, SLOT(AddItemText()));
    QAction* TBAAddTextarea = new QAction(Kor("글 상자"), boxLayout);
    connect(TBAAddTextarea, SIGNAL(triggered()), this, SLOT(AddItemTextarea()));
    QAction* TBAAddDropdown = new QAction(Kor("드롭 다운"), boxLayout);
    connect(TBAAddDropdown, SIGNAL(triggered()), this, SLOT(AddItemDropdown()));
    QAction* TBAAddDate = new QAction(Kor("날짜"), boxLayout);
    connect(TBAAddDate, SIGNAL(triggered()), this, SLOT(AddItemDate()));
    QAction* TBAAddImage = new QAction(Kor("이미지"), boxLayout);
    connect(TBAAddImage, SIGNAL(triggered()), this, SLOT(AddItemImage()));

    Menu->addAction(TBAAdd);
    Menu->addAction(TBADelete);
    InputMenu->addAction(TBAAddText);
    InputMenu->addAction(TBAAddTextarea);
    InputMenu->addAction(TBAAddDropdown);
    InputMenu->addAction(TBAAddDate);
    InputMenu->addAction(TBAAddImage);

    TBAAdd->setMenu(InputMenu);
    tool->setMenu(Menu);
    tool->setPopupMode(QToolButton::InstantPopup);
    toolWidget->setObjectName("tool");
    nameWidget->setObjectName("text");
    ageWidget->setObjectName("text");
    addressWidget->setObjectName("text");

    boxLayout->addWidget(toolWidget);


    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    layout->addWidget(box);

    return boxLayout;
}
void Document::AddItemText() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title=new QLabel(Kor("이 름"),newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QLineEdit* LineEdit=new QLineEdit(newWidget);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(LineEdit);
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    LineEdit->setObjectName("QLineEdit");
    newWidget->setObjectName("text");
}
void Document::AddItemText(Data* item,QVBoxLayout * boxlayout) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title=new QLabel(item->name,newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QLineEdit* LineEdit=new QLineEdit(item->value,newWidget);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(LineEdit);
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    LineEdit->setObjectName("QLineEdit");
    newWidget->setObjectName("text");
}
void Document::AddItemTextarea() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title = new QLabel(Kor("이 름"), newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QTextEdit* TextEdit = new QTextEdit(newWidget);
    TextEdit->setMinimumHeight(150);
    TextEdit->setMaximumHeight(150);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(TextEdit);
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignTop);
    newLayout->setAlignment(sep, Qt::AlignTop);
    newLayout->setAlignment(delButton, Qt::AlignTop);

    delButton->setFlat(1);
    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    TextEdit->setObjectName("QTextEdit");
    newWidget->setObjectName("textArea");
}
void Document::AddItemTextarea(Data* item,QVBoxLayout * boxlayout) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title = new QLabel(item->name, newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QTextEdit* TextEdit = new QTextEdit(item->value,newWidget);
    TextEdit->setPlainText(item->value);
    TextEdit->setMinimumHeight(150);
    TextEdit->setMaximumHeight(150);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(TextEdit);
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignTop);
    newLayout->setAlignment(sep, Qt::AlignTop);
    newLayout->setAlignment(delButton, Qt::AlignTop);

    delButton->setFlat(1);
    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    TextEdit->setObjectName("QTextEdit");
    newWidget->setObjectName("textArea");
}
void Document::imageUpload() {
    QObject* item = QObject::sender();
    QLabel* path = item->parent()->findChild<QLabel*>("path");
    QFileDialog  dlg;
    QString filepath = dlg.getOpenFileName(this, "Load Image", "", "Image Files (*.png *.jpg *.bmp)");
    QString fileName = filepath.section("/", -1);
    path->setText(fileName);
}

void Document::AddItemImage() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title = new QLabel(Kor("이 름"), newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QPushButton* addButton = new QPushButton(Kor("업로드"), newWidget);
    QLabel* path = new QLabel(Kor("경로"), newWidget);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(addButton);
    newLayout->addWidget(path);
    newLayout->addStretch();
    newLayout->addWidget(delButton);
    connect(addButton, SIGNAL(clicked()), this, SLOT(imageUpload()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);


    delButton->setFlat(1);
    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    path->setObjectName("path");
    newWidget->setObjectName("image");
}
void Document::AddItemImage(Data* item,QVBoxLayout * boxlayout) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title = new QLabel(item->name, newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QPushButton* addButton = new QPushButton(Kor("업로드"), newWidget);
    QLabel* path = new QLabel(item->path, newWidget);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(addButton);
    newLayout->addWidget(path);
    newLayout->addStretch();
    connect(addButton, SIGNAL(clicked()), this, SLOT(imageUpload()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);


    delButton->setFlat(1);
    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    path->setObjectName("path");
    newWidget->setObjectName("image");
}
void Document::AddItemDate() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title = new QLabel(Kor("이 름"), newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QDateEdit* newdate = new QDateEdit();

    newdate->setCalendarPopup(1);
    newdate->setDate(QDate::currentDate());
    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdate);
    newLayout->addStretch();
    delButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);
    newLayout->setAlignment(title, Qt::AlignLeft);
    newLayout->setAlignment(sep, Qt::AlignLeft);
    newLayout->setAlignment(newdate, Qt::AlignLeft);
    newLayout->setAlignment(delButton, Qt::AlignRight);


    delButton->setFlat(1);
    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdate->setObjectName("QDate");
    newWidget->setObjectName("date");
}
void Document::AddItemDate(Data* item,QVBoxLayout * boxlayout) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title = new QLabel(item->name, newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QDateEdit* newdate = new QDateEdit();

    newdate->setCalendarPopup(1);
    newdate->setDate(QDate::fromString(item->date,"yyyy-MM-dd"));
    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdate);
    newLayout->addStretch();
    delButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);
    newLayout->setAlignment(title, Qt::AlignLeft);
    newLayout->setAlignment(sep, Qt::AlignLeft);
    newLayout->setAlignment(newdate, Qt::AlignLeft);
    newLayout->setAlignment(delButton, Qt::AlignRight);


    delButton->setFlat(1);
    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdate->setObjectName("QDate");
    newWidget->setObjectName("date");
}
void Document::AddItemDropdown() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title = new QLabel(Kor("이 름"), newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QComboBox* newdd = new QComboBox();
    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdd);
    newLayout->addStretch();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFlat(1);
    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdd->setObjectName("QComboBox");
    newWidget->setObjectName("dropDown");
}
void Document::AddItemDropdown(Data* item,QVBoxLayout * boxlayout) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* title = new QLabel(item->name, newWidget);
    QLabel* sep = new QLabel((" :"), newWidget);
    QComboBox* newdd = new QComboBox();
    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdd);
    newLayout->addStretch();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFlat(1);
    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdd->setObjectName("QComboBox");
    newWidget->setObjectName("dropDown");
}

void Document::deleteItem() {

    QObject* item = QObject::sender();
    disconnect(item, SIGNAL(clicked()), this, SLOT(deleteItem()));
    delete item->parent();
}

void Document::deleteBox() {
    QObject* item = QObject::sender();
    disconnect(item, SIGNAL(triggered()), this, SLOT(deleteBox()));
    delete item->parent()->parent()->parent();
}

void Document::make_doc0() {
}

void Document::make_doc1() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;
    QWidget* toolWidget = new QWidget(box);

    QWidget* tmp=new QWidget();
    Widget* nameWidget = new Widget(tmp);
    Widget* ageWidget = new Widget(tmp);
    Widget* addressWidget = new Widget(tmp);

    QToolButton* tool = new QToolButton(toolWidget);
    QHBoxLayout* toolLayout = new QHBoxLayout(toolWidget);
    QMenu* Menu = new QMenu();
    QMenu* InputMenu = new QMenu();
    toolLayout->addStretch();
    toolLayout->addWidget(tool, Qt::AlignRight);
    //tool->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QAction* TBAAdd = new QAction(Kor("추가"), tool);
    TBAAdd->setStatusTip(Kor("인적사항을 추가합니다."));
    QAction* TBADelete = new QAction(Kor("삭제"), tool);
    TBADelete->setStatusTip(Kor("인적사항을 삭제합니다."));
    connect(TBADelete, SIGNAL(triggered()), this, SLOT(deleteBox()));


    QAction* TBAAddText = new QAction(Kor("텍스트"), boxLayout);
    connect(TBAAddText, SIGNAL(triggered()), this, SLOT(AddItemText()));
    QAction* TBAAddTextarea = new QAction(Kor("글 상자"), boxLayout);
    connect(TBAAddTextarea, SIGNAL(triggered()), this, SLOT(AddItemTextarea()));
    QAction* TBAAddDropdown = new QAction(Kor("드롭 다운"), boxLayout);
    connect(TBAAddDropdown, SIGNAL(triggered()), this, SLOT(AddItemDropdown()));
    QAction* TBAAddDate = new QAction(Kor("날짜"), boxLayout);
    connect(TBAAddDate, SIGNAL(triggered()), this, SLOT(AddItemDate()));
    QAction* TBAAddImage = new QAction(Kor("이미지"), boxLayout);
    connect(TBAAddImage, SIGNAL(triggered()), this, SLOT(AddItemImage()));

    Menu->addAction(TBAAdd);
    Menu->addAction(TBADelete);
    InputMenu->addAction(TBAAddText);
    InputMenu->addAction(TBAAddTextarea);
    InputMenu->addAction(TBAAddDropdown);
    InputMenu->addAction(TBAAddDate);
    InputMenu->addAction(TBAAddImage);

    TBAAdd->setMenu(InputMenu);
    tool->setMenu(Menu);
    tool->setPopupMode(QToolButton::InstantPopup);
    toolWidget->setObjectName("tool");
    nameWidget->setObjectName("text");
    ageWidget->setObjectName("text");
    addressWidget->setObjectName("text");

    boxLayout->addWidget(toolWidget);
    boxLayout->addWidget(nameWidget);
    boxLayout->addWidget(ageWidget);
    boxLayout->addWidget(addressWidget);

    QPushButton* delButton;
    QHBoxLayout* nameLayout = new QHBoxLayout(nameWidget);

    delButton = new QPushButton(nameWidget);
    //    DoubleClickedWidget * tmp2= new DoubleClickedWidget();
    //    connect(tmp2, SIGNAL(doubleClicked()), this, SLOT(onDoubleClicked()));
    QLabel * Label = new QLabel(Kor("이 름 : "));
    QLineEdit* LineEdit =new QLineEdit(nameWidget);
    Label->setObjectName("QLabel");
    LineEdit->setObjectName("QLineEdit");

    nameLayout->addWidget(delButton);
    nameLayout->addWidget(Label);
    nameLayout->addWidget(LineEdit);
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    delButton->setObjectName("delButton");
    delButton->setFlat(1);

    QHBoxLayout* ageLayout = new QHBoxLayout(ageWidget);
    delButton = new QPushButton(ageWidget);

    Label = new QLabel(Kor("나 이 : "));
    LineEdit =new QLineEdit(ageWidget);
    Label->setObjectName("QLabel");
    LineEdit->setObjectName("QLineEdit");

    ageLayout->addWidget(delButton);
    ageLayout->addWidget(Label);
    ageLayout->addWidget(LineEdit);
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    delButton->setObjectName("delButton");
    delButton->setFlat(1);

    QHBoxLayout* addressLayout = new QHBoxLayout(addressWidget);
    delButton = new QPushButton(addressWidget);

    Label = new QLabel(Kor("주 소 : "));
    LineEdit =new QLineEdit(addressWidget);
    Label->setObjectName("QLabel");
    LineEdit->setObjectName("QLineEdit");

    addressLayout->addWidget(delButton);
    addressLayout->addWidget(Label);
    addressLayout->addWidget(LineEdit);
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    delButton->setObjectName("delButton");
    delButton->setFlat(1);

    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    layout->addWidget(box);
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

void Document::make_doc8() {

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
