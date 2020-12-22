#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>

class proyectil: public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    proyectil();

public slots:
    void movimiento();
};

#endif // PROYECTIL_H
