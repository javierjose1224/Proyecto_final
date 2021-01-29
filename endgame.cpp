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
        ui->label_2->hide();
        delete ui->label_2;
        ui->label->show();
    }
    else {
        ui->label->hide();
        delete ui->label;
        ui->label_2->show();
    }
    actualizar();
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

void EndGame::actualizar()
{
    idt=0;
    for (;idt<20;idt++) {
        QString consultarDato;
        QSqlQuery query;
        consultarDato.append("SELECT * FROM usuarios WHERE id='"+QString::number(idt)+"'");
        query.prepare(consultarDato);
    //    qDebug()<<"(6) - consultar";
        if(query.exec()){
    //        qDebug()<<"(6) - Exitoso";
            if(query.next()){
                QTableWidgetItem *nombre=new QTableWidgetItem();
                nombre->setText(query.value(1).toString());
                ui->tabla->setItem(idt-1,0,nombre);
                QTableWidgetItem *puntos=new QTableWidgetItem();
                puntos->setText(query.value(4).toString());
                ui->tabla->setItem(idt-1,1,puntos);
                QTableWidgetItem *vida=new QTableWidgetItem();
                vida->setText(query.value(3).toString());
                ui->tabla->setItem(idt-1,2,vida);
            }
        }
    }
}

void EndGame::on_Eliminar_clicked()
{
    QString update;
    QSqlQuery query;

    //life
    update.append("UPDATE usuarios SET life='-',score='-',nivel='-',time='-' WHERE name='"+name+"'");
    query.prepare(update);
//        qDebug()<<"(15) - update";
    if(query.exec()){
//            qDebug()<<"(15) - Exitoso";
        if(query.next()){
//                qDebug()<<"hecho";
        }
    }
    update.clear();
    msgBox.setText("Datos eliminados exitosamente");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

    actualizar();
}

void EndGame::on_SALIR_clicked()
{
    this->close();
}
