#include "vida.h"
#include <QFont>

vida::vida(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    vidaT = 10;
    setPlainText(QString("Vidas: ")+ QString::number(vidaT));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void vida::decrease()
{
    vidaT--;
    setPlainText(QString("Vidas: ")+ QString::number(vidaT));
}

void vida::increase()
{
    vidaT++;
    setPlainText(QString("Vidas: ")+ QString::number(vidaT));
}

int vida::getvidaT()
{
    return vidaT;
}

void vida::setVidaT(int value)
{
    vidaT = value;
    setPlainText(QString("Vidas: ")+ QString::number(vidaT));
}
