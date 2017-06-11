#include "authoritycheckwindow.h"
AuthorityCheckWindow::AuthorityCheckWindow(QWidget *parent):
    QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("border:1px;border-style:solid;border-radius:4px;border-color:black");

    closeBtn= new ToolButton(this,QColor(0,0,0,0),QColor(0,153,255,255));
    closeBtn->setEnterColor("#ff6666");
    closeBtn->setGeometry(470*dpi,1*dpi,29*dpi,29*dpi);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    getPassWord=new QLineEdit(this);
    getPassWord->setGeometry(90*dpi,90*dpi,300*dpi,40*dpi);
    getPassWord->setStyleSheet("background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius:10px;padding: 4px");
    getPassWord->setFont(QFont("微软雅黑",20));
    getPassWord->setEchoMode(QLineEdit::Password);

    confirmBtn=new ToolButton(this,QColor(153,204,255,255),QColor(0,153,255,255));
    confirmBtn->setGeometry(400*dpi,90*dpi,80*dpi,40*dpi);
    confirmBtn->setFont(QFont("微软雅黑",15));
    confirmBtn->setText("确认");
    connect(this->confirmBtn,SIGNAL(clicked()),this,SLOT(isAdmin()));
    connect(this->confirmBtn,SIGNAL(clicked()),this,SLOT(close()));
}

AuthorityCheckWindow::~AuthorityCheckWindow()
{
    delete getPassWord;
    delete confirmBtn;
    delete closeBtn;
}

void AuthorityCheckWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont textFont("微软雅黑",20);
    QRect rect(0*dpi,50*dpi,this->width(),this->height()/5);
    painter.setFont(textFont);
    painter.drawText(rect,Qt::AlignCenter,"请输入管理员密码：");
}

void AuthorityCheckWindow::isAdmin()
{
    if(getPassWord->text()=="123")      //条件待定，因缺少用户信息
        emit isAuthorized();
    else
        emit notAuthorized();
    getPassWord->clear();
}
