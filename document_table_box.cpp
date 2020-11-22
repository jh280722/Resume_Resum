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
class myHeaderView : public QHeaderView{
public:
    QLineEdit* Line;
    int sectionedit;
    QRect edit_geometry;
    myHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr) : QHeaderView(orientation,parent){
        setSectionsMovable(1);
        setSectionsClickable(1);
        // This block sets up the edit line by making setting the parent
        // to the Headers Viewport.
        Line = new QLineEdit(viewport());  //#Create
        Line->setAlignment(Qt::AlignTop); //# Set the Alignmnet
        Line->setHidden(1);// # Hide it till its needed
        // This is needed because I am having a werid issue that I believe has
        //# to do with it losing focus after editing is done.
        Line->blockSignals(1);
        sectionedit = 0;
        //# Connects to double click

        connect(this, &QHeaderView::sectionDoubleClicked,this,&myHeaderView::editHeader);
        connect(Line, &QLineEdit::editingFinished,this,&myHeaderView::doneEditing);
    }

    void doneEditing(){
        // This block signals needs to happen first otherwise I have lose focus
        // problems again when there are no rows
        Line->blockSignals(true);
        Line->setHidden(true);

        QString newname = Line->text();
        QString oldname = model()->headerData(sectionedit,Qt::Horizontal,Qt::DisplayRole).toString();

        qDebug()<<model()->setHeaderData(sectionedit,Qt::Horizontal, QObject::tr("ID"),Qt::EditRole);
        //setItemDelegateForColumn(sectionedit,)
        //self.model().dataset.changeFieldName(oldname, newname)
        Line->setText("");
        setCurrentIndex(QModelIndex());
    }

    void editHeader(int section){
        //# This block sets up the geometry for the line edit
        edit_geometry = Line->geometry();
        edit_geometry.setWidth(sectionSize(section));
        edit_geometry.moveLeft(sectionViewportPosition(section));
        Line->setGeometry(edit_geometry);

        QString title = model()->headerData(section,Qt::Horizontal,Qt::DisplayRole).toString();
        Line->setText(title);

        Line->setHidden(false);// # Make it visiable
        Line->blockSignals(false);// # Let it send signals
        Line->setFocus();
        Line->selectAll();
        sectionedit = section;
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
    tableHeader << "Name" << "Phone Number";
    QTableWidget* table=new QTableWidget(box);
    table->setColumnCount(2); // Column을 2개로 설정
    table->setRowCount(2);
    //table->setHorizontalHeaderLabels(tableHeader); // Table Header 설정
    table->setHorizontalHeader(new myHeaderView(Qt::Horizontal));
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
    qDebug()<<1;
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
