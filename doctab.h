#ifndef DOCTAB_H
#define DOCTAB_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include <QScrollArea>
#include <QLabel>

class DocTab : public QWidget
{
    Q_OBJECT

public:
    DocTab(QWidget* parent, int srtIdx);
    ~DocTab();
    QVBoxLayout* VBox;
    QScrollArea* SA;
signals:
public slots:
    void make_doc0();
    void make_doc1();
    void make_doc2();
    void make_doc3();
    void make_doc4();
    void make_doc5();
    void make_doc6();
    void make_doc7();
    void make_doc8();
    void deleteItem();
    void imageUpload();
    void deleteBox();
    void AddItemText();
    void AddItemTextarea();
    void AddItemImage();
    void AddItemDate();
    void AddItemDropdown();

private slots:

private:
    int srtIdx;
};


#endif // DOCTAB_H
