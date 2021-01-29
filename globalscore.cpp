#include "globalscore.h"
#include "ui_globalscore.h"
#include "endgame.h"

GlobalScore::GlobalScore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlobalScore)
{
    ui->setupUi(this);
}

GlobalScore::GlobalScore(QString nombre):ui(new Ui::GlobalScore)

{
    ui->setupUi(this);
    name=nombre;
}

GlobalScore::~GlobalScore()
{
    delete ui;
}

void GlobalScore::on_cargar_clicked()
{
    idt=0;
    for (;idt<10;idt++) {
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

void GlobalScore::on_volver_clicked()
{
    EndGame *volver;
    volver = new EndGame;
    volver->show();
    this->close();
}

void GlobalScore::on_Eliminar_clicked()
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
    }else{
//            qDebug()<<"(15) - Error";
    }
    update.clear();
}

void GlobalScore::on_SALIR_clicked()
{
    this->close();
}
