#ifndef VIDA_H
#define VIDA_H
#include <QGraphicsTextItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>

class vida:public QGraphicsTextItem
{
public:
    vida(QGraphicsItem * parent = 0);
    void decrease();
    int getvidaT();
private:
    int vidaT;
};

#endif // VIDA_H
