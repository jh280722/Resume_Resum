#ifndef CUSTOMCONTEXTMENU_H
#define CUSTOMCONTEXTMENU_H
#include <QWidget>
#include <QPushButton>

class contextMenuQPushButton : public QPushButton{

public:
    contextMenuQPushButton(QString name,QWidget *p=nullptr): QPushButton(name,p){
        this->setObjectName(name);
        this->setParent(p);
    };
    ~contextMenuQPushButton(){

    };
public slots:
    void showSrtContextMenu(const QPoint &);
    void showDocBtnContextMenu(const QPoint &);

};




#endif // CUSTOMCONTEXTMENU_H
