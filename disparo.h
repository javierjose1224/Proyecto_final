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
#include <cmath>
#include <QPixmap>

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
    disparo(float posX_,float posY_,float velY_);
    ~disparo();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    void setEscala(float s);

    //void collisionball(QList<proyectil *> balas_player, QGraphicsScene *scene);

    void actualizar(float v_limit);
    float getPX() const;
    float getR() const;
    float getPY() const;

    void setVX(float value);
};

#endif // DISPARO_H
