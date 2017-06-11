#include "returnwindow.h"

ReturnWindow::ReturnWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    this->setStyleSheet("background-color:#ffffff;border:none");


    QStringList columnLabels;
    QFont labelFont("微软雅黑",12);
    columnLabels<<"已借书籍"<<"借书时间"<<"期望归还时间"<<" ";
    borrowTable=new QTableWidget(20,4,this);
    borrowTable->setHorizontalHeaderLabels(columnLabels);
    borrowTable->setFocusPolicy(Qt::NoFocus);
    borrowTable->setStyleSheet("background-color: #ffffff");
    borrowTable->setGeometry(40*dpi,20*dpi,800*dpi,600*dpi);
    borrowTable->setColumnWidth(0,370*dpi);
    borrowTable->setColumnWidth(1,110*dpi);
    borrowTable->setColumnWidth(2,110*dpi);
    borrowTable->setEnabled(true);
    borrowTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    borrowTable->setSelectionMode(QAbstractItemView::NoSelection);
    borrowTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:white;border:0px;border-style:solid");
    borrowTable->horizontalHeader()->setFont(labelFont);
    borrowTable->horizontalHeader()->setFixedHeight(30*dpi);
    borrowTable->verticalHeader()->hide();
    borrowTable->setFont(QFont("微软雅黑",10));
    for(int row=0;row<20;row++)
        borrowTable->setRowHeight(row,40*dpi);
    for(int i=0;i<20;i++)
    {
        returnBtn[i]=new ToolButton(this);
        returnBtn[i]->setGeometry(650*dpi,10+40*i*dpi,30*dpi,30*dpi);
        returnBtn[i]->setText("归还/续借/挂失");
        returnBtn[i]->setVisible(false);
        connect(returnBtn[i],SIGNAL(clicked()),this,SLOT(bookHandling()));
        returnBtn[i]->setObjectName(QString::number(i));
    }
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<3;j++)
        {
            item[i][j]=new QTableWidgetItem;
            item[i][j]->setText("");
        }
    }
    for(int i=0;i<20;i++)
    {
        borrowTable->setItem(i,0,item[i][0]);
        borrowTable->setItem(i,1,item[i][1]);
        borrowTable->setItem(i,2,item[i][2]);
        borrowTable->setCellWidget(i,3,returnBtn[i]);
    }
    borrowTable->setVisible(true);

    reportWindow = new ReportReasonWindow(this);
    reportWindow->setModal(true);
    reportWindow->setVisible(false);
    connect(reportWindow,SIGNAL(success()),this,SLOT(bookLost()));
    //选择操作模式：归还续借、挂失
    handleWindow=new BookHandleWindow(this);
    handleWindow->setVisible(false);
    connect(handleWindow,SIGNAL(returnPatternConfirmed()),this,SLOT(bookReturning()));
    connect(handleWindow,SIGNAL(renewPatternConfirmed()),this,SLOT(bookRenewing()));
    connect(handleWindow,SIGNAL(lossPatternConfirmed()),this,SLOT(getReason()));
}

ReturnWindow::~ReturnWindow()
{

    for(int i=0;i<20;i++)
    {
        delete returnBtn[i];
        for(int j=0;j<3;j++)
            delete item[i][j];
    }
    delete handleWindow;
    delete reportWindow;
    delete borrowTable;
}

void ReturnWindow::paintEvent(QPaintEvent *paintEvent)
{
    int l=activereader->getIntByTag("bor_num");
    for(int row=0;row<activereader->getIntByTag("bor_num");row++)
    {
        Book* borrowedBook=search(activereader->bor_list[row].id,5)[0];
        item[row][0]->setText(borrowedBook->getStringByTag("title"));
        item[row][1]->setText((activereader->bor_list)[row].st.toString("yyyy-MM-dd"));
        item[row][2]->setText((activereader->bor_list)[row].exp.toString("yyyy-MM-dd"));
        borrowTable->setItem(row,0,item[row][0]);
        borrowTable->setItem(row,1,item[row][1]);
        borrowTable->setItem(row,2,item[row][2]);
    }
    for(int i=l;i<20;i++)
    {
        item[i][0]->setText("");
        item[i][1]->setText("");
        item[i][2]->setText("");
        borrowTable->setItem(i,0,item[i][0]);
        borrowTable->setItem(i,1,item[i][1]);
        borrowTable->setItem(i,2,item[i][2]);
    }
    for(int i=0;i<l;i++)
        returnBtn[i]->setVisible(true);
    for(int i=l;i<20;i++)
        returnBtn[i]->setVisible(false);
    popUp=new MessageBox(this);
    popUp->setGeometry(this->width()/3,this->height()/4,popUp->width(),popUp->height());
    popUp->setVisible(false);
}

void ReturnWindow::bookHandling()
{
    ToolButton* clickedButton=qobject_cast<ToolButton*>(sender());
    int i=(clickedButton->objectName()).toInt();
    order=i;
    handleWindow->setVisible(true);
}

void ReturnWindow::bookReturning()
{
    handleWindow->setVisible(true);
    returning(order,activereader,systemDate);
    popUp->setText("归还成功");
    popUp->setVisible(true);
    saveXml();
    saveXml2();
    update();
}

void ReturnWindow::bookRenewing()
{
    int state=renew(order,activereader,systemDate);
    if(state==2)
        popUp->setText("抱歉，图书已被预订");
    else if(state==1)
        popUp->setText("图书超期，无法续借");
    else if(state==3)
        popUp->setText("无需续借");
    else
        popUp->setText("续借成功");
    saveXml();
    saveXml2();
    popUp->setVisible(true);
}

void ReturnWindow::bookLost()
{
    report(order,activereader,reportWindow->getReasons().join(","));
    saveXml();
    saveXml2();
}

void ReturnWindow::getReason(){
    reportWindow->setVisible(true);
}
