#ifndef DOUBLECLICKEDWIDGET_H
#define DOUBLECLICKEDWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QEvent>

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
            delButton->setAutoFillBackground(0);
            delButton->setFlat(0);
            return false;
        }
        else if(ev->type()==QEvent::Leave){
            delButton->setAutoFillBackground(0);
            delButton->setFlat(1);
            return false;
        }
    }
};

class DoubleClickedWidget : public QLabel{
    Q_GADGET
public:
    DoubleClickedWidget(QLabel *parent=nullptr): QLabel(parent){
        this->setText(parent->text());
        this->setMaximumWidth(200);
        this->setFixedWidth(100);
        this->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    };
    ~DoubleClickedWidget(){

    };
public slots:
    void hideText();
signals:
    void doubleClicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        emit doubleClicked();
    }

};

#endif // DOUBLECLICKEDWIDGET_H
