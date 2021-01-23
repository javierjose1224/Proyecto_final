#ifndef NIVEL_H
#define NIVEL_H

#include <QObject>
#include "pelota.h"
#include "personaje.h"
#include "muro.h"
#include "vida.h"
#include <QTimer>
#include "senoidal.h"
#include "puntaje.h"
#include "tiempo_juego.h"
#include "pua.h"

class nivel:public QObject
{
     Q_OBJECT
private:

    QList<pelota*>balls;
    QList<muro*>floors;
    QList<senoidal*>globos;
    QList<pua*>puas;
    tiempo_juego *cont_globos;

public slots:


public:
    explicit nivel(QObject *parent = nullptr);
    nivel(QList<pelota*>balls_,QList<muro*>floors_,QList<senoidal*>globos_,QList<pua*>puas_,QGraphicsScene *scene, float v_limit);
    ~nivel();

    void borrar_elementos(QGraphicsScene *scene);

    QList<pelota *> getBalls() const;
    QList<muro *> getFloors() const;

    void remove_bullet(personaje *protag,int j);

    void graficar(QGraphicsScene *scene,float v_limit);
    void actualizar_nivel(QGraphicsScene *scene,float v_limit,float h_limit,personaje *protag,QTimer *timer,vida *conVidas,puntaje *score,tiempo_juego *cont_abs);

    void agregar_globo(senoidal *a);
};

#endif // NIVEL_H





