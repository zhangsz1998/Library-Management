#include "bookinfowindow.h"
#include <QPainter>

extern qreal dpi;

BookInfoWindow::BookInfoWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:#ffffff; border:none");

    borrowBtn=new ToolButton(this);
    borrowBtn->setGeometry(60*dpi,323*dpi,150*dpi,40*dpi);
    borrowBtn->setIcon(QPixmap(":/Images/Icons/borrowbookBtn2.png"));
    borrowBtn->setIconSize(QSize(150*dpi,40*dpi));

    reservationBtn=new ToolButton(this);
    reservationBtn->setGeometry(60*dpi,373*dpi,150*dpi,40*dpi);
    reservationBtn->setIcon(QPixmap(":/Images/Icons/ReservationBtn.png"));
    reservationBtn->setIconSize(QSize(150*dpi,40*dpi));

    goBackBtn=new ToolButton(this);
    goBackBtn->setGeometry(15*dpi,480*dpi,40*dpi,40*dpi);
    goBackBtn->setIcon(QPixmap(":/Images/Icons/Goback.png"));
    goBackBtn->setIconSize(QSize(40*dpi,40*dpi));

}

BookInfoWindow::loadBook(Book *book)
{
    this->book=book;
    despList.clear();
    int l=0;
    QString desp=book->getStringByTag("description");
    while(l<(desp.length()))
    {
        QString a=desp.mid(l,44);
        int i=a.indexOf("\n");
        if(i!=-1&&i!=0)
        {
            a=a.mid(0,i);
            l+=i;
        }
        else
        {
            l+=44;
        }
        despList.push_back(a);
    }
    cover.load(book->getStringByTag("loc"));
}

BookInfoWindow::~BookInfoWindow()
{
    delete borrowBtn;
    delete goBackBtn;
    delete reservationBtn;
}

void BookInfoWindow::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);

    QPen dashLine(QColor("#cccccc"));
    QPen textPen(QColor("#000000"));
    QPen labelPen(QColor("#999999"));
    dashLine.setStyle(Qt::DashLine);

    QFont textFont("微软雅黑",15);
    QFont titleFont("微软雅黑",25);
    titleFont.setBold(true);
    QFont descriptionFont("宋体",10);
    QFont despFont("微软雅黑",20);
    despFont.setBold(true);       //内容简介这四个字的字体

    painter.setFont(titleFont);
    painter.setPen(textPen);
    painter.drawText(270*dpi,50*dpi,book->getStringByTag("title"));

    painter.setPen(dashLine);
    painter.drawLine(260*dpi,10*dpi,260*dpi,520*dpi);

    painter.setPen(labelPen);
    painter.setFont(textFont);
    //每行宽度为30*dpi
    painter.drawText(270*dpi,80*dpi,"作者:");
    painter.drawText(270*dpi,110*dpi,"出版社:");
    painter.drawText(270*dpi,140*dpi,"编号:");
    painter.drawText(270*dpi,170*dpi,"剩余量:");

    painter.setPen(textPen);
    painter.drawText(320*dpi,80*dpi,book->getStringByTag("author"));
    painter.drawText(345*dpi,110*dpi,book->getStringByTag("press"));
    painter.drawText(320*dpi,140*dpi,book->getStringByTag("id"));
    painter.drawText(345*dpi,170*dpi,QString::number(book->getIntByTag("amount")));

    painter.setPen(labelPen);
    painter.setFont(despFont);
    painter.drawText(270*dpi,210*dpi,"内容简介");
    //绘制简介
    painter.setFont(descriptionFont);
    painter.setPen(textPen);
    int h=240*dpi;
    for(int i=0;i<despList.size();i++)
    {
        painter.drawText(270*dpi,h+i*20*dpi,despList.at(i));
    }

    //绘制封面
    painter.drawPixmap(40*dpi,40*dpi,cover.scaled(200*dpi,267*dpi,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

}

