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
    msg.setText("Numero de jugadores");
    msg.setIcon(QMessageBox::Question);

    QPushButton *one_pButton = msg.addButton(tr("1 Jugador"), QMessageBox::RejectRole);
    QPushButton *two_pButton = msg.addButton(tr("2 Jugadores"), QMessageBox::RejectRole);
    msg.exec();

    if (msg.clickedButton() == one_pButton)
    {
        ver_num_pls=false;
        msg.close();
    }
    else if (msg.clickedButton() == two_pButton) {

        ver_num_pls=true;
        this->close();
    }
    msg.close();
    msg.removeButton(one_pButton);
    msg.removeButton(two_pButton);

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

void Partidas::on_pushButton_4_clicked()
{
    nivel=4;
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


