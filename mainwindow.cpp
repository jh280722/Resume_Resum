#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"

QString srtTitle[9]={Kor("인적 사항"), Kor("학력 사항"),Kor("경력 사항"),Kor("활동 및 수상 경력"),
                     Kor("자격증"),Kor("프로젝트"),Kor("자기소개서"),Kor("포트폴리오"), Kor("기타")};

QVector<QWidget*> docList[9];
QVector<QPushButton*> docBtnList[9];
Sortation *sortation;
QString AppPath=QApplication::applicationDirPath();
QString srtPath = AppPath+"/Data/Srt";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AppPath=QApplication::applicationDirPath();
    srtPath = AppPath+"/Data/Srt";

    ui->startImg->setStyleSheet("background-color: rgb(158, 158, 158)");
    sortation = new Sortation(ui->centralwidget);
    sortation->hide();
    ui->docTab->hide();

    QMenu *pFileMenu;
    QAction *pSlotNewFile = new QAction(Kor("저장"), this);
    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
    pSlotNewFile->setStatusTip(Kor("수정사항을 저장합니다."));
    connect(pSlotNewFile, SIGNAL(triggered()), sortation, SLOT(save_docList()));
    pFileMenu = menuBar()->addMenu(Kor("파일"));
    pFileMenu->addAction(pSlotNewFile); // 저장 옵션

    pSlotNewFile = new QAction(Kor("다른 이름으로 저장"), this);
    pSlotNewFile->setShortcut(Kor("Ctrl+Shift+S"));
    pSlotNewFile->setStatusTip(Kor("다른 이름으로 저장합니다."));
    connect(pSlotNewFile, SIGNAL(triggered()), sortation, SLOT(save_pdf()));
    pFileMenu->addAction(pSlotNewFile); // pdf 저장

    ui->docTab->setTabsClosable(true);
    connect(ui->docTab, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));

    //    this->setStyleSheet("#pushButton:hover { background-color: red; "
    //                        "border-style: outset; border-width: 2px;border-radius: 10px; border-color: beige;"
    //                        "font: bold 14px;min-width: 10em;padding: 6px; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_docTab_deleteTab(int idx) {
    ui->docTab->removeTab(idx);
    if (ui->docTab->count() == 0) {
        ui->docTab->hide();
        ui->startImg->show();
    }
}
