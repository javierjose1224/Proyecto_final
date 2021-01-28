#ifndef ENDGAME_H
#define ENDGAME_H

#include <QMainWindow>
#include<QString>
#include<QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>


namespace Ui {
class EndGame;
}

class EndGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit EndGame(QWidget *parent = nullptr);
    EndGame(QString nombre, float puntos,float t, float vidas, float nivel, bool);
    void imprimir_datos();
    ~EndGame();

private slots:
    void on_regButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::EndGame *ui;
    QString name;
    int idt;
    float score;
    float tiempo;
    float level;
    float life;
};

#endif // ENDGAME_H
