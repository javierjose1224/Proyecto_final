#include "tiempo_juego.h"

tiempo_juego::tiempo_juego(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    contador = 0;
    setPlainText(QString("Tiempo: ")+ QString::number(contador));
    setDefaultTextColor(Qt::black);
    setFont(QFont("Segoe Script",16));
}

void tiempo_juego::increase_graf()
{
    contador++;
    con_abs=contador/200;
    setPlainText(QString("Tiempo: ")+ QString::number(con_abs));
}

void tiempo_juego::decrese()
{
    contador--;
    con_abs=(contador/200)+60;
    setPlainText(QString("Tiempo: ")+ QString::number(con_abs));
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

void tiempo_juego::reset_neg()
{
    contador=90;
    setPlainText(QString("Tiempo: ")+ QString::number(contador));
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
    con_abs=(contador/200)+90;
    setPlainText(QString("Tiempo: ")+ QString::number(con_abs));
}
