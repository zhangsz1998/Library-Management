#ifndef BORROWFORM_H
#define BORROWFORM_H

#include <QDialog>
#include "toolbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QStyle>
#include <book_mgmt.h>
#include <reader_mgmt.h>

class BorrowForm : public QDialog{
    Q_OBJECT
public:
    BorrowForm(QWidget *parent=0);
    ToolButton *cancelBtn;
    ToolButton *comfirmBtn;
    void setBook(Book &);
    void setReader(Reader &);
    void setIcon(QPixmap pixmap);
    Book item;
    Reader borrower;
    QPixmap *icon;
    ~BorrowForm();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BORROWFORM_H
