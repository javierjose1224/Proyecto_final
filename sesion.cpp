#include "sesion.h"
#include "ui_sesion.h"

sesion::sesion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sesion)
{
    ui->setupUi(this);
}

sesion::sesion(float puntaje, float tiempo,float nivel):ui(new Ui::sesion)
{
    ui->setupUi(this);
    score=puntaje;
    time=tiempo;
    level=nivel;
}

sesion::~sesion()
{
    delete ui;
}

void sesion::on_pushButton_clicked()
{
    qDebug()<<"puntaje: "<<score;
    qDebug()<<"tiempo: "<<time;
    qDebug()<<"Nivel: "<<level;
}
