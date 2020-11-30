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
extern int imgIdx;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    //UI
    Ui::MainWindow* ui;
private slots:
    void on_docTab_deleteTab(int);
};

#endif // MAINWINDOW_H
