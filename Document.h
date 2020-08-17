#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include <QScrollArea>

class Document : public QWidget
{
    Q_OBJECT

public:
    Document(QWidget* parent, int srtIdx, int listIdx);
    ~Document();
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
    void deleteBox();
    void AddItemText();
    void AddItemTextarea();
    void AddItemImage();
    void AddItemDate();
    void AddItemDropdown();
private slots:
    void save_doc();
    void delete_doc();
    void preview_doc();
    void active_doc_select();

private:
    int srtIdx,listIdx;
};
#endif // DOCUMENT_H
