#include "puntaje.h"

puntaje::puntaje(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    score = -1;
    setPlainText(QString("Puntos: ")+ QString::number(score));
    setDefaultTextColor(Qt::darkBlue);
    setFont(QFont("times",16));
}

void puntaje::increase()
{
    score++;
    setPlainText(QString("Puntos: ")+ QString::number(score));
}

int puntaje::getScore()
{
    return score;
}

void puntaje::setScore(int value)
{
    score = value;
    setPlainText(QString("Puntos: ")+ QString::number(score));
}

