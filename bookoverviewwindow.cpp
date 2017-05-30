#include "bookoverviewwindow.h"

BookOverviewWindow::BookOverviewWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    this->setStyleSheet("background-color:#ffffff;border:none");
    QList<QString> categoryList;
    categoryList.append("文学");
    categoryList.append("小说");
    categoryList.append("传记");
    categoryList.append("青春与动漫");
    categoryList.append("经济");
    categoryList.append("投资理财");
    categoryList.append("少儿");
    categoryList.append("历史");
    categoryList.append("哲学与宗教");
    categoryList.append("国学");
    categoryList.append("心理学");
    categoryList.append("政治与军事");
    categoryList.append("法律");
    categoryList.append("社会科学");
    categoryList.append("孕产育儿");
    categoryList.append("旅游与地图");
    categoryList.append("烹饪美食与酒");
    categoryList.append("健身与保健");
    categoryList.append("婚恋与两性");
    categoryList.append("娱乐");
    categoryList.append("时尚");
    categoryList.append("家居休闲");
    categoryList.append("教辅");
    categoryList.append("考试");
    categoryList.append("英语与其他外语");
    categoryList.append("词典与工具书");
    categoryList.append("励志与成功");
    categoryList.append("科技");
    categoryList.append("医学");
    categoryList.append("计算机与互联网");
    categoryList.append("科学与自然");
    std::vector<Book*> tempbooklist;
    for(int i=0;i<30;i++)
    {
        categories[i]=new ToolButton(this);
        categories[i]->setFixedHeight(30*dpi);
        categories[i]->setFixedWidth(100*dpi);
        categories[i]->setText(categoryList[i]);
        categories[i]->setObjectName(QString::number(i));

        tempbooklist=search(categoryList[i],6);
        int l=tempbooklist.size();
        for(int j=0;j<l;j++)
        {
            covers[i].append(tempbooklist[j]->getStringByTag("loc"));
            titles[i].append(tempbooklist[j]->getStringByTag("title"));
        }
    }
    buttons=new QTableWidget(30,1,this);
    buttons->setGeometry(20*dpi,10*dpi,140*dpi,210*dpi);
    buttons->verticalHeader()->hide();
    buttons->horizontalHeader()->hide();
    for(int i=0;i<30;i++)
    {
        buttons->setRowHeight(i,30*dpi);
        buttons->setCellWidget(i,0,categories[i]);
    }

    toLeft=new ToolButton(this);
    toLeft->setIcon(QPixmap(":/Images/Icons/PrePage.png"));
    toLeft->setIconSize(QSize(30*dpi,30*dpi));
    toLeft->setGeometry(170*dpi,100*dpi,30*dpi,30*dpi);
    toLeft->setEnterColor("#ebf2fa");
    connect(toLeft,SIGNAL(clicked()),this,SLOT(graduallyDisappear()));
    connect(toLeft,SIGNAL(clicked()),this,SLOT(moveLeft()));
    connect(toLeft,SIGNAL(clicked()),this,SLOT(startTimerL()));

    toRight=new ToolButton(this);
    toRight->setIcon(QPixmap(":/Images/Icons/NextPage.png"));
    toRight->setIconSize(QSize(30*dpi,30*dpi));
    toRight->setGeometry(this->width()-40*dpi,100*dpi,30*dpi,30*dpi);
    toRight->setEnterColor("#ebf2fa");

    lastIndex=4;
    firstIndexOnDisplay=0;

    categoryOnDisplay=0;
    for(int i=0;i<5;i++)
    {
        coversOnDisplay[i]=new Label(this);
        coversOnDisplay[i]->setGeometry((205+i*157)*dpi,10*dpi,135*dpi,190*dpi);
        coversOnDisplay[i]->setVisible(false);
        titlesOnDisplay[i]=new Label(this);
        titlesOnDisplay[i]->setGeometry((205+i*157)*dpi,200*dpi,135*dpi,30*dpi);
        titlesOnDisplay[i]->setStyleSheet("background-color:transparent");
        titlesOnDisplay[i]->setAlignment(Qt::AlignCenter);
        titlesOnDisplay[i]->setVisible(false);
    }
    for(int i=0;i<7;i++)
    {
        r_Cover.push_back(QRect((205+(i-1)*157)*dpi,10*dpi,135*dpi,190*dpi));
        r_Title.push_back(QRect((205+(i-1)*157)*dpi,200*dpi,135*dpi,30*dpi));
    }
    //初始化，内容待定，先取所有图书的前四本
    for(int i=0;i<5;i++)
    {
        coversOnDisplay[i]->setPixmap(QPixmap(booklist[i].getStringByTag("loc")).scaled(135*dpi,190*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        QString title=booklist[i].getStringByTag("title");
        titlesOnDisplay[i]->setText(title);
        if(i==4)
        {
           coversOnDisplay[i]->setOpacity(0.0);
           titlesOnDisplay[i]->setOpacity(0.0);
        }
        coversOnDisplay[i]->setVisible(true);
        titlesOnDisplay[i]->setVisible(true);
    }
    timerL=new QTimer(this);
    connect(timerL,SIGNAL(timeout()),this,SLOT(changeOrderL()));
}

void BookOverviewWindow::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    QPen dashLine(QColor("#cccccc"));
    QPen textPen(QColor("#000000"));
    QPen labelPen(QColor("#999999"));
    dashLine.setStyle(Qt::DashLine);
    painter.setPen(dashLine);
    painter.drawLine(10*dpi,230*dpi,this->width()-10*dpi,230*dpi);
}

void BookOverviewWindow::startTimerL()
{
    timerL->start(400);
}

void BookOverviewWindow::showBookByCategory()
{
    ToolButton* clickedButton=qobject_cast<ToolButton*>(sender());
    int i=(clickedButton->objectName()).toInt();
    firstIndexOnDisplay=0;
    categoryOnDisplay=i;
    int l=covers[i].size();
    QPixmap pic;
    for(int j=0;j<l&&j<5;j++)
    {
        pic.load(covers[i].at(j));
        coversOnDisplay[j]->setPixmap(pic.scaled(120*dpi,200*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

void BookOverviewWindow::moveLeft()
{
//    int l=covers[categoryOnDisplay].size();
    int l=booklist.size();
    if(l<=4)
        return;
    for(int i=0;i<5;i++)
    {
        moveAction_Cover[i].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+i)%5]);
        moveAction_Cover[i].setPropertyName("geometry");
        moveAction_Cover[i].setDuration(400);
        moveAction_Cover[i].setStartValue(r_Cover[i+1]);
        moveAction_Cover[i].setEndValue(r_Cover[i]);
        moveAction_Cover[i].setEasingCurve(QEasingCurve::Linear);
        moveAction_Cover[i].start();

        moveAction_Title[i].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+i)%5]);
        moveAction_Title[i].setPropertyName("geometry");
        moveAction_Title[i].setDuration(400);
        moveAction_Title[i].setStartValue(r_Title[i+1]);
        moveAction_Title[i].setEndValue(r_Title[i]);
        moveAction_Title[i].setEasingCurve(QEasingCurve::Linear);
        moveAction_Title[i].start();
    }

//    coversOnDisplay[hidenIndex]->setGeometry(r_Cover[5]);
//    coversOnDisplay[hidenIndex]->setGeometry(r_Title[5]);
    repaint();
}

void BookOverviewWindow::moveRight()
{

}

void BookOverviewWindow::graduallyDisappear()
{
    qDebug()<<firstIndexOnDisplay;
    qDebug()<<(firstIndexOnDisplay+4)%5;
    opacityAction_Cover[0].setTargetObject(coversOnDisplay[firstIndexOnDisplay]);
    opacityAction_Cover[0].setPropertyName("opacity");
    opacityAction_Cover[0].setDuration(400);
    opacityAction_Cover[0].setStartValue(1.0);
    opacityAction_Cover[0].setEndValue(0.0);
    opacityAction_Cover[0].setEasingCurve((QEasingCurve::Linear));
    opacityAction_Cover[0].start();

    opacityAction_Cover[1].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+4)%5]);
    opacityAction_Cover[1].setPropertyName("opacity");
    opacityAction_Cover[1].setDuration(400);
    opacityAction_Cover[1].setStartValue(0.0);
    opacityAction_Cover[1].setEndValue(1.0);
    opacityAction_Cover[1].setEasingCurve((QEasingCurve::Linear));
    opacityAction_Cover[1].start();

    opacityAction_Title[0].setTargetObject(titlesOnDisplay[firstIndexOnDisplay]);
    opacityAction_Title[0].setPropertyName("opacity");
    opacityAction_Title[0].setDuration(400);
    opacityAction_Title[0].setStartValue(1.0);
    opacityAction_Title[0].setEndValue(0.0);
    opacityAction_Title[0].setEasingCurve((QEasingCurve::Linear));
    opacityAction_Title[0].start();

    opacityAction_Title[1].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+4)%5]);
    opacityAction_Title[1].setPropertyName("opacity");
    opacityAction_Title[1].setDuration(400);
    opacityAction_Title[1].setStartValue(0.0);
    opacityAction_Title[1].setEndValue(1.0);
    opacityAction_Title[1].setEasingCurve((QEasingCurve::Linear));
    opacityAction_Title[1].start();
}

void BookOverviewWindow::changeOrderL()
{
    int l=booklist.size();
    lastIndex=(lastIndex+1)%l;
    int hidenIndex=firstIndexOnDisplay;
    coversOnDisplay[hidenIndex]->setPixmap(QPixmap(booklist[lastIndex].getStringByTag("loc")).scaled(135*dpi,190*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    QString title=booklist[lastIndex].getStringByTag("title");
    titlesOnDisplay[hidenIndex]->setText(title);
    firstIndexOnDisplay=(firstIndexOnDisplay+1)%5;
    timerL->stop();
}


