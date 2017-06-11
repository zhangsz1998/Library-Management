#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QPainter>

extern qreal dpi;
class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    MessageWidget(QWidget *parent = 0);
    ~MessageWidget();
    void loadMessage(QString m_msg[],int num);
protected:
    QString* msg[30];
    int msg_num;
    void paintEvent(QPaintEvent *event);
signals:

public slots:
};

#endif // MESSAGEWIDGET_H
