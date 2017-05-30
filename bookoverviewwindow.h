#ifndef BOOKOVERVIEWWINDOW_H
#define BOOKOVERVIEWWINDOW_H

#include <QMdiSubWindow>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPainter>
#include <QList>
#include <QPropertyAnimation>

#include "book_mgmt.h"
#include "toolbutton.h"
#include "label.h"

extern std::vector<Book> booklist;
extern qreal dpi;

class BookOverviewWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    BookOverviewWindow(QWidget *parent = 0);
    QStringList covers[30];
    QStringList titles[30];
    Label* coversOnDisplay[6];
    Label* titlesOnDisplay[6];
    std::vector<Book*> bookList;
    std::vector<Label*> mostBorsCovers;
    std::vector<Label*> mostBorsTitles;
    std::vector<Label*> mostRefCovers;
    std::vector<Label*> mostRefsTitles;
    QTableWidget* buttons;
    QVector<QRect> r_Cover;
    QVector<QRect> r_Title;
    ToolButton* categories[30];
    ToolButton* toLeft;
    ToolButton* toRight;
    QPropertyAnimation moveAction_Cover[6];
    QPropertyAnimation opacityAction_Cover[2];
    QPropertyAnimation moveAction_Title[6];
    QPropertyAnimation opacityAction_Title[2];
    QTimer* timerL;
protected:
    int lastIndex;  //当前被隐藏的是该类的第几本图书
    int firstIndexOnDisplay;  //第一个coversOndisplay的编号;
    int categoryOnDisplay;
    void paintEvent(QPaintEvent *paintEvent);
signals:

public slots:
    void startTimerL();
    void showBookByCategory();
    void moveLeft();
    void moveRight();
    void graduallyDisappear();
    void changeOrderL();
};

#endif // BOOKOVERVIEWWINDOW_H
