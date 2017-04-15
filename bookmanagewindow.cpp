#include "bookmanagewindow.h"
#include <QPainter>
#include <QDebug>
#include <QList>

extern QString coverDir;
extern qreal dpi;

BookManageWindow::BookManageWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    this->setStyleSheet("background-color:#ffffff;border:none");
    isAddingBook=true;
    defaultCoverPath=new QString(":/Images/NoCover.png");
    newCoverPath=*defaultCoverPath;
    newBook=Q_NULLPTR;      //初始化当前添加书籍

    //切换模式按键
    changePatternBtn=new QToolButton(this);
    rightArrow=new QPixmap(":/Images/Icons/RightArrow.png");
    leftArrow=new QPixmap(":/Images/Icons/LeftArrow.png");
    changePatternBtn->setIcon(*rightArrow);
    changePatternBtn->setIconSize(QSize(50*dpi,50*dpi));
    changePatternBtn->setStyleSheet("background-color:transparent");
    changePatternBtn->setGeometry(this->width()/2+40*dpi,5*dpi,50*dpi,50*dpi);
    connect(changePatternBtn,SIGNAL(clicked()),this,SLOT(changePattern()));

    //添加对话框
        //LineEdit字体调色板
    QPalette textPalette;
    textPalette.setColor(QPalette::Text,Qt::gray);

    getTitile=new QLineEdit(this);
    getTitile->setGeometry(100*dpi,70*dpi,400*dpi,40*dpi);
    getTitile->setStyleSheet("background-color:#ccffff");
    getTitile->setFont(QFont("微软雅黑",20));
    getTitile->setPalette(textPalette);

    getAuthor=new QLineEdit(this);
    getAuthor->setGeometry(100*dpi,120*dpi,400*dpi,40*dpi);
    getAuthor->setStyleSheet("background-color:#ccffff");
    getAuthor->setFont(QFont("微软雅黑",20));
    getAuthor->setPalette(textPalette);

    getPress=new QLineEdit(this);
    getPress->setGeometry(130*dpi,170*dpi,370*dpi,40*dpi);
    getPress->setStyleSheet("background-color:#ccffff");
    getPress->setFont(QFont("微软雅黑",20));
    getPress->setPalette(textPalette);

    getAmount=new QSpinBox(this);
    getAmount->setGeometry(100*dpi,220*dpi,400*dpi,40*dpi);
    getAmount->setMaximum(10000);
    getAmount->setStyleSheet("background-color:#ccffff;");
    getAmount->setFont(QFont("微软雅黑",20));
    getAmount->setPalette(textPalette);

    getCategory=new QComboBox(this);
    getCategory->setGeometry(100*dpi,270*dpi,400*dpi,40*dpi);
    getCategory->setStyleSheet("background-color:#ccffff");
    getCategory->setFont(QFont("微软雅黑",20));
    getCategory->setPalette(textPalette);
    QList<QString> categoryList;
    categoryList.append("文学");
    categoryList.append("小说");
    categoryList.append("传记");
    categoryList.append("青春与动漫");
    categoryList.append("经济");
    categoryList.append("投资理财");
    categoryList.append("少儿");
    categoryList.append("历史");
    categoryList.append("哲学与宗教");
    categoryList.append("国学");
    categoryList.append("心理学");
    categoryList.append("政治与军事");
    categoryList.append("法律");
    categoryList.append("社会科学");
    categoryList.append("孕产育儿");
    categoryList.append("旅游与地图");
    categoryList.append("烹饪美食与酒");
    categoryList.append("健身与保健");
    categoryList.append("婚恋与两性");
    categoryList.append("娱乐");
    categoryList.append("时尚");
    categoryList.append("家居休闲");
    categoryList.append("教辅");
    categoryList.append("考试");
    categoryList.append("英语与其他外语");
    categoryList.append("词典与工具书");
    categoryList.append("励志与成功");
    categoryList.append("科技");
    categoryList.append("医学");
    categoryList.append("计算机与互联网");
    categoryList.append("科学与自然");
    const QStringList bookCategories(categoryList);
    getCategory->addItems(bookCategories);


    getDescription=new QTextEdit(this);
    getDescription->setGeometry(30*dpi,370*dpi,470*dpi,150*dpi);
    getDescription->setStyleSheet("background-color:#ccffff");
    getDescription->setFont(QFont("微软雅黑",15));
    getDescription->setPalette(textPalette);

    addBookBtn=new QPushButton(this);
    addBookBtn->setFont(QFont("微软雅黑",15));
    addBookBtn->setText("添加图书");
    addBookBtn->setGeometry(603*dpi,473*dpi,150*dpi,40*dpi);
    addBookBtn->setStyleSheet("background-color:#ccffff");
    connect(addBookBtn,SIGNAL(clicked()),this,SLOT(addNewBook()));

    addCompleteWindow=new MessageBox(this);
    addCompleteWindow->setText("添加成功");
    addCompleteWindow->setVisible(false);
    addCompleteWindow->setModal(true);
    addCompleteWindow->setGeometry(220*dpi,150*dpi,addCompleteWindow->width(),addCompleteWindow->height());

    //添加图片部分
    cover.load(*defaultCoverPath);

    addCoverBtn=new QPushButton(this);
    addCoverBtn->setText("添加封面");
    addCoverBtn->setFont(QFont("微软雅黑",15));
    addCoverBtn->setGeometry(603*dpi,423*dpi,150*dpi,40*dpi);
    addCoverBtn->setStyleSheet("background-color:#ccffff");
    connect(addCoverBtn,SIGNAL(clicked()),this,SLOT(chooseCover()));

    //设置部件不可见
    getTitile->setVisible(false);
    getAuthor->setVisible(false);
    getPress->setVisible(false);
    getAmount->setVisible(false);
    addCoverBtn->setVisible(false);
}

BookManageWindow::~BookManageWindow()
{
    delete getTitile;     //用于获取标题
    delete getAuthor;     //用于获取作者
    delete getPress;      //用于获取出版社
    delete getDescription; //用于获取简介
    delete getAmount;     //用于获取数量
    delete defaultCoverPath;     //默认封面路径
    delete rightArrow;
    delete leftArrow;
    delete addBookBtn;  //添加图书按钮
    delete addCoverBtn; //添加封面按钮
    delete changePatternBtn; //改变模式的按钮，添加界面为左箭头，否则为右箭头
    delete getCategory;
}

void BookManageWindow::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont titleFont("微软雅黑",30);
    QFont elemFont("微软雅黑",20);
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
        painter.drawText(this->width()/3,45*dpi,"添加图书");
        painter.setPen(dashLine);
        painter.drawLine(0*dpi,60*dpi,this->width(),60*dpi);
        painter.setFont(elemFont);
        painter.setPen(textPen);
        //绘制表单提示字符
        painter.drawText(30*dpi,100*dpi,"书名:");
        painter.drawText(30*dpi,150*dpi,"作者:");
        painter.drawText(30*dpi,200*dpi,"出版社:");
        painter.drawText(30*dpi,250*dpi,"数量:");
        painter.drawText(30*dpi,300*dpi,"类别");
        painter.drawText(30*dpi,350*dpi,"简介:");
        //绘制封面
        painter.drawPixmap(550*dpi,70*dpi,250*dpi,333*dpi,cover);

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
        painter.drawText(this->width()/3,45*dpi,"删减图书");
        painter.setPen(dashLine);
        painter.drawLine(0*dpi,60*dpi,this->width(),60*dpi);

        //设置部件不可见
        getTitile->setVisible(false);
        getAuthor->setVisible(false);
        getPress->setVisible(false);
        getAmount->setVisible(false);
        addCoverBtn->setVisible(false);
        addBookBtn->setVisible(false);
        getDescription->setVisible(false);
        getCategory->setVisible(false);
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
    newCoverPath=coverUrl.path().mid(1);
    if(!cover.load(newCoverPath))
    {
        cover.load(*defaultCoverPath);
        newCoverPath=*defaultCoverPath;
    }
    this->update();
}

void BookManageWindow::addNewBook()
{
    QString title=getTitile->text();
    QString author=getAuthor->text();
    QString press=getPress->text();
    QString desp=getDescription->toPlainText();
    QString category=getCategory->currentText();
    int amount=getAmount->value();
    if(newBook!=Q_NULLPTR)
        delete newBook;
    if(newCoverPath!=defaultCoverPath)
    {
        cover.save(coverDir+"/"+title+".png","png");
        newCoverPath=coverDir+"/"+title+".png";
    }
    newBook=new Book(title,author,press,desp,title,category,amount,amount,0,0,newCoverPath);        //由于编号函数暂未确定，先置编号为titile
    add_newbook(*newBook);
    saveXml();
    cover.load(*defaultCoverPath);
    addCompleteWindow->setVisible(true);
    getTitile->clear();
    getAuthor->clear();
    getPress->clear();
    getDescription->clear();
    getAmount->clear();
    this->repaint();
}
