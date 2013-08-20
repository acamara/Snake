#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QGraphicsView>

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QGraphicsView *parent = 0);

signals:
    void changespeed(int newvx, int newvy);
public slots:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MYGRAPHICVIEW_H
