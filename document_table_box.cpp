#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "doubleclickedwidget.h"
#include <QFile>
#include <QTableWidget>
#include <QHeaderView>
#include <QFrame>
#include <QAbstractTableModel>
#include <QAbstractItemModel>

class myTable : public QTableWidget{
public:
    QLineEdit* Line;
    int sectionedit;
    QRect edit_geometry;
    myTable(QWidget *parent = nullptr) : QTableWidget(parent){
        //click, move가능
        horizontalHeader()->setSectionsMovable(1);
        horizontalHeader()->setSectionsClickable(1);

        // 헤더의 viewport를 부모로 라인에디터 생성
        Line = new QLineEdit(horizontalHeader()->viewport());  //#Create
        Line->setAlignment(Qt::AlignTop); //# Set the Alignmnet
        Line->setHidden(1);// # Hide it till its needed
        Line->blockSignals(1);
        sectionedit = 0;

        //더블클릭시 라벨 에디터 함수 실행, 라벨 수정 끝에 텍스트 수정 함수 실행
        connect(horizontalHeader(), &QHeaderView::sectionDoubleClicked,this,&myTable::editHeader);
        connect(Line, &QLineEdit::editingFinished,this,&myTable::doneEditing);
    }

    void doneEditing(){
        //라벨이 수정됐으면 다시 시그널을 막고 히든해준다.
        Line->blockSignals(true);
        Line->setHidden(true);
        QString newname = Line->text();
        QString oldname = horizontalHeaderItem(sectionedit)->text();

        Line->setText("");

        horizontalHeaderItem(sectionedit)->setText(newname); //새 이름으로 적용

        resizeColumnsToContents(); //문자 길이에 따라 폭 수정
        setCurrentIndex(QModelIndex()); //현재 인덱스로 설정
    }

    void editHeader(int section){
        edit_geometry = Line->geometry(); //라인 에디터의 좌표를 받아온다.
        //선택된 헤더의 섹션에 맞게 위치를 조절한다.
        edit_geometry.setWidth(horizontalHeader()->sectionSize(section));
        edit_geometry.moveLeft(horizontalHeader()->sectionViewportPosition(section));
        Line->setGeometry(edit_geometry);

        QString oldname = horizontalHeaderItem(sectionedit)->text();
        Line->setText(oldname);

        //라인 에디터의 hidden,blocksignal을 풀고 포커스해준다음 전체를 셀렉해준다.
        Line->setHidden(false);
        Line->blockSignals(false);
        Line->setFocus();
        Line->selectAll();

        sectionedit = section; //현재 선택된 세션의 인덱스를 저장한다.
    }
};


void Document::add_table_box() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("tableBox");
    QLayout* layout = tab->boxArea;

    add_table_tool_option(box, boxLayout);

    QStringList tableHeader;
    tableHeader << "1" << "2";
    myTable* table=new myTable(box);
    table->setColumnCount(2); // Column을 2개로 설정
    table->setRowCount(2);
    table->setHorizontalHeaderLabels(tableHeader); // Table Header 설정

    table->setObjectName("table");
    boxLayout->addWidget(table);

    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    int h = table->horizontalHeader()->height() + 68;
    if(DPI==1.25){
        h+=13;
    }
    else if(DPI==1.5){
        h+=27;
    }
    //헤더 높이 + 툴 버튼 30 + 마진 9씩(툴 18, table 18) 36 + box margin 2 = 68
    for(int i=0;i<table->rowCount();i++){
        h += table->rowHeight(i);
    }
    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800,h);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    boxLayout->setSizeConstraint(QLayout::SetMinimumSize);
    boxLayout->setAlignment(Qt::AlignTop);
    layout->addWidget(box);

    box->setFixedSize(box->width(),h);
}

void Document::add_row(){
    QGroupBox* box = qobject_cast<QGroupBox*>(QObject::sender()->parent());
    QTableWidget* table = box->findChild<QTableWidget*>("table");

    table->setRowCount(table->rowCount()+1);
    table->resizeRowsToContents();

    int h = table->horizontalHeader()->height() + 68;
    if(DPI==1.25){
        h+=13;
    }
    else if(DPI==1.5){
        h+=27;
    }
    //헤더 높이 + 툴 버튼 30 + 마진 9씩(툴 18, table 18) 36 + box margin 2 = 68
    for(int i=0;i<table->rowCount();i++){
        h += table->rowHeight(i);
    }

    box->setFixedSize(box->width(),h);
}

void Document::add_col(){
    QGroupBox* box = qobject_cast<QGroupBox*>(QObject::sender()->parent());
    QTableWidget* table = box->findChild<QTableWidget*>("table");

    QStringList label;
    for(int i=0;i<table->columnCount();i++){
        label<<table->horizontalHeaderItem(i)->text();
    }
    label << QString::number(table->columnCount()+1);
    //QString만 한다고 되는게 아니라 실제 카운트를 늘려주어야한다.
    table->setColumnCount(table->columnCount()+1);
    //headerview는 변경이 안되므로(? 못 찾았으므로) QString으로 set해주어서 변경을 한다.
    table->setHorizontalHeaderLabels(label);

    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    int h = table->horizontalHeader()->height()+68;
    if(DPI==1.25){
        h+=13;
    }
    else if(DPI==1.5){
        h+=27;
    }
    //헤더 높이 + 툴 버튼 30 + 마진 9씩(툴 18, table 18) 36 + box margin 2 = 68
    for(int i=0;i<table->rowCount();i++){
        h += table->rowHeight(i);
    }

    box->setFixedSize(box->width(),h);
}

void Document::add_table_tool_option(QGroupBox* box, QLayout * boxLayout){
    QWidget* toolWidget = new QWidget(box);
    QToolButton* tool = new QToolButton(toolWidget);
    QHBoxLayout* toolLayout = new QHBoxLayout(toolWidget);
    QMenu* Menu = new QMenu();
    QMenu* InputMenu = new QMenu();
    toolLayout->addStretch();
    toolLayout->addWidget(tool, Qt::AlignRight);


    QAction* TBAAddRow = new QAction(Kor("행 추가"), box);
    connect(TBAAddRow, SIGNAL(triggered()), this, SLOT(add_row()));
    TBAAddRow->setStatusTip(Kor("행을 추가합니다."));

    QAction* TBAAddCol = new QAction(Kor("열 추가"), box);
    connect(TBAAddCol, SIGNAL(triggered()), this, SLOT(add_col()));
    TBAAddCol->setStatusTip(Kor("열을 추가합니다."));

    QAction* TBADelete = new QAction(Kor("삭제"), tool);
    TBADelete->setStatusTip(Kor("박스를 삭제합니다."));
    connect(TBADelete, SIGNAL(triggered()), this, SLOT(deleteBox()));

    Menu->addAction(TBAAddRow);
    Menu->addAction(TBAAddCol);
    Menu->addAction(TBADelete);

    tool->setMenu(Menu);
    tool->setPopupMode(QToolButton::InstantPopup);
    toolWidget->setObjectName("tool");
    boxLayout->addWidget(toolWidget);
}
