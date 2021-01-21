#include "senoidal.h"

void senoidal::setU(float value)
{
    u = value;
}

float senoidal::getPX() const
{
    return PX;
}

senoidal::senoidal(float posx, float posy,float w_)
{
    R=20;
    W=w_;
    PX=posx;
    PY=posy;
    dt=0.01;
    u=1;
}

void senoidal::actualizar(float v_limit)
{

   K=(2*(3.14))/0.1;
   PY=2*sin((W*dt)-(K*PX))+PY;
   dt=dt+0.01;
   PX=PX+0.5;//*(u);
   setPos(PX,v_limit-PY);

}

QRectF senoidal::boundingRect() const
{
    return QRectF(-1*R,-1*R,2*R,2*R);
}

void senoidal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect());
}

