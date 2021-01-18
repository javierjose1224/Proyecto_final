#ifndef PELOTA_H
#define PELOTA_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>
#include <stdlib.h>
#include <time.h>
#include <proyectil.h>
#include <QList>

class pelota:public QObject,public QGraphicsItem
{
private:
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
    pelota(float posX_,float posY_,float velX_,float velY_,float masa,float radio,float k_,float e_,float G_);
    ~pelota();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    void setEscala(float s);

    //void collisionball(QList<proyectil *> balas_player, QGraphicsScene *scene);
    void collision_lados_escena(float v_limit,float h_limit);
    void actualizar(float v_limit);

    float getPX() const;
    float getPY() const;
    float getMass() const;
    float getR() const;
    float getVX() const;
    float getVY() const;
    float getE() const;
    void set_vel(float vx,float vy, float px,float py);
};

#endif // PELOTA_H
