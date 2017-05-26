#include "borrowform.h"

extern qreal dpi;

BorrowForm::BorrowForm(QWidget *parent):
    QDialog(parent){
   // this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(0*dpi,0*dpi,550*dpi,480*dpi);
    this->icon=Q_NULLPTR;

    cancelBtn = new ToolButton(this,QColor(204,255,204,255),QColor(0,153,255,255));
    cancelBtn->setGeometry(320*dpi,420*dpi,100*dpi,30*dpi);
    cancelBtn->setPlainColor(QColor(30,136,229,255));
    cancelBtn->setFont(QFont("微软雅黑"));
    cancelBtn->setText("取消");

    comfirmBtn = new ToolButton(this,QColor(204,255,204,255),QColor(0,153,255,255));
    comfirmBtn->setGeometry(130*dpi,420*dpi,100*dpi,30*dpi);
    comfirmBtn->setPlainColor(QColor(30,136,229,255));
    comfirmBtn->setFont(QFont("微软雅黑"));
    comfirmBtn->setText("确定");

}

BorrowForm::~BorrowForm(){
    delete cancelBtn;
    delete comfirmBtn;
    if (icon) delete icon;
}

void BorrowForm::setBook(Book & item){
    this->item = item;
}

void BorrowForm::setReader(Reader & borrower){
    this->borrower = borrower;
}

void BorrowForm::setIcon(QPixmap pixmap){
    if (this->icon)
        delete icon;
    icon = new QPixmap(pixmap);
}

void BorrowForm::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QFont textFont("微软雅黑",15);
    //QRect rect(30*dpi,30*dpi,60*dpi,25*dpi);
    painter.setFont(textFont);
    painter.drawText(30*dpi,50*dpi,QString("书名:"));
    //rect.adjust(90*dpi,30*dpi,100*dpi,25*dpi);
    painter.drawText(90*dpi,50*dpi,(this->item.getStringByTag("title")));
    //rect.adjust(200*dpi,30*dpi,60*dpi,25*dpi);
    painter.drawText(200*dpi,50*dpi,QString("编号:"));
    //rect.adjust(260*dpi,30*dpi,100*dpi,25*dpi);
    painter.drawText(260*dpi,50*dpi,(this->item.getStringByTag("id")));
    //rect.adjust(360*dpi,30*dpi,60*dpi,25*dpi);
    painter.drawText(360*dpi,50*dpi,QString("类别:"));
    //rect.adjust(420*dpi,30*dpi,100*dpi,25*dpi);
    painter.drawText(420*dpi,50*dpi,(this->item.getStringByTag("category")));

    //rect.adjust(30*dpi,90*dpi,90*dpi,25*dpi);
    painter.drawText(30*dpi,110*dpi,QString("出版社:"));
    //rect.adjust(120*dpi,90*dpi,200*dpi,25*dpi);
    painter.drawText(120*dpi,110*dpi,(this->item.getStringByTag("press")));
    //rect.adjust(350*dpi,90*dpi,60*dpi,25*dpi);
    painter.drawText(350*dpi,110*dpi,QString("作者:"));
    //rect.adjust(410*dpi,90*dpi,80*dpi,25*dpi);
    painter.drawText(410*dpi,110*dpi,(this->item.getStringByTag("author")));

    //rect.adjust(30*dpi,150*dpi,100*dpi,25*dpi);
    painter.drawText(30*dpi,170*dpi,QString("馆藏数量:"));
    //rect.adjust(150*dpi,150*dpi,60*dpi,25*dpi);
    painter.drawText(150*dpi,170*dpi,QString(this->item.getIntByTag("total")));
    //rect.adjust(230*dpi,150*dpi,100*dpi,25*dpi);
    painter.drawText(230*dpi,170*dpi,QString("剩余数量:"));
    //rect.adjust(340*dpi,150*dpi,60*dpi,25*dpi);
    painter.drawText(340*dpi,170*dpi,QString(this->item.getIntByTag("amount")));

    painter.drawLine(30*dpi,220*dpi,510*dpi,220*dpi);

    //rect.adjust(30*dpi,250*dpi,60*dpi,25*dpi);
    painter.drawText(30*dpi,270*dpi,QString("姓名："));
    //rect.adjust(90*dpi,250*dpi,100*dpi,25*dpi);
    painter.drawText(90*dpi,270*dpi,(this->borrower.getStringByTag("name")));
    //rect.adjust(200*dpi,250*dpi,140*dpi,25*dpi);
    painter.drawText(220*dpi,270*dpi,QString("学号/教师编号:"));
    //rect.adjust(340*dpi,250*dpi,140*dpi,25*dpi);
    painter.drawText(360*dpi,270*dpi,(this->borrower.getStringByTag("id")));
    //rect.adjust(30*dpi,310*dpi,60*dpi,25*dpi);
    painter.drawText(30*dpi,330*dpi,QString("权限:"));
    //rect.adjust(90*dpi,310*dpi,100*dpi,25*dpi);
    painter.drawText(90*dpi,330*dpi,(this->borrower.getStringByTag("authority")));
    //rect.adjust(240*dpi,310*dpi,100*dpi,25*dpi);
    painter.drawText(240*dpi,330*dpi,QString("信用等级:"));
    //rect.adjust(350*dpi,310*dpi,100*dpi,25*dpi);
    painter.drawText(350*dpi,330*dpi,(this->borrower.getStringByTag("credit")));

}
