#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "mygraphicview.h"

struct Punto{
    int x,y;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void start_game();
    void cuadrado(const Punto &p, QColor c);

public slots:
    void update_state();
    void update_speed(int newvx, int newvy);
    bool hay_choque(const Punto &cabeza, const QList<Punto> &cola);
    Punto al_azar();

private slots:
    void on_pushButton_playagain_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    MyGraphicView *view;
    QTimer *timer;

    QPen pen;
    int XTAM;
    int YTAM;
    int SZ;

    Punto cabeza;
    Punto comida;
    QList<Punto> cola;
    int vx;
    int vy;
    int engorda;
    bool choque;
    int score;
};

#endif // MAINWINDOW_H
