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
extern std::vector<Reader> readerlist,*preaderlist;
extern bool userMessageChanged;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setGeometry(320*dpi,90*dpi,1024*dpi,725*dpi);
    setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setStyleSheet("background-color:#99ccff;");
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
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(tryClose()));
    closeBtn->show();

    //添加搜索条
    searchBar=new SearchBar(this);
    connect(searchBar->lineEdit,SIGNAL(returnPressed()),this,SLOT(showSearchResult()));

    //添加消息中心按钮
    messageCentreBtn= new ToolButton(this);
    messageCentreBtn->setIcon(QPixmap(":/Images/Icons/Message.png").scaled(40*dpi,40*dpi,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    messageCentreBtn->setStyleSheet("background-color:transparent;");
    messageCentreBtn->setGeometry(this->width()-3*40*dpi,0*dpi,40*dpi,40*dpi);
    connect(messageCentreBtn,SIGNAL(clicked()),this,SLOT(showMessages()));
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
    connect(overviewBtn,SIGNAL(clicked()),this,SLOT(showOverviewWindow()));

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
    personalInfoBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*dpi,120*dpi,90*dpi);
    connect(personalInfoBtn,SIGNAL(clicked()),this,SLOT(showPersonalInfoWindow()));

    //添加读者管理按钮
    readerManagementBtn=new ToolButton(this);
    readerManagementBtn->setIcon(QPixmap(":/Images/Icons/ReaderManagementButton.png"));
    readerManagementBtn->setIconSize(QSize(120*dpi,80*dpi));
    readerManagementBtn->setStyleSheet("background-color:transparent; border:none");
    readerManagementBtn->setGeometry(10*dpi,this->height()/6+50*dpi+90*3*dpi,120*dpi,90*dpi);
    connect(readerManagementBtn,SIGNAL(clicked()),this,SLOT(showReaderSearchWindow()));

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
    bookInfoWindow->setVisible(false);
    connect(bookInfoWindow->goBackBtn,SIGNAL(clicked()),this,SLOT(showPreWindow()));

    personalInfoWindow=new PersonalInfoWindow(this);
    personalInfoWindow->setVisible(false);

    returnWindow=new ReturnWindow(this);
    returnWindow->setVisible(false);
    connect(giveBackBtn,SIGNAL(clicked()),this,SLOT(showReturnWindow()));

    readerSearchWindow=new ReaderSearchWindow(this);
    readerSearchWindow->setVisible(false);
    connect(readerSearchWindow,SIGNAL(readerInfoRequest()),this,SLOT(showReaderInfoByRequest()));

    bookOverviewWindow=new BookOverviewWindow(this);
    bookOverviewWindow->setVisible(true);

    //添加登录界面
    loginWindow=new LoginWindow(this);
    loginWindow->setVisible(false);
    connect(loginWindow,SIGNAL(logedIn()),this,SLOT(userLogedIn()));

    checkUp=new AuthorityCheckWindow(this);
    checkUp->setGeometry(this->width()/3,this->height()/3,500*dpi,175*dpi);
    checkUp->setVisible(false);
    connect(checkUp,SIGNAL(isAuthorized()),this,SLOT(userChecked()));
    connect(checkUp,SIGNAL(notAuthorized()),this,SLOT(checkUpFailed()));
    userAuthorized=false;

    //注销弹窗,该弹窗用于注销或提示登录
    popUp=new MessageBox(this);
    popUp->setGeometry(this->width()/3,this->height()/3,popUp->width(),popUp->height());
    this->popUp->setStyleSheet("background-color:white");
    connect(popUp->confirmBtn,SIGNAL(clicked()),this,SLOT(tryToLogOut()));
    popUp->setVisible(false);

    connect(this,SIGNAL(dateChanged()),this,SLOT(daycheck()));
    connect(bookOverviewWindow,SIGNAL(actionTimeout()),this,SLOT(addDate()));
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
    delete bookInfoWindow;
    delete personalInfoWindow;
    delete loginWindow;
    delete returnWindow;
    delete readerSearchWindow;

    delete changeDateBtn1;                //日期前进一天
    delete changeDateBtn2;                //日期前进一个月

    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    //设置背景图片
    QPainter painter(this);
    painter.setFont(QFont("微软雅黑",10));
    QPixmap hasMessages(":/Images/Icons/haveMessage.png");
    this->setAutoFillBackground(true);
    QPixmap pixmap(":/Images/WidgetBackground.jpg");
    QPixmap fitpixmap=pixmap.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background,fitpixmap);
   // this->setPalette(palette);//图片不搭

    if(userMessageChanged)
        messageCentreBtn->setIcon(QPixmap(":/Images/Icons/haveMessage.png").scaled(40*dpi,40*dpi,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    else
        messageCentreBtn->setIcon(QPixmap(":/Images/Icons/Message.png").scaled(40*dpi,40*dpi,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
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

void Widget::showCheckUpWindow()
{
    checkUp->setVisible(true);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //恢复鼠标形状
    QApplication::restoreOverrideCursor();
}

void Widget::showBookInfoBySearch()
{
    this->bookInfoWindow->loadBook(this->bookExhibitionWindow->bookOnDisplay());
    bookExhibitionWindow->setVisible(false);
    bookManagementWindow->setVisible(false);
    bookInfoWindow->setVisible(true);
    personalInfoWindow->setVisible(false);
    returnWindow->setVisible(false);
    personalInfoWindow->setVisible(false);
    readerSearchWindow->setVisible(false);
    bookOverviewWindow->setVisible(false);
    bookOverviewWindow->actionTimer->stop();
}

void Widget::showBookManagementWindow()
{
    if(activereader==Q_NULLPTR)
    {
        popUp->setText("请先登录");
        popUp->setVisible(true);
        return;
    }
    if(userAuthorized==false)
    {
        checkUp->setVisible(true);
        return;
    }
    bookExhibitionWindow->setVisible(false);
    bookManagementWindow->setVisible(true);
    bookInfoWindow->setVisible(false);
    personalInfoWindow->setVisible(false);
    returnWindow->setVisible(false);
    readerSearchWindow->setVisible(false);
    bookOverviewWindow->setVisible(false);
    bookOverviewWindow->actionTimer->stop();
}

void Widget::showPersonalInfoWindow()
{
    if(activereader==Q_NULLPTR)
    {
        popUp->setText("请先登录");
        popUp->setVisible(true);
        return;
    }
    bookExhibitionWindow->setVisible(false);
    bookManagementWindow->setVisible(false);
    bookInfoWindow->setVisible(false);
    personalInfoWindow->loadReader(activereader);
    personalInfoWindow->setLoadPattern(bySelf);
    personalInfoWindow->repaint();
    personalInfoWindow->setVisible(true);
    returnWindow->setVisible(false);
    readerSearchWindow->setVisible(false);
    bookOverviewWindow->setVisible(false);
    bookOverviewWindow->actionTimer->stop();
}

void Widget::showMessages()
{
    if(activereader==Q_NULLPTR)
    {
        popUp->setText("请先登录");
        popUp->setVisible(true);
        return;
    }
    personalInfoWindow->setLoadPattern(bySelf);
    personalInfoWindow->loadReader(activereader);
    this->personalInfoWindow->showMessages();
    personalInfoWindow->setVisible(true);
    bookInfoWindow->setVisible(false);
    bookExhibitionWindow->setVisible(false);
    bookManagementWindow->setVisible(false);
    returnWindow->setVisible(false);
    readerSearchWindow->setVisible(false);
    bookOverviewWindow->setVisible(false);
}

void Widget::showSearchResult()    //在此添加查询结果
{
    this->preWindowFlag=1;
    std::vector<Book*> &books=(this->bookExhibitionWindow->books);
    int mode=this->searchBar->mode();
    books=search(this->searchBar->lineEdit->text(),mode);
    for (int i=0;i<books.size();i++)
        books[i]->IncIntByTag("refer_count");
    this->bookExhibitionWindow->currentPage=0;
    bookExhibitionWindow->setVisible(true);
    bookManagementWindow->setVisible(false);
    bookInfoWindow->setVisible(false);
    personalInfoWindow->setVisible(false);
    returnWindow->setVisible(false);
    readerSearchWindow->setVisible(false);
    bookOverviewWindow->setVisible(false);
    personalInfoWindow->setVisible(false);
    bookOverviewWindow->actionTimer->stop();

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

void Widget::showReturnWindow()
{
    if(activereader==Q_NULLPTR)
    {
        popUp->setText("请先登录");
        popUp->setVisible(true);
        return;
    }
    else
    {
        bookExhibitionWindow->setVisible(false);
        bookManagementWindow->setVisible(false);
        bookInfoWindow->setVisible(false);
        personalInfoWindow->setVisible(false);
        returnWindow->setVisible(true);
        readerSearchWindow->setVisible(false);
        bookOverviewWindow->setVisible(false);
        bookOverviewWindow->actionTimer->stop();
    }
}

void Widget::showOverviewWindow()
{
    bookExhibitionWindow->setVisible(false);
    bookManagementWindow->setVisible(false);
    bookInfoWindow->setVisible(false);
    personalInfoWindow->setVisible(false);
    returnWindow->setVisible(false);
    readerSearchWindow->setVisible(false);
    bookOverviewWindow->setVisible(true);
    bookOverviewWindow->actionTimer->start(5000);
}

void Widget::userLogedIn()
{
    isloged=true;
    userAuthorized=false;
    userMessageChanged=false;
    update();
}

void Widget::tryClose(){
    if (activereader) log_print("signout",activereader->getStringByTag("id"),"","");
    log_print("close","","","");
    saveXml();
    saveXml2();
    this->close();
}

void Widget::tryToLogOut()
{
    if(popUp->getText()=="您真的要注销么？")
    {
        isloged=false;
        log_print("signout",activereader->getStringByTag("id"),"","");
        activereader=Q_NULLPTR;
        bookManagementWindow->setVisible(false);
        personalInfoWindow->setVisible(false);
        returnWindow->setVisible(false);
        readerSearchWindow->setVisible(false);
        bookManagementWindow->setVisible(false);
        bookOverviewWindow->setVisible(true);
        update();
    }
}

void Widget::showReaderInfoByRequest()
{
    personalInfoWindow->setLoadPattern(byAdmin);
    personalInfoWindow->loadReader(readerSearchWindow->getRequestedUser());
    bookExhibitionWindow->setVisible(false);
    bookManagementWindow->setVisible(false);
    bookInfoWindow->setVisible(false);
    personalInfoWindow->setVisible(true);
    returnWindow->setVisible(false);
    readerSearchWindow->setVisible(false);
    bookOverviewWindow->actionTimer->stop();
}

void Widget::showReaderSearchWindow()
{
    if(activereader==Q_NULLPTR)
    {
        popUp->setText("请先登录");
        popUp->setVisible(true);
        return;
    }
    if(userAuthorized==false)
    {
        checkUp->setVisible(true);
        return;
    }
    else
    {
        bookExhibitionWindow->setVisible(false);
        bookManagementWindow->setVisible(false);
        bookInfoWindow->setVisible(false);
        personalInfoWindow->setVisible(false);
        returnWindow->setVisible(false);
        readerSearchWindow->setVisible(true);
        bookOverviewWindow->actionTimer->stop();
    }
}

void Widget::checkUpFailed()
{
    popUp->setText("密码错误");
    popUp->setVisible(true);
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
    systemDate=systemDate.addDays(1);
    emit dateChanged();
    update();
    configureDate();
}

void Widget::addMonth()
{
   QDate dueDate=systemDate.addMonths(1);
   while (systemDate !=dueDate){
       systemDate = systemDate.addDays(1);
       emit dateChanged();
   }
   update();
   configureDate();
}

void Widget::daycheck()
{
    for (int i=0;i<readerlist.size();i++){
        int num = readerlist[i].getIntByTag("bor_num");
        for (int j=0;j<num;j++){
            if (readerlist[i].bor_list[j].exp.addDays(1) == systemDate){
                userMessageChanged=true;
                if (readerlist[i].getIntByTag("msg_num")!=30)
                    readerlist[i].msg[readerlist[i].getIntByTag("msg_num")] = QString(systemDate.toString("yyyy-MM-dd")+" 您借阅的图书:"+readerlist[i].bor_list[j].id+"已过期一天，请尽快归还！");
                else {
                   for (int k=0;k<29;k++)
                       readerlist[i].msg[k]=readerlist[i].msg[k+1];
                   readerlist[i].msg[29] = QString(systemDate.toString("yyyy-MM-dd")+" 您借阅的图书:"+readerlist[i].bor_list[j].id+"已过期一天，请尽快归还！");
                }
                if (readerlist[i].getIntByTag("msg_num") != 30) readerlist[i].IncIntByTag("msg_num");
                else readerlist[i].is_modf = true;
                Book *b;
                for (int k=0;k<booklist.size();k++)
                    if (booklist[k].getStringByTag("id") == readerlist[i].bor_list[j].id){
                        b=&booklist[k];
                        break;
                    }
                log_print("expire",readerlist[i].getStringByTag("id"),b->getStringByTag("id"),"一");
                readerlist[i].IncIntByTag("illegal_count");
                int cnt = readerlist[i].getIntByTag("illegal_count");
                if (cnt>5) readerlist[i].setStringByTag("credit",QString("3"));
                else if (cnt > 3) readerlist[i].setStringByTag("credit",QString("2"));
                else readerlist[i].setStringByTag("credit",QString("1"));
                log_print("illegal",readerlist[i].getStringByTag("id"),QString::number(cnt),readerlist[i].getStringByTag("credit"));
            } else
            if (readerlist[i].bor_list[j].exp.addDays(10) == systemDate){
                userMessageChanged=true;
                if (readerlist[i].getIntByTag("msg_num")!=30)
                    readerlist[i].msg[readerlist[i].getIntByTag("msg_num")] = QString(systemDate.toString("yyyy-MM-dd")+" 您借阅的图书:"+readerlist[i].bor_list[j].id+"已过期十天，请尽快归还！");
                else {
                   for (int k=0;k<29;k++)
                       readerlist[i].msg[k]=readerlist[i].msg[k+1];
                   readerlist[i].msg[29] = QString(systemDate.toString("yyyy-MM-dd")+" 您借阅的图书:"+readerlist[i].bor_list[j].id+"已过期十天，请尽快归还！");
                }
                if (readerlist[i].getIntByTag("msg_num") != 30) readerlist[i].IncIntByTag("msg_num");
                else readerlist[i].is_modf = true;
                Book *b;
                for (int k=0;k<booklist.size();k++)
                    if (booklist[k].getStringByTag("id") == readerlist[i].bor_list[j].id){
                        b=&booklist[k];
                        break;
                    }
                log_print("expire",readerlist[i].getStringByTag("id"),b->getStringByTag("id"),"十");
            } else
            if (readerlist[i].bor_list[j].exp.addDays(30) == systemDate){
                userMessageChanged=true;
                if (readerlist[i].getIntByTag("msg_num")!=30)
                    readerlist[i].msg[readerlist[i].getIntByTag("msg_num")] = QString(systemDate.toString("yyyy-MM-dd")+" 您借阅的图书:"+readerlist[i].bor_list[j].id+"已过期三十天，请尽快归还！");
                else {
                   for (int k=0;k<29;k++)
                       readerlist[i].msg[k]=readerlist[i].msg[k+1];
                   readerlist[i].msg[29] = QString(systemDate.toString("yyyy-MM-dd")+" 您借阅的图书:"+readerlist[i].bor_list[j].id+"已过期三十天，请尽快归还！");
                }
                if (readerlist[i].getIntByTag("msg_num") != 30) readerlist[i].IncIntByTag("msg_num");
                else readerlist[i].is_modf = true;
                Book *b;
                for (int k=0;k<booklist.size();k++)
                    if (booklist[k].getStringByTag("id") == readerlist[i].bor_list[j].id){
                        b=&booklist[k];
                        break;
                    }
                log_print("expire",readerlist[i].getStringByTag("id"),b->getStringByTag("id"),"三十");
            }
            if (readerlist[i].bor_list[j].exp < systemDate){
                readerlist[i].is_modf=true;
                int days = readerlist[i].bor_list[j].exp.daysTo(systemDate);
                if (days < 10) {
                    readerlist[i].balance -= 0.5;
                    log_print("balance",readerlist[i].getStringByTag("id"),"0.5",QString::number(readerlist[i].balance,'f',2));
                }
                else if (days < 30) {
                    readerlist[i].balance -= 0.75;
                    log_print("balance",readerlist[i].getStringByTag("id"),"0.75",QString::number(readerlist[i].balance,'f',2));
                }
                else {
                    readerlist[i].balance -= 1;
                    log_print("balance",readerlist[i].getStringByTag("id"),"1.0",QString::number(readerlist[i].balance,'f',2));
                }
            }
        }
    }
    saveXml();
    saveXml2();
}

void Widget::userChecked()
{
    userAuthorized=true;
    popUp->setText("验证通过");
    popUp->setVisible(true);
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
