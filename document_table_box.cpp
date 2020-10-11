#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "doubleclickedwidget.h"
#include <QFile>
#include <QTableWidget>
#include <QHeaderView>

void Document::add_table_box() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("tableBox");
    QLayout* layout = tab->boxArea;

    add_table_tool_option(box, boxLayout);

    QStringList tableHeader;
    tableHeader << "Name" << "Phone Number";
    QTableWidget* table=new QTableWidget(box);
    table->setColumnCount(2); // Column을 2개로 설정
    table->setRowCount(2);
    table->setHorizontalHeaderLabels(tableHeader); // Table Header 설정
    table->setObjectName("table");
    boxLayout->addWidget(table);

    //헤더 수정
    //table->horizontalHeaderItem(0)->setText("Whatever");

    //QTableWidgetItem *header2 = new QTableWidgetItem();
    //header2->setText("Parameter No.");
    //tableWidget->setHorizontalHeaderItem(1,header2);

    //헤더 추가
    //tableWiget->setHorizontalHeaderLabels(QStringList() << "Switch.." << "Parameter...");

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
    table->setColumnCount(table->columnCount()+1);
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
