#include "messagebox.h"

extern qreal dpi;

MessageBox::MessageBox(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(0*dpi,0*dpi,250*dpi,175*dpi);
    this->setStyleSheet("border:1px;border-style:solid;border-color:black;border-radius: 4px");
    this->icon=Q_NULLPTR;

    closeBtn= new ToolButton(this,QColor(0,0,0,0),QColor(0,153,255,255));
    closeBtn->setEnterColor("#ff6666");
    closeBtn->setGeometry(220*dpi,1*dpi,29*dpi,29*dpi);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    confirmBtn=new ToolButton(this,QColor(153,204,255,255),QColor(0,153,255,255));
    confirmBtn->setPlainColor(QColor(153,204,255,255));
    confirmBtn->setGeometry(75*dpi,130*dpi,100*dpi,20*dpi);
    confirmBtn->setFont(QFont("微软雅黑"));
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

QString MessageBox::getText()
{
    return text;
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
    QRect rect(0*dpi,50*dpi,250*dpi,75*dpi);
    painter.setFont(textFont);
    painter.drawText(rect,Qt::AlignCenter,(this->text));
}
