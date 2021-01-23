#include "pua.h"

pua::pua(float posx, float posy, float ancho, float alto)
{
    PX=posx;
    PY=posy;
    Ancho=ancho;
    Alto=alto;
    R=1;
}

QRectF pua::boundingRect() const
{
    return QRectF(-1*R,-1*R,Ancho,Alto);
}

void pua::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::gray);
    painter->drawRect(boundingRect());
}

void pua::posicionar(float v_limit)
{
    setPos(PX,v_limit-PY);
}
