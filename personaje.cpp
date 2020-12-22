#include "personaje.h"
#include <math.h>
#include <cmath>

void personaje::setPX(float value)
{
    PX = value;
}

void personaje::setPY(float value)
{
    PY = value;
}

personaje::personaje(float posX_, float posY_, float velX_, float velY_, float masa, float radio, float k_, float e_,float G_)
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

personaje::~personaje()
{

}

QRectF personaje::boundingRect() const
{
    return QRectF(-1*escala*R,-1*escala*R,2*escala*R,2*escala*R);
}

void personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkRed);
    painter->drawEllipse(boundingRect());
}

void personaje::setEscala(float s)
{
    escala=s;
}

void personaje::actualizar(float v_limit)
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

float personaje::getPY() const
{
    return PY;
}

float personaje::getMass() const
{
    return mass;
}

float personaje::getR() const
{
    return R;
}

float personaje::getVX() const
{
    return VX;
}

float personaje::getVY() const
{
    return VY;
}

float personaje::getE() const
{
    return e;
}

void personaje::set_vel(float vx, float vy, float px, float py)
{
    VX=vx;
    VY=vy;
    PX=px;
    PY=py;
}

float personaje::getPX() const
{
    return PX;
}
