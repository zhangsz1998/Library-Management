#include "bookexhibition.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

BookExhibition::BookExhibition(QWidget *parent) : QMdiSubWindow(parent)
{
    titile.push_back(QString("《算法导论》"));
    titile.push_back(QString("《计算机网络》"));
    titile.push_back(QString("《算法设计与分析》"));
    titile.push_back(QString("《操作系统》"));
    titile.push_back(QString("《数据结构》"));
    titile.push_back(QString("《格列佛游记》"));
    titile.push_back(QString("《象拔蚌》"));
    titile.push_back(QString("《老人与海》"));
    titile.push_back(QString("《走xx的蛇皮位》"));
    titile.push_back(QString("《里皮》"));
    for(int i=0;i<10;i++)
    {
        cover.push_back(QPixmap(":/Images/NoCover.png").scaled(120,160,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150,170,859,533);
    this->setStyleSheet("background-color:#ffffff;border:none");
    cursorLayer=1;
}

void BookExhibition::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(QFont("微软雅黑",17));
    QPen dashLine(QColor("#cccccc"));
    dashLine.setStyle(Qt::DashLine);
    painter.setPen(dashLine);
    QPen text(QColor("#5b5b5b"));
    int h=0;
    for(int i=1;i<=10;i++)
    {
        if(i<cursorLayer)
            h+=41;
        else if(i==cursorLayer)
            h+=41*4;
        else
            h+=41;
        painter.drawLine(0,h,this->width(),h);
        if(i==cursorLayer)
        {
            painter.drawPixmap(20,h-164+2,cover[i-1]);
            painter.setPen(text);
            painter.drawText(20+120,h-164+30,titile[i-1]);
        }
        else
        {
            painter.setPen(text);
            painter.drawText(20,h-41+30,titile[i-1]);
        }
        painter.setPen(dashLine);
    }
}

void BookExhibition::mouseMoveEvent(QMouseEvent *event)
{
    int y=(event->pos()).y();
    if(y>=0&&y<(cursorLayer-1)*41)
    {
        cursorLayer=y/41+1;
        update();
    }
    else if(y>=(cursorLayer+3)*41&&y<this->height())
    {
        cursorLayer=y/41-2;
        update();
    }
}
