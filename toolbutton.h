#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QWidget>
#include <QToolButton>
#include <QPalette>

class ToolButton : public QToolButton
{
public:
    ToolButton(QWidget* parent);
    ~ToolButton();
protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
};


#endif // TOOLBUTTON_H
