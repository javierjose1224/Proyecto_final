#ifndef TIEMPO_JUEGO_H
#define TIEMPO_JUEGO_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
//cambionuevo
class tiempo_juego:public QGraphicsTextItem
{
public:
    tiempo_juego(QGraphicsItem * parent = 0);
    void increase_graf();
    void increase();
    int getTimerG();
    void setContador(int value);


private:
    int contador;
};

#endif // TIEMPO_JUEGO_H
