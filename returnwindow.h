#ifndef RETURNWINDOW_H
#define RETURNWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QTableWidget>
#include <QHeaderView>
#include "toolbutton.h"
#include "reader_mgmt.h"

extern Reader* activereader;
extern qreal dpi;
extern QDate systemDate;

class ReturnWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    ReturnWindow(QWidget *parent = 0);
    QTableWidget* borrowTable;
    QTableWidgetItem* item[20][3];
    ToolButton* returnBtn[20];
protected:
    void paintEvent(QPaintEvent *paintEvent);
signals:

public slots:
    void bookReturned();
};

#endif // RETURNWINDOW_H
