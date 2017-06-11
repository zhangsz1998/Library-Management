#include "bookmanagewindow.h"
#include <QPainter>
#include <QDebug>
#include <QList>
#include <QSPinBox>
#include "book_mgmt.h"
#include "reader_mgmt.h"

extern QString coverDir;
extern QDate systemDate;
extern qreal dpi;
extern std::vector<Book> booklist;
extern Reader * activereader;
extern std::vector<Reader> readerlist;
extern bool userMessageChanged;

BookManageWindow::BookManageWindow(QWidget *parent) : QMdiSubWindow(parent)
{
    bookEditing=Q_NULLPTR;

    setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(150*dpi,170*dpi,859*dpi,533*dpi);
    this->setStyleSheet("background-color:#ffffff;border:none");
    pattern=adding;
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

/********************************添加图书界面***********************************/
    //添加对话框
        //LineEdit字体调色板
    QPalette textPalette;
    textPalette.setColor(QPalette::Text,Qt::gray);

    getTitile=new QLineEdit(this);
    getTitile->setGeometry(100*dpi,70*dpi,400*dpi,40*dpi);
    getTitile->setStyleSheet("background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius:10px;padding: 4px");
    getTitile->setFont(QFont("微软雅黑",20));
    getTitile->setPalette(textPalette);

    getAuthor=new QLineEdit(this);
    getAuthor->setGeometry(100*dpi,120*dpi,400*dpi,40*dpi);
    getAuthor->setStyleSheet("background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius:10px;padding: 4px");
    getAuthor->setFont(QFont("微软雅黑",20));
    getAuthor->setPalette(textPalette);

    getPress=new QLineEdit(this);
    getPress->setGeometry(130*dpi,170*dpi,370*dpi,40*dpi);
    getPress->setStyleSheet("background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius:10px;padding: 4px");
    getPress->setFont(QFont("微软雅黑",20));
    getPress->setPalette(textPalette);

    getAmount=new QSpinBox(this);
    getAmount->setGeometry(100*dpi,220*dpi,400*dpi,40*dpi);
    getAmount->setMaximum(10000);
    getAmount->setStyleSheet(
                "QSpinBox{background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius: 4px}"
                "QSpinBox::down-button{width:30px;height:30px;image:url(:/Images/Icons/DownArrow.png);}"
                "QSpinBox::up-button{width:30px;height:30px;image:url(:/Images/Icons/UpArrow.png);}}"
                );
    getAmount->setFont(QFont("微软雅黑",20));
    getAmount->setPalette(textPalette);

    getCategory=new QComboBox(this);
    getCategory->setGeometry(100*dpi,270*dpi,400*dpi,40*dpi);
    getCategory->setStyleSheet(
                "QComboBox{background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius: 4px}"
                "QComboBox::drop-down{width:40px;height:40px;image:url(:/Images/Icons/DownArrow.png);}"
                );
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
    getDescription->setStyleSheet("background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius:10px;padding: 4px");
    getDescription->setFont(QFont("微软雅黑",15));
    getDescription->setPalette(textPalette);

    addBookBtn=new QPushButton(this);
    addBookBtn->setFont(QFont("微软雅黑",15));
    addBookBtn->setText("添加图书");
    addBookBtn->setGeometry(603*dpi,473*dpi,150*dpi,40*dpi);
    addBookBtn->setStyleSheet("background-color:#ccffff");
    connect(addBookBtn,SIGNAL(clicked()),this,SLOT(addNewBook()));


    //添加图片部分
    cover.load(*defaultCoverPath);

    addCoverBtn=new QPushButton(this);
    addCoverBtn->setText("添加封面");
    addCoverBtn->setFont(QFont("微软雅黑",15));
    addCoverBtn->setGeometry(603*dpi,423*dpi,150*dpi,40*dpi);
    addCoverBtn->setStyleSheet("background-color:#ccffff");
    connect(addCoverBtn,SIGNAL(clicked()),this,SLOT(chooseCover()));
/**********************************************************************************/

/*********************************搜索待修改图书信息界面**********************************/

    getId=new QLineEdit(this);
    getId->setGeometry(200*dpi,210*dpi,400*dpi,40*dpi);
    getId->setStyleSheet("background-color:transparent;border:1px;border-color:gray;border-style:solid;border-radius:10px;padding: 4px");
    getId->setFont(QFont("微软雅黑",20));
    getId->setPalette(textPalette);
    getId->setPlaceholderText("请输入待修改图书编号");

    searchBtn=new ToolButton(this);
    searchBtn->setGeometry(610*dpi,210*dpi,40*dpi,40*dpi);
    searchBtn->setIcon(QPixmap(":/Images/Icons/Goback.png"));
    searchBtn->setIconSize(QSize(30*dpi,30*dpi));

/**********************************************************************************/

/**********************************修改图书界面******************************************/
    modifyConfirmBtn=new ToolButton(this);
    modifyConfirmBtn->setText("确认");
    modifyConfirmBtn->setFont(QFont("微软雅黑",15));
    modifyConfirmBtn->setGeometry(763*dpi,473*dpi,80*dpi,40*dpi);
    connect(modifyConfirmBtn,SIGNAL(clicked()),this,SLOT(nowEditing()));
    connect(modifyConfirmBtn,SIGNAL(clicked()),this,SLOT(isAuthorized()));

    deleteBtn=new ToolButton(this);
    deleteBtn->setFont(QFont("微软雅黑",15));
    deleteBtn->setText("删除图书");
    deleteBtn->setGeometry(603*dpi,473*dpi,150*dpi,40*dpi);
    connect(deleteBtn,SIGNAL(clicked()),this,SLOT(nowDeleting()));
    connect(deleteBtn,SIGNAL(clicked()),this,SLOT(isAuthorized()));

    checkWindow=new AuthorityCheckWindow(this);
    checkWindow->setModal(true);
    checkWindow->setGeometry(200*dpi,100*dpi,500*dpi,175*dpi);
    checkWindow->setVisible(false);
    connect(checkWindow,SIGNAL(isAuthorized()),this,SLOT(isAuthorized()));
    connect(checkWindow,SIGNAL(notAuthorized()),this,SLOT(notAuthorized()));

    getReasonWindow=new GetReasonWindow(this);
    getReasonWindow->setModal(true);
    getReasonWindow->setVisible(false);
    connect(getReasonWindow,SIGNAL(successfullyModified()),this,SLOT(changeBookInfo()));
/***************************************************************************************/

    //弹窗
    popUp=new MessageBox(this);
    popUp->setVisible(false);
    popUp->setModal(true);
    popUp->setGeometry(220*dpi,150*dpi,popUp->width(),popUp->height());

    //设置部件不可见
    getTitile->setVisible(false);
    getAuthor->setVisible(false);
    getPress->setVisible(false);
    getAmount->setVisible(false);
    addCoverBtn->setVisible(false);
    getId->setVisible(false);
    searchBtn->setVisible(false);
    modifyConfirmBtn->setVisible(false);
    deleteBtn->setVisible(false);
}

int BookManageWindow::getCategoryIndex(QString s)
{
    if(s=="文学")
        return 0;
    if(s=="小说")
        return 1;
    if(s=="传记")
        return 2;
    if(s=="青春与动漫")
        return 3;
    if(s=="经济")
        return 4;
    if(s=="投资理财")
        return 5;
    if(s=="少儿")
        return 6;
    if(s=="历史")
        return 7;
    if(s=="哲学与宗教")
        return 8;
    if(s=="国学")
        return 9;
    if(s=="心理学")
        return 10;
    if(s=="政治与军事")
        return 11;
    if(s=="法律")
        return 12;
    if(s=="社会科学")
        return 13;
    if(s=="孕产育儿")
        return 14;
    if(s=="旅游与地图")
        return 15;
    if(s=="烹饪美食与酒")
        return 16;
    if(s=="健身与保健")
        return 17;
    if(s=="婚恋与两性")
        return 18;
    if(s=="娱乐")
        return 19;
    if(s=="时尚")
        return 20;
    if(s=="家居休闲")
        return 21;
    if(s=="教辅")
        return 22;
    if(s=="考试")
        return 23;
    if(s=="英语与其他外语")
        return 24;
    if(s=="词典与工具书")
        return 25;
    if(s=="励志与成功")
        return 26;
    if(s=="科技")
        return 27;
    if(s=="医学")
        return 28;
    if(s=="计算机与互联网")
        return 29;
    if(s=="科学与自然")
        return 30;
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
    delete getId;
    delete modifyConfirmBtn;
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

    painter.setPen(dashLine);
    painter.drawLine(0*dpi,60*dpi,this->width(),60*dpi);
    switch (pattern)
    {
    case adding:
        changePatternBtn->setIcon(*rightArrow);
        painter.setPen(titlePen);
        painter.drawText(this->width()/3,45*dpi,"添加图书");
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
        getCategory->setVisible(true);
        getAmount->setVisible(true);
        addCoverBtn->setVisible(true);
        addBookBtn->setVisible(true);
        getDescription->setVisible(true);

        //设置不可见
        getId->setVisible(false);
        searchBtn->setVisible(false);
        modifyConfirmBtn->setVisible(false);
        deleteBtn->setVisible(false);
        break;
    case searching:
        changePatternBtn->setIcon(*leftArrow);
        painter.setPen(titlePen);
        painter.drawText(this->width()/3,45*dpi,"修改图书");
        painter.setFont(elemFont);
        painter.setPen(textPen);

        //设置部件可见
        getId->setVisible(true);
        connect(getId,SIGNAL(returnPressed()),this,SLOT(searchToEdit()));

        searchBtn->setVisible(true);
        connect(searchBtn,SIGNAL(clicked()),this,SLOT(searchToEdit()));

        //设置部件不可见
        getTitile->setVisible(false);
        getAuthor->setVisible(false);
        getPress->setVisible(false);
        getAmount->setVisible(false);
        addCoverBtn->setVisible(false);
        addBookBtn->setVisible(false);
        getDescription->setVisible(false);
        getCategory->setVisible(false);
        modifyConfirmBtn->setVisible(false);
        deleteBtn->setVisible(false);
        break;
    case editing:
        painter.setPen(titlePen);
        painter.drawText(this->width()/3,45*dpi,"修改图书");
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
        getCategory->setVisible(true);
        getAmount->setVisible(true);
        addCoverBtn->setVisible(true);
        addBookBtn->setVisible(true);
        getDescription->setVisible(true);
        modifyConfirmBtn->setVisible(true);
        deleteBtn->setVisible(true);

        //设置不可见
        getId->setVisible(false);
        searchBtn->setVisible(false);
        addBookBtn->setVisible(false);

        break;
    }
}


void BookManageWindow::changePattern()
{
    if(pattern==adding)
    {
        pattern=searching;
    }
    else
    {
        pattern=adding;
        getTitile->clear();
        getAuthor->clear();
        getPress->clear();
        getAmount->clear();
        getDescription->clear();
    }
    repaint();
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
        newCoverPath="/"+title+".png";
    }
    QString id = myHash(author,press,category,title);
    newBook=new Book(title,author,press,desp,id,category,amount,amount,0,0,newCoverPath,0);        //由于编号函数暂未确定，先置编号为titile
    add_newbook(*newBook);
    saveXml();
    cover.load(*defaultCoverPath);
    popUp->setText("添加成功");
    popUp->setVisible(true);
    getTitile->clear();
    getAuthor->clear();
    getPress->clear();
    getDescription->clear();
    getAmount->clear();
    log_print("add",activereader->getStringByTag("id"),id,"");
    this->repaint();
}

void BookManageWindow::searchToEdit()
{
     std::vector<Book*> result=search(this->getId->text(),5);
     if(result.size()==0)
     {
         popUp->setText("未搜索到相关结果");
         popUp->setWindowFlags(Qt::WindowStaysOnTopHint);
         popUp->setVisible(true);
     }
     else
     {
         bookEditing=result[0];
         pattern=editing;
         getTitile->setText(bookEditing->getStringByTag("title"));
         getAuthor->setText(bookEditing->getStringByTag("author"));
         getPress->setText(bookEditing->getStringByTag("press"));
         getAmount->setValue(bookEditing->getIntByTag("amount"));
         getCategory->setCurrentIndex(getCategoryIndex(bookEditing->getStringByTag("category")));
         getDescription->setText(bookEditing->getStringByTag("description"));   //这句话迷之运行特别慢.....
         cover.load(bookEditing->getStringByTag("loc"));
         newCoverPath=bookEditing->getStringByTag("loc");
         update();
     }
}

void BookManageWindow::changeBookInfo()
{
    if(changeInfoPattern==Modify)
    {
        QString title=getTitile->text();
        QString author=getAuthor->text();
        QString press=getPress->text();
        QString desp=getDescription->toPlainText();
        QString category=getCategory->currentText();
        if(newCoverPath!=defaultCoverPath)
        {
            cover.save(coverDir+"/"+title+".png","png");
            newCoverPath=coverDir+"/"+title+".png";
        }
        int amount=getAmount->value();
        bookEditing->setStringByTag("title",title);
        bookEditing->setStringByTag("author",author);
        bookEditing->setStringByTag("press",press);
        bookEditing->setStringByTag("description",desp);
        bookEditing->setStringByTag("category",category);
        bookEditing->setIntByTag("amount",amount);
        bookEditing->setStringByTag("loc",newCoverPath);
        log_print("modify",activereader->getStringByTag("id"),bookEditing->getStringByTag("id"),getReasonWindow->getReasons().join(","));
        if (bookEditing->is_resv=1 && bookEditing->getIntByTag("amount")>0){
            for (int i=0;i<readerlist.size();i++){
                int rnum = readerlist[i].getIntByTag("resv_num");
                for (int j=0;j<rnum;j++)
                    if (readerlist[i].resvs[j] == bookEditing->getStringByTag("id")) {
                        for (int k=j+1;k<rnum;k++)
                            readerlist[i].resvs[k-1] = readerlist[i].resvs[k];
                        rnum--;
                        if (readerlist[i].getIntByTag("msg_num")!=30)
                            readerlist[i].msg[readerlist[i].getIntByTag("msg_num")] = systemDate.toString("yyyy-MM-dd")+" 您预约的图书"+bookEditing->getStringByTag("id")+"已有库存，请尽快前往借阅！";
                        else {
                           for (int k=0;k<29;k++)
                               readerlist[i].msg[k]=readerlist[i].msg[k+1];
                           readerlist[i].msg[29] = systemDate.toString("yyyy-MM-dd")+" 您预约的图书"+bookEditing->getStringByTag("id")+"已有库存，请尽快前往借阅！";
                        }
                        if (readerlist[i].getIntByTag("msg_num") != 30) readerlist[i].IncIntByTag("msg_num");
                        else readerlist[i].is_modf = true;
                        userMessageChanged=true;
                    }
                readerlist[i].setIntByTag("resv_num",rnum);
            }

        }
        saveXml();      //无法保存...
        cover.load(*defaultCoverPath);
        popUp->setText("修改成功");
        popUp->setVisible(true);
        getTitile->clear();
        getAuthor->clear();
        getPress->clear();
        getDescription->clear();
        getAmount->clear();
    }
    if(changeInfoPattern==Delete)
    {
        bookEditing->is_delete=true;
        log_print("delete",activereader->getStringByTag("id"),bookEditing->getStringByTag("id"),getReasonWindow->getReasons().join(","));
        saveXml();
        popUp->setText("删除成功");
        popUp->setVisible(true);
        getTitile->clear();
        getAuthor->clear();
        getPress->clear();
        getDescription->clear();
        getAmount->clear();
    }
    pattern=searching;
    this->repaint();
}

void BookManageWindow::checkAuthority()
{
    if(changeInfoPattern==Delete&&bookEditing->getIntByTag("amount")!=bookEditing->getIntByTag("total"))
    {
        popUp->setText("图书已被外借！\n");
        popUp->setVisible(true);
    }
    else
    {
        checkWindow->setVisible(true);
    }
}

void BookManageWindow::notAuthorized()
{
    checkWindow->close();
    popUp->setText("身份验证失败!");
    popUp->show();
}

void BookManageWindow::isAuthorized()
{
    getReasonWindow->setVisible(true);
}

void BookManageWindow::nowEditing()
{
    changeInfoPattern=Modify;
}

void BookManageWindow::nowDeleting()
{
    changeInfoPattern=Delete;
}
