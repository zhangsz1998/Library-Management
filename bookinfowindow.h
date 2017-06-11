#ifndef BOOKINFOWINDOW_H
#define BOOKINFOWINDOW_H

/*该类用于图书详细信息的展示*/
#include <QWidget>
#include <QMdiSubWindow>
#include "book_mgmt.h"
#include "reader_mgmt.h"
#include <QVector>
#include "borrowform.h"
#include "toolbutton.h"
#include "messagebox.h"
#include "resvform.h"

class BookInfoWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    BookInfoWindow(QWidget *parent = 0);
    Book* book;
    QPixmap cover;       //图书的封面
    QVector<QString> despList;    //图书简介分行
    ToolButton *borrowBtn;       //借阅按钮
    BorrowForm *borrowForm; //jieyuebiaodan
    ResvForm *resvForm;
    ToolButton *reservationBtn;  //预约按钮
    ToolButton *goBackBtn;      //返回按钮
    loadBook(Book* book);        //更新所需展示的图书信息
    MessageBox *popUp;
    ~BookInfoWindow();
signals:
public slots:
protected slots:
    void borrowEvent(void);
    void resvEvent(void);
protected:
    void paintEvent(QPaintEvent *paintEvent);
};

#endif // BOOKINFOWINDOW_H
