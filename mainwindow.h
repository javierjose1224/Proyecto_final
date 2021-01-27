#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include "pelota.h"
#include <QKeyEvent>
#include "personaje.h"
#include "vida.h"
#include "nivel.h"
#include "muro.h"
#include "puntaje.h"
#include "disparo.h"
#include "tiempo_juego.h"
#include "senoidal.h"
#include "pua.h"
#include "hd_nivel.h"
#include "endgame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    MainWindow(QString name);
    ~MainWindow();
    void cambiar_nivel();

public slots:

    void actualizarm();

private slots:
    void on_pushButton_clicked();

private:

    Ui::MainWindow *ui;
    QString nombre_jugador;
    QTimer *timer;
    QGraphicsScene *scene;
    QList<senoidal *>globs;

    float dt;
    int h_limit;
    int v_limit;

    nivel *nivel_1;
    QList<muro *>muros;
    QList<pelota *>bars;
    QList<pua*>puas;

    nivel *nivel_2;
    QList<muro *>muros2;
    QList<pelota *>bars2;
    QList<pua*>puas2;

    nivel *nivel_3;
    QList<muro*>muros3;
    QList<pelota*>bars3;
    QList<pua*>puas3;

    senoidal *bomba;
    tiempo_juego *contador_n1;
    tiempo_juego *gener_glob;
    puntaje *score;
    vida *conVidas;
    hd_nivel *nivel_graf;
    QList<personaje*>jugadores;
    personaje *principal;
    personaje *segundo_plyr;
    EndGame *pasar;

    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
