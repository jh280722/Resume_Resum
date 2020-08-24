#ifndef SORTATION_H
#define SORTATION_H

#include <QWidget>
#include <QInputDialog>
#include "Document.h"

class Sortation : public QWidget
{
    Q_OBJECT

public:
    Sortation(QWidget *parent = nullptr);
    ~Sortation();
    void delete_tab(int srtIdx);
    int srtIdx;
    QVector<Document*> docList[9];

private slots:
    void on_srtopen_clicked();
    void on_srtadd_clicked();
    void on_docopen_clicked();
    void on_docactive_clicked();

private:

};
#endif // SORTATION_H
