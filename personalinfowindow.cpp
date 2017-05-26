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

    showBookInfoBtn=new ToolButton(this);
    showBookInfoBtn->setFont(QFont("微软雅黑",15));
    showBookInfoBtn->setPlainColor("#ff0099ff");
    showBookInfoBtn->setEnterColor("#ebf2fa");
    showBookInfoBtn->setPalette(textPalette);
    showBookInfoBtn->setGeometry(0*dpi,250*dpi,200*dpi,50*dpi);
    showBookInfoBtn->setText("图书相关信息");
    connect(showBookInfoBtn,SIGNAL(clicked()),this,SLOT(showBookInfo()));

    showMessagesBtn=new ToolButton(this);
    showMessagesBtn->setFont(QFont("微软雅黑",15));
    showMessagesBtn->setPlainColor("#ff0099ff");
    showMessagesBtn->setEnterColor("#ebf2fa");
    showMessagesBtn->setPalette(textPalette);
    showMessagesBtn->setGeometry(0*dpi,300*dpi,200*dpi,50*dpi);
    showMessagesBtn->setText("系统消息");
    connect(showMessagesBtn,SIGNAL(clicked()),this,SLOT(showMessagesInfo()));
}

void PersonalInfoWindow::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    QPixmap partBackGround(":/Images/background.png");
    painter.drawPixmap(0,0,partBackGround.scaled(200*dpi,this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if(activereader->getStringByTag("agency")=="st")
        painter.drawPixmap(35*dpi,50*dpi,QPixmap(":/Images/Icons/Student.png").scaled(150*dpi,150*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    else
        painter.drawPixmap(35*dpi,50*dpi,QPixmap(":/Images/Icons/Teacher.png").scaled(150*dpi,150*dpi, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if(pattern==PersonalInfo)
    {
        showPersonalInfoBtn->setStyleSheet("background-color:#ffffff");
        showBookInfoBtn->setEnabled(true);
        showPersonalInfoBtn->setEnabled(false);
        showMessagesBtn->setEnabled(true);
    }
    else if(pattern==BookInfo)
    {
        showBookInfoBtn->setStyleSheet("background-color:#ffffff");
        showBookInfoBtn->setEnabled(false);
        showPersonalInfoBtn->setEnabled(true);
        showMessagesBtn->setEnabled(true);
    }
    else if(pattern==Messages)
    {
        showMessagesBtn->setStyleSheet("background-color:#ffffff");
        showBookInfoBtn->setEnabled(true);
        showPersonalInfoBtn->setEnabled(true);
        showMessagesBtn->setEnabled(false);
    }
}

void PersonalInfoWindow::showPersonalInfo()
{
    pattern=PersonalInfo;
    this->update();
}

void PersonalInfoWindow::showBookInfo()
{
    pattern=BookInfo;
    this->update();
}

void PersonalInfoWindow::showMessagesInfo()
{
    pattern=Messages;
    this->update();
}
