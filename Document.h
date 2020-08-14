#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

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
private slots:

private:
};
#endif // DOCUMENT_H
