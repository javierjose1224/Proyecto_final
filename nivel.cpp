#include "nivel.h"

nivel::nivel(QList<pelota *> balls_,QList<muro *> floors_,QList<senoidal*>globos_,QGraphicsScene *scene, float v_limit)
{
    balls=balls_;
    floors=floors_;
    globos=globos_;
    this->graficar(scene,v_limit);
}


nivel::~nivel()
{
    balls.clear();
    floors.clear();    
    globos.clear();
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

    for(int i=0;i<balls.size();i++)
    {
        scene->removeItem(balls.at(i));
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

    for(int i=0;i<globos.size();i++)
    {
        globos.at(i)->actualizar(v_limit);
        scene->addItem(globos.at(i));
    }
}

void nivel::actualizar_nivel(QGraphicsScene *scene,float v_limit,float h_limit,personaje *protag,QTimer *timer,vida *conVidas,puntaje *score,tiempo_juego *cont_abs)
{
    if(cont_abs->getCon_abs()==10)
    {
        globos.push_back(new senoidal(0,v_limit-200,1));
        scene->addItem(globos.back());
        cont_abs->reset();
        //qDebug()<<"ya llego el lechero";
    }

    protag->actualizar(v_limit);
    protag->colision_lados_escena(v_limit,h_limit);
    //COLISION DE LOS MUROS/PLATAFORMAS CON EL PERONAJE
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
    //+++++++++++++++++++

    //COLISION DEL PERSONAJE CON LAS PELOTAS
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
    //+++++++++++++++++++

    //COLISION DE LAS BALAS CON LAS PELOTAS
    bool ban=false;
    int nv;
    for(int i=0;i<protag->getBalas_jugador().size();i++)
    {
        for(int j=0;j<balls.size();j++)
        {
            if(protag->getBalas_jugador().at(i)->collidesWithItem(balls.at(j)))
            {
                scene->removeItem(protag->getBalas_jugador().at(i));
                protag->eliminar_disparo(i);
                score->increase();
                ban=true;
                nv=j;
                break;
            }
        }
    }

    if(ban==true)
    {
        float posx=balls.at(nv)->getPX();
        float posy=balls.at(nv)->getPY();
        float rad=balls.at(nv)->getR()/2;

        if(rad>=10)
        {
            scene->removeItem(balls.at(nv));
            balls.removeAt(nv);
            balls.push_back(new pelota(posx,posy,10,15,50,rad,0,1,2));
            scene->addItem(balls.back());

            balls.push_back(new pelota(posx,posy,-10,15,50,rad,0,1,2));
            scene->addItem(balls.back());
        }
        else
        {
            //score->increase();
            scene->removeItem(balls.at(nv));
            balls.removeAt(nv);
        }
    }
    //+++++++++++++++++++

    //COLISION BALAS CON GLOBOS

    for(int i=0;i<protag->getBalas_jugador().size();i++)
    {
        for(int j=0;j<globos.size();j++)
        {
            if(protag->getBalas_jugador().at(i)->collidesWithItem(globos.at(j)))
            {
                scene->removeItem(protag->getBalas_jugador().at(i));
                protag->eliminar_disparo(i);

                protag->setVD(30);

                scene->removeItem(globos.at(j));
                globos.removeAt(j);
//                ban=true;
//                nv=j;
                break;
            }
        }
    }



    //COLISION BALAS CON MUROS
    for(int i=0;i<protag->getBalas_jugador().size();i++)
    {
        for(int j=0;j<floors.size();j++)
        {
            if(protag->getBalas_jugador().at(i)->collidesWithItem(floors.at(j)))
            {
                scene->removeItem(protag->getBalas_jugador().at(i));
                protag->eliminar_disparo(i);
                break;
            }
        }
    }
    //+++++++++++++++++++


    //COLISION DE LOS GLOBOS CON EL MURO/PLATAFORMAS
    for(int i=0;i<balls.size();i++)
    {
        for(int j=0;j<floors.size();j++)
        {
            muro *floo= floors.at(j);
            if(balls.at(i)->collidesWithItem(floo))
            {
                if(balls.at(i)->getPX()<floo->getPX() && balls.at(i)->getPY()<floo->getPY())
                {
                    //qDebug()<<"colisione en la izquierda";
                    balls.at(i)->set_vel(-1*balls.at(i)->getE()*balls.at(i)->getVX(),balls.at(i)->getVY(),floo->getPX()-balls.at(i)->getR(),balls.at(i)->getPY());
                    //balls.at(i)->set_vel(-1*balls.at(i)->getE()*protag->getVX(),protag->getVY(),protag->getPX(),protag->getPY());
                }
                if(balls.at(i)->getPX()>floo->getPX()+floo->getAncho() && balls.at(i)->getPY()<floo->getPY())
                {
                    //qDebug()<<"colisione en la derecha";
                    balls.at(i)->set_vel(-1*balls.at(i)->getE()*balls.at(i)->getVX(),balls.at(i)->getVY(),floo->getPX()+floo->getAncho()+balls.at(i)->getR(),balls.at(i)->getPY());
                }
                if(balls.at(i)->getPY()>floo->getPY())
                {
                     //qDebug()<<"colisione arriba"
                     balls.at(i)->set_vel(balls.at(i)->getVX(),-1*balls.at(i)->getE()*balls.at(i)->getVY(),balls.at(i)->getPX(),floo->getPY()+balls.at(i)->getR());
                }
                if(balls.at(i)->getPY()<floo->getPY()-floo->getAlto() && balls.at(i)->getPX()>floo->getPX())
                {
                    //qDebug()<<"colisione abajo";
                    balls.at(i)->set_vel(balls.at(i)->getVX(),-1*balls.at(i)->getE()*balls.at(i)->getVY(),balls.at(i)->getPX(),floo->getPY()-floo->getAlto()-balls.at(i)->getR());
                }
            }
        }
    }
    //+++++++++++++++++++





    //ACTUALIZACION DE LAS PELOTAS
    for(int i=0;i<balls.size();i++)
    {
        balls.at(i)->actualizar(v_limit);
        balls.at(i)->collision_lados_escena(v_limit,h_limit);
    }
    //+++++++++++++++++++

    //ACTUALIZACION DE LOS GLOBOS
    for(int i=0;i<globos.size();i++)
    {
        globos.at(i)->actualizar(v_limit);
        if(globos.at(i)->getPX()+globos.at(i)->getR()>h_limit)
        {
            scene->removeItem(globos.at(i));
            globos.removeAt(i);
        }
    }
    //+++++++++++++++++++

    //ACTUALIZACION MOVIMIENTO DE LAS BALAS
    for(int i=0;i<protag->getBalas_jugador().size();i++)
    {
        protag->getBalas_jugador().at(i)->actualizar(v_limit);
        if(protag->getBalas_jugador().at(i)->getPY()>=v_limit)
        {
            scene->removeItem(protag->getBalas_jugador().at(i));
            protag->eliminar_disparo(i);
        }
    }
    //+++++++++++++++++++

}

void nivel::agregar_globo(senoidal *a)
{
    globos.push_back(a);
}

nivel::nivel(QObject *parent)
{

}


QList<muro *> nivel::getFloors() const
{
    return floors;
}

void nivel::remove_bullet(personaje *protag,int j)
{
    protag->getBalas_jugador().removeAt(j);
}

