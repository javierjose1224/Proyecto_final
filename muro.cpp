#include "muro.h"

float muro::getPX() const
{
    return PX;
}

float muro::getPY() const
{
    return PY;
}

float muro::getAncho() const
{
    return Ancho;
}

float muro::getAlto() const
{
    return Alto;
}

muro::muro(float posx, float posy,float ancho, float alto)
{
    PX=posx;
    PY=posy;
    Ancho=ancho;
    Alto=alto;
    R=1;
    //setPixmap(QPixmap(":/imagen/ladrillos.jpg"));
//    pixmap = new QPixmap();
}

QRectF muro::boundingRect() const
{
    return QRectF(-1*R,-1*R,Ancho,Alto);
}

void muro::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->drawPixmap(-Ancho/2, -Alto/2,*pixmap,columnas,filas,ancho,alto);
//    setScale(0.1);

//    painter->setBrush(Qt::red);
//    painter->drawRect(boundingRect());

    QPixmap pixmap;
    pixmap.load(":/Imagenes/piedras .png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

void muro::posicionar(float v_limit)
{
    setPos(PX,v_limit-PY);
}


