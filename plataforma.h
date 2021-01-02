#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <QGraphicsItem>
#include <QPainter>

class plataforma:public QGraphicsItem
{
private:
    float posX;
    float posY;
    float ancho;
    float alto;
public:
    plataforma(float posx_,float posy_, float ancho_, float alto_);
    void posicionAbs(float v_limit);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    float getPosX() const;
    void setPosX(float value);
    float getPosY() const;
    void setPosY(float value);
};

#endif // PLATAFORMA_H
