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
#include "rechargewindow.h"
#include "messagebox.h"

extern Reader* activereader;
extern qreal dpi;
extern bool userMessageChanged;

enum LoadPattern
{
    byAdmin,
    bySelf
};

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
    ~PersonalInfoWindow();
    void setLoadPattern(LoadPattern a);
    void loadReader(Reader* m_reader);
protected:
    ToolButton* showPersonalInfoBtn;
    ToolButton* showBorrowInfoBtn;
    ToolButton* showReserveInfoBtn;

    ExhibitPattern pattern;
    LoadPattern loadPattern;

    std::vector<QString> coverPath_bor;
    std::vector<QString> bookTitle_bor;
    std::vector<QString> coverPath_rev;
    std::vector<QString> bookTitle_rev;
    MessageWidget* messageArea;
    RechargeWindow* rechargeWindow;
    Reader* reader;
    MessageBox* popUp;
    MessageBox* popUp2;
    QScrollArea* area;
    QTableWidget* borrowInfo;
    QTableWidget* reserveInfo;
    QTableWidgetItem* borrowItem[20][3];
    QTableWidgetItem* reserveItem[20][2];

    ToolButton* rechargeBtn;

    void paintEvent(QPaintEvent *paintEvent);

signals:

public slots:
    void showMessages();
    void showPersonalInfo();
    void showBorrowInfo();
    void showReserveInfo();
    void showRechargeWindow();
    void reCharge();
};

#endif // PERSONALINFOWINDOW_H
