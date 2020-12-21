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
//    posx= 32;//50+(rand()%951);
//    posy= 300;//50+(rand()%951);
//    r= 20;//5+(rand()%26);
//    mass= 50;//50+(rand()%651);
//    velx= 10;//0(rand()%300);
//    vely= 0;//(rand()%300);
//    k= 0.0;//(rand()%10)/1000;//0.2
//    e= 1;//(0.5+(rand()%5)/10);//1.17
    //esf= new cuerpo(posx,posy,velx,vely,mass,r,k,e);
    timer->start(5);
    bars.push_back(new pelota(32,300,10,0,50,20,0,1,2));
    bars.back()->actualizar(v_limit);
    scene->addItem(bars.back());

    bars.push_back(new pelota(32,300,30,0,50,8,0,1,7));
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

