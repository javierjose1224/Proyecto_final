#include "nivel.h"

nivel::nivel(QList<pelota *> balls_, personaje *protag_, QList<plataforma *> floors_)
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

personaje *nivel::getProtag() const
{
    return protag;
}

QList<plataforma *> nivel::getFloors() const
{
    return floors;
}
