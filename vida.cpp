#include "vida.h"
#include <QFont>

vida::vida(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    vidaT = 3;
    setPlainText(QString("Vidas: ")+ QString::number(vidaT));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void vida::decrease()
{
    vidaT--;
    setPlainText(QString("Vidas: ")+ QString::number(vidaT));
}

int vida::getvidaT()
{
    return vidaT;
}
