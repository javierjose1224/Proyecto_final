#include "senoidal.h"

void senoidal::setU(float value)
{
    u = value;
}

float senoidal::getPX() const
{
    return PX;
}

float senoidal::getR() const
{
    return R;
}

int senoidal::getIdt() const
{
    return idt;
}

senoidal::senoidal(float posx, float posy,float w_,int idt_)
{
    R=20;
    W=w_;
    PX=posx;
    PY=posy;
    dt=0.01;
    u=1;
    idt=idt_;
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
//    painter->setBrush(Qt::magenta);
//    painter->drawEllipse(boundingRect());
    if(idt==1)
    {
        QPixmap pixmap;
        pixmap.load(":/Imagenes/potenciador.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }
    else
    {
        QPixmap pixmap;
        pixmap.load(":/Imagenes/vida++.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }


}

