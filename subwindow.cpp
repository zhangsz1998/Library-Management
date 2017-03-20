#include "subwindow.h"
#include <QDebug>

SubWindow::SubWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:#ffffff;");
    this->setGeometry(140,parent->height()/6+50,870,540);
    int infoWindowHeight=(this->height())/13;
    int infoWindowWidth=this->width();
    qDebug()<<this->height()<<" "<<this->width()<<" "<<infoWindowHeight<<" "<<infoWindowWidth;
    for(int i=0;i<10;i++)
    {
        bookInfo[i]=new BookInfoWindow(this);
        if(i==0)
            bookInfo[i]->setGeometry(0,0,infoWindowWidth,infoWindowHeight*4);
        else
            bookInfo[i]->setGeometry(0,bookInfo[i-1]->y()+bookInfo[i-1]->height(),infoWindowWidth,infoWindowHeight);
        qDebug()<<bookInfo[i]->x()<<bookInfo[i]->y()<<bookInfo[i]->width()<<bookInfo[i]->height()<<"\n";
        bookInfo[i]->bookInfo->setGeometry(0,0,bookInfo[i]->width(),bookInfo[i]->height());
    }
}
