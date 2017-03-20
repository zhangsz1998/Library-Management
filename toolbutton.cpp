#include "toolbutton.h"

ToolButton::ToolButton(QWidget *parent)
    :QToolButton(parent)
{
    setStyleSheet("background-color:#5599ff;border:none; margin: 0px;");
}

ToolButton::~ToolButton()
{

}

void ToolButton::enterEvent(QEvent *event)
{
    this->setStyleSheet("background-color:#0099ff;border:none; margin: 0px;");
    //this->update();
}

void ToolButton::leaveEvent(QEvent *event)
{
    this->setStyleSheet("background-color:transparent;border:none; margin: 0px;");
    //this->repaint();
}
