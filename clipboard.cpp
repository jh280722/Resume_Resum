#include "mainwindow.h"
#include "customContextMenu.h"
#include <QApplication>

void contextMenuQPushButton::copy_doc(){
    QObject* sel = QObject::sender();
    QPushButton* openPB = (QPushButton*)sel;
    QObject* PBS=sel->parent()->parent();
    Document* doc = sortation->find_doc(PBS);
    clipBoard.clear();
    clipBoardName=doc->name;
    QObjectList tabList = doc->tab->box->children();
    for(auto it:tabList){
        if(it->objectName()=="boxAreaLayout") continue;
        QObjectList itemList = it->children();
        for(auto item: itemList){
            if(item->objectName()=="groupBoxLayout") {
                clipBoard.push_back(new Data("box"));
                continue;
            }
            if(item->objectName()=="tool") continue;
            QString type=item->objectName();
            QString name="";
            int valueLine=1;
            QString value="";
            QString date="";
            QString stdate="";
            QString eddate="";
            QString path="";
            if(type=="text"){
                name=item->findChild<QLabel*>("QLabel")->text();
                value=item->findChild<QLineEdit*>("QLineEdit")->text();
            }
            else if(type=="textArea"){
                name=item->findChild<QLabel*>("QLabel")->text();
                value=item->findChild<QTextEdit*>("QTextEdit")->toPlainText();
                for(int i=0;i<value.size();i++){
                    if(value[i]=='\n'){
                        valueLine++;
                    }
                }
            }
            else if(type=="image"){
                name=item->findChild<QLabel*>("QLabel")->text();
                path=item->findChild<QLabel*>("path")->text();
            }
            else if(type=="date"){
                name=item->findChild<QLabel*>("QLabel")->text();
                date=item->findChild<QDateEdit*>("QDate")->text();
            }
            else if(type=="period"){
                name=item->findChild<QLabel*>("QLabel")->text();
                stdate=item->findChild<QDateEdit*>("QPeriodSt")->text();
                eddate=item->findChild<QDateEdit*>("QPeriodEd")->text();
            }
            else if(type=="dropDown"){
                name=item->findChild<QLabel*>("QLabel")->text();
            }
            clipBoard.push_back(new Data(type, name, valueLine, value, date,path,stdate,eddate));
        }
    }
}

void contextMenuQPushButton::paste_doc(){
    if(clipBoard.empty())//현재 클립보드가 비어있으면 종료
        return;
    QObject* sel = QObject::sender();
    QWidget* srt = (QWidget*)sel->parent()->parent();
    int srtIdx = srt->objectName().left(1).toInt();
    sortation->paste_doc(clipBoardName,srtIdx);
}

void Sortation::paste_doc(QString docName, int srtIdx){
    QString getName =name_check(docName,srtIdx);

    if (!getName.isEmpty()) {
        make_docBtn(getName, srtIdx, 2);//paste_doc 함수를 실행해서 만듬
    }
}

void contextMenuQPushButton::cut_doc(){

}

void Document::paste_doc(){
    if(tab){
        QObjectList tabList = tab->box->children();
        for(auto it:tabList){
            if(it->objectName()=="boxAreaLayout") continue;
            delete it;
        }
    }
    QVBoxLayout* loadBox;
    for(auto it: clipBoard){
        qDebug()<<it->type;
        qDebug()<<it->name;
        qDebug()<<it->valueLine;
        qDebug()<<it->value;
        qDebug()<<it->path;
        qDebug()<<it->stdate;
        qDebug()<<it->eddate;
        if(it->type=="box"){
            loadBox=load_add_box();
        }
        else if(it->type=="text"){
            AddItemText(loadBox,it->name,it->value);
        }
        else if(it->type=="textArea"){
            AddItemTextarea(loadBox,it->name,it->value);
        }
        else if(it->type=="image"){
            AddItemImage(loadBox,it->name,it->path);
        }
        else if(it->type=="date"){
            AddItemDate(loadBox,it->name,it->date);
        }
        else if(it->type=="period"){
            AddItemPeriod(loadBox,it->name,it->stdate, it->eddate);
        }
        else if(it->type=="dropDown"){//setting value
            AddItemDropdown(loadBox,it->name,it->value);
        }
    }
    save_doc();
}
