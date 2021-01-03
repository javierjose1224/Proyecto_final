#include "proyectil.h"
#include "pelota.h"

float proyectil::getPosX() const
{
    return posX;
}

proyectil::proyectil(float v_limit)
{
    setRect(0,0,10,v_limit);
    QTimer * timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(movimiento()));
    timer->start(20);//20
}

void proyectil::movimiento()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0; i < colliding_items.size();++i){
        if(typeid (*(colliding_items[i]))== typeid (pelota))
        {
            //incrementa el puntaje
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete colliding_items[i];
            colliding_items.removeAt(i);
            delete this;
        }
    }

    setPos(x(),y()-10);
    if(pos().y()+rect().height()<0)
    {
        scene()->removeItem(this);
        delete this;
        qDebug()<<"bala eliminada";
    }
}
