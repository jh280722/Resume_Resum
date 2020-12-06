#include "data.h"
#include "document.h"
#include "mainwindow.h"
#include "sortation.h"
#include <QApplication>
#include <QTextDocument>
#include <QPrinter>

Data::Data(QString type, QString name ,int valueLine, QString value, QString date,QString path, QString stdate,QString eddate){
    this->type=type;
    this->name=name;
    this->value=value;
    this->valueLine=valueLine;
    this->date=date;
    this->path=path;
    this->stdate=stdate;
    this->eddate=eddate;
}

Data::~Data(){

}


void Document::load_doc(){
    dataList.clear();
    //img 폴더 생성
    QString ApplicationPath=QApplication::applicationDirPath();

    QDir Directory(ApplicationPath+"/img/"); // 폴더 지정
    if(!Directory.exists()) // 폴더가 존재하지 않을경우
    {
        Directory.mkdir(ApplicationPath+"/img"); // 폴더 생성/ 폴더 생성
    }

    Directory = QDir(ApplicationPath+"/Data/Srt"+QString::number(srtIdx)); // 폴더 지정
    if(!Directory.exists()) // 폴더가 존재하지 않을경우
    {
        Directory.mkdir(ApplicationPath+"/Data"); // 폴더 생성
        Directory.mkdir(ApplicationPath+"/Data/Srt"+QString::number(srtIdx)); // 폴더 생성
    }
    QFile File(ApplicationPath+"/Data/Srt"+QString::number(srtIdx)+"/"+name+".data");
    File.open(QFile::ReadOnly|QFile::Text); // 읽기 전용, 텍스트
    QTextStream in(&File);
    while(!in.atEnd())  // 파일 끝까지 읽어서
    {
        Data* data=new Data();
        data->type=in.readLine();
        data->name = in.readLine();
        data->valueLine=in.readLine().toInt();
        data->value = "";
        for(int i=0;i<data->valueLine;i++){
            data->value+=in.readLine();
            if(i+1!=data->valueLine)
                data->value+='\n';
        }
        data->date = in.readLine();
        data->path = in.readLine();
        data->stdate = in.readLine();
        data->eddate = in.readLine();
        dataList.push_back(data);
    }
    File.close(); // 파일닫기

//    for(auto data:dataList){
//        qDebug()<<data->type<<'\n';
//        qDebug()<<data->name<<'\n';
//        qDebug()<<data->valueLine<<'\n';
//        qDebug()<<data->value<<'\n';
//        qDebug()<<data->date<<'\n';
//        qDebug()<<data->path<<'\n';
//    }
    if(tab){
        QObjectList tabList = tab->box->children();
        for(auto it:tabList){
            if(it->objectName()=="boxAreaLayout") continue;
            delete it;
        }
    }
    QVBoxLayout* loadBox;
    for(auto it: dataList){
        if(it->type=="box"){
            loadBox=load_add_box();
        }
        else if(it->type=="text"){
            AddItemText(loadBox,it->name,it->value);
        }
        else if(it->type=="textArea"){
            AddItemTextarea(loadBox,it->name,it->value);
        }
        else if(it->type=="image"){
            AddItemImage(loadBox,it->name,it->path);
        }
        else if(it->type=="date"){
            AddItemDate(loadBox,it->name,it->date);
        }
        else if(it->type=="period"){
            AddItemPeriod(loadBox,it->name,it->stdate, it->eddate);
        }
        else if(it->type=="dropDown"){//setting value
            AddItemDropdown(loadBox,it->name,it->value);
        }
    }
}

void Document::save_doc(){
    dataList.clear();
    QObjectList tabList = tab->box->children();
    for(auto it:tabList){
        if(it->objectName()=="boxAreaLayout") continue;
        QObjectList itemList = it->children();
        for(auto item: itemList){
            if(item->objectName()=="groupBoxLayout") {
                dataList.push_back(new Data("box"));
                continue;
            }
            if(item->objectName()=="tool") continue;
            qDebug()<<item->objectName();
            QString type=item->objectName();
            QString name="";
            int valueLine=1;
            QString value="";
            QString date="";
            QString stdate="";
            QString eddate="";
            QString path="";
            if(type=="text"){
                name=item->findChild<QLabel*>("QLabel")->text();
                value=item->findChild<QLineEdit*>("QLineEdit")->text();
            }
            else if(type=="textArea"){
                name=item->findChild<QLabel*>("QLabel")->text();
                value=item->findChild<QTextEdit*>("QTextEdit")->toPlainText();
                for(int i=0;i<value.size();i++){
                    if(value[i]=='\n'){
                        valueLine++;
                    }
                }
            }
            else if(type=="image"){
                name=item->findChild<QLabel*>("QLabel")->text();
                path=item->findChild<QLabel*>("path")->text();
            }
            else if(type=="date"){
                name=item->findChild<QLabel*>("QLabel")->text();
                date=item->findChild<QDateEdit*>("QDate")->text();
            }
            else if(type=="period"){
                name=item->findChild<QLabel*>("QLabel")->text();
                stdate=item->findChild<QDateEdit*>("QPeriodSt")->text();
                eddate=item->findChild<QDateEdit*>("QPeriodEd")->text();
            }
            else if(type=="dropDown"){
                name=item->findChild<QLabel*>("QLabel")->text();
            }
            dataList.push_back(new Data(type, name, valueLine, value, date,path,stdate,eddate));
        }
    }

    QString ApplicationPath=QApplication::applicationDirPath();
    qDebug()<<ApplicationPath;
    QDir Directory(ApplicationPath+"/Data/Srt"+QString::number(srtIdx)); // 폴더 지정
    if(!Directory.exists()) // 폴더가 존재하지 않을경우
    {
        Directory.mkdir(ApplicationPath+"/Data"); // 폴더 생성
        Directory.mkdir(ApplicationPath+"/Data/Srt"+QString::number(srtIdx)); // 폴더 생성
    }
    QFile File(ApplicationPath+"/Data/Srt"+QString::number(srtIdx)+"/"+name+".data");
    File.open(QFile::WriteOnly|QFile::Text); // 쓰기 전용, 텍스트, 이어쓰기
    QTextStream out(&File);
    for(auto data:dataList){
        out<<data->type<<'\n';
        out<<data->name<<'\n';
        out<<data->valueLine<<'\n';
        out<<data->value<<'\n';
        out<<data->date<<'\n';
        out<<data->path<<'\n';
        out<<data->stdate<<'\n';
        out<<data->eddate<<'\n';
    }
    File.close(); // 파일닫기
}


QString Document::get_html(){
    QString html;
    QObjectList tabList = tab->box->children();
    for(auto it:tabList){
        if(it->objectName()=="boxAreaLayout") continue;
        QObjectList itemList = it->children();
        for(auto item: itemList){
            if(item->objectName()=="groupBoxLayout") {
                //새로운 박스를 만났을때
                continue;
            }
            if(item->objectName()=="tool") continue;

            QString type=item->objectName();
            QString name="";
            QString value="";
            QString date="";
            QString stdate="";
            QString eddate="";
            QString path="";

            html+="<p>"; //문단 시작(아이템 종류마다)

            if(type=="text"){
                name=item->findChild<QLabel*>("QLabel")->text();
                value=item->findChild<QLineEdit*>("QLineEdit")->text();

                html+=name + " : " + value;
            }
            else if(type=="textArea"){
                name=item->findChild<QLabel*>("QLabel")->text();
                value=item->findChild<QTextEdit*>("QTextEdit")->toPlainText();

                html+=name + "\n" + value;
            }
            else if(type=="image"){
                name=item->findChild<QLabel*>("QLabel")->text();
                path=item->findChild<QLabel*>("path")->text();

                html+="<img src='"+QApplication::applicationDirPath()+"/img/"+path+"' width=300 height=300>";
            }
            else if(type=="date"){
                name=item->findChild<QLabel*>("QLabel")->text();
                date=item->findChild<QDateEdit*>("QDate")->text();

                html+=name + " : " + date;
            }
            else if(type=="period"){
                name=item->findChild<QLabel*>("QLabel")->text();
                stdate=item->findChild<QDateEdit*>("QPeriodSt")->text();
                eddate=item->findChild<QDateEdit*>("QPeriodEd")->text();

                html+=name + " : " + stdate + " ~ " + eddate;
            }
            else if(type=="dropDown"){
                name=item->findChild<QLabel*>("QLabel")->text();
            }
            html+="</p>";
        }
    }
    return html;
}


void Sortation::save_pdf(){
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QString html;
    html+="<html>";
    html+="<head>";
    //head 공간
    html+="</head>";
    html+="<body>";
    //body 공간
    for(int i=0;i<10;i++){
        for(auto doc:docList[i]){
            if(!doc->getActive()) continue;
            //활성화돼있으면 html 추출 함수 실행
            html+=doc->get_html();
        }
    }

    //body마무리
    html+="</body>";
    html+="</html>";
    doc.setHtml(html);
    qDebug()<<html;
    //doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}
