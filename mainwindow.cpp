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
    //scene->setBackgroundBrush(Qt::yellow);

    ui->graphicsView->setScene(scene);
    ui->centralwidget ->adjustSize();
    scene->addRect(scene->sceneRect());//para ver los limites de la escne
    ui->graphicsView->resize(scene->width(),scene->height());
    this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+100);

    principal = new personaje(h_limit/2,0,0,0,20,0.3,0,5);//0.3k
    principal->actualizar(v_limit);
    scene->addItem(principal);

//NIVEL 1
{
//PUAS PARA NIVEL 1
    puas.push_back(new pua(3*h_limit/4,25,50,25));


//PELOTAS PARA NIVEL 1

    bars.push_back(new pelota(80,300,10,0,50,40,0,1,2));

}

//NIVEL 2
{
//MUROS NIVEL 2
    muros2.push_back(new muro(100,v_limit/2,100,100));
    muros2.push_back(new muro(h_limit-200,v_limit/2,100,100));


//PELOTAS NIVEL 2
    bars2.push_back(new pelota(20,300,10,0,50,40,0,1,2));
    bars2.push_back(new pelota(80,300,10,0,50,40,0,1,2));
}

//NIVEL 3
{
//PELOTAS NIVEL 3
    bars3.push_back(new pelota((300),400,10,0,50,40,0,1,2));
    bars3.push_back(new pelota((300)+40,400,10,0,50,40,0,1,2));
    bars3.push_back(new pelota((300)+80,400,10,0,50,40,0,1,2));

//MUROS NIVEL 3
    muros3.push_back(new muro(100,v_limit/2,100,100));
    muros3.push_back(new muro(h_limit-200,v_limit/2,100,100));
    muros3.push_back(new muro(h_limit/2-50,v_limit/3,100,50));
}
    nivel_1=new nivel(bars,muros,globs,puas,scene,v_limit);

//VIDAS, PUNTAJE Y TIEMPO
    conVidas= new vida();
    conVidas->setPos(0,-30);
    scene->addItem(conVidas);

    score = new puntaje();
    score->setPos(h_limit-150,-30);
    scene->addItem(score);

    contador_n1= new tiempo_juego();
    contador_n1->setPos(h_limit/2-50,-30);
    scene->addItem(contador_n1);

//+++++++++++++++++++++++++++

    gener_glob = new tiempo_juego();
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

    if(conVidas->getvidaT()>0)
    {
        if(score->getScore()<7)
        {
            nivel_1->actualizar_nivel(scene,v_limit,h_limit,principal,timer,conVidas,score,gener_glob);
        }

        else if(score->getScore()==7)
        {
            conVidas->increase();
            //timer->stop();
            nivel_1->borrar_elementos(scene);
            nivel_2= new nivel(bars2,muros2,globs,puas2,scene,v_limit);
            principal->setVD(20);
            qDebug()<<"nivel 3";
            score->setScore(8);
            //score->setScore(22);
        }

        else if(score->getScore()>7 && score->getScore()<22)
        {
            nivel_2->actualizar_nivel(scene,v_limit,h_limit,principal,timer,conVidas,score,gener_glob);
        }

        else if(score->getScore()==22)
        {
            conVidas->increase();
            nivel_2->borrar_elementos(scene);
            nivel_3= new nivel(bars3,muros3,globs,puas3,scene,v_limit);
            principal->setVD(20);
            score->setScore(23);
            qDebug()<<"nivel 3";
        }

        else if(score->getScore()>22 && score->getScore()<44)
        {
            nivel_3->actualizar_nivel(scene,v_limit,h_limit,principal,timer,conVidas,score,gener_glob);
        }

        if(score->getScore()==44)
        {
            timer->stop();
        }
    }
    else
    {
        timer->stop();
        scene->removeItem(principal);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    personaje *b = principal;

    if(event->key() == Qt::Key_D)
    {
        b->set_vel(15,b->getVY(),b->getPX(),b->getPY());
        b->setGolpe(true);
    }
    if(event->key() == Qt::Key_A)
    {
        b->set_vel(-15,b->getVY(),b->getPX(),b->getPY());
        b->setGolpe(true);
    }
    if(event->key() == Qt::Key_W && b->getPY()<=b->getR())
    {
        b->set_vel(b->getVX(),40,b->getPX(),b->getPY());
        b->setGolpe(true);
    }
    if((event->key() == Qt::Key_Space && b->getBalas_jugador().size()==0) && b->getGolpe()==true)
    {
        principal->disparo_lis(scene,v_limit);
    }
}
