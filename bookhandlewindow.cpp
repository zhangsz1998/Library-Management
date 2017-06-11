#include "bookhandlewindow.h"

BookHandleWindow::BookHandleWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(250*dpi,100*dpi,275*dpi,140*dpi);
    this->setStyleSheet("background-color:#ebf2fa");

    getPattern=new QComboBox(this);
    getPattern->setGeometry(160*dpi,47*dpi,100*dpi,30*dpi);
    QStringList patterns;
    patterns<<"图书归还"<<"图书续借"<<"图书挂失";
    getPattern->addItems(patterns);
    getPattern->setFont(QFont("微软雅黑",12));
    getPattern->setStyleSheet(
                "QComboBox{background-color:transparent;border:1px;border-color:white;border-style:solid}"
                "QComboBox::drop-down{width:30px;height:30px;image:url(:/Images/Icons/DownArrow.png);}"
                );

    closeBtn= new ToolButton(this,QColor(0,0,0,0),QColor(0,153,255,255));
    closeBtn->setEnterColor("#ff6666");
    closeBtn->setGeometry(this->width()-29*dpi,1*dpi,29*dpi,29*dpi);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    confirmBtn=new ToolButton(this,QColor(153,204,255,255),QColor(0,153,255,255));
    confirmBtn->setPlainColor(QColor(153,204,255,255));
    confirmBtn->setGeometry(85*dpi,100*dpi,100*dpi,20*dpi);
    confirmBtn->setFont(QFont("微软雅黑"));
    confirmBtn->setText("确定");
    connect(confirmBtn,SIGNAL(clicked()),this,SLOT(emitPattern()));
    connect(confirmBtn,SIGNAL(clicked()),this,SLOT(close()));

}

BookHandleWindow::~BookHandleWindow()
{
    delete getPattern;
    delete closeBtn;
    delete confirmBtn;
}

void BookHandleWindow::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setFont(QFont("微软雅黑",13));
    painter.drawText(10*dpi,70*dpi,"请选择一种操作: ");
}

void BookHandleWindow::emitPattern()
{

    if(getPattern->currentText()=="图书归还")
        emit returnPatternConfirmed();
    else if(getPattern->currentText()=="图书续借")
        emit renewPatternConfirmed();
    else
        emit lossPatternConfirmed();
}
