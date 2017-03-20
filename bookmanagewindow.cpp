#include "bookmanagewindow.h"
#include <QPainter>
#include <QDebug>

BookManageWindow::BookManageWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150,170,859,533);
    this->setStyleSheet("background-color:#ffffff;border:none");
    isAddingBook=true;
    defaultCoverPath=new QString(":/Images/NoCover.png");

    //切换模式按键
    changePatternBtn=new QToolButton(this);
    rightArrow=new QPixmap(":/Images/Icons/RightArrow.png");
    leftArrow=new QPixmap(":/Images/Icons/LeftArrow.png");
    changePatternBtn->setIcon(*rightArrow);
    changePatternBtn->setIconSize(QSize(50,50));
    changePatternBtn->setStyleSheet("background-color:transparent");
    changePatternBtn->setGeometry(this->width()/2+40,5,50,50);
    connect(changePatternBtn,SIGNAL(clicked()),this,SLOT(changePattern()));

    //添加对话框
        //LineEdit字体调色板
    QPalette textPalette;
    textPalette.setColor(QPalette::Text,Qt::gray);

    getTitile=new QLineEdit(this);
    getTitile->setGeometry(100,70,400,40);
    getTitile->setStyleSheet("background-color:#ccffff");
    getTitile->setFont(QFont("微软雅黑",20));
    getTitile->setPalette(textPalette);

    getAuthor=new QLineEdit(this);
    getAuthor->setGeometry(100,120,400,40);
    getAuthor->setStyleSheet("background-color:#ccffff");
    getAuthor->setFont(QFont("微软雅黑",20));
    getAuthor->setPalette(textPalette);

    getPress=new QLineEdit(this);
    getPress->setGeometry(130,170,370,40);
    getPress->setStyleSheet("background-color:#ccffff");
    getPress->setFont(QFont("微软雅黑",20));
    getPress->setPalette(textPalette);

    getAmount=new QSpinBox(this);
    getAmount->setGeometry(100,220,400,40);
    getAmount->setMaximum(10000);
    getAmount->setStyleSheet("background-color:#ccffff;");
    getAmount->setFont(QFont("微软雅黑",20));
    getAmount->setPalette(textPalette);

    getDescription=new QTextEdit(this);
    getDescription->setGeometry(30,320,470,200);
    getDescription->setStyleSheet("background-color:#ccffff");
    getDescription->setFont(QFont("微软雅黑",15));
    getDescription->setPalette(textPalette);

    addBookBtn=new QPushButton(this);
    addBookBtn->setFont(QFont("微软雅黑",15));
    addBookBtn->setText("添加图书");
    addBookBtn->setGeometry(603,473,150,40);
    addBookBtn->setStyleSheet("background-color:#ccffff");
    //connect(addBook)


    //添加图片部分
    cover.load(*defaultCoverPath);

    addCoverBtn=new QPushButton(this);
    addCoverBtn->setText("添加封面");
    addCoverBtn->setFont(QFont("微软雅黑",15));
    addCoverBtn->setGeometry(603,423,150,40);
    addCoverBtn->setStyleSheet("background-color:#ccffff");
    connect(addCoverBtn,SIGNAL(clicked()),this,SLOT(chooseCover()));

    //设置部件不可见
    getTitile->setVisible(false);
    getAuthor->setVisible(false);
    getPress->setVisible(false);
    getAmount->setVisible(false);
    addCoverBtn->setVisible(false);
}

void BookManageWindow::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont titleFont("幼圆",30);
    QFont elemFont("幼圆",20);
    painter.setFont(titleFont);

    //标题画笔
    QPen titlePen(QColor("#336699"));

    //表单文字画笔
    QPen textPen(QColor("#99cccc"));

    //分割线画笔
    QPen dashLine;
    dashLine.setColor(QColor("#cccccc"));
    dashLine.setStyle(Qt::DashLine);

    if(isAddingBook==true)
    {
        changePatternBtn->setIcon(*rightArrow);
        painter.setPen(titlePen);
        painter.drawText(this->width()/3,45,"添加图书");
        painter.setPen(dashLine);
        painter.drawLine(0,60,this->width(),60);
        painter.setFont(elemFont);
        painter.setPen(textPen);
        //绘制表单提示字符
        painter.drawText(30,100,"书名:");
        painter.drawText(30,150,"作者:");
        painter.drawText(30,200,"出版社:");
        painter.drawText(30,250,"数量:");
        painter.drawText(30,300,"简介:");
        //绘制封面
        painter.drawPixmap(550,70,250,333,cover);

        //设置部件可见
        getTitile->setVisible(true);
        getAuthor->setVisible(true);
        getPress->setVisible(true);
        getAmount->setVisible(true);
        addCoverBtn->setVisible(true);
        addBookBtn->setVisible(true);
        getDescription->setVisible(true);
    }
    else
    {
        changePatternBtn->setIcon(*leftArrow);
        painter.setPen(titlePen);
        painter.drawText(this->width()/3,45,"删减图书");
        painter.setPen(dashLine);
        painter.drawLine(0,60,this->width(),60);

        //设置部件不可见
        getTitile->setVisible(false);
        getAuthor->setVisible(false);
        getPress->setVisible(false);
        getAmount->setVisible(false);
        addCoverBtn->setVisible(false);
        addBookBtn->setVisible(false);
        getDescription->setVisible(false);
    }
}

void BookManageWindow::changePattern()
{
    isAddingBook=!isAddingBook;
    update();
}

void BookManageWindow::chooseCover()
{
    QUrl coverUrl=QFileDialog::getOpenFileUrl(this,tr("Choose a Cover"),tr("F:"),tr("Image(*.png *.jpg)"));
    QString coverPath=coverUrl.path().mid(1);
    if(!cover.load(coverPath))
        cover.load(*defaultCoverPath);
    this->update();
}


