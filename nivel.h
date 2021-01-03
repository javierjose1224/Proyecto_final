#ifndef NIVEL_H
#define NIVEL_H

#include "pelota.h"
#include "personaje.h"
#include "plataforma.h"

class nivel
{
private:
    QList<pelota*>balls;
    personaje *protag;
    QList<plataforma*>floors;

public:
    nivel(QList<pelota*>balls_,personaje *protag_,QList<plataforma*>floors_);
    ~nivel();
    QList<pelota *> getBalls() const;
    personaje *getProtag() const;
    QList<plataforma *> getFloors() const;

};

#endif // NIVEL_H
