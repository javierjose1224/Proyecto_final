#ifndef SENOIDAL_H
#define SENOIDAL_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>
#include <stdlib.h>
#include <time.h>
#include <QList>

class senoidal:public QGraphicsItem
{
    float PX;
    float PY;
    float R;
    float K;
    float W;
    float dt;
    float u;

public:
    senoidal(float posx,float posy,float w_);
    void actualizar(float v_limit);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    void setU(float value);
    float getPX() const;
};

#endif // SENOIDAL_H
