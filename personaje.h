#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <stdlib.h>
#include <time.h>
#include "disparo.h"
#include <QPixmap>
#include <QMessageBox>

class personaje:public QGraphicsItem
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
    int con=0;
    float VD;
    bool golpe;
    int color;
    QList<disparo*> balas_jugador;

public:

    personaje(float posX_,float posY_,float velX_,float velY_,float radio,float k_,float e_,float G_,int col);
    ~personaje();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    void setEscala(float s);

    void actualizar(float v_limit);
    void colision_lados_escena(float v_limit,float h_limit);
    bool saltar();


    float getPX() const;
    float getPY() const;
    float getMass() const;
    float getR() const;
    float getVX() const;
    float getVY() const;
    float getE() const;
    void set_vel(float vx,float vy, float px,float py);
    void set_Newvel(float vx,float vy);
    void setPX(float value);
    void setPY(float value);

    void eliminar_disparo(int i);

    void disparo_lis(QGraphicsScene *scene,float v_limit);
    QList<disparo *> getBalas_jugador() const;

    float getVD() const;
    void setVD(float value);
    bool getGolpe() const;
    void setGolpe(bool value);
    void setK(float value);
};

#endif // PERSONAJE_H
