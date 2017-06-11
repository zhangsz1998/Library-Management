#include "messagewidget.h"

MessageWidget::MessageWidget(QWidget *parent) : QWidget(parent)
{

}

MessageWidget::~MessageWidget()
{
}

void MessageWidget::loadMessage(QString m_msg[], int num)
{
    for(int i=0;i<num;i++)
    {
        msg[i]=&m_msg[i];
    }
    msg_num=num;
    return;
}

void MessageWidget::paintEvent(QPaintEvent *event)
{
    QPainter messagePainter(this);
    messagePainter.setFont(QFont("微软雅黑",15));
    for(int i=(msg_num-1),j=1;i>=0;i--)
    {
        messagePainter.drawText(10*dpi,20*dpi+(j-1)*35*dpi,QString::number(j)+". "+*msg[i]);
        messagePainter.drawLine(10*dpi,25*dpi+(j-1)*35*dpi,this->width()-10*dpi,25*dpi+(j-1)*35*dpi);
        j++;
    }
}


