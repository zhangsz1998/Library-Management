#include "signupwindow.h"
extern qreal dpi;
extern Reader * activereader;

SignUpWindow::SignUpWindow(QWidget *parent) : QDialog(parent)
{
    this->setGeometry(0*dpi,0*dpi,450*dpi,400*dpi);
    setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    this->setStyleSheet("background-color:#ebf2fa;border:1px; border-style:solid;border-color:white");

    closeBtn= new ToolButton(this,QColor(0,0,0,0),QColor(0,153,255,255));
    closeBtn->setEnterColor("#ff6666");
    closeBtn->setGeometry(this->width()-29*dpi,1*dpi,29*dpi,29*dpi);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    getUserName=new QLineEdit(this);
    getUserName->setGeometry(250*dpi,50*dpi,150*dpi,30*dpi);
    getUserName->setStyleSheet({"background-color:transparent;border:2px;"
                          "border-top:none;border-left:none;"
                          "border-right:none;border-color:#c0c0c0;border-style:solid;"
                          "border-top-left-radius:4px;border-top-right-radius: 4px;"});
    isStudent=new QRadioButton(this);
    isStudent->setGeometry(250*dpi,120*dpi,70*dpi,20*dpi);
    isStudent->setStyleSheet("border:none");
    isStudent->setFont(QFont("微软雅黑",10));
    isStudent->setText("学生");


    isTeacher=new QRadioButton(this);
    isTeacher->setGeometry(350*dpi,120*dpi,70*dpi,20*dpi);
    isTeacher->setStyleSheet("border:none");
    isTeacher->setFont(QFont("微软雅黑",10));
    isTeacher->setText("教师");

    getId=new QLineEdit(this);
    getId->setGeometry(250*dpi,180*dpi,150*dpi,30*dpi);
    getId->setStyleSheet({"background-color:transparent;border:2px;"
                          "border-top:none;border-left:none;"
                          "border-right:none;border-color:#c0c0c0;border-style:solid;"
                          "border-top-left-radius:4px;border-top-right-radius: 4px;"});

    getPassWord=new QLineEdit(this);
    getPassWord->setGeometry(250*dpi,240*dpi,150*dpi,30*dpi);
    getPassWord->setStyleSheet("background-color:transparent;border:1px ;border-color:#c0c0c0;border-style:solid;border-top-left-radius:4px;border-top-right-radius: 4px;");
    getPassWord->setStyleSheet({"background-color:transparent;border:2px;"
                          "border-top:none;border-left:none;"
                          "border-right:none;border-color:#c0c0c0;border-style:solid;"
                          "border-top-left-radius:4px;border-top-right-radius: 4px;"});

    confirmBtn=new ToolButton(this);
    confirmBtn->setPlainColor("#09a3dc");
    confirmBtn->setEnterColor("#3cc3f5");
    confirmBtn->setGeometry(280*dpi,290*dpi,100*dpi,35*dpi);
    confirmBtn->setText("确认");
    connect(confirmBtn,SIGNAL(clicked()),this,SLOT(addNewUser()));

    popUp=new MessageBox(this);
    popUp->setGeometry(30*dpi,30*dpi,popUp->width(),popUp->height());
    popUp->setVisible(false);
    connect(popUp->confirmBtn,SIGNAL(clicked()),this,SLOT(close()));
}

void SignUpWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont textFont("微软雅黑",13);
    painter.setFont(textFont);
    QPalette textpalette(QColor("#99ccff"));
    painter.drawText(250*dpi,40*dpi,"姓名");
    painter.drawText(250*dpi,110*dpi,"身份");
    painter.drawText(250*dpi,170*dpi,"ID");
    painter.drawText(250*dpi,230*dpi,"密码");
}

void SignUpWindow::addNewUser()
{
    QString userName=getUserName->text();
    QString agency;
    if(isStudent->isChecked())
        agency="st";
    else
        agency="te";
    QString id=getId->text();
    QString passWord=getPassWord->text();
    QString authority("1");
    QString credit("5");

    Reader newReader(Reader(userName,id,passWord,agency,authority,credit,0,0,0,0));
    if(add_newreader(newReader)==1)
    {
        saveXml2();
        popUp->setText("注册成功");
        int tmp;
        activereader = sign_in(id,passWord,tmp);
        emit signedUp();
        popUp->setVisible(true);
    }
    else
    {
        popUp->setText("用户已存在！");
        popUp->setVisible(true);
    }
    this->getId->clear();
    this->getUserName->clear();
    this->getUserName->clear();
    this->getPassWord->clear();
    isStudent->setChecked(false);
    isTeacher->setChecked(false);
}
