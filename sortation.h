#ifndef SORTATION_H
#define SORTATION_H

#include <QWidget>
#include <QInputDialog>
#include <QMouseEvent>
#include <QDrag>
#include <QPainter>
#include <QMimeData>
#include "document.h"

class Sortation : public QWidget
{
    Q_OBJECT

public:
    Sortation(QWidget *parent = nullptr);
    ~Sortation();
    void delete_tab(int srtIdx);
    int srtIdx;
    QVector<Document*> docList[10];
    Document* find_doc(QObject* pbs);
    void paste_doc(QString docName, int srtIdx);

protected:

private slots:
    void on_srtopen_clicked();
    void on_srtadd_clicked();
    void on_docopen_clicked();
    void save_docList();
    void load_docList();
    void save_pdf();


private:
    bool eventFilter(QObject *object, QEvent *event);
    void make_docBtn(QString docName, int srtIdx, int type);
    QString name_check(QString,int);
};
#endif // SORTATION_H
