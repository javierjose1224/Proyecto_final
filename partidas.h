#ifndef PARTIDAS_H
#define PARTIDAS_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QMessageBox>

namespace Ui {
class Partidas;
}

class Partidas : public QMainWindow
{
    Q_OBJECT

public:
    explicit Partidas(QWidget *parent = nullptr);
    Partidas(QString nombre,int level,bool id_lev);
    ~Partidas();
    void num_players();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_volver_clicked();

private:
    Ui::Partidas *ui;
    QString name;
    QMessageBox msg;
    MainWindow *juego;
    bool ver_num_pls;
    int nivel;
    bool id_niv;
};

#endif // PARTIDAS_H
