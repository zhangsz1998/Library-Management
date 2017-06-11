#include "readersearchwindow.h"

ReaderSearchWindow::ReaderSearchWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    this->setStyleSheet("background-color:#ffffff;border:none");


    QStringList columnLabels;
    QFont labelFont("微软雅黑",12);
    columnLabels<<"用户姓名"<<"用户Id";
    readerList=new QTableWidget(0,2,this);
    readerList->setHorizontalHeaderLabels(columnLabels);
    readerList->setStyleSheet("background-color: #ffffff");
    readerList->setGeometry(20*dpi,20*dpi,400*dpi,400*dpi);
    readerList->setColumnWidth(0,180*dpi);
    readerList->setColumnWidth(1,180*dpi);
    readerList->setEnabled(true);
    readerList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    readerList->setSelectionMode(QAbstractItemView::NoSelection);
    readerList->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:white;border:0px;border-style:solid");
    readerList->horizontalHeader()->setFont(labelFont);
    readerList->horizontalHeader()->setFixedHeight(30*dpi);
    readerList->verticalHeader()->hide();
    readerList->setFont(QFont("微软雅黑",10));
    readerList->setRowHeight(1,40*dpi);
    readerList->setVisible(true);

    getName=new QLineEdit(this);
    getName->setStyleSheet("background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius:10px;padding: 4px");
    getName->setFont(QFont("微软雅黑",12));
    getName->setPalette(QPalette(Qt::gray));
    getName->setPlaceholderText("在此输入用户姓名");
    getName->setGeometry(450*dpi,50*dpi,200*dpi,30*dpi);
    connect(getName,SIGNAL(returnPressed()),this,SLOT(searchByName()));

    getId=new QLineEdit(this);
    getId->setStyleSheet("background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius:10px;padding: 4px");
    getId->setFont(QFont("微软雅黑",12));
    getId->setPalette(QPalette(Qt::gray));
    getId->setPlaceholderText("在此输入用户ID");
    getId->setGeometry(450*dpi,150*dpi,200*dpi,30*dpi);
    connect(getId,SIGNAL(returnPressed()),this,SLOT(askForInfo()));

    searchUser=new ToolButton(this);
    searchUser->setGeometry(670*dpi,50*dpi,30*dpi,30*dpi);
    searchUser->setIcon(QPixmap(":/Images/Icons/Goback.png"));
    searchUser->setIconSize(QSize(30*dpi,30*dpi));
    connect(searchUser,SIGNAL(clicked()),this,SLOT(searchByName()));

    searchDetail=new ToolButton(this);
    searchDetail->setGeometry(670*dpi,150*dpi,30*dpi,30*dpi);
    searchDetail->setIcon(QPixmap(":/Images/Icons/Goback.png"));
    searchDetail->setIconSize(QSize(30*dpi,30*dpi));
    connect(searchDetail,SIGNAL(clicked()),this,SLOT(askForInfo()));

    resetBtn=new ToolButton(this);
    resetBtn->setGeometry(450*dpi,200*dpi,80*dpi,30*dpi);
    resetBtn->setText("查看完整表格");
    resetBtn->setVisible(false);
    connect(resetBtn,SIGNAL(clicked()),this,SLOT(resetTable()));

    popUp=new MessageBox(this);
    popUp->setVisible(false);
    popUp->setModal(true);
    popUp->setGeometry(220*dpi,150*dpi,popUp->width(),popUp->height());
}

ReaderSearchWindow::~ReaderSearchWindow()
{
    delete readerList;
    delete searchDetail;    //搜索id
    delete searchUser;   //搜索用户
    delete resetBtn;     //展开表格
    delete getId;     //用于获取读者编号,用于查询详细信息
    delete getName;    //用于搜索姓名对应Id
    delete popUp;
}

Reader *ReaderSearchWindow::getRequestedUser()
{
    return requestedUser;
}

void ReaderSearchWindow::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    QFont textFont("微软雅黑",15);
    QFont titleFont("微软雅黑",15);
    int l=readerlist.size();
    for(int i=0;i<l;i++)
    {
        if(i>=readerList->rowCount())
        {
            readerList->setRowCount(readerList->rowCount()+1);
            QTableWidgetItem* item0=new QTableWidgetItem;
            item0->setText(readerlist[i].getStringByTag("name"));
            readerList->setItem(i,0,item0);
            QTableWidgetItem* item1=new QTableWidgetItem;
            item1->setText(readerlist[i].getStringByTag("id"));
            readerList->setItem(i,1,item1);
        }
    }
    titleFont.setBold(true);
    painter.setFont(textFont);
    painter.drawText(450*dpi,40*dpi,"搜索用户ID");
    painter.drawText(450*dpi,140*dpi,"输入ID以查询详细信息:");
}

void ReaderSearchWindow::searchByName()
{
    QString text=getName->text();
    if(text=="")
    {
        popUp->setText("未搜索到相关结果");
        popUp->setVisible(true);
        return;
    }
    QList<QTableWidgetItem*> item=readerList->findItems(text,Qt::MatchContains);
    if (!item.isEmpty())//不为空
    {
        for (int i=0;i<readerList->rowCount();i++)
        {
            readerList->setRowHidden(i, true);//隐藏所有行
        }
        for (int i=0; i<item.count();i++)
        {
            readerList->setRowHidden(item.at(i)->row(),false);//item.at(i).row()输出行号
        }
        resetBtn->setVisible(true);
    }
    else
    {
        popUp->setText("未搜索到相关结果");
        popUp->setVisible(true);
    }
}

void ReaderSearchWindow::askForInfo()
{
    QString id=getId->text();
    if(id=="")
    {
        popUp->setText("未搜索到相关结果");
        popUp->setVisible(true);
    }
    Reader* requested=getUser(id);
    if(requested==Q_NULLPTR)
    {
        popUp->setText("未搜索到相关结果");
        popUp->setVisible(true);
    }
    else
    {
        requestedUser=requested;
        emit readerInfoRequest();
    }
}

void ReaderSearchWindow::resetTable()
{
    resetBtn->setVisible(false);
    for (int i=0;i<readerList->rowCount();i++)
    {
        readerList->setRowHidden(i, false);//隐藏所有行
    }
}
