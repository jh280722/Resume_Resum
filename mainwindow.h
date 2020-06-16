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

private:
    Ui::MainWindow *ui;
    QPushButton *mb[3];
    int num[3];
    QList<QPushButton*> list[3];
    QPushButton* newButton(QString name, QString str);
    void makeTab(QWidget* Tab);
};


#endif // MAINWINDOW_H
