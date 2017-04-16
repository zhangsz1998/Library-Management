#ifndef BOOKINFOWINDOW_H
#define BOOKINFOWINDOW_H

/*该类用于图书详细信息的展示*/

#include <QWidget>
#include <QMdiSubWindow>
#include "book_mgmt.h"
#include <QVector>
#include "toolbutton.h"

class BookInfoWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit BookInfoWindow(QWidget *parent = 0);
    Book* book;
    QPixmap cover;       //图书的封面
    QVector<QString> despList;    //图书简介分行
    ToolButton *borrowBtn;       //借阅按钮
    ToolButton *reservationBtn;  //预约按钮
    ToolButton *goBackBtn;      //返回按钮
    loadBook(Book* book);        //更新所需展示的图书信息
    ~BookInfoWindow();
signals:
public slots:

protected:
    void paintEvent(QPaintEvent *paintEvent);
};

#endif // BOOKINFOWINDOW_H
