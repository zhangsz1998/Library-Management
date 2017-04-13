#include "messagebox.h"

MessageBox::MessageBox(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(0,0,250,175);
    this->icon=Q_NULLPTR;

    closeBtn= new ToolButton(this,QColor(0,0,0,0),QColor(0,153,255,255));
    closeBtn->setGeometry(220,0,30,30);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    confirmBtn=new ToolButton(this,QColor(204,255,204,255),QColor(0,153,255,255));
    confirmBtn->setPlainColor(QColor(153,204,255,255));
    confirmBtn->setGeometry(75,130,100,20);
    confirmBtn->setFont(QFont("幼圆"));
    confirmBtn->setText("确定");
    connect(confirmBtn,SIGNAL(clicked()),this,SLOT(close()));
}

MessageBox::~MessageBox()
{
    delete closeBtn;
    delete confirmBtn;
    if(icon)
       delete icon;
}

void MessageBox::setText(QString text)
{
    (this->text)=text;
}

void MessageBox::setIcon(QPixmap pixmap)
{
    if(!(this->icon))
        delete icon;
    icon=new QPixmap(pixmap);
}

void MessageBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont textFont("微软雅黑",20);
    QRect rect(0,50,250,75);
    painter.setFont(textFont);
    painter.drawText(rect,Qt::AlignCenter,(this->text));
}
