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
    QVBoxLayout* VLayout;
    QVBoxLayout* boxArea;
    QScrollArea* SA;
    QWidget* box;
signals:
public slots:

private slots:

private:
    int srtIdx;
};


#endif // DOCTAB_H
