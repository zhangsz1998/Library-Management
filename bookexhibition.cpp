#include "bookexhibition.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <vector>
#include <QVector>

extern qreal dpi;

BookExhibition::BookExhibition(QWidget *parent) : QMdiSubWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    this->setStyleSheet("background-color:#ffffff;border:none");
    cursorLayer=1;
    currentPage=0;
    maxPages=0;

    nextPage=new ToolButton(this);
    nextPage->setGeometry(460*dpi,500*dpi,30*dpi,30*dpi);
    nextPage->setIcon(QPixmap(":/Images/Icons/NextPage.png"));
    connect(nextPage,SIGNAL(clicked()),this,SLOT(toNextPage()));

    prePage=new ToolButton(this);
    prePage->setGeometry(360*dpi,500*dpi,30*dpi,30*dpi);
    prePage->setIcon(QPixmap(":/Images/Icons/PrePage.png"));
    connect(prePage,SIGNAL(clicked()),this,SLOT(toPrePage()));
}

BookExhibition::~BookExhibition()
{
    delete nextPage;
    delete prePage;
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
    for(unsigned int i=0;i<books.size();i++)
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

Book* BookExhibition::bookOnDisplay()
{
    if(books.size()>0)
        return books[9*currentPage+cursorLayer-1];
    else
        return Q_NULLPTR;
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
    int h=0*dpi;
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
                h+=41*dpi;
            else if(i==cursorLayer)
                h+=41*4*dpi;
            else
                h+=41*dpi;
            painter.drawLine(0,h,this->width(),h);
            if(i==cursorLayer)
            {
                painter.drawPixmap(20*dpi,h-164*dpi+2*dpi,QPixmap((this->books)[index]->getStringByTag("loc")).scaled(120*dpi,160*dpi,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                painter.setPen(titleText);
                painter.drawText(20*dpi+120*dpi,h-164*dpi+30*dpi,(this->books)[index]->getStringByTag("title"));
                painter.setPen(subscript);
                painter.setFont(authorFont);
                painter.drawText((20+120)*dpi,h-164*dpi+55*dpi,(this->books)[index]->getStringByTag("author"));
                painter.drawText(20*dpi+120*dpi,h-164*dpi+80*dpi,(this->books)[index]->getStringByTag("press"));

                //打印简介
                for(int j=0;j<despList[index].size();j++)
                {
                    if(j==0)
                        painter.drawText(20*dpi+430*dpi,h-164*dpi+55*dpi+20*j*dpi,despList[index].at(j));
                    else
                        painter.drawText(20*dpi+400*dpi,h-164*dpi+55*dpi+20*j*dpi,despList[index].at(j));
                }
            }
            else
            {
                painter.setPen(titleText);
                painter.setFont(titleFont);
                painter.drawText(20*dpi,h-41*dpi+30*dpi,(this->books)[index]->getStringByTag("title"));
            }
            painter.setPen(dashLine);
        }
    }
    painter.setPen(subscript);
    painter.setFont(subFont);
    painter.drawText(20*dpi,520*dpi,QString("共%1条搜索结果").arg(QString::number(books.size())));
    painter.drawText(408*dpi,520*dpi,QString("%1 / %2").arg(QString::number(currentPage+1)).arg(maxPages+1));
}

void BookExhibition::mouseMoveEvent(QMouseEvent *event)
{
    int y=(event->pos()).y();
    if(y>=0&&y<(cursorLayer-1)*41*dpi)
    {
        cursorLayer=y/(41*dpi)+1;
        update();
    }
    else if(y>=(cursorLayer+3)*41*dpi&&y<this->height())
    {
        cursorLayer=y/(41*dpi)-2;
        update();
    }
    if(currentPage<maxPages&&cursorLayer>=9)         //除尾页外每页显示9组数据,鼠标层数为10则置为9
        cursorLayer=9;
    else if(currentPage==maxPages&&cursorLayer>=(books.size()-1)%9+1)      //尾页显示books.size()%10+1组数据,鼠标层数超过则显示最后一组
        cursorLayer=(books.size()-1)%9+1;
}

void BookExhibition::mousePressEvent(QMouseEvent *event)
{
    if(event->button()&Qt::LeftButton)
    {
        int y=event->pos().y();
        if(y>=0*dpi&&y<=492*dpi)
            emit bookInfoClicked();
    }
}
