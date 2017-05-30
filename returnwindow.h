#ifndef RETURNWINDOW_H
#define RETURNWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QTableWidget>
#include <QHeaderView>
#include "toolbutton.h"
#include "reader_mgmt.h"
#include "bookhandlewindow.h"
#include "messagebox.h"
#include "reportreasonwindow.h"

extern Reader* activereader;
extern qreal dpi;
extern QDate systemDate;

class ReturnWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    ReturnWindow(QWidget *parent = 0);
    ~ReturnWindow();
    QTableWidget* borrowTable;
    QTableWidgetItem* item[20][3];
    ToolButton* returnBtn[20];
    BookHandleWindow* handleWindow;
    ReportReasonWindow * reportWindow;
    MessageBox* popUp;
    int order;   //当前操作的图书
protected:
    void paintEvent(QPaintEvent *paintEvent);
signals:

public slots:
    void bookHandling();
    void bookReturning();
    void bookRenewing();
    void bookLost();
    void getReason();
};

#endif // RETURNWINDOW_H
