#ifndef VIDA_H
#define VIDA_H
#include <QGraphicsTextItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
//cambio
class vida:public QGraphicsTextItem
{
public:
    vida(QGraphicsItem * parent = 0);
    void decrease();
    void increase();
    int getvidaT();
    void setVidaT(int value);

private:
    int vidaT;
};

#endif // VIDA_H
