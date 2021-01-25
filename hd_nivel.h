#ifndef HD_NIVEL_H
#define HD_NIVEL_H


#include <QGraphicsTextItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

//cambionuevo
class hd_nivel:public QGraphicsTextItem
{
public:
    hd_nivel(QGraphicsItem * parent = 0);
    void increase();
    void reset();
    int getNivel_act() const;

private:
    int nivel_act;
    //incluido push
};

#endif // HD_NIVEL_H
