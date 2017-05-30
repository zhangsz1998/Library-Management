#ifndef READERSEARCHWINDOW_H
#define READERSEARCHWINDOW_H

#include <QMdiSubWindow>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QPainter>

#include "toolbutton.h"
#include "reader_mgmt.h"
#include "messagebox.h"

extern std::vector<Reader> readerlist;
extern qreal dpi;

class ReaderSearchWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    ReaderSearchWindow(QWidget *parent = 0);
    ~ReaderSearchWindow();
    Reader* getRequestedUser();
protected:
    QTableWidget* readerList;
    ToolButton* searchDetail;    //搜索id
    ToolButton* searchUser;   //搜索用户
    ToolButton* resetBtn;     //展开表格
    QLineEdit* getId;     //用于获取读者编号,用于查询详细信息
    QLineEdit* getName;    //用于搜索姓名对应Id
    Reader* requestedUser;
    MessageBox* popUp;
    void paintEvent(QPaintEvent *paintEvent);
signals:
    void readerInfoRequest();
public slots:
    void searchByName();
    void askForInfo();
    void resetTable();
};

#endif // READERSEARCHWINDOW_H
