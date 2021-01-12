#ifndef NIVEL_H
#define NIVEL_H

#include "pelota.h"
#include "personaje.h"
#include "muro.h"

class nivel
{
private:

    QList<pelota*>balls;
    personaje *protag;
    QList<muro*>floors;

public:
    nivel(QList<pelota*>balls_,personaje *protag_,QList<muro*>floors_);
    ~nivel();
    QList<pelota *> getBalls() const;
    personaje *getProtag() const;
    QList<muro *> getFloors() const;
};

#endif // NIVEL_H
