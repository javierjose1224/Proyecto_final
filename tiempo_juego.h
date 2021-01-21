#ifndef TIEMPO_JUEGO_H
#define TIEMPO_JUEGO_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

//cambionuevo
class tiempo_juego:public QGraphicsTextItem
{
public:
    tiempo_juego(QGraphicsItem * parent = 0);    
    void increase();
    void reset();
    int getTimerG();
    void setContador(int value);
    void increase_graf();

    int getCon_abs() const;
    void setCon_abs(int value);

private:
    int contador;
    int con_abs;
};

#endif // TIEMPO_JUEGO_H
