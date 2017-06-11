#include "bookoverviewwindow.h"

BookOverviewWindow::BookOverviewWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    this->setStyleSheet("background-color:#ffffff;border:none");

    categoryOnDisplay=0;
//    for(int i=0;i<6;i++)
//    {
//        coversOnDisplay[i]=new Label(this);
//        coversOnDisplay[i]->setGeometry((205+(i-1)*157)*dpi,10*dpi,135*dpi,190*dpi);
//        coversOnDisplay[i]->setVisible(false);
//        titlesOnDisplay[i]=new Label(this);
//        titlesOnDisplay[i]->setGeometry((205+(i-1)*157)*dpi,200*dpi,135*dpi,30*dpi);
//             titlesOnDisplay[i]->setStyleSheet("background-color:transparent");
//        titlesOnDisplay[i]->setAlignment(Qt::AlignCenter);
//        titlesOnDisplay[i]->setVisible(false);
//        r_Cover.push_back(QRect((205+(i-1)*157)*dpi,10*dpi,135*dpi,190*dpi));
//        r_Title.push_back(QRect((205+(i-1)*157)*dpi,200*dpi,135*dpi,30*dpi));
//    }

        for(int i=0;i<7;i++)
        {
            coversOnDisplay[i]=new Label(this);
            coversOnDisplay[i]->setGeometry((48+(i-1)*157)*dpi,10*dpi,135*dpi,190*dpi);
            coversOnDisplay[i]->setVisible(false);
            titlesOnDisplay[i]=new Label(this);
            titlesOnDisplay[i]->setGeometry((48+(i-1)*157)*dpi,200*dpi,135*dpi,30*dpi);
                 titlesOnDisplay[i]->setStyleSheet("background-color:transparent");
            titlesOnDisplay[i]->setVisible(false);
            r_Cover.push_back(QRect((48+(i-1)*157)*dpi,10*dpi,135*dpi,190*dpi));
            r_Title.push_back(QRect((48+(i-1)*157)*dpi,200*dpi,135*dpi,30*dpi));
        }


    int l=booklist.size();
    //初始化，内容待定，先取所有图书的前四本
    if(l!=0)
    {
        for(int i=0;i<5&&i<l;i++)
        {
            coversOnDisplay[i+1]->setPixmap(QPixmap(booklist[i].getStringByTag("loc")).scaled(135*dpi,190*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            QString title=booklist[i].getStringByTag("title");
            titlesOnDisplay[i+1]->setText(title);
        }
        for(int i=l+1;i<6;i++)
        {
            coversOnDisplay[i]->setPixmap(QPixmap(""));
            titlesOnDisplay[i]->setText("");
        }
        //初始化最左最右标签
        QString title;
        firstIndexInBookList=0;
        firstIndexOnDisplay=1;

//        coversOnDisplay[5]->setPixmap(QPixmap(booklist[4%l].getStringByTag("loc")).scaled(135*dpi,190*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
//        title=booklist[4%l].getStringByTag("title");
//        titlesOnDisplay[5]->setText(title);
//        coversOnDisplay[5]->setOpacity(0.0);
//        titlesOnDisplay[5]->setOpacity(0.0);

        coversOnDisplay[6]->setPixmap(QPixmap(booklist[5%l].getStringByTag("loc")).scaled(135*dpi,190*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        title=booklist[5%l].getStringByTag("title");
        titlesOnDisplay[6]->setText(title);
        coversOnDisplay[6]->setOpacity(0.0);
        titlesOnDisplay[6]->setOpacity(0.0);



        coversOnDisplay[0]->setPixmap(QPixmap(booklist[l-1].getStringByTag("loc")).scaled(135*dpi,190*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        title=booklist[l-1].getStringByTag("title");
        titlesOnDisplay[0]->setText(title);
        coversOnDisplay[0]->setOpacity(0.0);
        titlesOnDisplay[0]->setOpacity(0.0);
    }
    for(int i=0;i<7;i++)
    {
        coversOnDisplay[i]->setVisible(true);
        titlesOnDisplay[i]->setVisible(true);
    }
    timerL=new QTimer(this);
    connect(timerL,SIGNAL(timeout()),this,SLOT(changeOrderL()));

    timerR=new QTimer(this);
    connect(timerR,SIGNAL(timeout()),this,SLOT(changeOrderR()));

//    QList<QString> categoryList;
//    categoryList.append("文学");
//    categoryList.append("小说");
//    categoryList.append("传记");
//    categoryList.append("青春与动漫");
//    categoryList.append("经济");
//    categoryList.append("投资理财");
//    categoryList.append("少儿");
//    categoryList.append("历史");
//    categoryList.append("哲学与宗教");
//    categoryList.append("国学");
//    categoryList.append("心理学");
//    categoryList.append("政治与军事");
//    categoryList.append("法律");
//    categoryList.append("社会科学");
//    categoryList.append("孕产育儿");
//    categoryList.append("旅游与地图");
//    categoryList.append("烹饪美食与酒");
//    categoryList.append("健身与保健");
//    categoryList.append("婚恋与两性");
//    categoryList.append("娱乐");
//    categoryList.append("时尚");
//    categoryList.append("家居休闲");
//    categoryList.append("教辅");
//    categoryList.append("考试");
//    categoryList.append("英语与其他外语");
//    categoryList.append("词典与工具书");
//    categoryList.append("励志与成功");
//    categoryList.append("科技");
//    categoryList.append("医学");
//    categoryList.append("计算机与互联网");
//    categoryList.append("科学与自然");
    std::vector<Book*> tempbooklist;
    for(int i=0;i<8;i++)
    {
        categories[i]=new ToolButton(this);
        categories[i]->setFixedHeight(35*dpi);
        categories[i]->setFixedWidth(150*dpi);
        //categories[i]->setText(categoryList[i]);
        //connect(categories[i],SIGNAL(clicked()),this,SLOT(showBookByCategory()));
        connect(categories[i],SIGNAL(clicked()),this,SLOT(changeCategory()));
        categories[i]->setObjectName(QString::number(i));
//        tempbooklist=search(categoryList[i],6);
//        int l=tempbooklist.size();
//        for(int j=0;j<l;j++)
//        {
//            covers[i].append(tempbooklist[j]->getStringByTag("loc"));
//            titles[i].append(tempbooklist[j]->getStringByTag("title"));
//        }
    }
    buttons=new QTableWidget(8,1,this);
    buttons->setGeometry(20*dpi,240*dpi,150*dpi,280*dpi);
    buttons->verticalHeader()->hide();
    buttons->horizontalHeader()->hide();
    buttons->setColumnWidth(0,150*dpi);
    for(int i=0;i<8;i++)
    {
        buttons->setRowHeight(i,35*dpi);
        buttons->setCellWidget(i,0,categories[i]);
    }
    toLeft=new ToolButton(this);
    toLeft->setIcon(QPixmap(":/Images/Icons/PrePage.png"));
    toLeft->setIconSize(QSize(30*dpi,30*dpi));
    toLeft->setGeometry(10*dpi,100*dpi,30*dpi,30*dpi);
    toLeft->setEnterColor("#ebf2fa");
    connect(toLeft,SIGNAL(clicked()),this,SLOT(graduallyDisappearR()));
    connect(toLeft,SIGNAL(clicked()),this,SLOT(moveRight()));
    connect(toLeft,SIGNAL(clicked()),this,SLOT(startTimerR()));

    toRight=new ToolButton(this);
    toRight->setIcon(QPixmap(":/Images/Icons/NextPage.png"));
    toRight->setIconSize(QSize(30*dpi,30*dpi));
    toRight->setGeometry(this->width()-40*dpi,100*dpi,30*dpi,30*dpi);
    toRight->setEnterColor("#ebf2fa");
    connect(toRight,SIGNAL(clicked()),this,SLOT(graduallyDisappearL()));
    connect(toRight,SIGNAL(clicked()),this,SLOT(moveLeft()));
    connect(toRight,SIGNAL(clicked()),this,SLOT(startTimerL()));

    actionTimer = new QTimer(this);
    connect(actionTimer,SIGNAL(timeout()),this,SLOT(noAction()));
    actionTimer->start(5000);
}

BookOverviewWindow::~BookOverviewWindow()
{
    for(int i=0;i<6;i++)
    {
        delete coversOnDisplay[i];
        delete titlesOnDisplay[i];
    }
    for(int i=0;i<8;i++)
        delete categories[i];
    delete timerL;
    delete timerR;
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

    //painter.drawLine(200*dpi,520*dpi,820*dpi,520*dpi);
    QFont titleFont("微软雅黑",12);
    QFont authorFont("宋体",13);
    QFont subFont("微软雅黑",13);
    QPen titleText(QColor("#5b5b5b"));
    QPen subscript(Qt::gray);

    std::vector<QString> categoryList=getTopCat();
    for(int i=0;i<8;i++)
        categories[i]->setText(categoryList[i]);
    bookList=getCatTopBor(categoryList[categoryOnDisplay]);
    int h=240*dpi;
    painter.setPen(textPen);
    painter.drawLine(200*dpi,240*dpi,820*dpi,240*dpi);
    for(int i=1;i<=5&&i<=bookList.size();i++)
    {
        if(i<cursorLayer)
            h+=35*dpi;
        else if(i==cursorLayer)
            h+=35*4*dpi;
        else
            h+=35*dpi;
        painter.drawLine(200*dpi,h,820*dpi,h);
        if(i==cursorLayer)
        {
            painter.setFont(titleFont);
            painter.drawPixmap(200*dpi,h-130*dpi,QPixmap(bookList[i-1]->getStringByTag("loc")).scaled(90*dpi,120*dpi,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            //绘制标题，编号，作者
            painter.drawText(300*dpi,h-130*dpi+10*dpi,bookList[i-1]->getStringByTag("title"));
            painter.drawText(300*dpi,h-130*dpi+35*dpi,"作者: "+bookList[i-1]->getStringByTag("author"));
            painter.drawText(300*dpi,h-130*dpi+60*dpi,"出版社: "+bookList[i-1]->getStringByTag("press"));
            painter.drawText(300*dpi,h-130*dpi+85*dpi,"编号: "+bookList[i-1]->getStringByTag("id"));
            painter.drawText(300*dpi,h-130*dpi+110*dpi,"借阅数量:"+ QString::number(bookList[i-1]->getIntByTag("bor_count"))+"     查询次数： "+QString::number(bookList[i-1]->getIntByTag("refer_count")));
        }
        else
        {
            painter.setPen(titleText);
            painter.setFont(titleFont);
            painter.drawText(220*dpi,h-35*dpi+22*dpi,(bookList[i-1]->getStringByTag("title")));
        }
    }
    //每项高35，

}

void BookOverviewWindow::mouseMoveEvent(QMouseEvent *event)
{
    int y=(event->pos()).y();
    int x=(event->pos()).x();
    if(x<200*dpi||x>820*dpi||y<240*dpi||y>820*dpi)
        return;
    if(y>=240*dpi&&y-240*dpi<(cursorLayer-1)*35*dpi)
    {
        cursorLayer=(y-240*dpi)/(35*dpi)+1;
        update();
    }
    else if(y-240*dpi>=(cursorLayer+3)*35*dpi&&y<this->height())
    {
        cursorLayer=(y-240*dpi)/(35*dpi)-2;
        update();
    }
    if(cursorLayer>=5)         //除尾页外每页显示9组数据,鼠标层数为10则置为9
        cursorLayer=5;
    else if(bookList.size()<5&&cursorLayer>=(bookList.size()-1)%5+1)      //尾页显示books.size()%10+1组数据,鼠标层数超过则显示最后一组
        cursorLayer=(bookList.size()-1)%9+1;
}

void BookOverviewWindow::mousePressEvent(QMouseEvent *mouseEvent)
{

}

void BookOverviewWindow::moveLeft()
{
    int l=booklist.size();
    if(l<=4)
        return;
    //for(int i=0;i<5;i++)
    for(int i=0;i<6;i++)
    {
        //moveAction_Cover[i].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+i)%6]);
        moveAction_Cover[i].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+i)%7]);
        moveAction_Cover[i].setPropertyName("geometry");
        moveAction_Cover[i].setDuration(400);
        moveAction_Cover[i].setStartValue(r_Cover[i+1]);
        moveAction_Cover[i].setEndValue(r_Cover[i]);
        moveAction_Cover[i].setEasingCurve(QEasingCurve::Linear);
        moveAction_Cover[i].start();

        //moveAction_Title[i].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+i)%6]);
        moveAction_Title[i].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+i)%7]);
        moveAction_Title[i].setPropertyName("geometry");
        moveAction_Title[i].setDuration(400);
        moveAction_Title[i].setStartValue(r_Title[i+1]);
        moveAction_Title[i].setEndValue(r_Title[i]);
        moveAction_Title[i].setEasingCurve(QEasingCurve::Linear);
        moveAction_Title[i].start();
    }
    repaint();
}

void BookOverviewWindow::graduallyDisappearL()
{
    int l=booklist.size();
    if(l<=4)
        return;
    opacityAction_Cover[0].setTargetObject(coversOnDisplay[firstIndexOnDisplay]);
    opacityAction_Cover[0].setPropertyName("opacity");
    opacityAction_Cover[0].setDuration(400);
    opacityAction_Cover[0].setStartValue(1.0);
    opacityAction_Cover[0].setEndValue(0.0);
    opacityAction_Cover[0].setEasingCurve((QEasingCurve::Linear));
    opacityAction_Cover[0].start();

    //opacityAction_Cover[1].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+4)%6]);
    opacityAction_Cover[1].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+5)%7]);
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

    //opacityAction_Title[1].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+4)%6]);
    opacityAction_Title[1].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+5)%7]);
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
    if(l<=4)
        return;
    //int lastIndex=(firstIndexOnDisplay+5)%6;
    //int indexToload=(firstIndexInBookList+5)%l;
    int lastIndex=(firstIndexOnDisplay+6)%7;
    int indexToload=(firstIndexInBookList+6)%l;

    coversOnDisplay[lastIndex]->setPixmap(QPixmap(booklist[indexToload].getStringByTag("loc")).scaled(135*dpi,190*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    QString title=booklist[indexToload].getStringByTag("title");
    titlesOnDisplay[lastIndex]->setText(title);
//    firstIndexOnDisplay=(firstIndexOnDisplay+1)%6;
//    firstIndexInBookList=(firstIndexInBookList+1)%l;
    firstIndexOnDisplay=(firstIndexOnDisplay+1)%7;
    firstIndexInBookList=(firstIndexInBookList+1)%l;

    timerL->stop();
}

void BookOverviewWindow::startTimerL()
{
    int l=booklist.size();
    if(l<=4)
        return;
    timerL->start(400);
}

void BookOverviewWindow::moveRight()
{
    int l=booklist.size();
    if(l<=4)
        return;
    //for(int i=0;i<5;i++)
    for(int i=0;i<6;i++)
    {
        //moveAction_Cover[i].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+i+5)%6]);
        moveAction_Cover[i].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+i+6)%7]);
        moveAction_Cover[i].setPropertyName("geometry");
        moveAction_Cover[i].setDuration(400);
        moveAction_Cover[i].setStartValue(r_Cover[i]);
        moveAction_Cover[i].setEndValue(r_Cover[i+1]);
        moveAction_Cover[i].setEasingCurve(QEasingCurve::Linear);
        moveAction_Cover[i].start();

        //moveAction_Title[i].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+i+5)%6]);
        moveAction_Title[i].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+i+6)%7]);
        moveAction_Title[i].setPropertyName("geometry");
        moveAction_Title[i].setDuration(400);
        moveAction_Title[i].setStartValue(r_Title[i]);
        moveAction_Title[i].setEndValue(r_Title[i+1]);
        moveAction_Title[i].setEasingCurve(QEasingCurve::Linear);
        moveAction_Title[i].start();
    }
    repaint();
}

void BookOverviewWindow::graduallyDisappearR()
{
    int l=booklist.size();
    if(l<=4)
        return;
    //opacityAction_Cover[0].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+5)%6]);
    opacityAction_Cover[0].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+6)%7]);
    opacityAction_Cover[0].setPropertyName("opacity");
    opacityAction_Cover[0].setDuration(400);
    opacityAction_Cover[0].setStartValue(0.0);
    opacityAction_Cover[0].setEndValue(1.0);
    opacityAction_Cover[0].setEasingCurve((QEasingCurve::Linear));
    opacityAction_Cover[0].start();

    //opacityAction_Cover[1].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+3)%6]);
    opacityAction_Cover[1].setTargetObject(coversOnDisplay[(firstIndexOnDisplay+4)%7]);
    opacityAction_Cover[1].setPropertyName("opacity");
    opacityAction_Cover[1].setDuration(400);
    opacityAction_Cover[1].setStartValue(1.0);
    opacityAction_Cover[1].setEndValue(0.0);
    opacityAction_Cover[1].setEasingCurve((QEasingCurve::Linear));
    opacityAction_Cover[1].start();

    //opacityAction_Title[0].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+5)%6]);
    opacityAction_Title[0].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+6)%7]);
    opacityAction_Title[0].setPropertyName("opacity");
    opacityAction_Title[0].setDuration(400);
    opacityAction_Title[0].setStartValue(0.0);
    opacityAction_Title[0].setEndValue(1.0);
    opacityAction_Title[0].setEasingCurve((QEasingCurve::Linear));
    opacityAction_Title[0].start();

    //opacityAction_Title[1].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+3)%6]);
    opacityAction_Title[1].setTargetObject(titlesOnDisplay[(firstIndexOnDisplay+4)%7]);
    opacityAction_Title[1].setPropertyName("opacity");
    opacityAction_Title[1].setDuration(400);
    opacityAction_Title[1].setStartValue(1.0);
    opacityAction_Title[1].setEndValue(0.0);
    opacityAction_Title[1].setEasingCurve((QEasingCurve::Linear));
    opacityAction_Title[1].start();
}

void BookOverviewWindow::changeOrderR()
{
    int l=booklist.size();
    if(l<=4)
        return;
//    int firstIndex=(firstIndexOnDisplay+4)%6;
//    int indexToload=(firstIndexInBookList-2+l)%l;

    int firstIndex=(firstIndexOnDisplay+5)%7;
    int indexToload=(firstIndexInBookList-2+l)%l;

    coversOnDisplay[firstIndex]->setPixmap(QPixmap(booklist[indexToload].getStringByTag("loc")).scaled(135*dpi,190*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    QString title=booklist[indexToload].getStringByTag("title");
    titlesOnDisplay[firstIndex]->setText(title);
    firstIndexOnDisplay=(firstIndexOnDisplay+6)%7;
    firstIndexInBookList=(firstIndexInBookList-1+l)%l;
    timerR->stop();
}

void BookOverviewWindow::changeCategory()
{
    ToolButton* clickedButton=qobject_cast<ToolButton*>(sender());
    int i=(clickedButton->objectName()).toInt();
    categoryOnDisplay=i;
    update();
}

void BookOverviewWindow::startTimerR()
{
    int l=booklist.size();
    if(l<=4)
        return;
    timerR->start(400);
}

void BookOverviewWindow::noAction(){
    emit actionTimeout();
}

