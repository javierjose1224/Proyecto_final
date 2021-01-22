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
    con_abs=contador/200;
    setPlainText(QString("tiempo: ")+ QString::number(con_abs));
}

int tiempo_juego::getCon_abs() const
{
    return con_abs;
}

void tiempo_juego::setCon_abs(int value)
{
    con_abs = value;
}

void tiempo_juego::increase()
{
    contador++;
    con_abs=contador/200;
}

void tiempo_juego::reset()
{
    contador=0;
}

int tiempo_juego::getTimerG()
{
    return contador;
}

void tiempo_juego::setContador(int value)
{
    contador = value;
}
