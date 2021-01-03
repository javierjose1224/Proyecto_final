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
    pisos.push_back(new plataforma(h_limit/2,v_limit/2,200,50));
    //pisos.push_back(new plataforma(h_limit/8,v_limit/3,200,50));

    principal = new personaje(h_limit/2,0,0,0,50,20,0.3,0,5);//0.3

    bars.push_back(new pelota(32,300,10,0,50,40,0,1,2));
    bars.push_back(new pelota(32,300,30,0,50,10,0,1,7));
    bars.push_back(new pelota(32,300,10,0,50,20,0,1,1));

    nivel_1=new nivel(bars,principal,pisos);

    //AÑADIDO DE LOS ELEMENTOS EN LA ESCENA
    for(int i=0;i<nivel_1->getFloors().size();i++)
    {
        nivel_1->getFloors().at(i)->posicionAbs(v_limit);
        scene->addItem(nivel_1->getFloors().at(i));
    }

    for(int i=0;i<nivel_1->getBalls().size();i++)
    {
        nivel_1->getBalls().at(i)->actualizar(v_limit);
        scene->addItem(nivel_1->getBalls().at(i));
    }

    nivel_1->getProtag()->actualizar(v_limit);
    scene->addItem(nivel_1->getProtag());
    //++++++++++++++++++++++++++++++++++++++++++++
    timer->start(5);
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarm()
{
    nivel_1->getProtag()->actualizar(v_limit);
    borderColilisionPer(nivel_1->getProtag());
    for(int i=0;i<nivel_1->getFloors().size();i++)
    {
        if(nivel_1->getProtag()->collidesWithItem(nivel_1->getFloors().at(i)))
        {
            if(nivel_1->getProtag()->getPY()>2*(nivel_1->getFloors().at(i)->getPosY()))
            {
                nivel_1->getProtag()->set_Newvel(nivel_1->getProtag()->getVX(),-1*nivel_1->getProtag()->getE()*nivel_1->getProtag()->getVY());
                nivel_1->getProtag()->setPY(2*(nivel_1->getFloors().at(i)->getPosY())+nivel_1->getProtag()->getR());
            }
            else if(nivel_1->getProtag()->getPY()<2*(nivel_1->getFloors().at(i)->getPosY()))
            {
                nivel_1->getProtag()->set_Newvel(nivel_1->getProtag()->getVX(),-1*nivel_1->getProtag()->getVY());
                //nivel_1->getProtag()->setPY(pisos.at(i)->getPosY());
                qDebug()<<"POSICION EN Y DE EL MURO debajo"<<pisos.at(i)->getPosY();
            }
//            if(nivel_1->getProtag()->getPX()>2*(pisos.at(i)->getPosX()))
//            {
//                 principal->set_vel(-1*principal->getE()*principal->getVX(),principal->getVY(),-2*(pisos.at(i)->getPosX())-principal->getR(),principal->getPY());
//                 qDebug()<<"POSICION EN X DE EL MURO izq"<<pisos.at(i)->getPosX();
//            }
//            else if(principal->getPX()<2*(pisos.at(i)->getPosX()))
//            {
//                principal->set_Newvel(-1*principal->getE()*principal->getVX(),principal->getVY());
//            }
            //qDebug()<<"POSICION EN Y DE EL MURO "<<pisos.at(i)->getPosY();
        }
    }
    for(int i=0;i<nivel_1->getBalls().size();i++)
    {
        if(nivel_1->getProtag()->collidesWithItem(nivel_1->getBalls().at(i)))
        {
            if(conVidas->getvidaT()>0)
            {
                conVidas->decrease();
                qDebug()<<"Me golpeo";
                nivel_1->getProtag()->setPos(0,0);
                nivel_1->getProtag()->setPX(0);
                nivel_1->getProtag()->setPY(0);
            }
            else
            {                               
                scene->removeItem(nivel_1->getProtag());
                timer->stop();
                nivel_1->~nivel();
            }
        }
    }
    for(int i=0;i<nivel_1->getBalls().size();i++)
    {
        nivel_1->getBalls().at(i)->actualizar(v_limit);
        borderColilision(nivel_1->getBalls().at(i));
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
    personaje *b = nivel_1->getProtag();
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
        proyectil *bullet = new proyectil(v_limit);
        bullet->setPos(b->getPX(),v_limit-b->getPY());
        scene->addItem(bullet);
    }
}
