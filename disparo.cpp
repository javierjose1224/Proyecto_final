#include "disparo.h"

float disparo::getPX() const
{
    return PX;
}

float disparo::getR() const
{
    return R;
}

float disparo::getPY() const
{
    return PY;
}

void disparo::setVX(float value)
{
    VX = value;
}

disparo::disparo(float posX_, float posY_, float velY_)
{
    PX=posX_;
    PY=posY_;
    mass=10;
    R=2.5;
    VX=0;
    VY=velY_;
    AX=0;
    AY=0;
    G=0;//2
    K=0;
    e=0;
    V = 0;
    dt = 0.1;
    escala=1;
}

disparo::~disparo()
{
    qDebug()<<"hlola";
    //delete this;
}

QRectF disparo::boundingRect() const
{
    return QRectF(-1*escala*R,-1*escala*R,2*escala*R,500);
}

void disparo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setBrush(Qt::darkGray);
//    painter->drawRect(boundingRect());

    QPixmap pixmap;
    pixmap.load(":/Imagenes/gancho.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

void disparo::actualizar(float v_limit)
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



