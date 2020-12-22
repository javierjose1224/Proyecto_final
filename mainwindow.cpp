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


//    pisos.push_back(new plataforma(0,10,h_limit,20));
//    pisos.push_back(new plataforma(0,200,h_limit,20));

//    for(int i=0;i<pisos.size();i++)
//    {
//        pisos.at(i)->posicionAbs(v_limit);
//        scene->addItem(pisos.at(i));
//    }

    principal = new personaje(0,0,0,0,50,20,0.3,0,5);
    principal->actualizar(v_limit);

    scene->addItem(principal);

    timer->start(5);
    bars.push_back(new pelota(32,300,10,0,50,40,0,1,2));
    bars.back()->actualizar(v_limit);
    scene->addItem(bars.back());

    bars.push_back(new pelota(32,300,30,0,50,10,0,1,7));
    bars.back()->actualizar(v_limit);
    scene->addItem(bars.back());

    connect(timer,SIGNAL(timeout()),this,SLOT(actualizarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarm()
{
    principal->actualizar(v_limit);
    borderColilisionPer(principal);

    for(int i=0;i<bars.size();i++)
    {
        bars.at(i)->actualizar(v_limit);
        borderColilision(bars.at(i));
    }
}

void MainWindow::borderColilision(pelota *b)
{
    if(b->getPX()<b->getR())
    {
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getR(),b->getPY());
    }
    if(b->getPX()>h_limit-b->getR())
    {
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),h_limit-b->getR(),b->getPY());
    }
    if(b->getPY()<b->getR())
    {
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getR());
    }
    if(b->getPY()>v_limit-b->getR())
    {
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),v_limit-b->getR());
    }
}

void MainWindow::borderColilisionPer(personaje *b)
{
    if(b->getPX()<b->getR())
    {
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getR(),b->getPY());
    }
    if(b->getPX()>h_limit-b->getR())
    {
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),h_limit-b->getR(),b->getPY());
    }
    if(b->getPY()<b->getR())
    {
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getR());
    }
    if(b->getPY()>v_limit-b->getR())
    {
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),v_limit-b->getR());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    personaje *b = principal;
    if(event->key() == Qt::Key_D)
    {
        b->set_vel(15,b->getVY(),b->getPX(),b->getPY());
//        for(auto it=pisos.begin();it!=pisos.end();it++)
//        {
//            if(b->collidesWithItem(*it)){
//                b->set_vel(-15,b->getVY(),b->getPX(),b->getPY());
//            }
//        }
    }
    if(event->key() == Qt::Key_A)
    {
        b->set_vel(-15,b->getVY(),b->getPX(),b->getPY());
    }
    if(event->key() == Qt::Key_W)
    {
        b->set_vel(b->getVX(),40,b->getPX(),b->getPY());
    }
    if(event->key() == Qt::Key_Space)
    {
        proyectil *bullet = new proyectil();
        bullet->setPos(b->getPX(),v_limit-b->getPY());
        scene->addItem(bullet);
    }
}
