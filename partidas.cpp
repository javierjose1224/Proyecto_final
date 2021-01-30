#include "partidas.h"
#include "ui_partidas.h"
#include "sesion.h"

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
        delete ui->x_2;
    }
    else if(nivel==2)
    {
        ui->pushButton_2->setEnabled(true);
        delete ui->x_1;
    }

}

Partidas::~Partidas()
{
    delete ui;
}

void Partidas::num_players()
{
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Numero de jugadores");

    QPushButton *one_pButton = msgBox.addButton(tr("1 Jugador"), QMessageBox::RejectRole);
    QPushButton *two_pButton = msgBox.addButton(tr("2 Jugadores"), QMessageBox::RejectRole);
    QPushButton *three_pButton = msgBox.addButton(tr("cancelar"), QMessageBox::RejectRole);

    msgBox.exec();
    if (msgBox.clickedButton() == one_pButton)
    {
        ver_num_pls=false;
        msgBox.close();
    }
    else if (msgBox.clickedButton() == two_pButton) {

        ver_num_pls=true;
        this->close();
    }
//    else if (msgBox.clickedButton() == three_pButton) {

//        msgBox.close();
//        Sesion *p;
//        p = new Sesion;
//        p->show();
//        this->close();
//    }

    delete one_pButton;
    delete two_pButton;

}

void Partidas::on_pushButton_clicked()
{
    nivel=1;
    num_players();
    juego = new MainWindow(name,nivel,ver_num_pls);
    juego->show();
    this->close();
}

void Partidas::on_pushButton_2_clicked()
{
    nivel=2;
    num_players();
    juego = new MainWindow(name,nivel,ver_num_pls);
    juego->show();
    this->close();
}

void Partidas::on_pushButton_3_clicked()
{
    nivel=3;
    num_players();
    juego = new MainWindow(name,nivel,ver_num_pls);
    juego->show();
    this->close();
}


void Partidas::on_volver_clicked()
{
    Sesion *p;
    p = new Sesion;
    p->show();
    this->close();
}
