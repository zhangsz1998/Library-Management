#include "bookinfowindow.h"
#include <QPainter>

extern qreal dpi;
extern Reader* activereader;
extern QDate systemDate;

BookInfoWindow::BookInfoWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:#ffffff; border:none");

    borrowBtn=new ToolButton(this);
    borrowBtn->setGeometry(60*dpi,323*dpi,150*dpi,40*dpi);
    borrowBtn->setIcon(QPixmap(":/Images/Icons/borrowbookBtn2.png"));
    borrowBtn->setIconSize(QSize(150*dpi,40*dpi));
    connect(borrowBtn,SIGNAL(clicked()),this,SLOT(borrowEvent()));

    reservationBtn=new ToolButton(this);
    reservationBtn->setGeometry(60*dpi,373*dpi,150*dpi,40*dpi);
    reservationBtn->setIcon(QPixmap(":/Images/Icons/ReservationBtn.png"));
    reservationBtn->setIconSize(QSize(150*dpi,40*dpi));
    connect(reservationBtn,SIGNAL(clicked()),this,SLOT(resvEvent()));

    goBackBtn=new ToolButton(this);
    goBackBtn->setGeometry(15*dpi,480*dpi,40*dpi,40*dpi);
    goBackBtn->setIcon(QPixmap(":/Images/Icons/Goback.png"));
    goBackBtn->setIconSize(QSize(40*dpi,40*dpi));

    borrowForm = new BorrowForm(this);
    borrowForm->setVisible(false);

    resvForm = new ResvForm(this);
    resvForm->setVisible(false);

    popUp=new MessageBox(this);
    popUp->setGeometry(220*dpi,150*dpi,popUp->width(),popUp->height());
    popUp->setVisible(false);
}

BookInfoWindow::loadBook(Book *book)
{
    this->book=book;
    despList.clear();
    int l=0;
    QString desp=book->getStringByTag("description");
    while(l<(desp.length()))
    {
        QString a=desp.mid(l,44);
        int i=a.indexOf("\n");
        if(i!=-1&&i!=0)
        {
            a=a.mid(0,i);
            l+=i;
        }
        else
        {
            l+=44;
        }
        despList.push_back(a);
    }
    cover.load(book->getStringByTag("loc"));
}

BookInfoWindow::~BookInfoWindow()
{
    delete borrowBtn;
    delete goBackBtn;
    delete reservationBtn;
    delete borrowForm;
    delete resvForm;
}

void BookInfoWindow::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);

    QPen dashLine(QColor("#cccccc"));
    QPen textPen(QColor("#000000"));
    QPen labelPen(QColor("#999999"));
    dashLine.setStyle(Qt::DashLine);

    QFont textFont("微软雅黑",15);
    QFont titleFont("微软雅黑",25);
    titleFont.setBold(true);
    QFont descriptionFont("宋体",10);
    QFont despFont("微软雅黑",20);
    despFont.setBold(true);       //内容简介这四个字的字体

    painter.setFont(titleFont);
    painter.setPen(textPen);
    painter.drawText(270*dpi,50*dpi,book->getStringByTag("title"));

    painter.setPen(dashLine);
    painter.drawLine(260*dpi,10*dpi,260*dpi,520*dpi);

    painter.setPen(labelPen);
    painter.setFont(textFont);
    //每行宽度为30*dpi
    painter.drawText(270*dpi,80*dpi,"作者:");
    painter.drawText(270*dpi,110*dpi,"出版社:");
    painter.drawText(270*dpi,140*dpi,"编号:");
    painter.drawText(270*dpi,170*dpi,"剩余量:");
    painter.drawText(450*dpi,170*dpi,"馆藏数量:");
    painter.drawText(580*dpi,170*dpi,"类别:");

    painter.setPen(textPen);
    painter.drawText(320*dpi,80*dpi,book->getStringByTag("author"));
    painter.drawText(345*dpi,110*dpi,book->getStringByTag("press"));
    painter.drawText(320*dpi,140*dpi,book->getStringByTag("id"));
    if (book->getIntByTag("amount")) painter.drawText(345*dpi,170*dpi,QString::number(book->getIntByTag("amount")));
    else painter.drawText(345*dpi,170*dpi,QString("暂无库存"));
    painter.drawText(540*dpi,170*dpi,QString::number(book->getIntByTag("total")));
    painter.drawText(635*dpi,170*dpi,book->getStringByTag("category"));
    painter.setPen(labelPen);
    painter.setFont(despFont);
    painter.drawText(270*dpi,210*dpi,"内容简介");
    //绘制简介
    painter.setFont(descriptionFont);
    painter.setPen(textPen);
    int h=240*dpi;
    for(int i=0;i<despList.size();i++)
    {
        painter.drawText(270*dpi,h+i*20*dpi,despList.at(i));
    }

    //绘制封面
    painter.drawPixmap(40*dpi,40*dpi,cover.scaled(200*dpi,267*dpi,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

}

void BookInfoWindow::borrowEvent(){
    if(activereader!=Q_NULLPTR)
    {
        int num = activereader->getIntByTag("bor_num");
        int count = 0;
        for (int i=0;i<num;i++)
            if (activereader->bor_list[i].id == book->getStringByTag("id")) count++;
        if (count > 2){
            popUp->setText("借书数量过多");
            popUp->setVisible(true);
        }
        else if (activereader->balance <=0){
            popUp->setText("余额不足，请充值");
            popUp->setVisible(true);
        }
        else if (book->getIntByTag("amount") == 0){
            popUp->setText("暂无库存");
            popUp->setVisible(true);
        }
        else if ((activereader->getStringByTag("credit")=="3" && activereader->getIntByTag("bor_num")>=3)||(activereader->getStringByTag("credit")=="2" && activereader->getIntByTag("bor_num")>=10) || activereader->getIntByTag("bor_num")>=20){
            QString tmp = "信用等级限制借书数量<";
            if (activereader->getStringByTag("credit")=="3") tmp+="3本";
            else if (activereader->getStringByTag("credit")=="2") tmp+="10本";
            else tmp +="20本";
            popUp->setText(tmp);
            popUp->setVisible(true);
        }
        else{
            int flag = 0;
            int num = activereader->getIntByTag("resv_num");
            for (int i=0;i<num;i++){
                if (activereader->resvs[i] == book->getStringByTag("id")) {
                    flag = 1;
                    break;
                }
            }
            if (book->getIntByTag("amount") == 1 && book->is_resv && !flag){
                    popUp->setText("该图书处于预定状态");
                    popUp->setVisible(true);
            }
            else {
                borrowForm->setBook(book);
                borrowForm->setReader(activereader);
                borrowForm->setVisible(true);
            }
        }
    }
    else
    {
        popUp->setText("请先登录");
        popUp->setVisible(true);
    }
}

void BookInfoWindow::resvEvent(){
    if (activereader!=Q_NULLPTR){
        int flag=0;
        for (int i=0;i<activereader->getIntByTag("resv_num");i++)
            if (book->getStringByTag("id") == activereader->resvs[i]) flag =1;
        if (flag){
            popUp->setText("不能重复预约");
            popUp->setVisible(true);
        }else {
            if (book->getIntByTag("amount")==0){
                resvForm->setBook(book);
                resvForm->setReader(activereader);
                resvForm->setVisible(true);
            }else {
                popUp->setText("仍有库存，无需预约");
                popUp->setVisible(true);
            }
        }
    }
    else {
        popUp->setText("请先登录");
        popUp->setVisible(true);
    }
}
