#include "sesion.h"
#include "ui_sesion.h"

Sesion::Sesion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sesion)
{
    ui->setupUi(this);
    if(conexionBaseDatos()){
        if(crearBaseDatos()){
            crearTablaUsuarios();
        }
    }
}

Sesion::~Sesion()
{
    delete ui;
}

void Sesion::on_loginButton_clicked()
{
    QString consultarDato;
    QSqlQuery query;
    name=ui->usernameBox->text();
    password=ui->passwordBox->text();

    consultarDato.append("SELECT * FROM usuarios WHERE name='"+name+"'");
    query.prepare(consultarDato);
//    qDebug()<<"(5) - consultar";
    if(query.exec()){
//        qDebug()<<"(5) - Exitoso";
        if(query.next()){
            if(password==query.value(2).toString()){
                jugar = new MainWindow(name);
                jugar->show();
                this->close();
            }else{
                //ventana de dialogo
                //contraseña incorrecta
                msgBox.setText("Contraseña incorrecta");
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.exec();
            }
        }else{
            //ventana de dialogo
            //usuario no registrado
            msgBox.setText("Usuario no registrado");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }else{
//        qDebug()<<"(5) - Error";
    }
}

void Sesion::on_regButton_clicked()
{
    name=ui->usernameBox->text();

    QString consultarDato;
    QSqlQuery query;

    consultarDato.append("SELECT * FROM usuarios WHERE name='"+name+"'");
    query.prepare(consultarDato);
//    qDebug()<<"(5) - consultar";
    if(query.exec()){
//        qDebug()<<"(5) - Exitoso";
        if(query.next()){
            //ventana de dialogo
            //Usuario ya registrado
            msgBox.setText("Este usuario ya está registrado");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }else{
            password=ui->passwordBox->text();
            insertar();
        }
    }else{
//        qDebug()<<"(5) - Error";
    }
}

bool Sesion::conexionBaseDatos()
{
    QSqlQuery query;
//    qDebug()<<"(1) - Cargando Driver";
    if(QSqlDatabase::isDriverAvailable("QSQLITE")){
//        qDebug()<<"(1) - Exitoso";
        return true;
    }else{
//        qDebug()<<"(1) - Error";
        return false;
    }
}

bool Sesion::crearBaseDatos()
{
    baseDatos = QSqlDatabase::addDatabase("QSQLITE");
    baseDatos.setDatabaseName("database.sqlite");
//    qDebug()<<"(2) - Crear Base de Datos";
    if(baseDatos.open()){
//        qDebug()<<"(2) - Exitoso";
        return true;
    }else{
//        qDebug()<<"(2) - Error";
        return false;
    }
}

bool Sesion::crearTablaUsuarios()
{
    QString crear;
    QSqlQuery query;

    crear.append("CREATE TABLE IF NOT EXISTS usuarios (id INTEGER PRIMARY KEY AUTOINCREMENT,name VARCHAR(20), password VARCHAR(20),life INTEGER(20),score INTEGER(20),nivel INTEGER(20),time INTEGER(20))");
    query.prepare(crear);
//    qDebug()<<"(3) - Tabla";
    if(query.exec()){
//        qDebug()<<"(3) - Exitoso";
        return true;
    }else{
//        qDebug()<<"(3) - Error";
        return false;
    }
}

void Sesion::insertar()
{
    QString insertarDato;
    QSqlQuery query;
    insertarDato.append("INSERT INTO usuarios (name,password,life,score,nivel,time) VALUES ('"+name+"','"+password+"','0','12','13','8')");
    query.prepare(insertarDato);
//    qDebug()<<"(4) - Insertar";
    if(query.exec()){
//        qDebug()<<"(4) - Exitoso";
    }else{
//        qDebug()<<"(4) - Error";
    }
    insertarDato.clear();

    QString consultarDato;
    consultarDato.append("SELECT * FROM usuarios WHERE name='"+name+"'");
    query.prepare(consultarDato);
//    qDebug()<<"(5) - consultar";
    if(query.exec()){
//        qDebug()<<"(5) - Exitoso";
        if(query.next()){
            idt=query.value(0).toInt();
        }
    }else{
//        qDebug()<<"(5) - Error";
    }

}

void Sesion::on_loginButton_2_clicked()
{
    QString consultarDato;
    QSqlQuery query;
    name = "Invitado";

    consultarDato.append("SELECT * FROM usuarios WHERE name='"+name+"'");
    query.prepare(consultarDato);
//    qDebug()<<"(5) - consultar";
    if(query.exec()){
//        qDebug()<<"(5) - Exitoso";
        if(query.next()){
        }else{
            password= "0000";
            insertar();
        }
    }else{
//        qDebug()<<"(5) - Error";
    }
    jugar = new MainWindow(name);
    jugar->show();
    this->close();
}

