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


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void actualizarm();

private:

    Ui::MainWindow *ui;
    QTimer *timer;
    QGraphicsScene *scene;

    QList<muro *>muros;
    QList<pelota *>bars;
    QList<senoidal *>globs;

    float dt;
    int h_limit;
    int v_limit;

    nivel *nivel_1;
    senoidal *bomba;
    tiempo_juego *contador_n1;
    tiempo_juego *gener_glob;
    puntaje *score;
    vida *conVidas;
    personaje *principal;

    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
