#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "doubleclickedwidget.h"
#include <QFile>


void  DoubleClickedWidget::hideText(){
    QLabel* label=qobject_cast<QLabel*>(this);
    QLineEdit* edit=this->parent()->findChild<QLineEdit*>("titleEdit");
    label->setText(edit->text());
    label->show();
    edit->hide();
};
void DoubleClickedWidget:: doubleClicked(){

    QLabel* label= qobject_cast<QLabel*>(this);
    QLineEdit * text= label->parent()->findChild<QLineEdit*>("titleEdit");

    text->setText(label->text());
    text->show();
    label->hide();
    text->setFocus();
}

void Document::AddItemText() {
    QObject* item = QObject::sender();
    QLayout* boxlayout = qobject_cast<QLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("텍스트"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QLineEdit* LineEdit=new QLineEdit(newWidget);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(LineEdit);


    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    LineEdit->setObjectName("QLineEdit");
    newWidget->setObjectName("text");
}
void Document::AddItemText(QLayout * boxlayout,QString name,QString value) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QLineEdit* LineEdit=new QLineEdit(value,newWidget);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(LineEdit);

    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    LineEdit->setObjectName("QLineEdit");
    newWidget->setObjectName("text");
}
void Document::AddItemTextarea() {
    QObject* item = QObject::sender();
    QLayout* boxlayout = qobject_cast<QLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("텍스트"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QTextEdit* TextEdit = new QTextEdit(newWidget);

    TextEdit->setMinimumHeight(150);
    TextEdit->setFixedHeight(150);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignTop|Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(TextEdit);

    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignTop);
    newLayout->setAlignment(titleEdit, Qt::AlignTop|Qt::AlignRight);
    newLayout->setAlignment(sep, Qt::AlignTop);
    newLayout->setAlignment(delButton, Qt::AlignTop);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    TextEdit->setObjectName("QTextEdit");
    newWidget->setObjectName("textArea");
}
void Document::AddItemTextarea(QLayout * boxlayout,QString name,QString value) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QTextEdit* TextEdit = new QTextEdit(value,newWidget);

    TextEdit->setPlainText(value);
    TextEdit->setMinimumHeight(150);
    TextEdit->setFixedHeight(150);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignTop|Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(TextEdit);

    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignTop);
    newLayout->setAlignment(sep, Qt::AlignTop);
    newLayout->setAlignment(titleEdit, Qt::AlignTop|Qt::AlignRight);
    newLayout->setAlignment(delButton, Qt::AlignTop);

    delButton->setFocusPolicy(Qt::NoFocus);
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
    QObjectList box=item->parent()->parent()->children();
    int idx=0;
    for(;idx<box.size();idx++){
        if(box[idx]==item->parent()){
            break;
        }
    }
    QString newName = docPath + QString::number(idx)+"_"+fileName;
    QFile::copy ( filepath, newName );
}

void Document::AddItemImage() {
    QObject* item = QObject::sender();
    QLayout* boxlayout = qobject_cast<QLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("이미지"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QPushButton* addButton = new QPushButton(Kor("업로드"), newWidget);
    QLabel* path = new QLabel(Kor("경로"), newWidget);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(addButton);
    newLayout->addWidget(path);
    newLayout->addStretch();
    newLayout->addWidget(delButton);

    titleEdit->hide();

    connect(addButton, SIGNAL(clicked()), this, SLOT(imageUpload()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    path->setObjectName("path");
    newWidget->setObjectName("image");
}
void Document::AddItemImage(QLayout * boxlayout,QString name,QString path) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QPushButton* addButton = new QPushButton(Kor("업로드"), newWidget);
    QLabel* newpath = new QLabel(path, newWidget);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(addButton);
    newLayout->addWidget(newpath);
    newLayout->addStretch();
    titleEdit->hide();

    connect(addButton, SIGNAL(clicked()), this, SLOT(imageUpload()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newpath->setObjectName("path");
    newWidget->setObjectName("image");
}
void Document::AddItemDate() {
    QObject* item = QObject::sender();
    QLayout* boxlayout = qobject_cast<QLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("날 짜"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QDateEdit* newdate = new QDateEdit();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newdate->setCalendarPopup(1);
    newdate->setDate(QDate::currentDate());
    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdate);
    newLayout->addStretch();

    titleEdit->hide();

    //delButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignLeft);
    newLayout->setAlignment(sep, Qt::AlignLeft);
    newLayout->setAlignment(newdate, Qt::AlignLeft);
    newLayout->setAlignment(delButton, Qt::AlignRight);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdate->setObjectName("QDate");
    newWidget->setObjectName("date");
}
void Document::AddItemDate(QLayout * boxlayout,QString name,QString date) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QDateEdit* newdate = new QDateEdit();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newdate->setCalendarPopup(1);
    newdate->setDate(QDate::fromString(date,"yyyy-MM-dd"));
    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdate);
    newLayout->addStretch();
    titleEdit->hide();

    //delButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignLeft);
    newLayout->setAlignment(sep, Qt::AlignLeft);
    newLayout->setAlignment(newdate, Qt::AlignLeft);
    newLayout->setAlignment(delButton, Qt::AlignRight);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdate->setObjectName("QDate");
    newWidget->setObjectName("date");
}
void Document::AddItemDropdown() {
    QObject* item = QObject::sender();
    QLayout* boxlayout = qobject_cast<QLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("드롭다운"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QComboBox* newdd = new QComboBox();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);


    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdd);
    newLayout->addStretch();

    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdd->setObjectName("QComboBox");
    newWidget->setObjectName("dropDown");
}
void Document::AddItemDropdown(QLayout * boxlayout,QString name,QString setting) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QComboBox* newdd = new QComboBox();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdd);
    newLayout->addStretch();
    titleEdit->hide();

    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdd->setObjectName("QComboBox");
    newWidget->setObjectName("dropDown");
}

void Document::AddItemPeriod() {
    QObject* item = QObject::sender();
    QLayout* boxlayout = qobject_cast<QLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("날 짜"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QDateEdit* stdate = new QDateEdit();
    QDateEdit* eddate = new QDateEdit();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    stdate->setCalendarPopup(1);
    stdate->setDate(QDate::currentDate());
    eddate->setCalendarPopup(1);
    eddate->setDate(QDate::currentDate());

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(stdate);
    newLayout->addWidget(eddate);
    newLayout->addStretch();

    titleEdit->hide();

    //delButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignLeft);
    newLayout->setAlignment(sep, Qt::AlignLeft);
    newLayout->setAlignment(stdate, Qt::AlignLeft);
    newLayout->setAlignment(eddate, Qt::AlignLeft);
    newLayout->setAlignment(delButton, Qt::AlignRight);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    stdate->setObjectName("QPeriodSt");
    eddate->setObjectName("QPeriodEd");
    newWidget->setObjectName("period");
}

void Document::AddItemPeriod(QLayout * boxlayout, QString name,QString st,QString ed) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("날 짜"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QDateEdit* stdate = new QDateEdit();
    QDateEdit* eddate = new QDateEdit();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    stdate->setCalendarPopup(1);
    stdate->setDate(QDate::fromString(st,"yyyy-MM-dd"));
    eddate->setCalendarPopup(1);
    eddate->setDate(QDate::fromString(ed,"yyyy-MM-dd"));

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(stdate);
    newLayout->addWidget(eddate);
    newLayout->addStretch();

    titleEdit->hide();

    //delButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignLeft);
    newLayout->setAlignment(sep, Qt::AlignLeft);
    newLayout->setAlignment(stdate, Qt::AlignLeft);
    newLayout->setAlignment(eddate, Qt::AlignLeft);
    newLayout->setAlignment(delButton, Qt::AlignRight);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    stdate->setObjectName("QPeriodSt");
    eddate->setObjectName("QPeriodEd");
    newWidget->setObjectName("period");
}
void Document::add_tool_option(QGroupBox* box, QLayout * boxLayout){
    QWidget* toolWidget = new QWidget(box);
    QToolButton* tool = new QToolButton(toolWidget);
    QHBoxLayout* toolLayout = new QHBoxLayout(toolWidget);
    QMenu* Menu = new QMenu();
    QMenu* InputMenu = new QMenu();
    toolLayout->addStretch();
    toolLayout->addWidget(tool, Qt::AlignRight);

    QAction* TBAAdd = new QAction(Kor("추가"), tool);
    TBAAdd->setStatusTip(Kor("아이템을 추가합니다."));
    QAction* TBADelete = new QAction(Kor("삭제"), tool);
    TBADelete->setStatusTip(Kor("박스를 삭제합니다."));
    connect(TBADelete, SIGNAL(triggered()), this, SLOT(deleteBox()));

    QAction* TBAAddText = new QAction(Kor("텍스트"), boxLayout);
    connect(TBAAddText, SIGNAL(triggered()), this, SLOT(AddItemText()));
    QAction* TBAAddTextarea = new QAction(Kor("글 상자"), boxLayout);
    connect(TBAAddTextarea, SIGNAL(triggered()), this, SLOT(AddItemTextarea()));
    QAction* TBAAddDropdown = new QAction(Kor("드롭 다운"), boxLayout);
    connect(TBAAddDropdown, SIGNAL(triggered()), this, SLOT(AddItemDropdown()));
    QAction* TBAAddDate = new QAction(Kor("날짜"), boxLayout);
    connect(TBAAddDate, SIGNAL(triggered()), this, SLOT(AddItemDate()));
    QAction* TBAAddPeriod = new QAction(Kor("기간"), boxLayout);
    connect(TBAAddPeriod, SIGNAL(triggered()), this, SLOT(AddItemPeriod()));
    QAction* TBAAddImage = new QAction(Kor("이미지"), boxLayout);
    connect(TBAAddImage, SIGNAL(triggered()), this, SLOT(AddItemImage()));

    Menu->addAction(TBAAdd);
    Menu->addAction(TBADelete);
    InputMenu->addAction(TBAAddText);
    InputMenu->addAction(TBAAddTextarea);
    InputMenu->addAction(TBAAddDropdown);
    InputMenu->addAction(TBAAddDate);
    InputMenu->addAction(TBAAddPeriod);
    InputMenu->addAction(TBAAddImage);

    TBAAdd->setMenu(InputMenu);
    tool->setMenu(Menu);
    tool->setPopupMode(QToolButton::InstantPopup);
    toolWidget->setObjectName("tool");

    boxLayout->addWidget(toolWidget);
}

void Document::deleteItem() {

    QObject* item = QObject::sender();
    disconnect(item, SIGNAL(clicked()), this, SLOT(deleteItem()));
    delete item->parent();
}
