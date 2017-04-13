#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QLabel>
#include <QComboBox>
#include <QList>
#include <QString>

#include "book_mgmt.h"

class SearchBar : public QWidget
{
    Q_OBJECT
public:
    SearchBar(QWidget* parent);
    ~SearchBar();
    QLabel* label;
    QLineEdit* lineEdit;
    QComboBox* chooseMode;
    //QToolButton* searchButton;
    QString text()
    {
        return lineEdit->text();
    }
    int mode()
    {
        QString s=this->chooseMode->currentText();
        if(s=="书名")
            return 1;
        else if(s=="作者")
            return 2;
        else if(s=="出版社")
            return 3;
        else if(s=="简介")
            return 4;
        else if(s=="编号")
            return 5;
        else if(s=="类别")
            return 6;
        else if(s=="任意")
            return 7;
    }
};

#endif // SEARCHBAR_H
