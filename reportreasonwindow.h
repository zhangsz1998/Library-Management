#ifndef REPORTREASONWINDOW_H
#define REPORTREASONWINDOW_H


#include <QDialog>
#include "toolbutton.h"
#include <QStyle>
#include <QCheckBox>
#include <QTextEdit>
#include <QPainter>
#include "messagebox.h"

class ReportReasonWindow : public QDialog
{
    Q_OBJECT
public:
    ReportReasonWindow(QWidget *parent = 0);
    ~ReportReasonWindow();
    ToolButton* closeBtn;
    ToolButton* confirmBtn;

    QCheckBox* reason1;
    QCheckBox* reason2;
    QCheckBox* reason3;
    QCheckBox* reason4;
    QCheckBox* reason5;
    QCheckBox* reason6;
    QCheckBox* reason7;
    QCheckBox* reason8;
    QTextEdit* getOtherReason;

    MessageBox* submitComplete;
    MessageBox* noReasonWarning;
    QStringList reasons;
    QStringList getReasons();
protected:
    void paintEvent(QPaintEvent* event);
signals:
    void success();
public slots:
    void showMessageBox();
    void refreshReasons();
    void modified();
};


#endif // REPORTREASONWINDOW_H
