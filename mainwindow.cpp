#include "mainwindow.h"
#include "Document.h"
#include "sortation.h"
#include "ui_mainwindow.h"

QString srtTitle[9]={Kor("인적 사항"), Kor("학력 사항"),Kor("경력 사항"),Kor("활동 및 수상 경력"),
                     Kor("자격증"),Kor("프로젝트"),Kor("자기소개서"),Kor("포트폴리오"), Kor("기타")};

QSet<QWidget*> docList2[9];
QVector<QWidget*> docList[9];
QVector<QPushButton*> docBtnList[9];
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Sortation *sortation = new Sortation(ui->centralwidget);
    //    int w=ui->intro->width();
    //    int h=ui->intro->height();
    //    QPixmap pix(":/img/Start.png");
    //ui->intro->setPixmap(pix);
    //ui->intro->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

//    QMenu *pFileMenu;
//    QAction *pSlotNewFile = new QAction(Kor("저장"), this);
//    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
//    pSlotNewFile->setStatusTip(Kor("수정사항을 저장합니다."));
//    //connect(pSlotNewFile, SIGNAL(triggered()), this, SLOT(Main_SlotTest1()));
//    pFileMenu = menuBar()->addMenu(Kor("파일"));
//    pFileMenu->addAction(pSlotNewFile); // 테스트


//    ui->docTab->setTabsClosable(true);
//    connect(ui->docTab, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));
//    for(int i=0;i<9;i++){
//        docNum[i]=0;
//        srtInit(i);
//    }

    //    this->setStyleSheet("#pushButton:hover { background-color: red; "
    //                        "border-style: outset; border-width: 2px;border-radius: 10px; border-color: beige;"
    //                        "font: bold 14px;min-width: 10em;padding: 6px; }");
}

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


void MainWindow::on_plus_clicked() {
    QObject* sel = QObject::sender();
    QString name;
    QWidget* menu = 0;
    for(int i=0;i<9;i++){
        if(sel==srtPlusBtn[i]){
            srtIdx = i;
            name = srtTitle[srtIdx] + QString::number(++docNum[srtIdx]);
            menu = ui->srtArea->findChild<QWidget*>("srt"+QString::number(srtIdx));
            break;
        }
    }
    int sz=docBtnList[srtIdx].size();

    srtPlusBtn[srtIdx]->setText(name);
    disconnect(sel, SIGNAL(clicked()), this, SLOT(on_plus_clicked()));

    docBtnList[srtIdx].push_back(new_button("plusButton" + QString::number(srtIdx), Kor("항목추가")));
    srtPlusBtn[srtIdx] = docBtnList[srtIdx][sz];
    menu->layout()->addWidget(docBtnList[srtIdx][sz]);

    QWidget* new_tab = new QWidget();
    add_box(new_tab, sz-1);
    docList[srtIdx].push_back(new_tab);
    connect(docBtnList[srtIdx][sz], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    connect(docBtnList[srtIdx][sz], SIGNAL(clicked()), this, SLOT(connect_doc()));

}

void MainWindow::srtInit(int srtIdx) {
    QWidget* menu = 0;

    menu = ui->srtArea->findChild<QWidget*>("srt"+QString::number(srtIdx));

    int sz=docBtnList[srtIdx].size();
    docBtnList[srtIdx].push_back(new_button("plusButton" + QString::number(srtIdx), Kor("항목추가")));

    srtPlusBtn[srtIdx] = docBtnList[srtIdx][sz];
    menu->layout()->addWidget(docBtnList[srtIdx][sz]);
    menu->layout()->setAlignment(Qt::AlignTop);

    connect(docBtnList[srtIdx][sz], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    connect(docBtnList[srtIdx][sz], SIGNAL(clicked()), this, SLOT(connect_doc()));
}

void MainWindow::connect_doc() {
    QObject* sel = QObject::sender();
    bool existList = false;
    int tmpIdx = -1;
    int subSrtIdx = -1;


    for(int j=0;j<9;j++){
        bool ok=0;
        for (int i = 0; i < docBtnList[j].size(); ++i) {
            if (docBtnList[j][i] == sel) {
                srtIdx = j;
                subSrtIdx = i;
                ok=1;
                break;
            }
        }
        if(ok)
            break;
    }
    for (int i = 0; i < ui->docTab->count(); ++i) {
        if (docBtnList[srtIdx][subSrtIdx]->text() == ui->docTab->tabText(i)) {
            existList = true;
            tmpIdx = i;
            break;
        }
    }
    if (existList) {
        ui->docTab->setCurrentIndex(tmpIdx);
    }
    else {
        pBtn = docBtnList[srtIdx][subSrtIdx];
        add_docTab(subSrtIdx);
        ui->docTab->setCurrentIndex(ui->docTab->count() - 1);
    }
}

void MainWindow::deleteTab() {
    ui->docTab->removeTab(ui->docTab->currentIndex());
}

void MainWindow::on_docTab_deleteTab(int idx) {
    ui->docTab->removeTab(idx);
}
void MainWindow::add_docTab(int subSrtIdx) {
    QWidget* new_tab = docList[srtIdx][subSrtIdx];
    ui->docTab->addTab(new_tab, pBtn->text());
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    srtIdx = index-1;
}
