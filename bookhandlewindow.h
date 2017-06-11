#ifndef BOOKHANDLEWINDOW_H
#define BOOKHANDLEWINDOW_H

#include <QMdiSubWindow>
#include <QComboBox>
#include "messagebox.h"
#include "toolbutton.h"

extern qreal dpi;

enum HandlePattern
{
    Return,
    Loss,
    Renew
};

class BookHandleWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    BookHandleWindow(QWidget *parent = 0);
    ~BookHandleWindow();
    QComboBox* getPattern;
    int order;
    HandlePattern pattern;
    MessageBox* popUp;
    ToolButton* closeBtn;
    ToolButton* confirmBtn;
protected:
    void paintEvent(QPaintEvent *paintEvent);
signals:
    void returnPatternConfirmed();
    void renewPatternConfirmed();
    void lossPatternConfirmed();
public slots:
    void emitPattern();
};

#endif // BOOKHANDLEWINDOW_H
