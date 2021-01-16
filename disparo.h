#ifndef DISPARO_H
#define DISPARO_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>
#include <stdlib.h>
#include <time.h>
#include <QList>
#include <QDebug>

class disparo: public QGraphicsItem
{
    float PX;
    float PY;
    float mass;
    float R;//radio
    float VX;
    float VY;
    float angulo;
    float AX;
    float AY;
    float G;
    float K;//resistencia del aire
    float e;//coef de restitucion
    float V;//vector de velocidad
    float dt;//var del tiempo
    float escala;
public:
    disparo(float posX_,float posY_,float velX_,float velY_,float radio);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    void setEscala(float s);

    //void collisionball(QList<proyectil *> balas_player, QGraphicsScene *scene);

    void actualizar(float v_limit);
};

#endif // DISPARO_H
