#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QWidget>
#include <QToolButton>
#include <QColor>
#include <QString>

class ToolButton : public QToolButton
{
public:
    ToolButton(QWidget* parent,QColor p_color,QColor e_color);
    ToolButton(QWidget *parent);
    ~ToolButton();
    setPlainColor(QColor color);           //修改鼠标未进入时按钮颜色
    setEnterColor(QColor color);           //修改鼠标进入时按钮颜色
    QString toARGBString(QColor color);     //将颜色转换为RGBA值
protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
private:
    QColor plainColor;                 //鼠标未进入时按钮颜色
    QColor enterColor;                 //鼠标进入时按钮颜色
};


#endif // TOOLBUTTON_H
