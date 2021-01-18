#ifndef NIVEL_H
#define NIVEL_H

#include <QObject>
#include "pelota.h"
#include "personaje.h"
#include "muro.h"
#include "proyectil.h"
#include "vida.h"
#include <QTimer>

class nivel:public QObject
{
     Q_OBJECT
private:

    QList<pelota*>balls;
    personaje *protag;
    QList<muro*>floors;
    vida *salud;
    QTimer *timer_emp;

public slots:

    void actualizar_nivel(QGraphicsScene *scene,float v_limit,float h_limit);

public:
    explicit nivel(QObject *parent = nullptr);
    nivel(QList<pelota*>balls_,personaje *protag_,QList<muro*>floors_);
    ~nivel();
    QList<pelota *> getBalls() const;
    void graficar(QGraphicsScene *scene,float v_limit,float h_limit);

    personaje *getProtag() const;
    QList<muro *> getFloors() const;
};

#endif // NIVEL_H
