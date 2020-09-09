#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "doctab.h"
#include "data.h"


class Document : public QWidget
{
    Q_OBJECT

public:
    Document(QString name, int srtIdx);
    ~Document();
    QString name;
    QWidget* PBS;
    DocTab* tab;
    void add_box();
    QVBoxLayout* load_add_box();

signals:
public slots:
    void save_doc();
    void load_doc();

private slots:
    void delete_doc();
    void preview_doc();
    void active_doc_select();

    //box
    void make_doc0();
    void make_doc1();
    void make_doc2();
    void make_doc3();
    void make_doc4();
    void make_doc5();
    void make_doc6();
    void make_doc7();
    void make_doc8();
    void deleteBox();

    //item
    void imageUpload();
    void AddItemText();
    void AddItemTextarea();
    void AddItemImage();
    void AddItemDate();
    void AddItemDropdown();
    void deleteItem();
    void AddItemText(QVBoxLayout*,QString,QString);
    void AddItemTextarea(QVBoxLayout*,QString,QString);
    void AddItemImage(QVBoxLayout*,QString,QString);
    void AddItemDate(QVBoxLayout*,QString,QString);
    void AddItemDropdown(QVBoxLayout*,QString,QString);
    void deletetext();

private:
    int srtIdx;
    bool active;
    QVector<Data*> dataList;
};
#endif // DOCUMENT_H
