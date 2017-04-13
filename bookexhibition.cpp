#include "bookexhibition.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <vector>
#include <QVector>

BookExhibition::BookExhibition(QWidget *parent) : QMdiSubWindow(parent)
{
    for(int i=0;i<10;i++)
    {
        cover.push_back(QPixmap(":/Images/NoCover.png").scaled(120,160,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150,170,859,533);
    this->setStyleSheet("background-color:#ffffff;border:none");
    cursorLayer=1;
    currentPage=0;
    maxPages=0;

    nextPage=new ToolButton(this);
    nextPage->setGeometry(460,500,30,30);
    nextPage->setIcon(QPixmap(":/Images/Icons/NextPage.png"));
    connect(nextPage,SIGNAL(clicked()),this,SLOT(toNextPage()));

    prePage=new ToolButton(this);
    prePage->setGeometry(360,500,30,30);
    prePage->setIcon(QPixmap(":/Images/Icons/PrePage.png"));
    connect(prePage,SIGNAL(clicked()),this,SLOT(toPrePage()));
}

void BookExhibition::toNextPage()
{
    if(currentPage<maxPages)
        currentPage+=1;
    update();
}

void BookExhibition::toPrePage()
{
    if(currentPage>0)
        currentPage-=1;
    update();
}

void BookExhibition::refreshDesp()
{
    despList.clear();
    if(books.size()==0)
        return;
    for(int i=0;i<books.size();i++)
    {
        QVector<QString> a;
        QString desc=(this->books)[i]->getStringByTag("description");
        if(desc.length()==0)
        {
            a.push_back(QString("本书暂无简介。"));
        }
        else
        {
            int j=0,l=0;
            while(j<5&&l+25<desc.length())
            {
                if(j==0)
                {
                    a.push_back(desc.mid(0,23));
                    l+=23;
                }
                else
                {
                    a.push_back(desc.mid(l,25));
                    l+=25;
                }
                j++;
            }
            if(j==5)
                a.push_back(desc.mid(l,20)+".......");
            else
                a.push_back(desc.mid(l,25));
        }
        despList.push_back(a);
    }
}

void BookExhibition::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QFont titleFont("微软雅黑",17);
    titleFont.setBold(true);
    QFont authorFont("宋体",13);
    QFont subFont("微软雅黑",13);
    QPen dashLine(QColor("#cccccc"));
    QPen titleText(QColor("#5b5b5b"));
    QPen subscript(Qt::gray);

    painter.setFont(titleFont);
    dashLine.setStyle(Qt::DashLine);
    painter.setPen(dashLine);
    int h=0;
    if(books.size()>0)
        maxPages=(books.size()-1)/9;
    else
        maxPages=0;
    int index;   //当前显示书籍的索引
    if(books.size()==0)       //未发现符合条件的图书
    {
        //显示提示字符
    }
    else
    {
        /*
         * 这里可以添加简介字符串的预处理
        */
        for(int i=1;(i+currentPage*9<=books.size())&&i<=9;i++)
        {
            index=i-1+currentPage*9;
            if(i<cursorLayer)
                h+=41;
            else if(i==cursorLayer)
                h+=41*4;
            else
                h+=41;
            painter.drawLine(0,h,this->width(),h);
            if(i==cursorLayer)
            {
                painter.drawPixmap(20,h-164+2,(this->cover)[0]);
                painter.setPen(titleText);
                painter.drawText(20+120,h-164+30,(this->books)[index]->getStringByTag("title"));
                painter.setPen(subscript);
                painter.setFont(authorFont);
                painter.drawText(20+120,h-164+55,(this->books)[index]->getStringByTag("author"));
                painter.drawText(20+120,h-164+80,(this->books)[index]->getStringByTag("press"));

                //打印简介
                for(int j=0;j<despList[index].size();j++)
                {
                    if(j==0)
                        painter.drawText(20+430,h-164+55+20*j,despList[index].at(j));
                    else
                        painter.drawText(20+400,h-164+55+20*j,despList[index].at(j));
                }
            }
            else
            {
                painter.setPen(titleText);
                painter.setFont(titleFont);
                painter.drawText(20,h-41+30,(this->books)[index]->getStringByTag("title"));
            }
            painter.setPen(dashLine);
        }
    }
    painter.setPen(subscript);
    painter.setFont(subFont);
    painter.drawText(20,520,QString("共%1条搜索结果").arg(QString::number(books.size())));
    painter.drawText(408,520,QString("%1 / %2").arg(QString::number(currentPage+1)).arg(maxPages+1));
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
    qDebug()<<currentPage<<" "<<maxPages<<" "<<books.size();
    if(currentPage<maxPages&&cursorLayer>=9)         //除尾页外每页显示9组数据,鼠标层数为10则置为9
        cursorLayer=9;
    else if(currentPage==maxPages&&cursorLayer>=(books.size()-1)%9+1)      //尾页显示books.size()%10+1组数据,鼠标层数超过则显示最后一组
        cursorLayer=(books.size()-1)%9+1;
}
