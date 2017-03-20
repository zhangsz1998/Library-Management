#include "bookinfowindow.h"

BookInfoWindow::BookInfoWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:transparent;border-top:1px dashed #cccccc;border-bottom:1px dashed #cccccc;");
    bookInfo=new QLabel(this);
    //bookInfo->setGeometry(0,0,this->width(),this->height());
    bookInfo->setFont(QFont("微软雅黑",15));
    bookInfo->setText("《算法导论》(第三版 机械工业出版社)");
}

void BookInfoWindow::enterEvent(QEvent *event)
{
    this->setGeometry(0,0,1024,55);
    //this->bookInfo->setGeometry(0,0,100,8);
}

void BookInfoWindow::leaveEvent(QEvent *event)
{
    this->setGeometry(0,0,1024,55);
    //this->bookInfo->setGeometry(0,0,100,4);
}
