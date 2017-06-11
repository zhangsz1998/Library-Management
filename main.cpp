/*******************************************************************************************************/
/*                    注意事项
/*      1.代码中全部变量名均以小写字母开头，类名均以大写字母开头
/*
/*******************************************************************************************************/
#include "widget.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QString>
#include <QtXml>
#include <QFile>
#include <QDate>
#include <QScreen>
#include "reader_mgmt.h"
#include <QStyleFactory>

QString dataDir;       //数据所在目录
QString bookInfoPath;  //图书信息文件路径
QString readerInfoPath; //读者信息文件路径
QString coverDir;      //图书封面所在目录,用于存储图书封面
QDate systemDate;      //程序当前日期
qreal dpi;
Reader* activereader=Q_NULLPTR;
bool userMessageChanged=false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //计算DPI
    QScreen* screen=a.primaryScreen();
    dpi=screen->logicalDotsPerInch()/96;

    //创建Data文件夹
    QDir dir;
    dataDir=dir.currentPath()+"/Data";
    coverDir=dataDir+"/Covers";
    bookInfoPath=dataDir+"/BookInfo.xml";
    readerInfoPath=dataDir+"/ReaderInfo.xml";
    if(!dir.exists(dataDir))          //在当前目录下创建Data文件夹,将读者与图书的相关信息存入Data文件夹
        dir.mkdir(dataDir);
    if(!dir.exists(coverDir))        //在Data目录下创建Cover文件夹
        dir.mkdir(coverDir);

    //创建xml文件

    systemDate=getDate();
    //建立图书的xml文件
    QFile bookInfo(bookInfoPath);
    QDomProcessingInstruction instruction;
    if(!bookInfo.exists())
    {
        QDomDocument bookInfoDom;
        //写文件头
        instruction=bookInfoDom.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"" );

        //写根元素
        bookInfoDom.appendChild(instruction);
        QDomElement root=bookInfoDom.createElement(QString("Library"));
        bookInfoDom.appendChild(root);

        if(!bookInfo.open(QIODevice::WriteOnly|QIODevice::Truncate))
        {
            return 0;
        }
        QTextStream out_1(&bookInfo);
        bookInfoDom.save(out_1,4);
        bookInfo.close();
    }
    //读者xml文件
    QFile readerInfo(readerInfoPath);
    if(!readerInfo.exists())
    {
        QDomDocument readerInfoDom;
        //写文件头
        instruction=readerInfoDom.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"" );

        //写根元素
        readerInfoDom.appendChild(instruction);
        QDomElement root=readerInfoDom.createElement(QString("readerlist"));
        readerInfoDom.appendChild(root);

        if(!readerInfo.open(QIODevice::WriteOnly|QIODevice::Truncate))
        {
            return 0;
        }
        QTextStream out_1(&readerInfo);
        readerInfoDom.save(out_1,4);
        readerInfo.close();
    }
    getXml();
    getXml2();
    log_print("initial","","","");
    Widget w;
    w.show();
    return a.exec();
}
