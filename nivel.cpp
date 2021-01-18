#include "nivel.h"

nivel::nivel(QList<pelota *> balls_, personaje *protag_, QList<muro *> floors_)
{
    balls=balls_;
    protag=protag_;
    floors=floors_;
}


nivel::~nivel()
{
    balls.clear();
    //delete protag;
    floors.clear();
}

QList<pelota *> nivel::getBalls() const
{
    return balls;
}

void nivel::graficar(QGraphicsScene *scene, float v_limit,float h_limit)
{
    for(int i=0;i<floors.size();i++)
    {
        floors.at(i)->posicionar(v_limit);
        scene->addItem(floors.at(i));
    }

    for(int i=0;i<balls.size();i++)
    {
        balls.at(i)->actualizar(v_limit);
        scene->addItem(balls.at(i));
    }
    this->getProtag()->actualizar(v_limit);
    scene->addItem(protag);


    timer_emp=new QTimer();
    //connect(timer_emp,&QTimer::timeout,this,SLOT(actualizar_nivel(scene,v_limit,h_limit)));
    timer_emp->start(5);

//    timer_emp->start(5);
//    connect(timer_emp,SIGNAL(timeout()),this,SLOT(actualizar_nivel()));
}

void nivel::actualizar_nivel(QGraphicsScene *scene,float v_limit,float h_limit)
{
    protag->actualizar(v_limit);
    protag->colision_lados_escena(v_limit,h_limit);
    for(int i=0;i<floors.size();i++)
    {
        muro *floo= floors.at(i);
        if(protag->collidesWithItem(floo))
        {
            if(protag->getPX()<floo->getPX() && protag->getPY()<floo->getPY())
            {
                //qDebug()<<"colisione en la derecha";
                protag->set_vel(-1*protag->getE()*protag->getVX(),protag->getVY(),protag->getPX(),protag->getPY());
            }
            if(protag->getPX()>floo->getPX()+floo->getAncho())
            {
                //qDebug()<<"colisione en la izq";
                protag->set_vel(-1*protag->getE()*protag->getVX(),protag->getVY(),floo->getPX()+floo->getAncho()+protag->getR(),protag->getPY());
            }
            if(protag->getPY()>floo->getPY() && protag->getPX()+protag->getR()>floo->getPX())
            {
                 qDebug()<<"colisione arriba"<< int(protag->getPY()-protag->getR());
                 protag->set_vel(protag->getVX(),-1*protag->getE()*protag->getVY(),protag->getPX(),floo->getPY()+protag->getR());
            }
            if(protag->getPY()<floo->getPY()-floo->getAlto() && protag->getPX()+protag->getPX()>floo->getPX())
            {
                //qDebug()<<"colisione abajo";
                protag->set_vel(protag->getVX(),-1*protag->getE()*protag->getVY(),protag->getPX(),floo->getPY()-floo->getAlto()-protag->getR());
            }
        }

    }
    for(int i=0;i<balls.size();i++)
    {
        if(protag->collidesWithItem(balls.at(i)))
        {
            if(salud->getvidaT()>0)
            {
                salud->decrease();
                qDebug()<<"Me golpeo";
                this->getProtag()->setPos(0,0);
                this->getProtag()->setPX(0);
                this->getProtag()->setPY(0);
            }
            else
            {
                scene->removeItem(this->getProtag());
                timer_emp->stop();
                this->~nivel();
            }
        }
    }

//    for(int i=0;i<bala_jugador.size();i++)
//    {
//        for(int j=0;j<this->getBalls().size();j++)
//        {
//            if(bala_jugador.at(i)->collidesWithItem(this->getBalls().at(j)))
//            {
//                qDebug()<<"colisione";
//                scene->removeItem(this->getBalls().at(i));
//                this->getBalls().removeAt(j);
//                //delete this->getBalls().at(i);
//            }
//        }
//    }

    for(int i=0;i<balls.size();i++)
    {
        balls.at(i)->actualizar(v_limit);
        balls.at(i)->collision_lados_escena(v_limit,h_limit);
        //borderColilision(balls.at(i));
        //this->getBalls().at(i)->collision_ball(balas_player,scene);
    }

    for(int i=0;i<protag->getBalas_jugador().size();i++)
    {
        protag->getBalas_jugador().at(i)->actualizar(v_limit);
    }
}

nivel::nivel(QObject *parent)
{

}

personaje *nivel::getProtag() const
{
    return protag;
}

QList<muro *> nivel::getFloors() const
{
    return floors;
}

