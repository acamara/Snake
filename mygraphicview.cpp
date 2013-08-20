#include "mygraphicview.h"
#include <QKeyEvent>
#include <QDebug>

MyGraphicView::MyGraphicView(QGraphicsView *parent) :
    QGraphicsView(parent)
{

}

void MyGraphicView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            //qDebug()<<"Up";
            emit changespeed(0,-1);
        break;
        case Qt::Key_Down:
            //qDebug()<<"Down";
            emit changespeed(0,1);
        break;
        case Qt::Key_Left:
            //qDebug()<<"Left";
            emit changespeed(-1,0);
        break;
        case Qt::Key_Right:
            //qDebug()<<"Right";
            emit changespeed(1,0);
        break;
    }
}

