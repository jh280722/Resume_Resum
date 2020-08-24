#include "mainwindow.h"
#include "Document.h"
#include "sortation.h"
#include "ui_mainwindow.h"

QString srtTitle[9]={Kor("인적 사항"), Kor("학력 사항"),Kor("경력 사항"),Kor("활동 및 수상 경력"),
                     Kor("자격증"),Kor("프로젝트"),Kor("자기소개서"),Kor("포트폴리오"), Kor("기타")};

QVector<QWidget*> docList[9];
QVector<QPushButton*> docBtnList[9];
Sortation *sortation;
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sortation = new Sortation(ui->centralwidget);
    //    int w=ui->intro->width();
    //    int h=ui->intro->height();
    //    QPixmap pix(":/img/Start.png");
    //ui->intro->setPixmap(pix);
    //ui->intro->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QMenu *pFileMenu;
    QAction *pSlotNewFile = new QAction(Kor("저장"), this);
    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
    pSlotNewFile->setStatusTip(Kor("수정사항을 저장합니다."));
    connect(pSlotNewFile, SIGNAL(triggered()), this, SLOT(Main_SlotTest1()));
    pFileMenu = menuBar()->addMenu(Kor("파일"));
    pFileMenu->addAction(pSlotNewFile); // 테스트

//    docTab1= new TabWidget(ui->docTab);
//    docTab1->setObjectName("docTab");
//    docTab1->setTabsClosable(true);
    ui->docTab->setTabsClosable(true);
//    connect(docTab1, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));
    connect(ui->docTab, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));

    //    this->setStyleSheet("#pushButton:hover { background-color: red; "
    //                        "border-style: outset; border-width: 2px;border-radius: 10px; border-color: beige;"
    //                        "font: bold 14px;min-width: 10em;padding: 6px; }");
}

//void MainWindow::Main_SlotTest1(){
//    QString fileName = QFileDialog::getSaveFileName(this,
//                                                    tr("Resume Resume"), "",
//                                                    tr("ReRe (*.rr);;All Files (*)"));

//    if(fileName.isEmpty())return;
//    else{
//        QFile file(fileName);
//        if(!file.open(QIODevice::WriteOnly)){           return;
//        }
//        QDataStream in(&file);
//        //in.setVersion(QDataStream::Qt_5_14);

//    }


//}

MainWindow::~MainWindow()
{
    delete ui;

}

QPushButton* MainWindow::new_button(QString name, QString str)
{
    QPushButton* button = new QPushButton(str);
    button->setObjectName(name);
    return button;
}


void MainWindow::on_docTab_deleteTab(int idx) {
    ui->docTab->removeTab(idx);
}
