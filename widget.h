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
#include <QDate>
#include <QPainter>
#include <QHeaderView>

#include "bookinfowindow.h"
#include "loginwindow.h"
#include "messagebox.h"
#include "personalinfowindow.h"
#include "searchbar.h"
#include "toolbutton.h"
#include "bookexhibition.h"
#include "bookmanagewindow.h"
#include "returnwindow.h"
#include "readersearchwindow.h"
#include "bookoverviewwindow.h"

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
    int preWindowFlag;       //若前一窗口为搜索框进入则为1,为图书概览界面则为2.....
protected:
    bool userAuthorized;
    bool isloged;
    ToolButton* minimizeBtn;           //最小化按钮
    ToolButton* closeBtn;              //最大化按钮
    ToolButton* messageCentreBtn;            //消息中心按钮
    SearchBar* searchBar;                 //搜索栏

    //以下两个按钮为管理员界面特有
    ToolButton* bookManagementBtn;           //图书管理
    ToolButton* readerManagementBtn;         //读者管理

    //以下为全体读者均有的功能
    ToolButton* reservationBtn;              //图书预定
    ToolButton* giveBackBtn;                 //图书归还
    ToolButton* overviewBtn;                 //图书概览
    ToolButton* loginBtn;                    //登录按钮
    ToolButton* logoutBtn;                   //注销登录按钮
    ToolButton* personalInfoBtn;             //个人信息
    MessageBox* popUp;
    AuthorityCheckWindow* checkUp;        //检查权限

    //中央界面
    BookOverviewWindow* bookOverviewWindow;
    BookExhibition* bookExhibitionWindow;
    BookManageWindow* bookManagementWindow;
    BookInfoWindow* bookInfoWindow;
    PersonalInfoWindow* personalInfoWindow;
    LoginWindow* loginWindow;
    ReturnWindow* returnWindow;
    ReaderSearchWindow* readerSearchWindow;

    void paintEvent(QPaintEvent* event);


    //日期管理
    ToolButton* changeDateBtn1;                //日期前进一天
    ToolButton* changeDateBtn2;                //日期前进一个月
    QString toWeekString(int week);            //1~7天转换成对应的英文字符串
    QString toMonthString(int month);          //1~12月转换成相应字符串
    void drawDate();                           //实现日期的显示

    //以下三个事件处理函数用于：实现窗口的拖动
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
public slots:
    void showBookInfoBySearch();
    void showBookManagementWindow();
    void showPersonalInfoWindow();
    void showMessages();
    void showSearchResult();
    void showLoginWindow();
    void showLogoutWindow();
    void showPreWindow();
    void showReturnWindow();
    void showOverviewWindow();
    void userLogedIn();
    void tryToLogOut();
    void tryClose();
    void showReaderInfoByRequest();
    void showReaderSearchWindow();
    void checkUpFailed();
    void showCheckUpWindow();
protected slots:
    void addDate();
    void addMonth();
    void daycheck();
    void userChecked();
signals:
    void dateChanged();
    void daysadd();
};

#endif // WIDGET_H
