#include "tiempo_juego.h"

tiempo_juego::tiempo_juego(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    contador = 0;
    setPlainText(QString("tiempo: ")+ QString::number(contador));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",16));
}

void tiempo_juego::increase_graf()
{
    contador++;
    setPlainText(QString("tiempo: ")+ QString::number(contador/150));
}

void tiempo_juego::increase()
{
    contador++;
}

int tiempo_juego::getTimerG()
{
    return contador;
}

void tiempo_juego::setContador(int value)
{
    contador = value;
}
