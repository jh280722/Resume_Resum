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
	void on_srt0_clicked();
	void on_srt1_clicked();
	void on_srt2_clicked();
	void connect_doc();
	void on_docTab_deleteTab(int);

    void on_toolBox_currentChanged(int index);

private:
	//UI
	Ui::MainWindow* ui;

    int srtIdx = -1;

    //QPLIST
	int docNum[3];
	QPushButton* srtPlusBtn[3];
	QPushButton* new_button(QString name, QString str);
	QList<QPushButton*> docBtnList[3];
	void hide_show_doc(int idx, int& flg);

    //TABLIST
	QPushButton* pBtn;
	QList<QWidget*> docList[3];
	void add_box(QWidget* docTab);
	void add_docTab(int);
};


#endif // MAINWINDOW_H
