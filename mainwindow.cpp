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

    principal = new personaje(0,0,0,0,50,20,0.3,0,5);//0.3k
    principal->actualizar(v_limit);
    scene->addItem(principal);
//MUROS PARA NIVEL 1
    muros.push_back(new muro(h_limit/2-25,v_limit/2,100,100));
//    muros.push_back(new muro(h_limit/2,v_limit/2,200,50));

//PELOTAS PARA MANDAR AL NIVEL

    bars.push_back(new pelota(32,300,10,0,50,40,0,1,2));
    bars.push_back(new pelota(80,300,10,0,50,40,0,1,2));


//GLOBOS PARA EL NIVEL 1
    //globs.push_back(new senoidal(0,v_limit/2,1));

    nivel_1=new nivel(bars,muros,globs,scene,v_limit);
    //nivel_1->graficar(scene,v_limit);

    conVidas= new vida();
    conVidas->setPos(0,-30);
    scene->addItem(conVidas);

    score = new puntaje();
    score->setPos(h_limit-150,-30);
    scene->addItem(score);

    gener_glob = new tiempo_juego();

    contador_n1= new tiempo_juego();
    contador_n1->setPos(h_limit/2-50,-30);

    scene->addItem(contador_n1);
    timer->start(5);//5
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarm()
{
    gener_glob->increase();
    contador_n1->increase_graf();

    if(contador_n1->getCon_abs()==20)
    {
        contador_n1->reset();
        //timer->stop();
    }

    if(conVidas->getvidaT()>0)
    {
        nivel_1->actualizar_nivel(scene,v_limit,h_limit,principal,timer,conVidas,score,gener_glob);
    }
    else
    {
        timer->stop();
        scene->removeItem(principal);
        nivel_1->borrar_elementos(scene);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    personaje *b = principal;

    if(event->key() == Qt::Key_D)
    {
        b->set_vel(15,b->getVY(),b->getPX(),b->getPY());
        //qDebug()<<"ME MOVI CON D";
    }
    if(event->key() == Qt::Key_A)
    {
        b->set_vel(-15,b->getVY(),b->getPX(),b->getPY());
        //qDebug()<<"ME MOVI CON A";
    }
    if(event->key() == Qt::Key_W && b->getPY()<=b->getR())
    {
        b->set_vel(b->getVX(),40,b->getPX(),b->getPY());
        //qDebug()<<"ME MOVI CON W";
    }
    if(event->key() == Qt::Key_Space && b->getBalas_jugador().size()==0)
    {
        principal->disparo_lis(scene,v_limit);
    }
}
