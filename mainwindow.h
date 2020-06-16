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
#define Kor(str) QString::fromLocal8Bit(str)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
private slots:
    void on_plus_clicked();
    void on_dm0_clicked();
    void on_dm1_clicked();
    void on_dm2_clicked();
    void connect_subTopic();
    void on_Tb1_deleteTab();
    void on_Tb1_addTab();

private:
    Ui::MainWindow *ui;
    int idx=0;
    QPushButton *mb[3];
    int num[3];
    QList<QPushButton*> list[3];
    QPushButton* new_button(QString name, QString str);
    void make_tab(QWidget* Tab);
    void hide_show(int idx, int flg);
};


#endif // MAINWINDOW_H
