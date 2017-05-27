#include "ui_widget.h"
#include "searchbar.h"
#include "widget.h"
#include <QDebug>
#include "book_mgmt.h"
#include <QPainter>

extern QDate systemDate;
extern qreal dpi;
extern std::vector<Book> booklist,*pbooklist;
extern Reader* activereader;

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
    closeBtn->setEnterColor(QColor("#ff6666"));
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
    connect(loginBtn,SIGNAL(clicked()),this,SLOT(showLoginWindow()));


    //添加注销按钮
    logoutBtn=new ToolButton(this);
    logoutBtn->setText("注销");
    logoutBtn->setFont(QFont("幼圆"));
    logoutBtn->setGeometry(this->width()-4*40*dpi,0*dpi,40*dpi,40*dpi);
    logoutBtn->setStyleSheet("background-color:transparent;");
    logoutBtn->setVisible(false);
    connect(logoutBtn,SIGNAL(clicked()),this,SLOT(showLogoutWindow()));


    isloged=false;


    //添加图书概览按钮
    overviewBtn=new ToolButton(this);
    overviewBtn->setIcon(QPixmap(":/Images/Icons/OverviewButton.png"));
    overviewBtn->setIconSize(QSize(120*dpi,80*dpi));
    overviewBtn->setStyleSheet("background-color:transparent; border:none");
    overviewBtn->setGeometry(10*dpi,this->height()/6+50*dpi,120*dpi,90*dpi);

    //添加还书按钮
    giveBackBtn=new ToolButton(this);
    giveBackBtn->setIcon(QPixmap(":/Images/Icons/ReturnBooksButton.png"));
    giveBackBtn->setIconSize(QSize(120*dpi,80*dpi));
    giveBackBtn->setStyleSheet("background-color:transparent; border:none");
    giveBackBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*dpi,120*dpi,90*dpi);

    //添加个人信息按钮
    personalInfoBtn=new ToolButton(this);
    personalInfoBtn->setIcon(QPixmap(":/Images/Icons/PersonalInfoButton.png"));
    personalInfoBtn->setIconSize(QSize(120*dpi,80*dpi));
    personalInfoBtn->setStyleSheet("background-color:transparent; border:none");
    personalInfoBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*2*dpi,120*dpi,90*dpi);
    connect(personalInfoBtn,SIGNAL(clicked()),this,SLOT(showPersonalInfoWindow()));

    //添加读者管理按钮
    readerManagementBtn=new ToolButton(this);
    readerManagementBtn->setIcon(QPixmap(":/Images/Icons/ReaderManagementButton.png"));
    readerManagementBtn->setIconSize(QSize(120*dpi,80*dpi));
    readerManagementBtn->setStyleSheet("background-color:transparent; border:none");
    readerManagementBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*3*dpi,120*dpi,90*dpi);

    //添加图书管理按钮
    bookManagementBtn=new ToolButton(this);
    bookManagementBtn->setIcon(QPixmap(":/Images/Icons/BooksManagementButton.png"));
    bookManagementBtn->setIconSize(QSize(120*dpi,80*dpi));
    bookManagementBtn->setStyleSheet("background-color:transparent; border:none");
    bookManagementBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*4*dpi,120*dpi,90*dpi);

    //添加中央窗口
    bookExhibitionWindow=new BookExhibition(this);
    bookExhibitionWindow->setVisible(false);
    connect(bookExhibitionWindow,SIGNAL(bookInfoClicked()),this,SLOT(showBookInfoBySearch()));

    bookManagementWindow=new BookManageWindow(this);
    bookManagementWindow->setVisible(false);
    connect(bookManagementBtn,SIGNAL(clicked()),this,SLOT(showBookManagementWindow()));

    bookInfoWindow=new BookInfoWindow(this);
    bookInfoWindow->loadBook(&(booklist.at(1)));
    bookInfoWindow->setVisible(false);
    connect(bookInfoWindow->goBackBtn,SIGNAL(clicked()),this,SLOT(showPreWindow()));

    personalInfoWindow=new PersonalInfoWindow(this);
    personalInfoWindow->setVisible(false);

    //添加登录界面
    loginWindow=new LoginWindow(this);
    loginWindow->setVisible(false);
    connect(loginWindow,SIGNAL(logedIn()),this,SLOT(userLogedIn()));
    //日期相关
    changeDateBtn1=new ToolButton(this);
    changeDateBtn1->setGeometry(200*dpi,85*dpi,20*dpi,20*dpi);
    changeDateBtn1->setStyleSheet("background-color:transparent; border:none");
    changeDateBtn1->setIcon(QPixmap(":/Images/Icons/RightArrow2.png"));
    connect(changeDateBtn1,SIGNAL(clicked()),this,SLOT(addDate()));

    changeDateBtn2=new ToolButton(this);
    changeDateBtn2->setGeometry(220*dpi,85*dpi,20*dpi,20*dpi);
    changeDateBtn2->setIcon(QPixmap(":/Images/Icons/DoubleRightArrow2.png"));
    changeDateBtn2->setStyleSheet("background-color:transparent; border:none");
    connect(changeDateBtn2,SIGNAL(clicked()),this,SLOT(addMonth()));

    //注销弹窗,该弹窗用于注销或提示登录
    popUp=new MessageBox(this);
    popUp->setVisible(false);
    popUp->setGeometry(this->width()/3,this->height()/3,popUp->width(),popUp->height());
    connect(popUp->confirmBtn,SIGNAL(clicked()),this,SLOT(tryToLogOut()));

}

Widget::~Widget()
{
    delete minimizeBtn;           //最小化按钮
    delete closeBtn;              //最大化按钮
    delete messageCentreBtn;            //消息中心按钮
    delete searchBar;                 //搜索栏

    delete bookManagementBtn;           //图书管理
    delete readerManagementBtn;         //读者管理
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
    QPainter painter(this);
    painter.setFont(QFont("微软雅黑",10));

    this->setAutoFillBackground(true);
    QPixmap pixmap(":/Images/WidgetBackground.jpg");
    QPixmap fitpixmap=pixmap.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background,fitpixmap);
   // this->setPalette(palette);//图片不搭

    //重新计算按钮的位置
    minimizeBtn->setGeometry(this->width()-2*40*dpi,0*dpi,40*dpi,40*dpi);
    closeBtn->setGeometry(this->width()-40*dpi,0*dpi,40*dpi,40*dpi);

    if(isloged)
    {
        loginBtn->setVisible(false);
        logoutBtn->setVisible(true);
        painter.drawText(this->width()-250*dpi,25*dpi,"欢迎，"+activereader->getStringByTag("name"));
    }
    else
    {
        loginBtn->setVisible(true);
        logoutBtn->setVisible(false);
    }

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

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //恢复鼠标形状
    QApplication::restoreOverrideCursor();
}

void Widget::showBookInfoBySearch()
{
    this->bookInfoWindow->loadBook(this->bookExhibitionWindow->bookOnDisplay());
    this->bookInfoWindow->setVisible(true);
    this->bookExhibitionWindow->setVisible(false);
    this->bookManagementWindow->setVisible(false);
    personalInfoWindow->setVisible(false);
}

void Widget::showBookManagementWindow()
{
    if(activereader==Q_NULLPTR)
    {
        popUp->setText("请先登录");
        popUp->setVisible(true);
        return;
    }
    this->bookManagementWindow->setVisible(true);
}

void Widget::showPersonalInfoWindow()
{
    if(activereader==Q_NULLPTR)
    {
        popUp->setText("请先登录");
        popUp->setVisible(true);
        return;
    }
    personalInfoWindow->setVisible(true);
}

void Widget::showSearchResult()    //在此添加查询结果
{
    this->preWindowFlag=1;
    this->bookManagementWindow->setVisible(false);
    std::vector<Book*> &books=(this->bookExhibitionWindow->books);
    int mode=this->searchBar->mode();
    books=search(this->searchBar->lineEdit->text(),mode);
    this->bookExhibitionWindow->currentPage=0;

    this->bookInfoWindow->setVisible(false);
    this->bookManagementWindow->setVisible(false);
    personalInfoWindow->setVisible(false);
    this->bookExhibitionWindow->setVisible(true);

    bookExhibitionWindow->refreshDesp();
    this->bookExhibitionWindow->repaint();
}

void Widget::showLoginWindow()
{
    loginWindow->setVisible(true);
}

void Widget::showLogoutWindow()
{
    popUp->setText("您真的要注销么？");
    popUp->setVisible(true);
}

void Widget::showPreWindow()
{
    if(preWindowFlag==1)
    {
        bookExhibitionWindow->setVisible(true);
        bookManagementWindow->setVisible(false);
        bookInfoWindow->setVisible(false);
    }
    else
    {

    }
}

void Widget::userLogedIn()
{
    isloged=true;
    update();
}

void Widget::tryToLogOut()
{
    if(popUp->getText()=="您真的要注销么？");
    {
        isloged=false;
        activereader=Q_NULLPTR;
        update();
    }
}


void Widget::drawDate()
{
    QPainter painter(this);\
    QPen pen(Qt::white);
    painter.setPen(pen);
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
