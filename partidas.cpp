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

void Partidas::num_players()
{
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Pausa");

    QPushButton *one_pButton = msgBox.addButton(tr("1 Jugador"), QMessageBox::RejectRole);
    QPushButton *two_pButton = msgBox.addButton(tr("2 Jugadores"), QMessageBox::RejectRole);

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

