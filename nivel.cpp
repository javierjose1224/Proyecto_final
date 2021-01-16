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

void nivel::graficar(QGraphicsScene *scene, float v_limit)
{
    for(int i=0;i<this->getFloors().size();i++)
    {
        this->getFloors().at(i)->posicionar(v_limit);
        scene->addItem(this->getFloors().at(i));
    }

    for(int i=0;i<this->getBalls().size();i++)
    {
        this->getBalls().at(i)->actualizar(v_limit);
        scene->addItem(this->getBalls().at(i));
    }
    this->getProtag()->actualizar(v_limit);
    scene->addItem(this->getProtag());
}

void nivel::actualizar_juego()
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

