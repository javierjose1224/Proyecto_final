#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
//cambio
class puntaje:public QGraphicsTextItem
{
public:
    puntaje(QGraphicsItem * parent = 0);
    void increase();
    int getScore();
private:
    int score;
};
#endif // PUNTAJE_H
