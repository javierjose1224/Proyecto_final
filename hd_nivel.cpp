#include "hd_nivel.h"


hd_nivel::hd_nivel(QGraphicsItem *parent)
{
    nivel_act = 1;
    setPlainText(QString("Nivel: ")+ QString::number(nivel_act));
    setDefaultTextColor(Qt::black);
    setFont(QFont("Segoe Script",16));
}

void hd_nivel::increase()
{
    nivel_act++;
    setPlainText(QString("Nivel: ")+ QString::number(nivel_act));
}

void hd_nivel::reset()
{
    nivel_act=1;
}


int hd_nivel::getNivel_act() const
{
    return nivel_act;
}

void hd_nivel::setNivel_graf(int value)
{
    nivel_act = value;
    setPlainText(QString("Nivel: ")+ QString::number(nivel_act));
}
