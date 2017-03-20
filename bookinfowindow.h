#ifndef BOOKINFOWINDOW_H
#define BOOKINFOWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QEvent>
#include <QLabel>

class BookInfoWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit BookInfoWindow(QWidget *parent = 0);
    QLabel* bookInfo;
signals:

public slots:

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
};

#endif // BOOKINFOWINDOW_H
