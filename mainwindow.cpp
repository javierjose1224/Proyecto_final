#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QString name,int id_lvl):ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nombre_jugador=name;

    id_niv=id_lvl;

    h_limit=1000;
    v_limit= 500;

    timer=new QTimer(this);
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);
    //scene->setBackgroundBrush(Qt::yellow);

    ui->graphicsView->setScene(scene);
    ui->centralwidget ->adjustSize();
    scene->addRect(scene->sceneRect());//para ver los limites de la escne
    ui->graphicsView->resize(scene->width(),scene->height()+20);
    this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+100);

    principal = new personaje(h_limit/2,0,0,0,20,0.3,0,5);//0.3k
    jugadores.push_back(principal);

    segundo_plyr = new personaje(h_limit/2,0,0,0,20,0.3,0,5);
    jugadores.push_back(segundo_plyr);

    principal->actualizar(v_limit);
    scene->addItem(principal);

    score_pasar=0;

//NIVEL 1
{
//PUAS PARA NIVEL 1
//    puas.push_back(new pua(3*h_limit/4,25,50,25));


//PELOTAS PARA NIVEL 1

//    bars.push_back(new pelota(80,300,10,0,50,40,0,1,2));

}

//NIVEL 2
{
//MUROS NIVEL 2
//    muros2.push_back(new muro(100,v_limit/2,100,100));
//    muros2.push_back(new muro(h_limit-200,v_limit/2,100,100));


//PELOTAS NIVEL 2
//    bars2.push_back(new pelota(20,300,10,0,50,40,0,1,2));
//    bars2.push_back(new pelota(80,300,10,0,50,40,0,1,2));
}

//NIVEL 3
{
//PELOTAS NIVEL 3
//    bars3.push_back(new pelota((300),400,10,0,50,40,0,1,2));
//    bars3.push_back(new pelota((300)+40,400,10,0,50,40,0,1,2));
//    bars3.push_back(new pelota((300)+80,400,10,0,50,40,0,1,2));

//MUROS NIVEL 3
//    muros3.push_back(new muro(100,v_limit/2,100,100));
//    muros3.push_back(new muro(h_limit-200,v_limit/2,100,100));
//    muros3.push_back(new muro(h_limit/2-50,v_limit/3,100,50));
}
//    nivel_1=new nivel(bars,muros,globs,puas,scene,v_limit);

//VIDAS, PUNTAJE Y TIEMPO
    conVidas= new vida();
    conVidas->setPos(0,-30);
    scene->addItem(conVidas);

    score = new puntaje();
    //score->setScore(score_in);
    score->setPos(h_limit-100,-30);//-150
    scene->addItem(score);

    if(id_niv==1)
    {
        score->setScore(-1);
        is_lineal=false;
    }
    else if(id_niv==2)
    {
        score->setScore(7);
        is_lineal=false;
    }
    else if(id_niv==3)
    {
        score->setScore(22);
        is_lineal=false;
    }

    contador_n1= new tiempo_juego();
    contador_n1->setPos(h_limit/2+100,-30);//-50
    scene->addItem(contador_n1);

    nivel_graf= new hd_nivel();
    nivel_graf->setPos(h_limit/2-200,-30);
    scene->addItem(nivel_graf);
//+++++++++++++++++++++++++++

    gener_glob = new tiempo_juego();
    timer->start(5);//5
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizarm()));
}

void MainWindow::actualizarm()
{
    gener_glob->increase();
    contador_n1->decrese();
    //contador_n1->increase_graf();
    if(conVidas->getvidaT()>0)
    {
        if(score->getScore()==-1)
        {
            puas.push_back(new pua(3*h_limit/4,25,50,25));
        //PELOTAS PARA NIVEL 1
            bars.push_back(new pelota(80,300,10,0,50,40,0,1,2));
            nivel_1=new nivel(bars,muros,globs,puas,scene,v_limit);
            score->setScore(0);
            is_lineal=true;
            contador_n1->setContador(15);
            //contador_n1->reset_neg();
        }
        if(score->getScore()>-1 && score->getScore()<7)
        {
            nivel_1->actualizar_nivel(scene,v_limit,h_limit,jugadores.at(0),timer,conVidas,score,gener_glob);
        }

        else if(score->getScore()==7)
        {
            tpn=contador_n1->getCon_abs();
            if(is_lineal==true)
            {
                nivel_1->borrar_elementos(scene);
            }
            muros2.push_back(new muro(100,v_limit/2,100,100));
            muros2.push_back(new muro(h_limit-200,v_limit/2,100,100));

        //PELOTAS NIVEL 2
            bars2.push_back(new pelota(20,300,10,0,50,40,0,1,2));
            bars2.push_back(new pelota(80,300,10,0,50,40,0,1,2));

            nivel_2= new nivel(bars2,muros2,globs,puas2,scene,v_limit);
            principal->setVD(20);
            nivel_graf->setNivel_graf(2);
            qDebug()<<"nivel 3";
            score->setScore(8);
            score_pasar=7;
            is_lineal=true;
            //contador_n1->reset_neg();
            contador_n1->setContador(30);
            //score->setScore(22);
        }

        else if(score->getScore()>7 && score->getScore()<22)
        {
            nivel_2->actualizar_nivel(scene,v_limit,h_limit,jugadores.at(0),timer,conVidas,score,gener_glob);
        }

        else if(score->getScore()==22)
        {
            tpn=contador_n1->getCon_abs();
            if(is_lineal==true)
            {
                nivel_2->borrar_elementos(scene);
            }
            //nivel_1->borrar_elementos(scene);
            bars3.push_back(new pelota((300),400,10,0,50,40,0,1,2));
            bars3.push_back(new pelota((300)+40,400,10,0,50,40,0,1,2));
            bars3.push_back(new pelota((300)+80,400,10,0,50,40,0,1,2));

        //MUROS NIVEL 3
            muros3.push_back(new muro(100,v_limit/2+100,100,100));
            muros3.push_back(new muro(h_limit-200,v_limit/2+100,100,100));
            muros3.push_back(new muro(h_limit/2-50,v_limit/3,100,50));

            nivel_3= new nivel(bars3,muros3,globs,puas3,scene,v_limit);

            principal->setVD(20);
            nivel_graf->setNivel_graf(3);
            score->setScore(23);
            score_pasar=22;
            //contador_n1->reset_neg();
            contador_n1->setContador(60);
            is_lineal=true;
            qDebug()<<"nivel 3";
        }

        else if(score->getScore()>22 && score->getScore()<44)
        {
            nivel_3->actualizar_nivel(scene,v_limit,h_limit,jugadores.at(0),timer,conVidas,score,gener_glob);
        }

        if(score->getScore()==44)
        {
            tpn=contador_n1->getCon_abs();
            timer->stop();
            pasar = new EndGame(nombre_jugador, score->getScore(),contador_n1->getCon_abs(),conVidas->getvidaT(),nivel_graf->getNivel_act());
            pasar->show();
            this->close();
        }
    }
    else
    {
        timer->stop();
        scene->removeItem(jugadores.at(0));
        pasar = new EndGame(nombre_jugador, score->getScore(),contador_n1->getCon_abs(),conVidas->getvidaT(),nivel_graf->getNivel_act());
        pasar->show();
        this->close();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    personaje *b = jugadores.at(0);
    personaje *b2 = jugadores.at(1);

    //CONTROLES JUGADOR PRINCIPAL
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
    if((event->key() == Qt::Key_F && b->getBalas_jugador().size()==0) && b->getGolpe()==true)
    {
        b->disparo_lis(scene,v_limit);
    }

    //CONTROLES DEL SEGUNDO JUGADOR
    if(event->key() == Qt::Key_L)
    {
        b->set_vel(15,b->getVY(),b->getPX(),b->getPY());
        b->setGolpe(true);
    }

    if(event->key() == Qt::Key_J)
    {
        b2->set_vel(-15,b2->getVY(),b2->getPX(),b2->getPY());
        b2->setGolpe(true);
    }
    if(event->key() == Qt::Key_I && b2->getPY()<=b2->getR())
    {
        b2->set_vel(b2->getVX(),40,b2->getPX(),b2->getPY());
        b2->setGolpe(true);
    }
    if((event->key() == Qt::Key_H && b2->getBalas_jugador().size()==0) && b2->getGolpe()==true)
    {
        b2->disparo_lis(scene,v_limit);
    }

//    if(event->key() == Qt::Key_Z)
//    {
//        iniciar_juego = new sesion(score->getScore(),contador_n1->getCon_abs());
//        this->close();
//        iniciar_juego->show();
//    }
}

void MainWindow::on_pushButton_clicked()
{
    if(timer->isActive())
    {
        timer->stop();
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText("Pausa");
        QPushButton *saveButton = msgBox.addButton(tr("Salir y guardar partida"), QMessageBox::AcceptRole);
        QPushButton *restartButton = msgBox.addButton(tr("Reiniciar Nivel"), QMessageBox::RejectRole);
        QPushButton *discardButton = msgBox.addButton(tr("Volver al juego"), QMessageBox::RejectRole);

        msgBox.exec();
        if (msgBox.clickedButton() == discardButton)
        {
            msgBox.close();
            timer->start();
        }
        else if (msgBox.clickedButton() == saveButton) {
            setcheckpoint();
            this->close();
        }
        else if (msgBox.clickedButton() == restartButton)
        {
            reiniciar_lvl();
            timer->start();
            qDebug()<<"funciona";
        }
        delete restartButton;
        delete saveButton;
        delete discardButton;

    }
}

void MainWindow::reiniciar_lvl()
{
    if(nivel_graf->getNivel_act()==1)
    {
        is_lineal=false;
        nivel_1->borrar_elementos(scene);
        bars.clear();
        muros.clear();
        puas.clear();
        score->setScore(-1);
    }
    else if(nivel_graf->getNivel_act()==2)
    {
        is_lineal=false;
        nivel_2->borrar_elementos(scene);
        bars2.clear();
        muros2.clear();
        puas2.clear();
        score->setScore(7);
    }
    else if(nivel_graf->getNivel_act()==3)
    {
        is_lineal=false;
        nivel_3->borrar_elementos(scene);
        bars3.clear();
        puas3.clear();
        muros3.clear();
        score->setScore(22);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setcheckpoint()
{
    QString update;
    QSqlQuery query;

    //life
    update.append("UPDATE usuarios SET life='"+QString::number(conVidas->getvidaT())+"',score='"+QString::number(score_pasar)+"',nivel='"+QString::number(nivel_graf->getNivel_act())+"',time='"+QString::number(tpn)+"' WHERE name='"+nombre_jugador+"'");
    query.prepare(update);
        qDebug()<<"(15) - update";
    if(query.exec()){
//            qDebug()<<"(15) - Exitoso";
        if(query.next()){
//                qDebug()<<"hecho";
        }
    }else{
//            qDebug()<<"(15) - Error";
    }
    update.clear();

    QString consultarDato;
    consultarDato.append("SELECT * FROM usuarios WHERE name='"+nombre_jugador+"'");
    query.prepare(consultarDato);
//    qDebug()<<"(6) - consultar";
    if(query.exec()){
//        qDebug()<<"(6) - Exitoso";
        if (query.next()) {
            qDebug()<<"hecho";
            qDebug()<<"Numero de usuario: "<<query.value(0).toString();
            qDebug()<<"Nombre: "<<query.value(1).toString();
            qDebug()<<"Contraseña: "<<query.value(2).toString();
            qDebug()<<"Vidas: "<<query.value(3).toString();
            qDebug()<<"Nivel: "<<query.value(5).toString();
            qDebug()<<"Tiempo: "<<query.value(6).toString();
            qDebug()<<"Puntaje final: "<<query.value(4).toString();
        }
    }else{
//                qDebug()<<"(15) - Error";
    }
    this->close();
}


