#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

class proyectil: public QObject,public QGraphicsRectItem
{
    Q_OBJECT
    float posX;
public:
    proyectil(float v_limit);
    float getPosX() const;

public slots:
    void movimiento();
};

#endif // PROYECTIL_H
