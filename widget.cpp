#include "ui_widget.h"
#include "searchbar.h"
#include "widget.h"
#include <QDebug>
#include "book_mgmt.h"

extern QDate systemDate;
extern qreal dpi;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setGeometry(320*dpi,90*dpi,1024*dpi,725*dpi);
    setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setStyleSheet("background-color:#99ccff;");

    //添加最小化按钮
    minimizeBtn=new ToolButton(this);
    QPixmap minPix=style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    minimizeBtn->setIcon(minPix);
    minimizeBtn->setStyleSheet("background-color:transparent;");
    minimizeBtn->setGeometry(this->width()-2*40*dpi,0*dpi,40*dpi,40*dpi);
    connect(minimizeBtn,SIGNAL(clicked()),this,SLOT(showMinimized()));
    minimizeBtn->show();

    //添加关闭按钮
    closeBtn=new ToolButton(this);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    closeBtn->setGeometry(this->width()-40*dpi,0*dpi,40*dpi,40*dpi);
    closeBtn->setStyleSheet("background-color:transparent;");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));
    closeBtn->show();

    //添加搜索条
    searchBar=new SearchBar(this);
    connect(searchBar->lineEdit,SIGNAL(returnPressed()),this,SLOT(showSearchResult()));

    //添加消息中心按钮
    messageCentreBtn= new ToolButton(this);
    messageCentreBtn->setIcon(QPixmap(":/Images/Icons/Message.png").scaled(40*dpi,40*dpi,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    messageCentreBtn->setStyleSheet("background-color:transparent;");
    messageCentreBtn->setGeometry(this->width()-3*40*dpi,0*dpi,40*dpi,40*dpi);
    messageCentreBtn->show();

    //添加登录按钮
    loginBtn=new ToolButton(this);
    loginBtn->setText("登录");
    loginBtn->setFont(QFont("幼圆"));
    loginBtn->setGeometry(this->width()-4*40*dpi,0*dpi,40*dpi,40*dpi);
    loginBtn->setStyleSheet("background-color:transparent;");

    //添加图书概览按钮
    overviewBtn=new ToolButton(this);
    overviewBtn->setIcon(QPixmap(":/Images/Icons/OverviewButton.png"));
    overviewBtn->setIconSize(QSize(120*dpi,80*dpi));
    overviewBtn->setStyleSheet("background-color:transparent; border:none");
    overviewBtn->setGeometry(10*dpi,this->height()/6+50*dpi,120*dpi,90*dpi);

    //添加图书管理按钮
    bookManagementBtn=new ToolButton(this);
    bookManagementBtn->setIcon(QPixmap(":/Images/Icons/BooksManagementButton.png"));
    bookManagementBtn->setIconSize(QSize(120*dpi,80*dpi));
    bookManagementBtn->setStyleSheet("background-color:transparent; border:none");
    bookManagementBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*5*dpi,120*dpi,90*dpi);

    //添加读者管理按钮
    readerManagementBtn=new ToolButton(this);
    readerManagementBtn->setIcon(QPixmap(":/Images/Icons/ReaderManagementButton.png"));
    readerManagementBtn->setIconSize(QSize(120*dpi,80*dpi));
    readerManagementBtn->setStyleSheet("background-color:transparent; border:none");
    readerManagementBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*4*dpi,120*dpi,90*dpi);

    //添加借书按钮
    borrowBtn=new ToolButton(this);
    borrowBtn->setIcon(QPixmap(":/Images/Icons/BorrowBooksButton.png"));
    borrowBtn->setIconSize(QSize(120*dpi,80*dpi));
    borrowBtn->setStyleSheet("background-color:transparent; border:none");
    borrowBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*dpi,120*dpi,90*dpi);

    //添加还书按钮
    giveBackBtn=new ToolButton(this);
    giveBackBtn->setIcon(QPixmap(":/Images/Icons/ReturnBooksButton.png"));
    giveBackBtn->setIconSize(QSize(120*dpi,80*dpi));
    giveBackBtn->setStyleSheet("background-color:transparent; border:none");
    giveBackBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*2*dpi,120*dpi,90*dpi);

    //添加个人信息按钮
    personalInfoBtn=new ToolButton(this);
    personalInfoBtn->setIcon(QPixmap(":/Images/Icons/PersonalInfoButton.png"));
    personalInfoBtn->setIconSize(QSize(120*dpi,80*dpi));
    personalInfoBtn->setStyleSheet("background-color:transparent; border:none");
    personalInfoBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*3*dpi,120*dpi,90*dpi);

    //添加中央窗口
    bookExhibitionWindow=new BookExhibition(this);
    bookExhibitionWindow->setVisible(false);
    bookManagementWindow=new BookManageWindow(this);
    bookManagementWindow->setVisible(false);
    connect(bookManagementBtn,SIGNAL(clicked()),this,SLOT(showBookManagementWindow()));

    //日期相关
    changeDateBtn1=new ToolButton(this);
    changeDateBtn1->setGeometry(200,85,20,20);
    changeDateBtn1->setStyleSheet("background-color:transparent; border:none");
    changeDateBtn1->setIcon(QPixmap(":/Images/Icons/RightArrow2.png"));
    connect(changeDateBtn1,SIGNAL(clicked()),this,SLOT(addDate()));

    changeDateBtn2=new ToolButton(this);
    changeDateBtn2->setGeometry(220,85,20,20);
    changeDateBtn2->setIcon(QPixmap(":/Images/Icons/DoubleRightArrow2.png"));
    changeDateBtn2->setStyleSheet("background-color:transparent; border:none");
    connect(changeDateBtn2,SIGNAL(clicked()),this,SLOT(addMonth()));
}

Widget::~Widget()
{
    delete minimizeBtn;           //最小化按钮
    delete closeBtn;              //最大化按钮
    delete messageCentreBtn;            //消息中心按钮
    delete searchBar;                 //搜索栏

    delete bookManagementBtn;           //图书管理
    delete readerManagementBtn;         //读者管理
    delete borrowBtn;                   //图书借阅
    delete giveBackBtn;                 //图书归还
    delete overviewBtn;                 //图书概览
    delete loginBtn;                    //登录按钮
    delete personalInfoBtn;             //个人信息

    delete bookExhibitionWindow;
    delete bookManagementWindow;

    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    //设置背景图片
    this->setAutoFillBackground(true);
    QPixmap pixmap(":/Images/WidgetBackground.jpg");
    QPixmap fitpixmap=pixmap.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background,fitpixmap);
   // this->setPalette(palette);//图片不搭

    //重新计算按钮的位置
    minimizeBtn->setGeometry(this->width()-2*40*dpi,0*dpi,40*dpi,40*dpi);
    closeBtn->setGeometry(this->width()-40*dpi,0*dpi,40*dpi,40*dpi);

    drawDate();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        //改变并存储鼠标形状
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);

        //计算鼠标位置与界面位置的差值
        offset=event->globalPos()-this->pos();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        //计算需要移动到的新位置
        QPoint temp;
        temp=event->globalPos()-offset;

        //移动界面
        move(temp);
    }
}

void Widget::showBookManagementWindow()
{
    this->bookExhibitionWindow->setVisible(false);
    this->bookManagementWindow->show();
}

void Widget::showSearchResult()    //在此添加查询结果
{
    this->bookManagementWindow->setVisible(false);
    std::vector<Book*> &books=(this->bookExhibitionWindow->books);
    int mode=this->searchBar->mode();
    books=search(this->searchBar->lineEdit->text(),mode);
    this->bookExhibitionWindow->show();
    this->bookExhibitionWindow->currentPage=0;
    bookExhibitionWindow->refreshDesp();
    this->bookExhibitionWindow->repaint();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //恢复鼠标形状
    QApplication::restoreOverrideCursor();
}

void Widget::drawDate()
{
    QPainter painter(this);\
    QPen pen(Qt::white);
    painter.setPen(pen);
//    QFont digitFont("Kozuka Gothic Pr6N EL",40);
//    QFont thFont("Kozuka Gothic Pr6N EL",20);
//    QFont weekFont("Kozuka Gothic Pr6N EL",30);
//    QFont monthFont("Kozuka Gothic Pr6N EL",12);
    QFont digitFont("Gothic",40);
    QFont thFont("Gothic",20);
    QFont weekFont("Gothic",30);
    QFont monthFont("Gothic",12);
    painter.setFont(digitFont);
    painter.drawText(50*dpi,75*dpi,QString::number(systemDate.day()));
    painter.setFont(thFont);
    if(systemDate.day()>9)
        painter.drawText(110*dpi,55*dpi,"th");
    else
        painter.drawText(80*dpi,55*dpi,"th");
    painter.setFont(weekFont);
    painter.drawText(150*dpi,70*dpi,toWeekString(systemDate.dayOfWeek()));
    painter.setFont(monthFont);
    painter.drawText(50*dpi,100*dpi,toMonthString(systemDate.month())+"  "+QString::number(systemDate.year()));
}

void Widget::addDate()
{
    qDebug()<<systemDate;
    systemDate=systemDate.addDays(1);
    qDebug()<<systemDate;
    update();
}

void Widget::addMonth()
{
   qDebug()<<systemDate;
   systemDate=systemDate.addMonths(1);
   qDebug()<<systemDate;
   update();
}

QString Widget::toWeekString(int week)
{
    switch (week) {
    case 1:
        return QString("Monday");
        break;
    case 2:
        return QString("Tuesday");
        break;
    case 3:
        return QString("Wednesday");
        break;
    case 4:
        return QString("Thursday");
        break;
    case 5:
        return QString("Friday");
        break;
    case 6:
        return QString("Saturday");
        break;
    case 7:
        return QString("Sunday");
        break;
    default:
        return QString("");
        break;
    }
}

QString Widget::toMonthString(int month)
{
    switch (month) {
    case 1:
        return QString("January");
        break;
    case 2:
        return QString("February");
        break;
    case 3:
        return QString("March");
        break;
    case 4:
        return QString("April");
        break;
    case 5:
        return QString("May");
        break;
    case 6:
        return QString("June");
        break;
    case 7:
        return QString("July");
        break;
    case 8:
        return QString("August");
        break;
    case 9:
        return QString("September");
        break;
    case 10:
        return QString("October");
        break;
    case 11:
        return QString("November");
        break;
    case 12:
        return QString("December");
        break;
    default:
        return QString("");
        break;
    }
}
