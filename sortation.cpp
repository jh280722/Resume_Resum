#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortation.h"

QStringList sortations = {Kor("인적 사항"), Kor("학력 사항"), Kor("경력 사항"), Kor("활동 및 수상경력"),
        Kor("자격증"), Kor("프로젝트"), Kor("자기소개서"), Kor("포트폴리오"), Kor("기타")};
int srtRange[11] = {0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

Sortation::Sortation(QWidget *parent)
    : QWidget(parent)
{
    QWidget* srtAreaWidgetContents = parent->findChild<QWidget*>("srtAreaWidgetContents");
    QVBoxLayout* srtAreaLayout = new QVBoxLayout(srtAreaWidgetContents);

    // 구분 탭, 문서 영역 생성
    for (int i=0; i<sortations.length(); i++) {
        QWidget* srt = new QWidget(srtAreaWidgetContents);
        QHBoxLayout* srtLayout = new QHBoxLayout(srt);
        QPushButton* open = new QPushButton(sortations.value(i).prepend(" "), srt);
        QPushButton* add = new QPushButton(srt);

        open->setObjectName("srt"+QString::number(i+1)+"open");
        open->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        open->setStyleSheet("padding-left: 10px; text-align: left; font-family: Malgun Gothic; font-weight: bold; color: white;");
        open->setIcon(QIcon(":/images/plus_white.png"));
        open->setIconSize(QSize(16, 16));
        open->setFlat(true);
        connect(open, SIGNAL(clicked()), this, SLOT(on_srtopen_clicked()));
        add->setObjectName("srt"+QString::number(i+1)+"add");
        add->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        add->setFixedWidth(41);
        add->setIcon(QIcon(":/images/portable-document-format-white.png"));
        add->setIconSize(QSize(16, 16));
        add->setFlat(true);
        connect(add, SIGNAL(clicked()), this, SLOT(on_srtadd_clicked()));

        srtLayout->setSpacing(0);
        srtLayout->setContentsMargins(0, 0, 0, 0);
        srtLayout->addWidget(open);
        srtLayout->addWidget(add);
        srt->setObjectName("srt"+QString::number(i+1));
        srt->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        srt->setFixedHeight(41);
        srt->setStyleSheet("background-color: rgb(44, 62, 80);");
        srt->setLayout(srtLayout);
        srtAreaLayout->addWidget(srt);

        QWidget* empty = new QWidget(srtAreaWidgetContents);

        empty->setObjectName("srt"+QString::number(i+1)+"empty");
        empty->setMinimumHeight(11);
        srtAreaLayout->addWidget(empty);
        empty->hide();

    }

    srtAreaLayout->setSpacing(0);
    srtAreaLayout->setContentsMargins(0, 0, 0, 0);
    srtAreaLayout->setAlignment(Qt::AlignTop);
    srtAreaWidgetContents->setObjectName("srtAreaWidgetContents");
    srtAreaWidgetContents->setLayout(srtAreaLayout);
}

Sortation::~Sortation()
{
    //delete ui;
}

void Sortation::on_srtopen_clicked()
{
    QObject* sel = QObject::sender();
    QPushButton* selBtn = (QPushButton*)sel;
    QWidget* srt = (QWidget*)sel->parent();
    int srtIdx = srt->objectName().remove(0,3).toInt();
    QString emptyName = srt->objectName().append("empty");
    QWidget* empty = srt->parent()->findChild<QWidget*>(emptyName);

    if (empty->isHidden()) {
        selBtn->setIcon(QIcon(":/images/minus_white.png"));
        empty->show();

        for (auto i : docList[srtIdx]) {
            QWidget* doc = i->PBS;
            doc->show();
        }
    }
    else {
        selBtn->setIcon(QIcon(":/images/plus_white.png"));
        empty->hide();
        for (auto i : docList[srtIdx]) {
            QWidget* doc = i->PBS;
            doc->show();
        }
    }
}

void Sortation::on_docopen_clicked() {
    QObject* sel = QObject::sender();
    QPushButton* selPB = (QPushButton*)sel;
    QWidget* selDoc = (QWidget*)sel->parent();
    bool existList = false;
    int tabIdx = -1;
    int srtIdx = -1;
    int subSrtIdx = -1;
    QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");


    for (int i=0; i<9; i++) {
        for(auto it:docList[i]){
            if(it->PBS==selDoc){
                srtIdx = i;
                subSrtIdx=docList[i].indexOf(it);
                break;
            }
        }
        if(srtIdx!=-1)
            break;
    }

    for (int i = 0; i < docTab->count(); ++i) {
        if (selPB->text() == docTab->tabText(i)) {
            existList = true;
            tabIdx = i;
            break;
        }
    }
    if (existList) {
        docTab->setCurrentIndex(tabIdx);
    }
    else {
        QWidget* new_tab = docList[srtIdx][subSrtIdx];

        docTab->tabBar()->setStyleSheet(QString("QTabBar::tab { width:100;; }").arg(100));
        docTab->addTab(new_tab, selPB->text());
        docTab->setCurrentIndex(docTab->count() - 1);
    }
}


void Sortation::on_srtadd_clicked()
{
    bool ok;

    QString docName = QInputDialog::getText(this, Kor("새 문서"), Kor("이름을 입력하세요:"), QLineEdit::Normal, "", &ok);

    if (ok && !docName.isEmpty()) {
        QObject* sel = QObject::sender();
        QWidget* srt = (QWidget*)sel->parent();

        QWidget* srtAreaWidgetContents = srt->parentWidget();
        QVBoxLayout* srtAreaLayout = (QVBoxLayout*)srtAreaWidgetContents->layout();
        QString selOpenName = srt->objectName().append("open");
        QPushButton* selOpen = srt->findChild<QPushButton*>(selOpenName);
        int srtIdx = srt->objectName().remove(0,3).toInt();

        QWidget* newPBS = new QWidget(srtAreaWidgetContents);
        QHBoxLayout* newPBSLayout = new QHBoxLayout(newPBS);
        QPushButton* open = new QPushButton(docName, newPBS);
        QPushButton* active = new QPushButton(newPBS);

        open->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        open->setStyleSheet("padding-left: 20px; text-align: left; font-family: Malgun Gothic; font-size: 12px;");
        open->setFlat(true);
        connect(open, SIGNAL(clicked()), this, SLOT(on_docopen_clicked()));
        active->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        active->setFixedWidth(41);
        active->setFlat(true);
        active->setIconSize(QSize(12, 12));
        connect(active, SIGNAL(clicked()), this, SLOT(on_docactive_clicked()));

        newPBSLayout->setSpacing(0);
        newPBSLayout->setContentsMargins(0, 0, 0, 0);
        newPBSLayout->addWidget(open);
        newPBSLayout->addWidget(active);
        //newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        newPBS->setFixedHeight(31);
        newPBS->setLayout(newPBSLayout);
        srtAreaLayout->insertWidget(srtRange[srtIdx+1]-1, newPBS);
        //srtAreaWidgetContents->layout()->addWidget(newDoc);
        //newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        //버튼 리스트에 추가 | connect 해주기

        Document* newDoc = new Document(nullptr,srtIdx);
        newDoc->PBS=newPBS;
        docList[srtIdx].push_back(newDoc);

        for (int i = srtIdx + 1; i < 11; i++){
            srtRange[i]++;
        }

        QString emptyName = srt->objectName().append("empty");
        QWidget* empty = srt->parent()->findChild<QWidget*>(emptyName);

        if (empty->height() > 0) empty->setFixedHeight(0);
        if (empty->isHidden()) {
            empty->show();
            selOpen->setIcon(QIcon(":/images/minus_white.png"));
        }
    }
}


void Sortation::on_docactive_clicked()
{
    QObject* sel = QObject::sender();
    QPushButton* active = (QPushButton*)sel;

    if (active->icon().isNull()) {
        active->setIcon(QIcon(":/images/dot.png"));
    }
    else {
        active->setIcon(QIcon());
    }

}

void Sortation::delete_tab(int srtIdx) {
    QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");
    QWidget* empty = parent()->findChild<QWidget*>("srt" + QString::number(srtIdx) + "empty");
    docTab->removeTab(docTab->currentIndex());

    for (int i = srtIdx + 1; i < 11; i++){
        srtRange[i]--;
    }
    if (docList[srtIdx].size() == 0) {
        empty->setFixedHeight(11);
    }
}
