#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QApplication>

#include "toolbutton.h"
#include "messagebox.h"
#include "signupwindow.h"

extern qreal dpi;
class LoginWindow : public QDialog
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    QLineEdit* getUserName;
    QLineEdit* getPassWord;
    ToolButton* loginBtn;
    ToolButton* signUpBtn;
    ToolButton* closeBtn;
    QPoint offset;
    SignUpWindow* signUpWindow;
    MessageBox* popUp;
private:
    bool passWordChecked();     //判断是否登陆成功
signals:
    void logedIn();     //登录成功信号
protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

public slots:
    void checkPassWord();
    void showSignUpWindow();
    void tryToClose();
    void userSignedUp();
};

#endif // LOGINWINDOW_H
