#ifndef MURO_H
#define MURO_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <stdlib.h>
#include <time.h>
#include <QPixmap>

class muro:public QGraphicsItem
{
private:
    float PX;
    float PY;
    float R;
    float Ancho;
    float Alto;
    QPixmap *pixmap;

public:
    muro(float posx,float posy,float ancho, float alto);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    void posicionar(float v_limit);
    float getPX() const;
    float getPY() const;
    float getAncho() const;
    float getAlto() const;
};

#endif // MURO_H
