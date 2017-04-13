#include "searchbar.h"

SearchBar::SearchBar(QWidget *parent)
    :QWidget(parent)
{
    label=new QLabel(parent);
    lineEdit=new QLineEdit(parent);
    //searchButton=new QToolButton(parent);
    label->setPixmap(QPixmap(":/Images/Icons/search-icon.png").scaled(30,30,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    label->setStyleSheet("background-color:transparent;");
    label->setGeometry(20,parent->height()/6,30,30);
    
    //搜索条
    lineEdit->setGeometry(155,parent->height()/6-5,parent->width()-170,40);
    lineEdit->setStyleSheet("background-color:transparent;border:1px;border-color:white;border-style:solid;border-left:none");
    lineEdit->setFont(QFont("微软雅黑",15));
    lineEdit->setPlaceholderText("Search");
    QPalette textPalette;
    textPalette.setColor(QPalette::Text,Qt::gray);
    lineEdit->setPalette(textPalette);

    //搜索类别选择
    chooseMode=new QComboBox(this);
    chooseMode->setGeometry(55,parent->height()/6-5,100,40);
    chooseMode->setPalette(textPalette);
    chooseMode->setFont(QFont("微软雅黑",15));
    QList<QString> modes_ini;
    modes_ini.append("书名");
    modes_ini.append("作者");
    modes_ini.append("出版社");
    modes_ini.append("简介");
    modes_ini.append("类别");
    modes_ini.append("编号");
    modes_ini.append("任意");
    const QStringList modes(modes_ini);
    chooseMode->addItems(modes);
    chooseMode->setStyleSheet(
                "QComboBox{background-color:transparent;border:1px;border-color:white;border-style:solid}"
                "QComboBox::drop-down{width:40px;height:40px;image:url(:/Images/Icons/DownArrow.png);}"
                );
}

SearchBar::~SearchBar()
{
    delete label;
    delete lineEdit;
}
