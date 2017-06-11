#ifndef AUTHORITYCHECKWINDOW_H
#define AUTHORITYCHECKWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include "toolbutton.h"
#include "messagebox.h"
extern qreal dpi;

class AuthorityCheckWindow : public QDialog
{
    Q_OBJECT
public:
    AuthorityCheckWindow(QWidget* parent);
    ~AuthorityCheckWindow();
protected:
    QLineEdit* getPassWord;
    ToolButton* confirmBtn;
    ToolButton* closeBtn;

private:
    void paintEvent(QPaintEvent* event);
protected slots:
    void isAdmin();        //判断是否是管理员
signals:
    void isAuthorized();
    void notAuthorized();
};

#endif // AUTHORITYCHECKWINDOW_H
