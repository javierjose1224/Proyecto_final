#include "nivel.h"

nivel::nivel(QList<pelota *> balls_,QList<muro *> floors_)
{
    balls=balls_;
    floors=floors_;
}


nivel::~nivel()
{
    balls.clear();
    //delete protag;
    floors.clear();
    qDebug()<<"borre el nivel";
}

void nivel::borrar_elementos(QGraphicsScene *scene)
{
    for(int i=0;i<balls.size();i++)
    {
        scene->removeItem(balls.at(i));
    }

    for(int i=0;i<floors.size();i++)
    {
        scene->removeItem(floors.at(i));
    }
    this->~nivel();
}

QList<pelota *> nivel::getBalls() const
{
    return balls;
}

void nivel::graficar(QGraphicsScene *scene, float v_limit)
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
}

void nivel::actualizar_nivel(QGraphicsScene *scene,float v_limit,float h_limit,personaje *protag,QTimer *timer,vida *conVidas,puntaje *score)
{
    protag->actualizar(v_limit);
    protag->colision_lados_escena(v_limit,h_limit);
    for(int i=0;i<floors.size();i++)
    {
        muro *floo= floors.at(i);
        if(protag->collidesWithItem(floo))
        {
            if(protag->getPX()<floo->getPX())
            {
                //qDebug()<<"colisione en la izquierda";
                protag->set_vel(-1*protag->getE()*protag->getVX(),protag->getVY(),floo->getPX()-protag->getR(),protag->getPY());
                //protag->set_vel(-1*protag->getE()*protag->getVX(),protag->getVY(),protag->getPX(),protag->getPY());
            }
            if(protag->getPX()>floo->getPX()+floo->getAncho())
            {
                //qDebug()<<"colisione en la derecha";
                protag->set_vel(-1*protag->getE()*protag->getVX(),protag->getVY(),floo->getPX()+floo->getAncho()+protag->getR(),protag->getPY());
            }
            if(protag->getPY()>floo->getPY())
            {
                 //qDebug()<<"colisione arriba"
                 protag->set_vel(protag->getVX(),-1*protag->getE()*protag->getVY(),protag->getPX(),floo->getPY()+protag->getR());
            }
            if(protag->getPY()<floo->getPY()-floo->getAlto())
            {
                //qDebug()<<"colisione abajo";
                protag->set_vel(protag->getVX(),-1*protag->getE()*protag->getVY(),protag->getPX(),floo->getPY()-floo->getAlto()-protag->getR());
            }
        }
    }

    for(int i=0;i<protag->getBalas_jugador().size();i++)
    {
        protag->getBalas_jugador().at(i)->actualizar(v_limit);
        if(protag->getBalas_jugador().at(i)->getPY()>v_limit)
        {
            protag->getBalas_jugador().removeAt(i);
        }
    }

    for(int i=0;i<balls.size();i++)
    {
        if(protag->collidesWithItem(balls.at(i)))
        {
            qDebug()<<"COLISIONE PEZ";
            if(conVidas->getvidaT()>0)
            {
                conVidas->decrease();
                qDebug()<<"Me golpeo";
                protag->setPos(0,0);
                protag->setPX(0);
                protag->setPY(0);
            }
//            else
//            {
//                scene->removeItem(protag);
//                timer->stop();
//                this->~nivel();
//            }
        }
    }

    for(int i=0;i<protag->getBalas_jugador().size();i++)
    {
        for(int j=0;j<balls.size();j++)
        {
            if(protag->getBalas_jugador().at(i)->collidesWithItem(balls.at(j)))
            {

                qDebug()<<"colisione";
                score->increase();
                float posx=balls.at(j)->getPX();
                float posy=balls.at(j)->getPY();
                float rad=balls.at(j)->getR()/2;
                float posx_b=protag->getBalas_jugador().at(i)->getPX();

                //scene->removeItem(protag->getBalas_jugador().at(i));
                //protag->eliminar_disparo(i);
                //protag->getBalas_jugador().removeAt(i);

                scene->removeItem(balls.at(j));
                balls.removeAt(j);

                if(posx>posx_b)
                {
                    balls.push_back(new pelota(posx,posy,10,20,50,rad,0,1,2));
                    scene->addItem(balls.back());

                    balls.push_back(new pelota(posx_b-2*rad,posy,-10,20,50,rad,0,1,2));
                    scene->addItem(balls.back());
                }
            }
        }
    }

    for(int i=0;i<balls.size();i++)
    {
        for(int j=0;j<floors.size();j++)
        {
            muro *floo= floors.at(j);
            if(balls.at(i)->collidesWithItem(floo))
            {
                if(balls.at(i)->getPX()<floo->getPX())
                {
                    //qDebug()<<"colisione en la izquierda";
                    balls.at(i)->set_vel(-1*balls.at(i)->getE()*balls.at(i)->getVX(),balls.at(i)->getVY(),floo->getPX()-balls.at(i)->getR(),balls.at(i)->getPY());
                    //balls.at(i)->set_vel(-1*balls.at(i)->getE()*protag->getVX(),protag->getVY(),protag->getPX(),protag->getPY());
                }
                if(balls.at(i)->getPX()>floo->getPX()+floo->getAncho())
                {
                    //qDebug()<<"colisione en la derecha";
                    balls.at(i)->set_vel(-1*balls.at(i)->getE()*balls.at(i)->getVX(),balls.at(i)->getVY(),floo->getPX()+floo->getAncho()+balls.at(i)->getR(),balls.at(i)->getPY());
                }
                if(balls.at(i)->getPY()>floo->getPY())
                {
                     //qDebug()<<"colisione arriba"
                     balls.at(i)->set_vel(balls.at(i)->getVX(),-1*balls.at(i)->getE()*balls.at(i)->getVY(),balls.at(i)->getPX(),floo->getPY()+balls.at(i)->getR());
                }
                if(balls.at(i)->getPY()<floo->getPY()-floo->getAlto())
                {
                    //qDebug()<<"colisione abajo";
                    balls.at(i)->set_vel(balls.at(i)->getVX(),-1*balls.at(i)->getE()*balls.at(i)->getVY(),balls.at(i)->getPX(),floo->getPY()-floo->getAlto()-balls.at(i)->getR());
                }
            }
        }
    }


    for(int i=0;i<balls.size();i++)
    {
        balls.at(i)->actualizar(v_limit);
        balls.at(i)->collision_lados_escena(v_limit,h_limit);
        //borderColilision(balls.at(i));
        //this->getBalls().at(i)->collision_ball(balas_player,scene);
    }

}

nivel::nivel(QObject *parent)
{

}


QList<muro *> nivel::getFloors() const
{
    return floors;
}

