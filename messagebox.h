
/*
 * 弹窗的类，可以添加图片与文字，但是图片显示功能暂未添加，以后需要的时候再加
*/


#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include "toolbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QStyle>

class MessageBox : public QDialog
{
    Q_OBJECT

public:
    MessageBox(QWidget *parent = 0);
    ToolButton *closeBtn;        //关闭按钮
    ToolButton *confirmBtn;      //确认按钮
    QPixmap* icon;
    QString text;
    ~MessageBox();
    void setText(QString text);         //设置提示文字
    QString getText();
    void setIcon(QPixmap pixmap);        //设置图片
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MESSAGEBOX_H
