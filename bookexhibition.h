#ifndef BOOKEXHIBITION_H
#define BOOKEXHIBITION_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QPixmap>
#include <QVector>

class BookExhibition : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit BookExhibition(QWidget *parent = 0);
    QVector<QString> titile;
    QVector<QPixmap> cover;
    QVector<QString> press;
    QVector<QString> description;
signals:

public slots:

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    int cursorLayer;
};

#endif // BOOKEXHIBITION_H
