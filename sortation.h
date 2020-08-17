#ifndef SORTATION_H
#define SORTATION_H

#include <QWidget>
#include <QInputDialog>

extern QVector<QWidget*> docList[9];
extern QVector<QPushButton*> docBtnList[9];

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
    void delete_tab();

private:
    int srtIdx;

    void add_box(QWidget* docTab, int listIdx);
};
#endif // SORTATION_H
