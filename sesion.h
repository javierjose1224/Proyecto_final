#ifndef SESION_H
#define SESION_H

#include <QMainWindow>
#include<fstream>
#include<QString>
#include<QMessageBox>
#include"mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>

using namespace std;

namespace Ui {
class Sesion;
}

class Sesion : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sesion(QWidget *parent = nullptr);
    ~Sesion();

private slots:

    void on_loginButton_clicked();

    void on_regButton_clicked();

    void on_loginButton_2_clicked();

private:
    Ui::Sesion *ui;
    MainWindow * jugar;
    QString name;
    QString password;
    int idt;
    QMessageBox msgBox;
    QSqlDatabase baseDatos;
    bool conexionBaseDatos();
    bool crearBaseDatos();
    bool crearTablaUsuarios();
    void insertar();
};

#endif // SESION_H
