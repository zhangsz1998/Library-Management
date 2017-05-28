#include "personalinfowindow.h"

PersonalInfoWindow::PersonalInfoWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    this->setStyleSheet("background-color:#ffffff;border:none;border-radius:0px");
    pattern=PersonalInfo;

    QPalette textPalette(QColor("#ffffff"));

    showPersonalInfoBtn=new ToolButton(this);
    showPersonalInfoBtn->setFont(QFont("微软雅黑",15));
    showPersonalInfoBtn->setPlainColor("#ff0099ff");
    showPersonalInfoBtn->setEnterColor("#ebf2fa");
    showPersonalInfoBtn->setPalette(textPalette);
    showPersonalInfoBtn->setGeometry(0*dpi,200*dpi,200*dpi,50*dpi);
    showPersonalInfoBtn->setText("个人信息");
    connect(showPersonalInfoBtn,SIGNAL(clicked()),this,SLOT(showPersonalInfo()));

    showBorrowInfoBtn=new ToolButton(this);
    showBorrowInfoBtn->setFont(QFont("微软雅黑",15));
    showBorrowInfoBtn->setPlainColor("#ff0099ff");
    showBorrowInfoBtn->setEnterColor("#ebf2fa");
    showBorrowInfoBtn->setPalette(textPalette);
    showBorrowInfoBtn->setGeometry(0*dpi,250*dpi,200*dpi,50*dpi);
    showBorrowInfoBtn->setText("已借书籍");
    connect(showBorrowInfoBtn,SIGNAL(clicked()),this,SLOT(showBorrowInfo()));

    showReserveInfoBtn=new ToolButton(this);
    showReserveInfoBtn->setFont(QFont("微软雅黑",15));
    showReserveInfoBtn->setPlainColor("#ff0099ff");
    showReserveInfoBtn->setEnterColor("#ebf2fa");
    showReserveInfoBtn->setPalette(textPalette);
    showReserveInfoBtn->setGeometry(0*dpi,300*dpi,200*dpi,50*dpi);
    showReserveInfoBtn->setText("已预约书籍");
    connect(showReserveInfoBtn,SIGNAL(clicked()),this,SLOT(showReserveInfo()));

    area=new QScrollArea(this);
    area->setGeometry(230*dpi,310*dpi,615*dpi,205*dpi);
    messageArea=new MessageWidget(area);
    messageArea->setWindowFlags(Qt::FramelessWindowHint);
    messageArea->setGeometry(0*dpi,0*dpi,700*dpi,500*dpi);
    area->setWidget(messageArea);
    area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i=0;i<20;i++)
    {
        for(int j=0;j<3;j++)
        {
            borrowItem[i][j]=new QTableWidgetItem;
            borrowItem[i][j]->setText("");
        }
        for(int j=0;j<2;j++)
        {
            reserveItem[i][j]=new QTableWidgetItem;
            reserveItem[i][j]->setText("");
        }
    }
    QStringList columnLabels;
    QFont labelFont("微软雅黑",12);
    columnLabels<<"已借书籍"<<"借书时间"<<"期望归还时间";
    borrowInfo=new QTableWidget(20,3,this);
    borrowInfo->setHorizontalHeaderLabels(columnLabels);
    borrowInfo->setFocusPolicy(Qt::NoFocus);
    borrowInfo->setStyleSheet("background-color: #ffffff");
    borrowInfo->setGeometry(220*dpi,10*dpi,620*dpi,510*dpi);
    borrowInfo->setColumnWidth(0,370*dpi);
    borrowInfo->setColumnWidth(1,110*dpi);
    borrowInfo->setColumnWidth(2,110*dpi);
    borrowInfo->setEnabled(true);
    borrowInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    borrowInfo->setSelectionMode(QAbstractItemView::NoSelection);
    borrowInfo->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:white;border:0px;border-style:solid");
    borrowInfo->horizontalHeader()->setFont(labelFont);
    borrowInfo->horizontalHeader()->setFixedHeight(30*dpi);
    borrowInfo->verticalHeader()->hide();
    borrowInfo->setFont(QFont("微软雅黑",10));
    for(int row=0;row<20;row++)
        borrowInfo->setRowHeight(row,40*dpi);
    for(int i=0;i<20;i++)
    {
        borrowInfo->setItem(i,0,Q_NULLPTR);
        borrowInfo->setItem(i,1,Q_NULLPTR);
        borrowInfo->setItem(i,2,Q_NULLPTR);
    }
    borrowInfo->setVisible(false);

    QStringList columnLabels2;
    columnLabels2<<"已预预约图书"<<"预约日期";
    reserveInfo=new QTableWidget(20,2,this);
    reserveInfo->setHorizontalHeaderLabels(columnLabels2);
    reserveInfo->setFocusPolicy(Qt::NoFocus);
    reserveInfo->setStyleSheet("background-color: #ffffff");
    reserveInfo->setGeometry(300*dpi,10*dpi,620*dpi,510*dpi);
    reserveInfo->setColumnWidth(0,370*dpi);
    reserveInfo->setColumnWidth(1,110*dpi);
    reserveInfo->setEnabled(true);
    reserveInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    reserveInfo->setSelectionMode(QAbstractItemView::NoSelection);
    reserveInfo->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:white;border:0px;border-style:solid");
    reserveInfo->horizontalHeader()->setFont(labelFont);
    reserveInfo->horizontalHeader()->setFixedHeight(30*dpi);
    reserveInfo->verticalHeader()->hide();
    reserveInfo->setFont(QFont("微软雅黑",10));
    for(int row=0;row<20;row++)
        reserveInfo->setRowHeight(row,40*dpi);
    for(int i=0;i<20;i++)
    {
        reserveInfo->setItem(i,0,Q_NULLPTR);
        reserveInfo->setItem(i,1,Q_NULLPTR);
        reserveInfo->setItem(i,2,Q_NULLPTR);
    }
    reserveInfo->setVisible(false);

}

void PersonalInfoWindow::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    QPixmap partBackGround(":/Images/background.png");
    QPen textPen(QColor("#000000"));
    QFont textFont("微软雅黑",15);
    QFont titleFont("微软雅黑",15);
    titleFont.setBold(true);
    painter.drawPixmap(0,0,partBackGround.scaled(200*dpi,this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if(activereader->getStringByTag("agency")=="st")
        painter.drawPixmap(35*dpi,50*dpi,QPixmap(":/Images/Icons/Student.png").scaled(150*dpi,150*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    else
        painter.drawPixmap(35*dpi,50*dpi,QPixmap(":/Images/Icons/Teacher.png").scaled(150*dpi,150*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if(pattern==PersonalInfo)
    {
        messageArea->loadMessage(activereader->msg,activereader->getIntByTag("msg_num"));
        messageArea->setVisible(true);
        area->setVisible(true);
        borrowInfo->setVisible(false);
        reserveInfo->setVisible(false);
        showPersonalInfoBtn->setStyleSheet("background-color:#ffffff");
        showBorrowInfoBtn->setEnabled(true);
        showPersonalInfoBtn->setEnabled(false);
        showReserveInfoBtn->setEnabled(true);

        painter.setPen(textPen);
        painter.setFont(titleFont);
        painter.drawText(220*dpi,50*dpi,"姓名: ");
        painter.drawText(220*dpi,90*dpi,"职位: ");
        painter.drawText(220*dpi,130*dpi,"ID：");
        painter.drawText(220*dpi,170*dpi,"权限: ");
        painter.drawText(220*dpi,210*dpi,"违约次数: ");
        painter.drawText(220*dpi,250*dpi,"信用等级: ");
        painter.drawText(220*dpi,290*dpi,"系统消息: ");

        QRect messageRect(220*dpi,300*dpi,630*dpi,220*dpi);
        painter.drawRoundedRect(messageRect,10.0,10.0);

        painter.setFont(textFont);
        painter.drawText(290*dpi,50*dpi,activereader->getStringByTag("name"));
        if(activereader->getStringByTag("agency")=="st")
            painter.drawText(290*dpi,90*dpi,"学生");
        else
            painter.drawText(290*dpi,90*dpi,"教师");
        painter.drawText(290*dpi,130*dpi,activereader->getStringByTag("id"));
        if(activereader->getStringByTag("authority")=="1")
            painter.drawText(290*dpi,170*dpi,"普通用户");
        else
            painter.drawText(290*dpi,170*dpi,"管理员");
        painter.drawText(320*dpi,210*dpi,QString::number(activereader->getIntByTag("illegal_count")));
        if(activereader->getStringByTag("credit")=="5")
            painter.drawText(320*dpi,250*dpi,"良好");
        if(activereader->getStringByTag("credit")=="2")
            painter.drawText(320*dpi,250*dpi,"较差");
    }
    else if(pattern==BorrowInfo)
    {
        int l=activereader->getIntByTag("bor_num");
        messageArea->loadMessage(activereader->msg,activereader->getIntByTag("msg_num"));
        borrowInfo->setVisible(true);
        reserveInfo->setVisible(false);
        messageArea->setVisible(false);
        area->setVisible(false);
        showBorrowInfoBtn->setStyleSheet("background-color:#ffffff");
        showBorrowInfoBtn->setEnabled(false);
        showPersonalInfoBtn->setEnabled(true);
        showReserveInfoBtn->setEnabled(true);
        for(int row=0;row<l;row++)
        {
            Book* borrowedBook=search(activereader->bor_list[row].id,5)[0];
            borrowItem[row][0]->setText(borrowedBook->getStringByTag("title"));
            borrowItem[row][1]->setText((activereader->bor_list)[row].st.toString("yyyy-MM-dd"));
            borrowItem[row][2]->setText((activereader->bor_list)[row].exp.toString("yyyy-MM-dd"));
            borrowInfo->setItem(row,0,borrowItem[row][0]);
            borrowInfo->setItem(row,1,borrowItem[row][1]);
            borrowInfo->setItem(row,2,borrowItem[row][2]);
        }
        for(int i=l;i<20;i++)
        {
            borrowItem[i][0]->setText("");
            borrowItem[i][1]->setText("");
            borrowItem[i][2]->setText("");
            borrowInfo->setItem(i,0,borrowItem[i][0]);
            borrowInfo->setItem(i,1,borrowItem[i][1]);
            borrowInfo->setItem(i,2,borrowItem[i][2]);
        }
    }
    else
    {
        int l=activereader->getIntByTag("resv_num");
        messageArea->setVisible(false);
        area->setVisible(false);
        borrowInfo->setVisible(false);
        reserveInfo->setVisible(true);
        showReserveInfoBtn->setStyleSheet("background-color:#ffffff");
        showReserveInfoBtn->setEnabled(false);
        showPersonalInfoBtn->setEnabled(true);
        showBorrowInfoBtn->setEnabled(true);
        for(int row=0;row<l;row++)
        {
            Book* reservedBook=search((activereader->resvs[row]).id,5)[0];
            reserveItem[row][0]->setText(reservedBook->getStringByTag("title"));
            reserveItem[row][1]->setText((activereader->resvs)[row].d.toString("yyyy-MM-dd"));
            reserveInfo->setItem(row,0,reserveItem[row][0]);
            reserveInfo->setItem(row,1,reserveItem[row][1]);
        }
        for(int i=l;i<20;i++)
        {
            reserveItem[i][0]->setText("");
            reserveItem[i][1]->setText("");
            reserveInfo->setItem(i,0,reserveItem[i][0]);
            reserveInfo->setItem(i,1,reserveItem[i][1]);
        }
    }
}

void PersonalInfoWindow::showPersonalInfo()
{
    pattern=PersonalInfo;
    showBorrowInfoBtn->setStyleSheet("background-color: #0099ff");
    showReserveInfoBtn->setStyleSheet("background-color: #0099ff");
    this->update();
}

void PersonalInfoWindow::showBorrowInfo()
{
    pattern=BorrowInfo;
    showPersonalInfoBtn->setStyleSheet("background-color: #0099ff");
    showReserveInfoBtn->setStyleSheet("background-color: #0099ff");
    this->update();
}
void PersonalInfoWindow::showReserveInfo()
{
    pattern=ReserveInfo;
    showPersonalInfoBtn->setStyleSheet("background-color: #0099ff");
    showBorrowInfoBtn->setStyleSheet("background-color: #0099ff");
    this->update();
}
