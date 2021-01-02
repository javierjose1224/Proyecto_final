#include "plataforma.h"

float plataforma::getPosX() const
{
    return posX;
}

void plataforma::setPosX(float value)
{
    posX = value;
}

float plataforma::getPosY() const
{
    return posY;
}

void plataforma::setPosY(float value)
{
    posY = value;
}

plataforma::plataforma(float posx_, float posy_, float ancho_, float alto_)
{
    posX=-posx_;//con -
    posY=posy_;
    ancho=ancho_;
    alto=alto_;
}

void plataforma::posicionAbs(float v_limit)
{
    setPos(-posX,v_limit-posY);//con -
}

QRectF plataforma::boundingRect() const
{
    return QRectF(-posX,-posY,ancho,alto);
}

void plataforma::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::magenta);
    painter->drawRect(boundingRect());
}
