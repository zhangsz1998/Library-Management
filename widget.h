#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QStyle>
#include <QPalette>
#include <QPoint>
#include <QMouseEvent>
#include <QPushButton>
#include <QPushButton>
#include "searchbar.h"
#include "toolbutton.h"
#include <QVBoxLayout>
#include "bookexhibition.h"
#include "bookmanagewindow.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QPoint offset;
protected:
    ToolButton* minimizeBtn;           //最小化按钮
    ToolButton* closeBtn;              //最大化按钮
    ToolButton* messageCentreBtn;            //消息中心按钮
    SearchBar* searchBar;                 //搜索栏

    //以下两个按钮为管理员界面特有
    ToolButton* bookManagementBtn;           //图书管理
    ToolButton* readerManagementBtn;         //读者管理
    //以下为全体读者均有的功能
    ToolButton* reservationBtn;              //图书预定
    ToolButton* borrowBtn;                   //图书借阅
    ToolButton* giveBackBtn;                 //图书归还
    ToolButton* overviewBtn;                 //图书概览
    ToolButton* loginBtn;                    //登录按钮
    ToolButton* personalInfoBtn;             //个人信息


    //中央界面
    BookExhibition* bookExhibitionWindow;
    BookManageWindow* bookManagementWindow;

    void paintEvent(QPaintEvent* event);

    //以下三个事件处理函数用于：实现窗口的拖动
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
protected slots:
    void showBookManagementWindow();
    void showSearchResult();
};

#endif // WIDGET_H
