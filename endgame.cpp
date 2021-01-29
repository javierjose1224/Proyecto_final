#include "endgame.h"
#include "ui_endgame.h"
//#include "mainwindow.h"

EndGame::EndGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EndGame)
{
    ui->setupUi(this);
}

EndGame::EndGame(QString nombre, float puntos, float t, float vidas, float nivel, bool fin):ui(new Ui::EndGame)
{
    ui->setupUi(this);
    name=nombre;
    score=puntos;
    tiempo=t;
    level=nivel;
    life=vidas;
    if (fin==true) {
        ui->label_5->hide();
        ui->label_4->show();
    }
    else{
        ui->label_4->hide();
        ui->label_5->show();
    }
}

//void EndGame::imprimir_datos()
//{
//    qDebug()<<"Usuario: "<<name;
//    qDebug()<<"Puntaje: "<<score;
//    qDebug()<<"Tiempo: "<<tiempo;
//    qDebug()<<"Nivel: "<<level;
//    qDebug()<<"Vida: "<<life;
//}

EndGame::~EndGame()
{
    delete ui;
}

void EndGame::on_regButton_clicked()
{
    this->close();
}

void EndGame::on_score_clicked()
{
    qDebug()<<"NOMBRE: "<<name;
    ver_puntos = new GlobalScore(name);
    ver_puntos->show();
    this->close();
}
