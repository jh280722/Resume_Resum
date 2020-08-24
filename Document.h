#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include "docTab.h"


class Document : public QWidget
{
    Q_OBJECT

public:
    Document(QWidget* parent, int srtIdx);
    ~Document();
    QWidget* PBS;
    DocTab* tab;
    void add_box();

signals:
public slots:

private slots:
    void save_doc();
    void delete_doc();
    void preview_doc();
    void active_doc_select();

private:
    int srtIdx;
    bool active;
};
#endif // DOCUMENT_H
