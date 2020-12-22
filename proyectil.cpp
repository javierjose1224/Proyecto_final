#include "proyectil.h"

proyectil::proyectil()
{
    setRect(0,0,10,500);
    //connect
    QTimer * timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(movimiento()));
    timer->start(40);//20
}

void proyectil::movimiento()
{
    setPos(x(),y()-10);

//    if(pos().y()+rect().height() <0)
//    {
//        scene()->removeItem(this);
//        delete this;
//        //qDebug()<<"bala eliminada";
//    }
}
