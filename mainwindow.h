#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include "pelota.h"
#include <QKeyEvent>
#include "personaje.h"
#include "plataforma.h"
#include "proyectil.h"

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
    float dt;
    int h_limit;
    int v_limit;
    void borderColilision(pelota *b);
    void borderColilisionPer(personaje *b);
    void keyPressEvent(QKeyEvent *event);

    //plataforma *suelo;
    personaje *principal;
    QList<plataforma *>pisos;
    QList<pelota *>bars;
};
#endif // MAINWINDOW_H
