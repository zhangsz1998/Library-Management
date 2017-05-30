#include "label.h"

Label::Label(QWidget *parent) : QLabel(parent)
{
    opacity=1.0;
    opacityeffect=new QGraphicsOpacityEffect();
    opacityeffect->setOpacity(opacity);
    this->setGraphicsEffect(opacityeffect);
}

double Label::getOpacity() const
{
    return opacity;
}

void Label::setOpacity(double o)
{
    opacity=o;
    opacityeffect->setOpacity(o);
}
