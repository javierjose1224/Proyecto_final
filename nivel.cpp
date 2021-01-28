#include "nivel.h"

nivel::nivel(QList<pelota *> balls_,QList<muro *> floors_,QList<senoidal*>globos_,QList<pua*>puas_,QGraphicsScene *scene, float v_limit)
{
    balls=balls_;
    floors=floors_;
    globos=globos_;
    puas=puas_;
    this->graficar(scene,v_limit);
}


nivel::~nivel()
{
    balls.clear();
    floors.clear();    
    globos.clear();
    puas.clear();
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

    for(int i=0;i<globos.size();i++)
    {
        scene->removeItem(globos.at(i));
    }

    for(int i=0;i<puas.size();i++)
    {
        scene->removeItem(puas.at(i));
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

    for(int i=0;i<puas.size();i++)
    {
        puas.at(i)->posicionar(v_limit);
        scene->addItem(puas.at(i));
    }
}

void nivel::actualizar_nivel(QGraphicsScene *scene,float v_limit,float h_limit,QList<personaje*>players,vida *conVidas,puntaje *score,tiempo_juego *cont_abs,tiempo_juego *cont_abs2)
{
    //ACTUALIZACION DE TIMER GENERADOR DE GLOBOS
    if(cont_abs->getCon_abs()==10)
    {
        globos.push_back(new senoidal(0,v_limit-200,1,1));
        scene->addItem(globos.back());
        cont_abs->reset();
    }
    if(cont_abs2->getCon_abs()==20)
    {
        scene->removeItem(globos.back());
        globos.clear();
        globos.push_back(new senoidal(0,v_limit-200,1,2));
        scene->addItem(globos.back());
        cont_abs2->reset();
    }
    //+++++++++++++
//    personaje *protag=players.at(0);
//    protag->actualizar(v_limit);
//    protag->colision_lados_escena(v_limit,h_limit);

    for(int i=0;i<players.size();i++)
    {
        players.at(i)->actualizar(v_limit);
        players.at(i)->colision_lados_escena(v_limit,h_limit);
    }


    //COLISION DE LOS MUROS/PLATAFORMAS CON LOS PERONAJES
    for(int j=0;j<players.size();j++)
    {
        for(int i=0;i<floors.size();i++)
        {
            muro *floo= floors.at(i);
            if(players.at(j)->collidesWithItem(floo))
            {
                if(players.at(j)->getPX()<floo->getPX())
                {
                    //qDebug()<<"colisione en la izquierda";
                    players.at(j)->set_vel(-1*players.at(j)->getE()*players.at(j)->getVX(),players.at(j)->getVY(),floo->getPX()-players.at(j)->getR(),players.at(j)->getPY());
                    //players.at(j)->set_vel(-1*players.at(j)->getE()*players.at(j)->getVX(),players.at(j)->getVY(),players.at(j)->getPX(),players.at(j)->getPY());
                }
                if(players.at(j)->getPX()>floo->getPX()+floo->getAncho())
                {
                    //qDebug()<<"colisione en la derecha";
                    players.at(j)->set_vel(-1*players.at(j)->getE()*players.at(j)->getVX(),players.at(j)->getVY(),floo->getPX()+floo->getAncho()+players.at(j)->getR(),players.at(j)->getPY());
                }
                if(players.at(j)->getPY()>floo->getPY())
                {
                     //qDebug()<<"colisione arriba"
                     players.at(j)->set_vel(players.at(j)->getVX(),-1*players.at(j)->getE()*players.at(j)->getVY(),players.at(j)->getPX(),floo->getPY()+players.at(j)->getR());
                }
                if(players.at(j)->getPY()<floo->getPY()-floo->getAlto())
                {
                    //qDebug()<<"colisione abajo";
                    players.at(j)->set_vel(players.at(j)->getVX(),-1*players.at(j)->getE()*players.at(j)->getVY(),players.at(j)->getPX(),floo->getPY()-floo->getAlto()-players.at(j)->getR());
                }
            }
        }
    }
//    //+++++++++++++++++++


    //COLISION PERSONAJE CON LAS PUAS
    for(int j=0;j<players.size();j++)
    {
        for(int i=0;i<puas.size();i++)
        {
            if(players.at(j)->collidesWithItem(puas.at(i)))
            {
                if(players.at(j)->getGolpe()==true)
                {
                    conVidas->decrease();
                    players.at(j)->setPos(0,0);
                    players.at(j)->setPX(0);
                    players.at(j)->setPY(0);
                    players.at(j)->setGolpe(false);
                }
            }
        }
    }
//    //+++++++++++++++++++


    //COLISION DEL PERSONAJE CON LAS PELOTAS
    for(int j=0;j<players.size();j++)
    {
        for(int i=0;i<balls.size();i++)
        {
            if(players.at(j)->collidesWithItem(balls.at(i)))
            {
                if(players.at(j)->getGolpe()==true)
                {
                    conVidas->decrease();
                    players.at(j)->setPos(0,0);
                    players.at(j)->setPX(0);
                    players.at(j)->setPY(0);
                    players.at(j)->setGolpe(false);
                }
            }
        }
     }
//    //+++++++++++++++++++


    //COLISION DE LAS BALAS CON LAS PELOTAS
    bool ban=false;
    int nv;

        for(int j=0;j<balls.size();j++)
        {
           for(int k=0;k<players.size();k++)
           {
                for(int i=0;i<players.at(k)->getBalas_jugador().size();i++)
                {
                    if(players.at(k)->getBalas_jugador().at(i)->collidesWithItem(balls.at(j)))
                    {
                        scene->removeItem(players.at(k)->getBalas_jugador().at(i));
                        players.at(k)->eliminar_disparo(i);
                        score->increase();
                        ban=true;
                        nv=j;
                        break;
                    }
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
                scene->removeItem(balls.at(nv));
                balls.removeAt(nv);
            }
        }


    //+++++++++++++++++++

    //COLISION BALAS CON GLOBOS
    for(int k=0;k<players.size();k++)
        for(int i=0;i<players.at(k)->getBalas_jugador().size();i++)
        {
            for(int j=0;j<globos.size();j++)
            {
                if(players.at(k)->getBalas_jugador().at(i)->collidesWithItem(globos.at(j)))
                {

                    scene->removeItem(players.at(k)->getBalas_jugador().at(i));
                    players.at(k)->eliminar_disparo(i);
                    if(globos.at(j)->getIdt()==1)
                    {
                        players.at(k)->setVD(30);
                    }
                    else if(globos.at(j)->getIdt()==2)
                    {
                        conVidas->increase();
                    }
                    scene->removeItem(globos.at(j));
                    globos.removeAt(j);
                    break;
                }
            }
        }

    //+++++++++++++++++++


//   COLISION BALAS CON MUROS
    for(int k=0;k<players.size();k++)
    {
        for(int i=0;i<players.at(k)->getBalas_jugador().size();i++)
        {
            for(int j=0;j<floors.size();j++)
            {
                if(players.at(k)->getBalas_jugador().at(i)->collidesWithItem(floors.at(j)))
                {
                    scene->removeItem(players.at(k)->getBalas_jugador().at(i));
                    players.at(k)->eliminar_disparo(i);
                    break;
                }
            }
        }
    }
    //+++++++++++++++++++


//    //COLISION DE LAS PELOTAS CON EL MURO/PLATAFORMAS
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
                    //balls.at(i)->set_vel(-1*balls.at(i)->getE()*players.at(j)->getVX(),players.at(j)->getVY(),players.at(j)->getPX(),players.at(j)->getPY());
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
//    //+++++++++++++++++++


//    //ACTUALIZACION DE LAS PELOTAS
    for(int i=0;i<balls.size();i++)
    {
        balls.at(i)->actualizar(v_limit);
        balls.at(i)->collision_lados_escena(v_limit,h_limit);
    }
//    //+++++++++++++++++++


//    //ACTUALIZACION DE LOS GLOBOS
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
    for(int j=0;j<players.size();j++)
    {
        for(int i=0;i<players.at(j)->getBalas_jugador().size();i++)
        {
            players.at(j)->getBalas_jugador().at(i)->actualizar(v_limit);
            if(players.at(j)->getBalas_jugador().at(i)->getPY()>=v_limit)
            {
                scene->removeItem(players.at(j)->getBalas_jugador().at(i));
                players.at(j)->eliminar_disparo(i);
            }
        }
    }
    //+++++++++++++++++++


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

