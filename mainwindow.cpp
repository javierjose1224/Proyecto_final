#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);

    h_limit=1000;
    v_limit= 500;

    timer=new QTimer(this);
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);

    ui->graphicsView->setScene(scene);
    ui->centralwidget ->adjustSize();
    scene->addRect(scene->sceneRect());//para ver los limites de la escne
    ui->graphicsView->resize(scene->width(),scene->height());
    this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+100);

    conVidas= new vida();
    conVidas->setPos(0,0);
    scene->addItem(conVidas);

    //pisos.push_back(new plataforma(0,10,h_limit,20));
    //pisos.push_back(new plataforma(0,100,h_limit,20));
    //pisos.push_back(new plataforma(h_limit,v_limit,200,100));
    //pisos.push_back(new plataforma(h_limit/8,v_limit/3,200,50));
    muros.push_back(new muro(h_limit/2,v_limit/2,200,50));

    principal = new personaje(0,0,0,0,50,20,0.3,0,5);//0.3k
    principal->actualizar(v_limit);
    scene->addItem(principal);

    bars.push_back(new pelota(32,300,10,0,50,40,0,1,2));
    bars.push_back(new pelota(32,300,30,0,50,10,0,1,7));
    bars.push_back(new pelota(32,300,10,0,50,20,0,1,1));

    nivel_1=new nivel(bars,muros);
    nivel_1->graficar(scene,v_limit,h_limit);
    //AÑADIDO DE LOS ELEMENTOS EN LA ESCENA
    //++++++++++++++++++++++++++++++++++++++++++++

    timer->start(5);
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizar_Level_esc()
{
    nivel_1->actualizar_nivel(scene,v_limit,h_limit,principal,timer,conVidas);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    personaje *b = principal;
    if(event->key() == Qt::Key_D)
    {
        b->set_vel(15,b->getVY(),b->getPX(),b->getPY());
        qDebug()<<"ME MOVI CON D";
    }
    if(event->key() == Qt::Key_A)
    {
        b->set_vel(-15,b->getVY(),b->getPX(),b->getPY());
        qDebug()<<"ME MOVI CON A";
    }
    if(event->key() == Qt::Key_W)
    {
        b->set_vel(b->getVX(),40,b->getPX(),b->getPY());
        qDebug()<<"ME MOVI CON W";
    }
    if(event->key() == Qt::Key_Space)
    {
        qDebug()<<"disparo";
        principal->disparo_lis(scene,v_limit);
        //principal->disparar(bala_jugador,scene,v_limit);
        //bala_jugador.push_back(new disparo(nivel_1->getProtag()->getPX()+nivel_1->getProtag()->getR(),nivel_1->getProtag()->getPY(),0,20,5));
        //bala_jugador.back()->actualizar(v_limit);
        //scene->addItem(bala_jugador.back());
        //b->disparar(balas_player,scene);
    }
}
