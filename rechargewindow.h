#ifndef RECHARGEWINDOW_H
#define RECHARGEWINDOW_H

#include <QDialog>
#include <QSpinBox>
#include "toolbutton.h"
#include "reader_mgmt.h"
#include <QStyle>
#include <QPainter>

extern Reader* activereader;
extern qreal dpi;
extern bool userMessageChanged;

class RechargeWindow : public QDialog
{
    Q_OBJECT
public:
    RechargeWindow(QWidget *parent = 0);
    ~RechargeWindow();
    QSpinBox* getMoney;
    ToolButton* closeBtn;
    ToolButton* confirmBtn;
    int getValue();
protected:
    void paintEvent(QPaintEvent* event);
signals:
    void chargeRequest();

public slots:
    void emitChargeRequest();
};

#endif // RECHARGEWINDOW_H
