#ifndef LABEL_H
#define LABEL_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsOpacityEffect>

class Label : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(double opacity READ getOpacity WRITE setOpacity USER true)
public:
    Label(QWidget *parent = 0);
    double getOpacity() const;
    void setOpacity(double o);
private:
    double opacity;
protected:
    QGraphicsOpacityEffect* opacityeffect;
signals:

public slots:
};

#endif // LABEL_H
