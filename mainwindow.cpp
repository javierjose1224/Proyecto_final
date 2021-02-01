#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QString name,int id_lvl,bool num_pls):ui(new Ui::MainWindow)
{
//    song = new QMediaPlayer;
//    song->setMedia(QUrl("qrc:/audio/Audio/main song.mp3"));
//    song->setVolume(15);
//    song->play();

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
    scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/paisaje_sat.png")));
    ui->graphicsView->resize(scene->width(),scene->height()+20);
    this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+100);

    principal = new personaje(40,0,0,0,20,0.3,0,5,1);//0.3k
    jugadores.push_back(principal);
    principal->actualizar(v_limit);
    scene->addItem(principal);

    segundo_plyr = new personaje(h_limit-40,-0,0,0,20,0.3,0,5,2);
    segundo_plyr->setGolpe(false);
    jugadores.push_back(segundo_plyr);


    score_pasar=0;

//VIDAS, PUNTAJE Y TIEMPO
    conVidas= new vida();
    conVidas->setPos(0,-30);
    conVidas->setVidaT(6);
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
    else if(id_niv==4)
    {
        score->setScore(44);
        is_lineal=false;
    }

    if(num_pls==true)
    {
        conVidas->setVidaT(10);
        segundo_plyr->setPY(0);
        segundo_plyr->actualizar(v_limit);
        scene->addItem(segundo_plyr);
    }

    contador_n1= new tiempo_juego();
    contador_n1->setPos(h_limit/2+100,-30);//-50
    scene->addItem(contador_n1);

    nivel_graf= new hd_nivel();
    nivel_graf->setPos(h_limit/2-200,-30);
    scene->addItem(nivel_graf);
//+++++++++++++++++++++++++++
    gener_glob2 = new tiempo_juego();
    gener_glob = new tiempo_juego();
    timer->start(5);//5
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizarm()));
}

void MainWindow::actualizarm()
{
    gener_glob2->increase();
    gener_glob->increase();
    contador_n1->decrese();
    //contador_n1->increase_graf();
    if(conVidas->getvidaT()>0)
    {
        if(score->getScore()==-1)
        {
            jugadores.at(0)->setGolpe(false);
            jugadores.at(1)->setGolpe(false);

            jugadores.at(0)->setPos(40,0);
            jugadores.at(0)->setPX(40);
            jugadores.at(0)->setPY(0);

            jugadores.at(1)->setPos(h_limit-40,0);
            jugadores.at(1)->setPX(h_limit-40);
            jugadores.at(1)->setPY(0);

        //PELOTAS PARA NIVEL 1
            bars.push_back(new pelota(80,300,10,0,50,40,0,1,2));
            nivel_1=new nivel(bars,muros,globs,puas,scene,v_limit);
            principal->setVD(20);
            segundo_plyr->setVD(20);
            score->setScore(0);
            is_lineal=true;
            contador_n1->setContador(15);
            //contador_n1->reset_neg();
        }
        if(score->getScore()>-1 && score->getScore()<7)
        {
            nivel_1->actualizar_nivel(scene,v_limit,h_limit,jugadores,conVidas,score,gener_glob,gener_glob2);
            if(contador_n1->getCon_abs()==0)
            {
                conVidas->decrease();
                reiniciar_lvl();
            }
        }

        else if(score->getScore()==7)
        {
            jugadores.at(0)->setGolpe(false);
            jugadores.at(1)->setGolpe(false);

            jugadores.at(0)->setPos(40,0);
            jugadores.at(0)->setPX(40);
            jugadores.at(0)->setPY(0);

            jugadores.at(1)->setPos(h_limit-40,0);
            jugadores.at(1)->setPX(h_limit-40);
            jugadores.at(1)->setPY(0);
            tpn=contador_n1->getCon_abs();
            if(is_lineal==true)
            {
                nivel_1->borrar_elementos(scene);
            }
            muros2.push_back(new muro(100,v_limit/2+100,100,100));
            muros2.push_back(new muro(h_limit-200,v_limit/2+100,100,100));

            puas2.push_back(new pua(h_limit/4,25,50,25));
            puas2.push_back(new pua(3*h_limit/4-70,25,50,25));
        //PELOTAS NIVEL 2
            bars2.push_back(new pelota(h_limit/2,300,10,0,50,40,0,1,2));
            bars2.push_back(new pelota(h_limit/2,300,-10,0,50,40,0,1,2));

            nivel_2= new nivel(bars2,muros2,globs,puas2,scene,v_limit);
            principal->setVD(20);
            segundo_plyr->setVD(20);
            nivel_graf->setNivel_graf(2);
//            qDebug()<<"nivel 3";
            score->setScore(8);
            score_pasar=7;
            is_lineal=true;
            //contador_n1->reset_neg();
            contador_n1->setContador(30);
            //score->setScore(22);
        }

        else if(score->getScore()>7 && score->getScore()<22)
        {

            nivel_2->actualizar_nivel(scene,v_limit,h_limit,jugadores,conVidas,score,gener_glob,gener_glob2);
            if(contador_n1->getCon_abs()==0)
            {
                conVidas->decrease();
                reiniciar_lvl();
            }
        }

        else if(score->getScore()==22)
        {
            jugadores.at(0)->setGolpe(false);
            jugadores.at(1)->setGolpe(false);

            jugadores.at(0)->setPos(40,0);
            jugadores.at(0)->setPX(40);
            jugadores.at(0)->setPY(0);

            jugadores.at(1)->setPos(h_limit-40,0);
            jugadores.at(1)->setPX(h_limit-40);
            jugadores.at(1)->setPY(0);
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
            segundo_plyr->setVD(20);
            nivel_graf->setNivel_graf(3);
            score->setScore(23);
            score_pasar=22;
            //contador_n1->reset_neg();
            contador_n1->setContador(60);
            is_lineal=true;
//            qDebug()<<"nivel 3";
        }

        else if(score->getScore()>22 && score->getScore()<44)
        {
            nivel_3->actualizar_nivel(scene,v_limit,h_limit,jugadores,conVidas,score,gener_glob,gener_glob2);
            if(contador_n1->getCon_abs()==0)
            {
                conVidas->decrease();
                reiniciar_lvl();
            }
        }

        else if(score->getScore()==44)
        {
            jugadores.at(0)->setGolpe(false);
            jugadores.at(1)->setGolpe(false);

            jugadores.at(0)->setPos(40,0);
            jugadores.at(0)->setPX(40);
            jugadores.at(0)->setPY(0);

            jugadores.at(1)->setPos(h_limit-40,0);
            jugadores.at(1)->setPX(h_limit-40);
            jugadores.at(1)->setPY(0);
            tpn=contador_n1->getCon_abs();
            if(is_lineal==true)
            {
                nivel_3->borrar_elementos(scene);
            }
            //nivel_1->borrar_elementos(scene);
            bars4.push_back(new pelota((h_limit-100),450,-10,0,50,20,0,1,2));
            bars4.push_back(new pelota(100,450,10,0,50,20,0,1,2));
            bars4.push_back(new pelota((h_limit-150),450,-10,0,50,20,0,1,2));
            bars4.push_back(new pelota(150,450,10,0,50,20,0,1,2));
            bars4.push_back(new pelota((h_limit-200),450,-10,0,50,20,0,1,2));
            bars4.push_back(new pelota(200,450,10,0,50,20,0,1,2));
//            bars4.push_back(new pelota((300)+40,400,10,0,50,40,0,1,2));
//            bars4.push_back(new pelota((300)+80,400,10,0,50,40,0,1,2));

            puas4.push_back(new pua(h_limit/4,25,50,25));
            puas4.push_back(new pua(3*h_limit/4-70,25,50,25));
        //MUROS NIVEL 4
            muros4.push_back(new muro(h_limit/2-50,v_limit,100,440));

            nivel_4= new nivel(bars4,muros4,globs,puas4,scene,v_limit);

            principal->setVD(20);
            principal->setK(0.05);
            segundo_plyr->setK(0.05);
            segundo_plyr->setVD(20);
            nivel_graf->setNivel_graf(4);
            score->setScore(45);
            //score_pasar=22;
            //contador_n1->reset_neg();
            contador_n1->setContador(60);
            is_lineal=true;
        }

        else if(score->getScore()>44 && score->getScore()<63)
        {
            nivel_4->actualizar_nivel(scene,v_limit,h_limit,jugadores,conVidas,score,gener_glob,gener_glob2);
            if(contador_n1->getCon_abs()==0)
            {
                conVidas->decrease();
                reiniciar_lvl();
            }
        }

        if(score->getScore()==63)
        {
            setcheckpoint();
            tpn=contador_n1->getCon_abs();
            timer->stop();
            pasar = new EndGame(nombre_jugador, score->getScore(),contador_n1->getCon_abs(),conVidas->getvidaT(),nivel_graf->getNivel_act(),true);
            pasar->show();
            this->close();
//            song->stop();
        }
    }
    else
    {
        setcheckpoint();
        timer->stop();
        scene->removeItem(jugadores.at(0));
        pasar = new EndGame(nombre_jugador, score->getScore(),contador_n1->getCon_abs(),conVidas->getvidaT(),nivel_graf->getNivel_act(),false);
        pasar->show();
        this->close();
//        song->stop();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{    

        personaje *b = jugadores.at(0);
        personaje *b2 = jugadores.at(1);

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
        if((event->key() == Qt::Key_E && b->getBalas_jugador().size()==0) && b->getGolpe()==true)
        {
            b->disparo_lis(scene,v_limit);
        }

        //CONTROLES DEL SEGUNDO JUGADOR
        if(event->key() == Qt::Key_L && b2->isActive())
        {
            b2->set_vel(15,b2->getVY(),b2->getPX(),b2->getPY());
            b2->setGolpe(true);
        }

        if(event->key() == Qt::Key_J && b2->isActive())
        {
            b2->set_vel(-15,b2->getVY(),b2->getPX(),b2->getPY());
            b2->setGolpe(true);
        }
        if(event->key() == Qt::Key_I && b2->getPY()<=b2->getR() && b2->isActive())
        {
            b2->set_vel(b2->getVX(),40,b2->getPX(),b2->getPY());
            b2->setGolpe(true);
        }
        if((event->key() == Qt::Key_U && b2->getBalas_jugador().size()==0) && b2->getGolpe()==true && b2->isActive())
        {
            b2->disparo_lis(scene,v_limit);
        }



    //CONTROLES JUGADOR PRINCIPAL


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
        QPushButton *salir = msgBox.addButton(tr("Salir"), QMessageBox::RejectRole);        

        msgBox.exec();

        if (msgBox.clickedButton() == discardButton)
        {
            msgBox.close();
            timer->start();
        }
        else if (msgBox.clickedButton() == saveButton) {
            if (nombre_jugador=="Invitado") {
                msm.setText("No puede guardar en modo invitado.\nPara guardar debe registrarse.");
                msm.setIcon(QMessageBox::Warning);
                msm.exec();
                timer->start();
            }
            else {
                setcheckpoint();
                pasar = new EndGame(nombre_jugador, score->getScore(),contador_n1->getCon_abs(),conVidas->getvidaT(),nivel_graf->getNivel_act(),false);
                pasar->show();
                this->close();
//                song->stop();
            }
        }
        else if (msgBox.clickedButton() == restartButton)
        {
            reiniciar_lvl();
            timer->start();
//            qDebug()<<"funciona";
        }
        else if (msgBox.clickedButton() == salir)
        {
            this->close();
        }
        delete restartButton;
        delete saveButton;
        delete discardButton;
        delete salir;

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
    else if(nivel_graf->getNivel_act()==4)
    {
        is_lineal=false;
        nivel_4->borrar_elementos(scene);
        bars4.clear();
        puas4.clear();
        muros4.clear();
        score->setScore(44);
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
    update.append("UPDATE usuarios SET life='"+QString::number(conVidas->getvidaT())+"',score='"+QString::number(score->getScore())+"',nivel='"+QString::number(nivel_graf->getNivel_act())+"',time='"+QString::number(contador_n1->getCon_abs())+"' WHERE name='"+nombre_jugador+"'");
    query.prepare(update);
//        qDebug()<<"(15) - update";
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
//            qDebug()<<"hecho";
//            qDebug()<<"Numero de usuario: "<<query.value(0).toString();
//            qDebug()<<"Nombre: "<<query.value(1).toString();
//            qDebug()<<"Contraseña: "<<query.value(2).toString();
//            qDebug()<<"Vidas: "<<query.value(3).toString();
//            qDebug()<<"Nivel: "<<query.value(5).toString();
//            qDebug()<<"Tiempo: "<<query.value(6).toString();
//            qDebug()<<"Puntaje final: "<<query.value(4).toString();
        }
    }
}


