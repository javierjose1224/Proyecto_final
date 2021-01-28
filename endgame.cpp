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
    else {
        ui->label_4->hide();
        ui->label_5->show();
    }
}

void EndGame::imprimir_datos()
{
    qDebug()<<"Usuario: "<<name;
    qDebug()<<"Puntaje: "<<score;
    qDebug()<<"Tiempo: "<<tiempo;
    qDebug()<<"Nivel: "<<level;
    qDebug()<<"Vida: "<<life;
}

EndGame::~EndGame()
{
    delete ui;
}

void EndGame::on_regButton_clicked()
{
    this->close();
}

void EndGame::on_loginButton_clicked()
{
    QString update;
    QSqlQuery query;

    //life
    update.append("UPDATE usuarios SET life='"+QString::number(life)+"',score='"+QString::number(score)+"',nivel='"+QString::number(level)+"',time='"+QString::number(tiempo)+"' WHERE name='"+name+"'");
    query.prepare(update);
        qDebug()<<"(15) - update";
    if(query.exec()){
//            qDebug()<<"(15) - Exitoso";
        if(query.next()){
//                qDebug()<<"hecho";
        }
    }else{
//            qDebug()<<"(15) - Error";
    }
    update.clear();

    QString consultarDato;
    consultarDato.append("SELECT * FROM usuarios WHERE name='"+name+"'");
    query.prepare(consultarDato);
//    qDebug()<<"(6) - consultar";
    if(query.exec()){
//        qDebug()<<"(6) - Exitoso";
        if (query.next()) {
//            qDebug()<<"hecho";
//            qDebug()<<"Numero de usuario: "<<query.value(0).toString();
//            qDebug()<<"Nombre: "<<query.value(1).toString();
//            qDebug()<<"Contraseña: "<<query.value(2).toString();
//            qDebug()<<"Vidas: "<<query.value(3).toString();
//            qDebug()<<"Puntaje final: "<<query.value(4).toString();
//            qDebug()<<"Nivel: "<<query.value(5).toString();
//            qDebug()<<"Tiempo: "<<query.value(6).toString();
        }
    }else{
//                qDebug()<<"(15) - Error";
    }

    this->close();
}
