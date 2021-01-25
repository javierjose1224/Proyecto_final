#include "endgame.h"
#include "ui_endgame.h"

EndGame::EndGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EndGame)
{
    ui->setupUi(this);
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

}
