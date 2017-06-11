#include "rechargewindow.h"

RechargeWindow::RechargeWindow(QWidget *parent) : QDialog(parent)
{
    this->setGeometry(400*dpi,200*dpi,400*dpi,100*dpi);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:#ebf2fa");

    closeBtn= new ToolButton(this,QColor(0,0,0,0),QColor(0,153,255,255));
    closeBtn->setEnterColor("#ff6666");
    closeBtn->setGeometry(this->width()-30*dpi,1*dpi,29*dpi,29*dpi);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    confirmBtn=new ToolButton(this,QColor(153,204,255,255),QColor(0,153,255,255));
    confirmBtn->setPlainColor(QColor(153,204,255,255));
    confirmBtn->setGeometry(this->width()/3,70*dpi,100*dpi,20*dpi);
    confirmBtn->setText("确定");
    connect(confirmBtn,SIGNAL(clicked()),this,SLOT(emitChargeRequest()));

    getMoney=new QSpinBox(this);
    getMoney->setMaximum(2000);
    getMoney->setMinimum(0);
    getMoney->setGeometry(200*dpi,30*dpi,100*dpi,30*dpi);\
    getMoney->setStyleSheet(
                "QSpinBox{background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius: 4px}"
                "QSpinBox::down-button{width:30px;height:30px;image:url(:/Images/Icons/DownArrow.png);}"
                "QSpinBox::up-button{width:30px;height:30px;image:url(:/Images/Icons/UpArrow.png);}}"
                );
    getMoney->setFont(QFont("微软雅黑",12));
}

RechargeWindow::~RechargeWindow()
{
    delete getMoney;
    delete closeBtn;
    delete confirmBtn;
}

void RechargeWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont titleFont("微软雅黑",15);
    titleFont.setBold(true);

    painter.setFont(titleFont);
    painter.drawText(30*dpi,50*dpi,"请输入充值金额");
}

void RechargeWindow::emitChargeRequest()
{
    emit chargeRequest();
}

int RechargeWindow::getValue()
{
    return getMoney->value();
}
