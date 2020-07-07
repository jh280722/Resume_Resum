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
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

signals:
private slots:
	void on_plus_clicked();
	void on_dm0_clicked();
	void on_dm1_clicked();
	void on_dm2_clicked();
	void connect_subTopic();
	void on_Tb1_deleteTab(int);
	void on_Tb1_addTab(int subTopicIdx);

private:
	//UI
	Ui::MainWindow* ui;

    int TopicIdx = -1;

    //QPLIST
	int num[3];
	QPushButton* mb[3];
	QPushButton* new_button(QString name, QString str);
	QList<QPushButton*> PBList[3];
	void hide_show(int idx, int& flg);

    //TABLIST
	QPushButton* mbt;
	QList<QWidget*> TList[3];
	void make_tab(QWidget* Tab);

};


#endif // MAINWINDOW_H
