#ifndef BOOKOVERVIEWWINDOW_H
#define BOOKOVERVIEWWINDOW_H

#include <QMdiSubWindow>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPainter>
#include <QList>
#include <QPropertyAnimation>
#include <QMouseEvent>

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
    ~BookOverviewWindow();
    QStringList covers[8];
    QStringList titles[8];
//    Label* coversOnDisplay[6];
//    Label* titlesOnDisplay[6];
    Label* coversOnDisplay[7];
    Label* titlesOnDisplay[7];

    std::vector<Book*> bookList;
    std::vector<Label*> mostBorsCovers;
    std::vector<Label*> mostBorsTitles;
    std::vector<Label*> mostRefCovers;
    std::vector<Label*> mostRefsTitles;
    QTableWidget* buttons;
    QVector<QRect> r_Cover;
    QVector<QRect> r_Title;
    ToolButton* categories[8];
    ToolButton* toLeft;
    ToolButton* toRight;
//    QPropertyAnimation moveAction_Cover[6];
//    QPropertyAnimation opacityAction_Cover[2];
//    QPropertyAnimation moveAction_Title[6];
//    QPropertyAnimation opacityAction_Title[2];
    QPropertyAnimation moveAction_Cover[7];
    QPropertyAnimation opacityAction_Cover[2];
    QPropertyAnimation moveAction_Title[7];
    QPropertyAnimation opacityAction_Title[2];
    QTimer* timerL;      //交换用定时器
    QTimer* timerR;
    QTimer * actionTimer;
protected:
    int cursorLayer;
    int firstIndexInBookList;  //当前最左的图标签指向的书目下标
    int firstIndexOnDisplay;  //第一个coversOndisplay的编号;
    int categoryOnDisplay;
    void paintEvent(QPaintEvent *paintEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
signals:
    void actionTimeout();
public slots:
    void startTimerL();
    void startTimerR();
    void moveLeft();
    void moveRight();
    void graduallyDisappearL();
    void graduallyDisappearR();
    void changeOrderL();
    void changeOrderR();
    void changeCategory();
    void noAction();
};

#endif // BOOKOVERVIEWWINDOW_H
