#include "searchbar.h"

extern qreal dpi;

SearchBar::SearchBar(QWidget *parent)
    :QWidget(parent)
{
    label=new QLabel(parent);
    lineEdit=new QLineEdit(parent);
    //searchButton=new QToolButton(parent);
    label->setPixmap(QPixmap(":/Images/Icons/search-icon.png").scaled(30*dpi,30*dpi,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    label->setStyleSheet("background-color:transparent;");
    label->setGeometry(20*dpi,parent->height()/6,30*dpi,30*dpi);
    
    //搜索条
    lineEdit->setGeometry(155*dpi,parent->height()/6-5*dpi,parent->width()-170*dpi,40*dpi);
    lineEdit->setStyleSheet("background-color:transparent;border:1px;border-color:white;border-style:solid;border-left:none");
    lineEdit->setFont(QFont("微软雅黑",15));
    lineEdit->setPlaceholderText("Search");
    QPalette textPalette;
    textPalette.setColor(QPalette::Text,Qt::gray);
    lineEdit->setPalette(textPalette);

    //搜索类别选择
    chooseMode=new QComboBox(this);
    chooseMode->setGeometry(55*dpi,parent->height()/6-5*dpi,100*dpi,40*dpi);
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
