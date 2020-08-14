#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>

class Document : public QWidget
{
    Q_OBJECT

public:
    Document(QWidget* parent = nullptr);
    ~Document();
    void init();
    QVBoxLayout* VBox;

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
private slots:

private:
};
#endif // DOCUMENT_H
