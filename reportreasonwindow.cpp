#include "reportreasonwindow.h"
#include <QDebug>

extern qreal dpi;

ReportReasonWindow::ReportReasonWindow(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet({"background-color:#ffffff;border:1px;border-style:solid;border-color:black;border-radius:4px"});
    this->setGeometry(20*dpi,10*dpi,800*dpi,520*dpi);

    closeBtn= new ToolButton(this,QColor(0,0,0,0),QColor(0,153,255,255));
    closeBtn->setEnterColor("#ff6666");
    closeBtn->setGeometry(this->width()-30*dpi,1*dpi,29*dpi,29*dpi);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));


    reason1=new QCheckBox(this);
    reason1->setGeometry(50*dpi,100*dpi,200*dpi,30*dpi);
    reason1->setFont(QFont("微软雅黑",15));
    reason1->setStyleSheet({"background-color:transparent;border:none"});
    reason1->setText("图书损坏");
    reason1->setVisible(true);
    reason1->setCheckState(Qt::Unchecked);

    reason2=new QCheckBox(this);
    reason2->setGeometry(50*dpi,150*dpi,200*dpi,30*dpi);
    reason2->setStyleSheet({"background-color:transparent;border:none"});
    reason2->setFont(QFont("微软雅黑",15));
    reason2->setText("图书内页缺失");
    reason2->setVisible(true);
    reason2->setCheckState(Qt::Unchecked);

    reason3=new QCheckBox(this);
    reason3->setGeometry(50*dpi,200*dpi,200*dpi,30*dpi);
    reason3->setStyleSheet({"background-color:transparent;border:none"});
    reason3->setFont(QFont("微软雅黑",15));
    reason3->setText("图书封面缺失");
    reason3->setVisible(true);
    reason3->setCheckState(Qt::Unchecked);

    reason4=new QCheckBox(this);
    reason4->setGeometry(300*dpi,100*dpi,200*dpi,30*dpi);
    reason4->setStyleSheet({"background-color:transparent;border:none"});
    reason4->setFont(QFont("微软雅黑",15));
    reason4->setText("图书内容篡改");
    reason4->setVisible(true);
    reason4->setCheckState(Qt::Unchecked);

    reason5=new QCheckBox(this);
    reason5->setGeometry(300*dpi,150*dpi,200*dpi,30*dpi);
    reason5->setStyleSheet({"background-color:transparent;border:none"});
    reason5->setFont(QFont("微软雅黑",15));
    reason5->setText("图书遗失");
    reason5->setVisible(true);
    reason5->setCheckState(Qt::Unchecked);

    reason6=new QCheckBox(this);
    reason6->setGeometry(300*dpi,200*dpi,400*dpi,30*dpi);
    reason6->setStyleSheet({"background-color:transparent;border:none"});
    reason6->setFont(QFont("微软雅黑",15));
    reason6->setText("图书已归还，但信息未更新");
    reason6->setVisible(true);
    reason6->setCheckState(Qt::Unchecked);

    reason7=new QCheckBox(this);
    reason7->setGeometry(550*dpi,100*dpi,200*dpi,30*dpi);
    reason7->setStyleSheet({"background-color:transparent;border:none"});
    reason7->setFont(QFont("微软雅黑",15));
    reason7->setText("图书借阅证明遗失");
    reason7->setVisible(true);
    reason7->setCheckState(Qt::Unchecked);

    reason8=new QCheckBox(this);
    reason8->setGeometry(550*dpi,150*dpi,200*dpi,30*dpi);
    reason8->setStyleSheet({"background-color:transparent;border:none"});
    reason8->setFont(QFont("微软雅黑",15));
    reason8->setText("借书证遗失");
    reason8->setVisible(true);
    reason8->setCheckState(Qt::Unchecked);

    getOtherReason=new QTextEdit(this);
    getOtherReason->setGeometry(50*dpi,300*dpi,600*dpi,200*dpi);
    getOtherReason->setStyleSheet({"background-color: #ffffff"});
    getOtherReason->setFont(QFont("微软雅黑",15));

    noReasonWarning=new MessageBox(this);
    noReasonWarning->setGeometry(280*dpi,150*dpi,noReasonWarning->width(),noReasonWarning->height());
    noReasonWarning->setText("请填写至少一个理由");
    noReasonWarning->setVisible(false);

    confirmBtn=new ToolButton(this);
    confirmBtn->setFont(QFont("微软雅黑",15));
    confirmBtn->setGeometry(670*dpi,450*dpi,100*dpi,40*dpi);
    confirmBtn->setText("提交");
    connect(confirmBtn,SIGNAL(clicked()),this,SLOT(refreshReasons()));
    connect(confirmBtn,SIGNAL(clicked()),this,SLOT(showMessageBox()));

    submitComplete=new MessageBox(this);
    submitComplete->setGeometry(280*dpi,150*dpi,submitComplete->width(),submitComplete->height());
    submitComplete->setText("提交成功");
    submitComplete->setVisible(false);
    connect(submitComplete->confirmBtn,SIGNAL(clicked()),this,SLOT(modified()));
    connect(submitComplete->confirmBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(submitComplete->closeBtn,SIGNAL(clicked()),this,SLOT(close()));
}

ReportReasonWindow::~ReportReasonWindow()
{
    delete closeBtn;
    delete confirmBtn;

    delete reason1;
    delete reason2;
    delete reason3;
    delete reason4;
    delete reason5;
    delete reason6;
    delete reason7;
    delete reason8;
    delete getOtherReason;

    delete submitComplete;
    delete noReasonWarning;
}

QStringList ReportReasonWindow::getReasons()
{
    return reasons;
}

void ReportReasonWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont titleFont("微软雅黑",30);
    QFont elemFont("微软雅黑",20);
    //标题画笔
    QPen titlePen(QColor("#336699"));

    painter.setPen(titlePen);
    painter.setFont(titleFont);
    painter.drawText(20*dpi,60*dpi,"请填写挂失理由");
    painter.setFont(elemFont);
    painter.drawText(20*dpi,280*dpi,"其他原因：");
}

void ReportReasonWindow::showMessageBox()
{
    if(reasons.length()!=0)
        submitComplete->setVisible(true);
    else
        noReasonWarning->setVisible(true);
}

void ReportReasonWindow::refreshReasons()
{
    reasons.clear();
    if(reason1->isChecked())
        reasons.append(reason1->text());
    if(reason2->isChecked())
        reasons.append(reason2->text());
    if(reason3->isChecked())
        reasons.append(reason3->text());
    if(reason4->isChecked())
        reasons.append(reason4->text());
    if(reason5->isChecked())
        reasons.append(reason5->text());
    if(reason6->isChecked())
        reasons.append(reason6->text());
    if(reason7->isChecked())
        reasons.append(reason7->text());
    if(reason8->isChecked())
        reasons.append(reason8->text());
    QString otherReason=getOtherReason->toPlainText();
    getOtherReason->clear();
    reason1->setCheckState(Qt::Unchecked);
    reason2->setCheckState(Qt::Unchecked);
    reason3->setCheckState(Qt::Unchecked);
    reason4->setCheckState(Qt::Unchecked);
    reason6->setCheckState(Qt::Unchecked);
    reason7->setCheckState(Qt::Unchecked);
    reason8->setCheckState(Qt::Unchecked);
    if(otherReason.length()!=0)
        reasons.append(otherReason);
}

void ReportReasonWindow::modified()
{
    emit success();
}
