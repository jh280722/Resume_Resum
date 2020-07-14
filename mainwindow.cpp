#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    docNum[0] = docNum[1] = docNum[2] = 0;
        int w=ui->intro->width();
        int h=ui->intro->height();
       QPixmap pix(":/img/Start.png");
        ui->intro->setPixmap(pix);
        ui->intro->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    QMenu *pFileMenu;
    QAction *pSlotNewFile = new QAction(Kor("저장"), this);
    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
    pSlotNewFile->setStatusTip(Kor("수정사항을 저장합니다."));
    connect(pSlotNewFile, SIGNAL(triggered()), this, SLOT(Main_SlotTest1()));
    pFileMenu = menuBar()->addMenu(Kor("파일"));
    pFileMenu->addAction(pSlotNewFile); // 테스트


    ui->docTab->setTabsClosable(true);
    connect(ui->docTab, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));
    QString s="srtBox";
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

void MainWindow::add_box(QWidget* docTab) {
    QWidget* widget = docTab;
    QVBoxLayout* layout = new QVBoxLayout(widget);

    widget->setLayout(layout);

    QGroupBox* box = new QGroupBox(Kor("기본 정보"), widget);
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    layout->addWidget(box);

    QWidget* nameWidget = new QWidget(box);
    QWidget* ageWidget = new QWidget(box);
    QWidget* addressWidget = new QWidget(box);

    boxLayout->addWidget(nameWidget);
    boxLayout->addWidget(ageWidget);
    boxLayout->addWidget(addressWidget);

    QHBoxLayout* nameLayout = new QHBoxLayout(nameWidget);
    nameLayout->addWidget(new QLabel(Kor("이 름 :")));
    nameLayout->addWidget(new QLineEdit(nameWidget));


    QHBoxLayout* ageLayout = new QHBoxLayout(ageWidget);
    ageLayout->addWidget(new QLabel(Kor("나 이 :")));
    ageLayout->addWidget(new QLineEdit(ageWidget));

    QHBoxLayout* addressLayout = new QHBoxLayout(addressWidget);
    addressLayout->addWidget(new QLabel(Kor("주 소 :")));
    addressLayout->addWidget(new QLineEdit(addressWidget));


    QWidget* validateWidget = new QWidget(widget);
    QHBoxLayout* validateLayout = new QHBoxLayout(validateWidget);
    validateLayout->addWidget(new QPushButton(Kor("확 인"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("리 셋"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("취 소"), validateWidget));
    layout->addWidget(validateWidget);
}


void MainWindow::on_plus_clicked() {
    QObject* sel = QObject::sender();
    QString name;
    QWidget* menu = 0;
    if (sel == srtPlusBtn[0]) {
        srtIdx = 0;
        name = Kor("기본 정보 ") + QString::number(docNum[srtIdx]);
        menu = ui->srt0;
    }
    else if (sel == srtPlusBtn[1]) {
        srtIdx = 1;
        name = Kor("인적 사항 ") + QString::number(docNum[srtIdx]);
        menu = ui->srt1;
    }
    else if (sel == srtPlusBtn[2]) {
        srtIdx = 2;
        name = Kor("자 소 서 ") + QString::number(docNum[srtIdx]);
        menu = ui->srt2;
    }
    srtPlusBtn[srtIdx]->setText(name);
    disconnect(srtPlusBtn[srtIdx], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    docBtnList[srtIdx].push_back(new_button("dm" + QString::number(srtIdx) + "_" + QString::number(docNum[srtIdx]), Kor("항목추가")));
    srtPlusBtn[srtIdx] = docBtnList[srtIdx][docNum[srtIdx]];
    menu->layout()->addWidget(docBtnList[srtIdx][docNum[srtIdx]]);
    QWidget* new_tab = new QWidget;
    add_box(new_tab);
    docList[srtIdx].push_back(new_tab);
    connect(docBtnList[srtIdx][docNum[srtIdx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    connect(docBtnList[srtIdx][docNum[srtIdx]++], SIGNAL(clicked()), this, SLOT(connect_doc()));
}

void MainWindow::hide_show_doc(int srtIdx, int& flg) {
    QWidget* menu = 0;
    if (srtIdx == 0)
        menu = ui->srt0;
    else if (srtIdx == 1)
        menu = ui->srt1;
    else if (srtIdx == 2)
        menu = ui->srt2;

    if (flg == 0) {
        flg = 2;
        docBtnList[srtIdx].push_back(new_button("dm" + QString::number(srtIdx) + "_" + QString::number(docNum[srtIdx]),
            Kor("항목추가")));
        srtPlusBtn[srtIdx] = docBtnList[srtIdx][docNum[srtIdx]];
        menu->layout()->addWidget(docBtnList[srtIdx][docNum[srtIdx]]);

        connect(docBtnList[srtIdx][docNum[srtIdx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        connect(docBtnList[srtIdx][docNum[srtIdx]++], SIGNAL(clicked()), this, SLOT(connect_doc()));
    }
    else if (flg == 1) {
        flg = 2;
        for (int i = 0; i < docNum[srtIdx]; i++)
        {
            docBtnList[srtIdx][i]->show();
        }
    }
    else if (flg == 2) {
        flg = 1;
        for (int i = 0; i < docNum[srtIdx]; i++)
        {
            docBtnList[srtIdx][i]->hide();
        }
    }
}

void MainWindow::connect_doc() {
    QObject* sel = QObject::sender();
    bool existList = false;
    int tmpIdx = -1;
    int subSrtIdx = -1;


    for (int i = 0; i < docBtnList[0].size(); ++i) {
        if (docBtnList[0][i] == sel) {
            srtIdx = 0;
            subSrtIdx = i;
        }
    }
    for (int i = 0; i < docBtnList[1].size(); ++i) {
        if (docBtnList[1][i] == sel) {
            srtIdx = 1;
            subSrtIdx = i;
        }
    }
    for (int i = 0; i < docBtnList[2].size(); ++i) {
        if (docBtnList[2][i] == sel) {
            srtIdx = 2;
            subSrtIdx = i;
        }
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

void MainWindow::on_docTab_deleteTab(int idx) {
    ui->docTab->removeTab(idx);
}
void MainWindow::add_docTab(int subSrtIdx) {
    QWidget* new_tab = docList[srtIdx][subSrtIdx];
    ui->docTab->addTab(new_tab, pBtn->text());
}


void MainWindow::on_srt0_clicked()
{
    static int flg = 0;
    srtIdx = 0;
    hide_show_doc(srtIdx, flg);
}

void MainWindow::on_srt1_clicked()
{
    static int flg = 0;
    srtIdx = 1;
    hide_show_doc(srtIdx, flg);
}

void MainWindow::on_srt2_clicked()
{
    static int flg = 0;
    srtIdx = 2;
    hide_show_doc(srtIdx, flg);
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    static int flg = 0;
    srtIdx = index-1;
    hide_show_doc(srtIdx, flg);
}
