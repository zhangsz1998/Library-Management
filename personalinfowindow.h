#ifndef PERSONALINFOWINDOW_H
#define PERSONALINFOWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <vector>
#include <QPainter>
#include <QTextEdit>
#include <QScrollArea>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

#include "reader_mgmt.h"
#include "toolbutton.h"
#include "messagewidget.h"
#include "book_mgmt.h"

extern Reader* activereader;
extern qreal dpi;

enum ExhibitPattern
{
    PersonalInfo,
    BorrowInfo,
    ReserveInfo
};

class PersonalInfoWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    PersonalInfoWindow(QWidget *parent = 0);
protected:
    ToolButton* showPersonalInfoBtn;
    ToolButton* showBorrowInfoBtn;
    ToolButton* showReserveInfoBtn;

    ExhibitPattern pattern;

    std::vector<QString> coverPath_bor;
    std::vector<QString> bookTitle_bor;
    std::vector<QString> coverPath_rev;
    std::vector<QString> bookTitle_rev;
    MessageWidget* messageArea;

    QScrollArea* area;
    QTableWidget* borrowInfo;
    QTableWidget* reserveInfo;
    QTableWidgetItem* borrowItem[20][3];
    QTableWidgetItem* reserveItem[20][2];

    void paintEvent(QPaintEvent *paintEvent);
signals:

public slots:
    void showPersonalInfo();
    void showBorrowInfo();
    void showReserveInfo();
};

#endif // PERSONALINFOWINDOW_H
