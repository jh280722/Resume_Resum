#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortation.h"

Sortation::Sortation(QWidget *parent)
    : QWidget(parent)
{
    QStringList sortations = {Kor("인적 사항"), Kor("학력 사항"), Kor("경력 사항"), Kor("활동 및 수상경력"),
            Kor("자격증"), Kor("프로젝트"), Kor("자기소개서"), Kor("포트폴리오"), Kor("기타")};

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


        QWidget* docList = new QWidget(srtAreaWidgetContents);
        QVBoxLayout* docListLayout = new QVBoxLayout(docList);

        docListLayout->setSpacing(0);
        docListLayout->setContentsMargins(0, 0, 0, 0);
        docList->setObjectName("srt"+QString::number(i+1)+"docList");
        //docList->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        docList->setMinimumHeight(11);
        docList->setLayout(docListLayout);
        srtAreaLayout->addWidget(docList);
        docList->hide();

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
    QString docListName = srt->objectName().append("docList");
    QWidget* docList = srt->parent()->findChild<QWidget*>(docListName);

    if (docList->isHidden()) {
        selBtn->setIcon(QIcon(":/images/minus_white.png"));
        docList->show();
    }
    else {
        selBtn->setIcon(QIcon(":/images/plus_white.png"));
        docList->hide();
    }
}


void Sortation::connect_doc() {
    QWidget* sel = (QWidget*)QObject::sender();
    bool existList = false;
    int tabIdx = -1;
    int subSrtIdx = -1;
    QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");

    QPushButton *selPB=(QPushButton*)(QObject::sender());

    subSrtIdx= docBtnList[srtIdx].indexOf(sel);
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
        QString openName = srt->objectName().append("open");
        QString docListName = srt->objectName().append("docList");
        QPushButton* open = srt->findChild<QPushButton*>(openName);
        QWidget* docList = srt->parent()->findChild<QWidget*>(docListName);
        QPushButton* newDoc = new QPushButton(docName, docList);
        newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        newDoc->setFixedHeight(31);
        newDoc->setStyleSheet("padding-left: 20px; text-align: left; font-family: Malgun Gothic; font-size: 12px;");
        newDoc->setFlat(true);
        docList->layout()->addWidget(newDoc);

        //버튼 리스트에 추가 | connect 해주기
        connect(newDoc, SIGNAL(clicked()), this, SLOT(connect_doc()));

        if (docList->height() < 31) {
            docList->setFixedHeight(31);
        }
        else {
            docList->setFixedHeight(docList->height()+30);
        }

        if (docList->isHidden()) {
            open->setIcon(QIcon(":/images/minus_white.png"));
            docList->show();
        }
    }
}
