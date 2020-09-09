#include "data.h"
#include "Document.h"
#include "mainwindow.h"
#include "sortation.h"
#include <QApplication>
#include <QTextDocument>
#include <QPrinter>

Data::Data(QString type, QString name ,int valueLine, QString value, QString date,QString path){
    this->type=type;
    this->name=name;
    this->value=value;
    this->valueLine=valueLine;
    this->date=date;
    this->path=path;
}

Data::~Data(){

}


void Document::load_doc(){
    dataList.clear();
    QString ApplicationPath=QApplication::applicationDirPath();
    QDir Directory(ApplicationPath+"/Data/Srt"+QString::number(srtIdx)); // 폴더 지정
    if(!Directory.exists()) // 폴더가 존재하지 않을경우
    {
        Directory.mkdir(ApplicationPath+"/Data"); // 폴더 생성
        Directory.mkdir(ApplicationPath+"/Data/Srt"+QString::number(srtIdx)); // 폴더 생성
    }
    QFile File(ApplicationPath+"/Data/Srt"+QString::number(srtIdx)+"/"+name+".data");
    File.open(QFile::ReadOnly|QFile::Text); // 쓰기 전용, 텍스트
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

        dataList.push_back(data);
    }
    File.close(); // 파일닫기

    for(auto data:dataList){
        qDebug()<<data->type<<'\n';
        qDebug()<<data->name<<'\n';
        qDebug()<<data->valueLine<<'\n';
        qDebug()<<data->value<<'\n';
        qDebug()<<data->date<<'\n';
        qDebug()<<data->path<<'\n';
    }
    QObjectList tabList = tab->box->children();
    for(auto it:tabList){
        if(it->objectName()=="boxAreaLayout") continue;
        delete it;
    }

    QVBoxLayout* loadBox;
    for(auto it: dataList){
        if(it->type=="box"){
            loadBox=load_add_box();
        }
        else if(it->type=="text"){
            AddItemText(it,loadBox);
        }
        else if(it->type=="textArea"){
            AddItemTextarea(it,loadBox);
        }
        else if(it->type=="image"){
            AddItemImage(it,loadBox);
        }
        else if(it->type=="date"){
            AddItemDate(it,loadBox);
        }
        else if(it->type=="dropDown"){
            AddItemDropdown(it,loadBox);
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
            else if(type=="dropDown"){

            }
            dataList.push_back(new Data(type, name, valueLine, value, date,path));
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
    }
    File.close(); // 파일닫기
}


void Sortation::save_pdf(){
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml("<h1>Hello, World!</h1>\n<p>Lorem ipsum dolor sit amet, consectitur adipisci elit.</p>");
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}
