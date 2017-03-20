#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QPaintEvent>

class SubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit SubWindow(QWidget *parent = 0);
private:
signals:
public slots:

protected:
//    void paintEvent(QPaintEvent* event);
};

#endif // SUBWINDOW_H
