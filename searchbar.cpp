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
    lineEdit->setGeometry(55,parent->height()/6-5,parent->width()-70,40);
    lineEdit->setStyleSheet("background-color:transparent;");//border:none");
    lineEdit->setFont(QFont("微软雅黑",15));
    lineEdit->setPlaceholderText("Search");
    QPalette textPalette;
    textPalette.setColor(QPalette::Text,Qt::gray);
    lineEdit->setPalette(textPalette);
}
