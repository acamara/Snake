#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    XTAM = 65;
    YTAM = 40;
    SZ = 12;

    ui->setupUi(this);
    setFixedSize(XTAM*SZ+25,YTAM*SZ+55);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,XTAM*SZ,YTAM*SZ);
    scene->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    view = new MyGraphicView();
    view->setScene(scene);
    connect(view,SIGNAL(changespeed(int,int)),this,SLOT(update_speed(int,int)));
    //view->setRenderHint(QPainter::Antialiasing, true);
    ui->verticalLayout->addWidget(view);
    start_game();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_game(){
    cabeza ={30,20};
    vx = 1;
    vy = 0;
    engorda = 0;
    choque = false;
    comida = al_azar();
    score = 0;

    ui->label_score->setText(QString("%1").arg(score, 5, 10, QLatin1Char('0')));
    ui->pushButton_playagain->setEnabled(false);

    cuadrado(cabeza,Qt::red);
    cuadrado(comida,Qt::yellow);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_state()));
    timer->start(100);
}

void MainWindow::cuadrado(const Punto& p, QColor c){
    pen = QPen(Qt::gray);
    pen.setWidth(1);
    scene->addRect(p.x*SZ,p.y*SZ,SZ,SZ,pen,c);
}

void MainWindow::update_state(){
    cola.push_front(cabeza);

    if(engorda>0){
        engorda--;
    }
    else{
        cola.pop_back();
    }

    cabeza.x+=vx;
    cabeza.y+=vy;

    if(hay_choque(cabeza,cola)){
        choque = true;
    }
    else if (cabeza.x == comida.x && cabeza.y == comida.y){
        engorda = 5;
        score += 5;
        ui->label_score->setText(QString("%1").arg(score, 5, 10, QLatin1Char('0')));
        comida = al_azar();
        while(hay_choque(comida, cola)||(comida.x == cabeza.x && comida.y == cabeza.y)){
            comida = al_azar();
        }
    }

    if(!choque){
        scene->clear();
        QList<Punto>::const_iterator it;
        for(it = cola.begin(); it != cola.end();it++){
            cuadrado(*it,Qt::green);
        }
        cuadrado(cabeza,Qt::red);
        cuadrado(comida,Qt::yellow);
    }
    else{
        timer->stop();
        ui->pushButton_playagain->setEnabled(true);
    }
}

void MainWindow::update_speed(int newvx, int newvy)
{
    //qDebug()<<"nombre de elements a la cua: "<<cola.size();
    if( (((newvx==0 && newvy==-1)&& (vx==0 && vy==1))
       ||((newvx==0 && newvy==1)&& (vx==0 && vy==-1))
       ||((newvx==-1 && newvy==0)&& (vx==1 && vy==0))
       ||((newvx==1 && newvy==0)&& (vx==-1 && vy==0)))
       && cola.size()>0){
        //qDebug()<<"Me intento comer a mi mismo";
    }
    else {
        vx = newvx;
        vy = newvy;
    }
}

bool MainWindow::hay_choque(const Punto& cabeza, const QList<Punto>& cola){
    if(cabeza.x >= XTAM || cabeza.x < 0){
        return true;
    }
    if(cabeza.y >= YTAM || cabeza.y < 0){
        return true;
    }

    QList<Punto>::const_iterator it;
    for(it= cola.begin(); it!=cola.end();it++){
        if(cabeza.x == it->x && cabeza.y == it->y){
            return true;
        }
    }
    return false;
}

Punto MainWindow::al_azar(){
    Punto p = {rand() % XTAM, rand() % YTAM};
    return p;
}

void MainWindow::on_pushButton_playagain_clicked()
{
    scene->clear();
    cola.clear();
    start_game();
}
