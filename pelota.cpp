#include "pelota.h"
#include <math.h>
#include <cmath>

pelota::pelota(float posX_, float posY_, float velX_, float velY_, float masa, float radio, float k_, float e_,float G_)
{
     PX=posX_;
     PY=posY_;
     mass=masa;
     R=radio;
     VX=velX_;
     VY=velY_;
     AX=0;
     AY=0;
     G=G_;//2
     K=k_;
     e=e_;
     V = 0;
     dt = 0.1;
     escala=1;
}

pelota::~pelota()
{

}

QRectF pelota::boundingRect() const
{
    return QRectF(-1*escala*R,-1*escala*R,2*escala*R,2*escala*R);
}

void pelota::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect());
}

void pelota::setEscala(float s)
{
    escala=s;
}

void pelota::actualizar(float v_limit)
{
    V = pow(((VX*VX)+(VY*VY)),(1/2));
    angulo=atan2(VY,VX);
    AX=-((K*(V*V)*(R*R))/mass)*cos(angulo);
    AY=(-((K*(V*V)*(R*R))/mass)*sin(angulo))-G;
    PX= PX+((VX*(dt)))+(((AX*(dt*dt)))/2);
    PY= PY+((VY*(dt)))+(((AY*(dt*dt)))/2);
    VX=VX+AX*dt;
    VY=VY+AY*dt;
    setPos(PX,v_limit-PY);
}

float pelota::getPY() const
{
    return PY;
}

float pelota::getMass() const
{
    return mass;
}

float pelota::getR() const
{
    return R;
}

float pelota::getVX() const
{
    return VX;
}

float pelota::getVY() const
{
    return VY;
}

float pelota::getE() const
{
    return e;
}

void pelota::set_vel(float vx, float vy, float px, float py)
{
    VX=vx;
    VY=vy;
    PX=px;
    PY=py;
}

float pelota::getPX() const
{
    return PX;
}
