#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>
#include <QPainter>

#include "toolbutton.h"

#include "messagebox.h"
#include "reader_mgmt.h"

class SignUpWindow : public QDialog
{
    Q_OBJECT
public:
    SignUpWindow(QWidget *parent = 0);
protected:
    QLineEdit* getUserName;
    QRadioButton* isStudent;
    QRadioButton* isTeacher;
    QLineEdit* getId;
    QLineEdit* getPassWord;
    ToolButton* closeBtn;
    ToolButton* confirmBtn;
    MessageBox* popUp;
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    void addNewUser();
};

#endif // SIGNUPWINDOW_H
