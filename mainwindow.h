#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QCoreApplication>
#include <QTextStream>
#include <QPixmap>
#include <QPushButton>
#include <QList>
#include <QObject>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QScrollArea>
#include <QAbstractScrollArea>
#include <QFormLayout>
#include <QSpacerItem>
#include <QToolButton>
#include <QToolBar>
#include <QMenu>
#include <QDateEdit>
#include <QFileDialog>
#include <QComboBox>
#include <QTextEdit>
#include <QMessageBox>
#include "document.h"
#define Kor(str) QString::fromLocal8Bit(str)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern QString srtTitle[9];
extern QString AppPath;
extern QString srtPath;
extern float DPI;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

signals:
private slots:
    void on_docTab_deleteTab(int);

private:
    //UI
    Ui::MainWindow* ui;

    int srtIdx = -1;
    //QPLIST
    QPushButton* new_button(QString name, QString str);

    //TABLIST
    QPushButton* pBtn;
    void add_box(QWidget* docTab, int listIdx);

};

#endif // MAINWINDOW_H
