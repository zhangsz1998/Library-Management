#ifndef PERSONALINFOWINDOW_H
#define PERSONALINFOWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <vector>
#include <QPainter>

#include "reader_mgmt.h"
#include "toolbutton.h"

extern Reader* activereader;
extern qreal dpi;

enum ExhibitPattern
{
    PersonalInfo,
    BookInfo,
    Messages
};

class PersonalInfoWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    PersonalInfoWindow(QWidget *parent = 0);
protected:
    ToolButton* showPersonalInfoBtn;
    ToolButton* showBookInfoBtn;
    ToolButton* showMessagesBtn;
    ExhibitPattern pattern;

    QString name;
    QString id;
    QString agency;
    QString credit;
    int illegal_count;

    std::vector<QString> coverPath_bor;
    std::vector<QString> bookTitle_bor;
    std::vector<QString> coverPath_rev;
    std::vector<QString> bookTitle_rev;

    void paintEvent(QPaintEvent *paintEvent);
signals:

public slots:
    void showPersonalInfo();
    void showBookInfo();
    void showMessagesInfo();
};

#endif // PERSONALINFOWINDOW_H
