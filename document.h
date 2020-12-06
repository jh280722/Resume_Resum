#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QToolButton>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include <QSplitter>
#include "doctab.h"
#include "data.h"


class Document : public QWidget
{
    Q_OBJECT

public:
    Document(QString name, int srtIdx, bool load=0);
    ~Document();
    QString name;
    QString docPath;
    QWidget* PBS;
    DocTab* tab;
    void init_docTab(bool load);
    QVBoxLayout* load_add_box();
    QString get_html(); //pdf로 변환할 html 추출 함수

    bool getActive();
    void setActive(bool val);
    int getSrtIdx();
    void setSrtIdx(int val);

private:
    void add_tool_option(QGroupBox* box, QLayout * boxLayout);
    void add_table_tool_option(QGroupBox* box, QLayout * boxLayout);

signals:
public slots:
    void save_doc();
    void load_doc();
    void active_doc_select();

private slots:
    void delete_doc();
    void preview_doc();

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
    void AddItemPeriod();
    void AddItemDropdown();
    void deleteItem();
    void AddItemText(QLayout*,QString,QString);
    void AddItemTextarea(QLayout*,QString,QString);
    void AddItemImage(QLayout*,QString,QString);
    void AddItemDate(QLayout*,QString,QString);
    void AddItemDropdown(QLayout*,QString,QString);
    void AddItemPeriod(QLayout*,QString,QString,QString);

    //table
    void add_table_box();
    void add_row();
    void add_col();
private:
    int srtIdx;
    bool active;
    QVector<Data*> dataList;
};
#endif // DOCUMENT_H
