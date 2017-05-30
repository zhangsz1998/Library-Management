#ifndef RESVFORM_H
#define RESVFORM_H

#include <QDialog>
#include "toolbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QStyle>
#include <QmouseEvent>
#include <QSpinBox>
#include <QApplication>
#include "book_mgmt.h"
#include "reader_mgmt.h"
#include "messagebox.h"

class ResvForm : public QDialog{
    Q_OBJECT
public:
    ResvForm(QWidget *parent=0);
    ToolButton *cancelBtn;
    MessageBox *popUp;
    ToolButton *comfirmBtn;
    ToolButton *closeBtn;
    void setBook(Book *);
    void setReader(Reader *);
    void setIcon(QPixmap pixmap);
    Book * item;
    Reader * borrower;
    QPixmap *icon;
    QPoint offset;
    ~ResvForm();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
protected slots:
    void comfirm();
};

#endif // RESVFORM_H
