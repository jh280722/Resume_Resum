#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortation.h"
#include "customContextMenu.h"
QStringList sortations = {Kor("인적 사항"), Kor("학력 사항"), Kor("경력 사항"), Kor("활동 및 수상경력"),
                          Kor("자격증"), Kor("프로젝트"), Kor("자기소개서"), Kor("포트폴리오"), Kor("기타")};
int srtRange[11] = {0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

Sortation::Sortation(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    QWidget* srtAreaWidgetContents = parent->findChild<QWidget*>("srtAreaWidgetContents");
    QVBoxLayout* srtAreaLayout = new QVBoxLayout(srtAreaWidgetContents);

    // 구분 탭, 문서 영역 생성
    for (int i=0; i<sortations.length(); i++) {
        QWidget* srt = new QWidget(srtAreaWidgetContents);
        QHBoxLayout* srtLayout = new QHBoxLayout(srt);
//        QPushButton* temp = new QPushButton(sortations.value(i).prepend(" "), srt);
//        contextMenuQPushButton* open = static_cast<contextMenuQPushButton*>(temp);
        contextMenuQPushButton* open = new contextMenuQPushButton(sortations.value(i).prepend(" "), srt);
        QPushButton* add = new QPushButton(srt);

        open->setObjectName("srt"+QString::number(i+1)+"open");
        open->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        open->setStyleSheet("padding-left: 10px; text-align: left; font-family: Malgun Gothic; font-weight: bold; color: white;");
        open->setIcon(QIcon(":/images/plus_white.png"));
        open->setIconSize(QSize(16, 16));
        open->setFlat(true);
        open->setAcceptDrops(true); //hahahahahaha
        open->installEventFilter(this);
        connect(open, SIGNAL(clicked()), this, SLOT(on_srtopen_clicked()));
        open->setContextMenuPolicy(Qt::CustomContextMenu);//팝업메뉴 생성가능 정책
        connect(open,&QLineEdit::customContextMenuRequested,open,&contextMenuQPushButton::showSrtContextMenu);//팝업메뉴 커넥트

        add->setObjectName("srt"+QString::number(i+1)+"add");
        add->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        add->setFixedWidth(41);
        add->setIcon(QIcon(":/images/portable-document-format-white.png"));
        add->setIconSize(QSize(16, 16));
        add->setFlat(true);
        add->setAcceptDrops(true); //hahahahahaha
        add->installEventFilter(this);
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
        //srt->installEventFilter(this);
        srtAreaLayout->addWidget(srt);

        QWidget* empty = new QWidget(srtAreaWidgetContents);

        empty->setObjectName("srt"+QString::number(i+1)+"empty");
        empty->setMinimumHeight(11);
        empty->setAcceptDrops(true);
        empty->installEventFilter(this);
        srtAreaLayout->addWidget(empty);
        empty->hide();

    }

    srtAreaLayout->setSpacing(0);
    srtAreaLayout->setContentsMargins(0, 0, 0, 0);
    srtAreaLayout->setAlignment(Qt::AlignTop);
    srtAreaWidgetContents->setObjectName("srtAreaWidgetContents");
    srtAreaWidgetContents->setLayout(srtAreaLayout);

    load_docList();
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
    int srtIdx = srt->objectName().mid(3).toInt();
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
            doc->hide();
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
    QWidget* startImg=parent()->findChild<QWidget*>("startImg");


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
        if (QString::number(srtIdx)+'_'+ selPB->text() == docTab->tabText(i)) {
            existList = true;
            tabIdx = i;
            break;
        }
    }
    if (existList) {
        docTab->setCurrentIndex(tabIdx);
    }
    else {
        docList[srtIdx][subSrtIdx]->load_doc();
        QWidget* new_tab = docList[srtIdx][subSrtIdx];

        startImg->hide();
        docTab->show();
        docTab->tabBar()->setStyleSheet(QString("QTabBar::tab { width:100; }"));
        docTab->addTab(new_tab, QString::number(srtIdx)+'_'+ selPB->text());
        docTab->setCurrentIndex(docTab->count() - 1);
    }
}

QString Sortation:: name_check(QString docName,int srtIdx){
    QStringList currentNameList;
    for (auto i : docList[srtIdx]) {
        QPushButton* docOpen = i->PBS->findChildren<QPushButton*>().first();
        currentNameList.append(docOpen->text());
    }

    if (currentNameList.contains(docName)) {
        int i = 2;
        QString alterName = docName;
        while(currentNameList.contains(alterName)) {
            alterName = docName + " (" + QString::number(i++) + ")";
        };
        QMessageBox msgBox;
        msgBox.setText("\"" + docName + Kor("\"에서 \"") + alterName + Kor("\"(으)로 이름을 변경하시겠습니까?"));
        msgBox.setInformativeText(Kor("이 위치에 이름이 같은 문서가 있습니다."));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if (ret == QMessageBox::No)docName="";
        else docName = alterName;
    }
    return docName;
}
void Sortation::on_srtadd_clicked()
{
    QObject* sel = QObject::sender();
    QWidget* srt = (QWidget*)sel->parent();
    int srtIdx = srt->objectName().mid(3).toInt();

    bool ok;

    QString docName = QInputDialog::getText(this, Kor("새 문서"), Kor("이름을 입력하세요:"), QLineEdit::Normal, "", &ok);
    QString getName =name_check(docName,srtIdx);

    if (ok && !getName.isEmpty()) {
        make_docBtn(getName, srtIdx, 0);//0 새 문서 만들기
    }
}

void Sortation::make_docBtn(QString docName, int srtIdx, int type){
    QWidget* srt = this->parent()->findChild<QWidget*>("srt"+QString::number(srtIdx));
    QWidget* srtAreaWidgetContents = srt->parentWidget();
    QVBoxLayout* srtAreaLayout = (QVBoxLayout*)srtAreaWidgetContents->layout();
    QString selOpenName = srt->objectName().append("open");
    QPushButton* selOpen = srt->findChild<QPushButton*>(selOpenName);

    QWidget* newPBS = new QWidget(srtAreaWidgetContents);
    QHBoxLayout* newPBSLayout = new QHBoxLayout(newPBS);
    contextMenuQPushButton* open = new contextMenuQPushButton(docName, newPBS);
//    customQPushButton* open = static_cast<customQPushButton*>(temp);
//    open->setParent(newPBS);
//    open->setObjectName(docName);
    QPushButton* active = new QPushButton(newPBS);

    open->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    open->setStyleSheet("padding-left: 20px; text-align: left; font-family: Malgun Gothic; font-size: 12px;");
    open->setFlat(true);
    open->installEventFilter(this);
    open->setAcceptDrops(true);
    connect(open, SIGNAL(clicked()), this, SLOT(on_docopen_clicked()));
    qDebug()<<open->objectName();
    open->setContextMenuPolicy(Qt::CustomContextMenu);//팝업메뉴 생성가능 정책
    connect(open,&QLineEdit::customContextMenuRequested,open,&contextMenuQPushButton::showDocBtnContextMenu);//팝업메뉴 커넥트

    active->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    active->setFixedWidth(41);
    active->setFlat(true);
    active->installEventFilter(this);
    active->setAcceptDrops(true);
    active->setIconSize(QSize(12, 12));

    newPBSLayout->setSpacing(0);
    newPBSLayout->setContentsMargins(0, 0, 0, 0);
    newPBSLayout->addWidget(open);
    newPBSLayout->addWidget(active);
    //newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    newPBS->setObjectName(QString::number(srtIdx) + "_" + docName);
    newPBS->setFixedHeight(31);
    newPBS->setLayout(newPBSLayout);
    srtAreaLayout->insertWidget(srtRange[srtIdx+1]-2, newPBS);
    //srtAreaWidgetContents->layout()->addWidget(newDoc);
    //newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    //버튼 리스트에 추가 | connect 해주기
    Document* newDoc = new Document(docName, srtIdx, type);
    newDoc->PBS=newPBS;

    if(type==1)
        newDoc->load_doc();
    else if(type==2)
        newDoc->paste_doc();

    docList[srtIdx].push_back(newDoc);

    //document에서 active_doc_select slot 실행
    connect(active, SIGNAL(clicked()), newDoc, SLOT(active_doc_select()));

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

void Sortation::delete_tab(int srtIdx) {
    QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");
    QWidget* empty = parent()->findChild<QWidget*>("srt" + QString::number(srtIdx) + "empty");
    docTab->removeTab(docTab->currentIndex());
    qDebug()<<srtIdx;
    for (int i = srtIdx + 1; i < 11; i++){
        srtRange[i]--;
    }
    if (docList[srtIdx].size() == 0) {
        empty->setFixedHeight(11);
    }
}

void Sortation::save_docList(){
    QString ApplicationPath=QApplication::applicationDirPath();
    QDir Directory(ApplicationPath+"/Data/Srt.ini"); // 폴더 지정
    if(!Directory.exists()) // 폴더가 존재하지 않을경우
    {
        Directory.mkdir(ApplicationPath+"/Data"); // 폴더 생성
    }
    QFile File(ApplicationPath+"/Data/Srt.ini");
    File.open(QFile::WriteOnly|QFile::Text); // 쓰기 전용, 텍스트, 이어쓰기
    QTextStream out(&File);
    for(int i=0;i<10;i++){
        out<<i<<'\n';
        out<<docList[i].size()<<'\n';
        for(auto doc:docList[i]){
            out<<doc->name<<'\n';
            doc->save_doc();
        }
    }
    out<<imgIdx<<'\n'; //imgIdx 저장
    File.close(); // 파일닫기
}

void Sortation::load_docList(){

    QString ApplicationPath=QApplication::applicationDirPath();
    QDir Directory(ApplicationPath+"/Data/Srt.ini"); // 폴더 지정
    if(!Directory.exists()) // 폴더가 존재하지 않을경우
    {
        Directory.mkdir(ApplicationPath+"/Data"); // 폴더 생성
    }
    QFile File(ApplicationPath+"/Data/Srt.ini");
    File.open(QFile::ReadOnly|QFile::Text); // 쓰기 전용, 텍스트
    QTextStream in(&File);

    while(!in.atEnd())  // 파일 끝까지 읽어서
    {
        int srtIdx,num;
        srtIdx=in.readLine().toInt();
        num=in.readLine().toInt();
        for(int i=0;i<num;i++){
            QString name;
            name = in.readLine();
            make_docBtn(name, srtIdx, 1);//1은 로드
        }
    }
    imgIdx=in.readLine().toInt();//imgIdx 초기화
    File.close(); // 파일닫기
}

bool Sortation::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::Drop) {
        QDropEvent*e= static_cast<QDropEvent *>(event);
        if(e->mimeData()->hasFormat("application/x-qtcustomitem")) {
            QWidget* targetObj;
            //공백 클릭시 targetObj는 object
            if((*object).objectName().right(5) == "empty")
                targetObj = (QWidget*)object;
            //문서버튼이나 분류탭 버튼 클릭시 targetObj는 object->parent
            else targetObj = (QWidget*)object->parent();
            if(targetObj->objectName().left(3)== "srt"){//드랍하는 위치가 분류버튼이거나 공백일시
                QWidget* srtAreaWidgetContents = targetObj->parentWidget();
                QWidget* srt;
                //공백 클릭시 srt 찾기
                if(targetObj->objectName().right(5) == "empty") {
                    QString srtName = targetObj->objectName().left(4);
                    srt = srtAreaWidgetContents->findChild<QWidget*>(srtName);
                }
                else srt = targetObj;
                QVBoxLayout* srtAreaLayout = (QVBoxLayout*)srt->parentWidget()->layout();
                QString selOpenName = srt->objectName().append("open");
                QPushButton* selOpen = srt->findChild<QPushButton*>(selOpenName);
                QString selDocObjName = e->mimeData()->text();
                QString selDocName = selDocObjName.mid(2);
                QWidget * selDoc = srtAreaWidgetContents->findChild<QWidget*>(selDocObjName);
                int subSrtIdx;

                int srtIdxTo = srt->objectName().mid(3).toInt();
                int srtIdxFrom = selDocObjName[0].unicode()-'0';


                if (srtIdxTo != srtIdxFrom) {
                    selDocName = name_check(selDocName, srtIdxTo);
                    if (selDocName.isEmpty()) return false;
                    selDocObjName = QString::number(srtIdxTo) + "_" + selDocName;
                    selDoc->setObjectName(selDocObjName);
                    selDoc->findChild<QPushButton*>()->setText(selDocName);
                }

                for(auto it:docList[srtIdxFrom]){

                    if(it->PBS==selDoc){
                        subSrtIdx=docList[srtIdxFrom].indexOf(it);
                        docList[srtIdxTo].push_back(it);
                        docList[srtIdxFrom].remove(subSrtIdx);
                        it->setSrtIdx(srtIdxTo);

                        //tab 이름 변경시 최신화
                        bool existList = false;
                        int tabIdx = -1;
                        QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");

                        for (int i = 0; i < docTab->count(); ++i) {
                            if (QString::number(srtIdxFrom)+'_'+ selDocName == docTab->tabText(i)) {
                                existList = true;
                                tabIdx = i;
                                break;
                            }
                        }
                        if (existList) {
                            docTab->setCurrentIndex(tabIdx);
                            docTab->setTabText(tabIdx,selDocObjName);
                        }
                        break;
                    }
                }

                srtAreaLayout->insertWidget(srtRange[srtIdxTo+1]-2,selDoc);

                for (int i = srtIdxTo+1; i < srtIdxFrom+1; i++){
                    srtRange[i]++;
                }
                for (int i = srtIdxFrom+1; i < srtIdxTo+1; i++){
                    srtRange[i]--;
                }

                //다른 분류탭으로 옮길 시 목적지에
                //문서가 없이 열려있었을 경우 -> empty: 0
                //닫혀있었을 경우 -> empty: 0, show
                QString emptyToName = srt->objectName().append("empty");
                QWidget* emptyTo = srt->parent()->findChild<QWidget*>(emptyToName);
                if (emptyTo->height() > 0) emptyTo->setFixedHeight(0);
                if (emptyTo->isHidden()) {
                    emptyTo->show();

                    selOpen->setIcon(QIcon(":/images/minus_white.png"));
                }
                //다른 분류탭으로 옮길 시 출발지에
                //문서가 0이 된 경우
                QWidget* srtFrom = targetObj->parent()->findChild<QWidget*>("srt"+QString::number(srtIdxFrom));
                QString emptyFromName = srtFrom->objectName().append("empty");
                QWidget* emptyFrom = srt->parent()->findChild<QWidget*>(emptyFromName);
                if (docList[srtIdxFrom].empty()) {
                    emptyFrom->setFixedHeight(11);
                }

                QByteArray itemData = e->mimeData()->data("application/x-qtcustomitem");
                QDataStream dataStream(&itemData, QIODevice::ReadOnly);

                QPixmap pixmap;
                QPoint offset;
                dataStream >> pixmap >> offset;

                //srtIdx 최신화 삭제에 필요
                srtIdx=srtIdxTo;
            }
            else{//드랍하는 위치가 문서버튼일시
                int srtIdxTo = targetObj->objectName().left(1).toInt();
                QWidget* srt = targetObj->parent()->findChild<QWidget*>("srt"+QString::number(srtIdxTo));
                QWidget* srtAreaWidgetContents = srt->parentWidget();
                QVBoxLayout* srtAreaLayout = (QVBoxLayout*)srt->parentWidget()->layout();
                QString selOpenName = srt->objectName().append("open");
                QPushButton* selOpen = srt->findChild<QPushButton*>(selOpenName);
                QString selDocObjName = e->mimeData()->text();
                QString selDocName = selDocObjName.mid(2);
                QWidget * selDoc = srtAreaWidgetContents->findChild<QWidget*>(selDocObjName);
                int subSrtIdxTo, subSrtIdxFrom;

                int srtIdxFrom = selDocObjName[0].unicode()-'0';

                if (srtIdxTo != srtIdxFrom) {//분류가 다를시 이름변경
                    selDocName = name_check(selDocName, srtIdxTo);
                    if (selDocName.isEmpty()) return false;
                    selDocObjName = QString::number(srtIdxTo) + "_" + selDocName;
                    selDoc->setObjectName(selDocObjName);
                    selDoc->findChild<QPushButton*>()->setText(selDocName);
                }

                for(auto it:docList[srtIdxTo]){//드랍하는 위치에 인덱스 찾기
                    if(it->PBS==targetObj){
                        subSrtIdxTo=docList[srtIdxTo].indexOf(it);
                        break;
                    }
                }

                QMouseEvent*MouseE= static_cast<QMouseEvent *>(event);

                if(16 < MouseE->globalY()){// 문서 위로 삽입
                    subSrtIdxTo++;
                }

                for(auto it:docList[srtIdxFrom]){

                    if(it->PBS==selDoc){
                        subSrtIdxFrom=docList[srtIdxFrom].indexOf(it);
                        if(srtIdxTo!=srtIdxFrom || subSrtIdxTo!=subSrtIdxFrom+1) {
                            if(subSrtIdxTo>subSrtIdxFrom){
                                docList[srtIdxTo].insert(subSrtIdxTo,it);
                                docList[srtIdxFrom].remove(subSrtIdxFrom);
                            }
                            else{

                                docList[srtIdxFrom].remove(subSrtIdxFrom);
                                docList[srtIdxTo].insert(subSrtIdxTo,it);
                            }
                            it->setSrtIdx(srtIdxTo);

                            //tab 이름 변경시 최신화
                            bool existList = false;
                            int tabIdx = -1;
                            QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");

                            for (int i = 0; i < docTab->count(); ++i) {
                                if (QString::number(srtIdxFrom)+'_'+ selDocName == docTab->tabText(i)) {
                                    existList = true;
                                    tabIdx = i;
                                    break;
                                }
                            }
                            if (existList) {
                                docTab->setCurrentIndex(tabIdx);
                                docTab->setTabText(tabIdx,selDocObjName);
                            }
                        }

                        break;
                    }
                }

                if(srtIdxTo==srtIdxFrom && subSrtIdxTo> subSrtIdxFrom)
                    subSrtIdxTo--;
                srtAreaLayout->insertWidget(srtRange[srtIdxTo]+subSrtIdxTo,selDoc);

                for (int i = srtIdxTo+1; i < srtIdxFrom+1; i++){
                    srtRange[i]++;
                }
                for (int i = srtIdxFrom+1; i < srtIdxTo+1; i++){
                    srtRange[i]--;
                }

                //다른 분류탭으로 옮길 시 목적지에
                //문서가 없이 열려있었을 경우 -> empty: 0
                //닫혀있었을 경우 -> empty: 0, show
                QString emptyToName = srt->objectName().append("empty");
                QWidget* emptyTo = srt->parent()->findChild<QWidget*>(emptyToName);
                if (emptyTo->height() > 0) emptyTo->setFixedHeight(0);
                if (emptyTo->isHidden()) {
                    emptyTo->show();
                    selOpen->setIcon(QIcon(":/images/minus_white.png"));
                }
                //다른 분류탭으로 옮길 시 출발지에
                //문서가 0이 된 경우
                QWidget* srtFrom = targetObj->parent()->findChild<QWidget*>("srt"+QString::number(srtIdxFrom));
                QString emptyFromName = srtFrom->objectName().append("empty");
                QWidget* emptyFrom = srt->parent()->findChild<QWidget*>(emptyFromName);
                if (docList[srtIdxFrom].empty()) {
                    emptyFrom->setFixedHeight(11);
                }

                QByteArray itemData = e->mimeData()->data("application/x-qtcustomitem");
                QDataStream dataStream(&itemData, QIODevice::ReadOnly);

                QPixmap pixmap;
                QPoint offset;
                dataStream >> pixmap >> offset;


                //srtIdx 최신화 삭제에 필요
                srtIdx=srtIdxTo;
            }


        } else {
            e->ignore();
        }
    }
    if(event->type()==QEvent::DragEnter){
        QDragEnterEvent*e= static_cast<QDragEnterEvent *>(event);
        if(e->mimeData()->hasFormat("application/x-qtcustomitem")) {
            if(e->source() == this) {
                e->setDropAction(Qt::MoveAction);
                e->accept();
            } else {
                e->acceptProposedAction();
            }
        } else {
            e->ignore();
        }
    }
    if(event->type()==QEvent::MouseMove){
        QMouseEvent*e= static_cast<QMouseEvent *>(event);
        if(e->buttons() & Qt::LeftButton) {
            QDrag * drag = new QDrag(this);
            QMimeData * mimeData = new QMimeData;
            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);

            if((*object).objectName().left(3)!= "srt"){//선택된 오브젝트가 문서버튼일시 드래그 가능
                QPushButton *targetBtn = qobject_cast<QPushButton*>(object);
                QWidget *target = (QWidget*)targetBtn->parent();
                QPixmap *widgetPixmap = new QPixmap(target->size());
                target->render(widgetPixmap);
                QPixmap *resultPixmap = new QPixmap(target->size());
                resultPixmap->fill(Qt::transparent);
                QPainter p;
                p.begin(resultPixmap);
                p.setOpacity(0.5);
                p.drawPixmap(0, 0, *widgetPixmap);
                p.end();

                drag->setHotSpot(e->pos() - target->rect().topLeft());

                mimeData->setData("application/x-qtcustomitem", itemData);
                mimeData->setText(target->objectName());
                drag->setMimeData(mimeData);
                drag->setPixmap(*resultPixmap);
                drag->exec();
            }


        }
    }

    return false;
}

void contextMenuQPushButton::showSrtContextMenu(const QPoint &pos){
    QMenu contextMenu(tr("Context menu"), this);
    QAction action1(Kor("이름변경"), this);
    //connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
    contextMenu.addAction(&action1);

    QAction action2(Kor("복사"), this);
    //connect(&action2,&QAction::triggered,this,&contextMenuQPushButton::copy_doc);//팝업메뉴 커넥트
    contextMenu.addAction(&action2);

    QAction action3(Kor("붙여넣기"), this);
    //connect(&action3,&QAction::triggered,this,&contextMenuQPushButton::paste_doc);
    contextMenu.addAction(&action3);

    contextMenu.exec(mapToGlobal(pos));
}

void contextMenuQPushButton::showDocBtnContextMenu(const QPoint &pos){
    QMenu contextMenu(tr("Context menu"), this);
    QAction action1(Kor("이름변경"), this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
    contextMenu.addAction(&action1);

    QAction action2(Kor("복사"), this);
    connect(&action2,&QAction::triggered,this,&contextMenuQPushButton::copy_doc);//팝업메뉴 커넥트
    contextMenu.addAction(&action2);

    QAction action3(Kor("잘라내기"), this);
    connect(&action3,&QAction::triggered,this,&contextMenuQPushButton::cut_doc);
    contextMenu.addAction(&action3);

    QAction action4(Kor("붙여넣기"), this);
    connect(&action4,&QAction::triggered,this,&contextMenuQPushButton::paste_doc);
    contextMenu.addAction(&action4);

    contextMenu.exec(mapToGlobal(pos));
}

Document* Sortation::find_doc(QObject* pbs){
    for(int i=0;i<(sizeof(docList) / sizeof(docList[0]));i++){
        for(auto it:docList[i]){
            if(it->PBS==pbs)
                return it;
        }
    }
    return nullptr;
}
