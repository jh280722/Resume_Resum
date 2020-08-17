#ifndef SORTATION_H
#define SORTATION_H

#include <QWidget>
#include <QInputDialog>

class Sortation : public QWidget
{
    Q_OBJECT

public:
    Sortation(QWidget *parent = nullptr);
    ~Sortation();

private slots:
    void on_srtopen_clicked();
    void on_srtadd_clicked();

    void connect_doc();

private:
    int srtIdx;
    QList<QWidgetList> docList;
    QList<QWidgetList> docBtnList;
};
#endif // SORTATION_H
