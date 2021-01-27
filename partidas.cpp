#include "partidas.h"
#include "ui_partidas.h"

Partidas::Partidas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Partidas)
{
    ui->setupUi(this);
}

Partidas::Partidas(QString nombre, int level, bool id_lev):ui(new Ui::Partidas)
{
    ui->setupUi(this);
    name=nombre;
    nivel=level;
    id_niv=id_lev;
    if(nivel==3)
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        delete ui->x_1;
        ui->x_2->deleteLater();
    }
    else if(nivel==2)
    {
        ui->pushButton_2->setEnabled(true);
        ui->x_1->deleteLater();
    }

}

Partidas::~Partidas()
{
    delete ui;
}

void Partidas::on_pushButton_clicked()
{
    nivel=1;
    juego = new MainWindow(name,nivel,id_niv);
    juego->show();
    this->close();
}

void Partidas::on_pushButton_2_clicked()
{
    nivel=2;
    juego = new MainWindow(name,nivel,false);
    juego->show();
    this->close();
}

void Partidas::on_pushButton_3_clicked()
{
    nivel=3;
    juego = new MainWindow(name,nivel,true);
    juego->show();
    this->close();
}


