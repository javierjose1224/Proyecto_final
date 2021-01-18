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
    QList<muro*>floors;

public slots:



public:
    explicit nivel(QObject *parent = nullptr);
    nivel(QList<pelota*>balls_,QList<muro*>floors_);
    ~nivel();

    void borrar_elementos(QGraphicsScene *scene);

    QList<pelota *> getBalls() const;
    QList<muro *> getFloors() const;

    void graficar(QGraphicsScene *scene,float v_limit,float h_limit);
    void actualizar_nivel(QGraphicsScene *scene,float v_limit,float h_limit,personaje *protag,QTimer *timer,vida *conVidas);

};

#endif // NIVEL_H





