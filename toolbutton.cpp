#include "toolbutton.h"

ToolButton::ToolButton(QWidget *parent,QColor p_color,QColor e_color)
    :QToolButton(parent)
{
    plainColor=p_color;
    enterColor=e_color;
    QString plainARGB=toARGBString(plainColor);
    setStyleSheet(QString("border:none; margin 0px; background-color:rgba(%1);").arg(plainARGB));
}

ToolButton::ToolButton(QWidget *parent)
    :QToolButton(parent)
{
    plainColor=QColor("#00000000");
    enterColor=QColor("#ff0099ff");
    setStyleSheet("border:none; margin 0px; background-color:#00000000");
}

ToolButton::~ToolButton()
{

}

ToolButton::setPlainColor(QColor color)
{
    plainColor=color;
    setStyleSheet(QString("background-color:rgba(%1); border: none;margin: 0px;").arg(toARGBString(plainColor)));
}

ToolButton::setEnterColor(QColor color)
{
    enterColor=color;
}

QString ToolButton::toARGBString(QColor color)
{
    return QString("%1,%2,%3,%4").arg(QString::number(color.red())).arg(QString::number(color.green())).arg(QString::number(color.blue())).arg(QString::number(color.alpha()));
}

void ToolButton::enterEvent(QEvent *event)
{
    this->setStyleSheet(QString("background-color:rgba(%1); border: none;margin: 0px;").arg(toARGBString(enterColor)));
}

void ToolButton::leaveEvent(QEvent *event)
{
    this->setStyleSheet(QString("border:none; margin 0px; background-color:rgba(%1)").arg(toARGBString(plainColor)));
}
