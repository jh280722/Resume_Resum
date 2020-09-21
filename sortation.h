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

protected:
    //void dragEnterEvent(QDragEnterEvent *event) override;
    //void dragLeaveEvent(QDragLeaveEvent *event) override;
    //void dragMoveEvent(QDragMoveEvent *event) override;
    //void dropEvent(QDropEvent *event) override;

private slots:
    void on_srtopen_clicked();
    void on_srtadd_clicked();
    void on_srtadd_clicked(QString docName, int srtIdx);
    void on_docopen_clicked();
    void on_docactive_clicked();
    void save_docList();
    void load_docList();
    void save_pdf();

private:
    bool eventFilter(QObject *object, QEvent *event);
};
#endif // SORTATION_H
