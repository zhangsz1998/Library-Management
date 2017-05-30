#ifndef BOOKEXHIBITION_H
#define BOOKEXHIBITION_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QPixmap>
#include <QVector>
#include <vector>
#include "book_mgmt.h"
#include "toolbutton.h"

class BookExhibition : public QMdiSubWindow
{
    Q_OBJECT
public:
    BookExhibition(QWidget *parent = 0);
    ~BookExhibition();
    QVector<QString> titile;
    QVector<QPixmap> cover;
    QVector<QString> press;
    QVector<QString> description;
    std::vector<Book*> books;
    QVector<QVector<QString>> despList;
    ToolButton* nextPage;
    ToolButton* prePage;
    int maxPages;
    int currentPage;
    void refreshDesp();        //用于预处理图书的简介列表
    Book* bookOnDisplay();       //用于获取当前放大展示的图书指针
signals:
    void bookInfoClicked();
public slots:
    void toNextPage();
    void toPrePage();
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
private:
    int cursorLayer;
};

#endif // BOOKEXHIBITION_H
