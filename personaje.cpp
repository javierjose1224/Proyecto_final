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

void personaje::eliminar_disparo(int i)
{
    //qDebug()<<"bala a eliminar"<<i;
    //balas_jugador.clear();
    balas_jugador.removeAt(i);
    //delete balas_jugador.at(i);
//sd
}

void personaje::disparo_lis(QGraphicsScene *scene,float v_limit)
{
    balas_jugador.push_back(new disparo(PX+R,PY,0,20));
    balas_jugador.back()->actualizar(v_limit);
    scene->addItem(balas_jugador.back());
}

QList<disparo *> personaje::getBalas_jugador() const
{
    return balas_jugador;
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
    painter->drawRect(boundingRect());
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

void personaje::colision_lados_escena(float v_limit,float h_limit)//v_limit,h_limit
{
    if(this->getPX()<this->getR())//IZQUIERDA
    {
        this->set_vel(-1*this->getE()*this->getVX(),this->getVY(),this->getR(),this->getPY());
    }
    if(this->getPX()>h_limit-this->getR())//DERECHA
    {
        this->set_vel(-1*this->getE()*this->getVX(),this->getVY(),h_limit-this->getR(),this->getPY());
    }
    if(this->getPY()<this->getR())//ABAJO
    {
        this->set_vel(this->getVX(),-1*this->getE()*this->getVY(),this->getPX(),this->getR());
    }
    if(this->getPY()>v_limit-this->getR())//ARRIBA
    {
        this->set_vel(this->getVX(),-1*this->getE()*this->getVY(),this->getPX(),v_limit-this->getR());
    }
}

bool personaje::saltar()
{
    if(this->getPY()<this->getR())//ABAJO
    {
        return true;
        //this->set_vel(this->getVX(),-1*this->getE()*this->getVY(),this->getPX(),this->getR());
    }
    else
        return false;
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

void personaje::set_Newvel(float vx, float vy)
{
    VX=vx;
    VY=vy;
}

float personaje::getPX() const
{
    return PX;
}
