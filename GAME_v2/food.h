#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <board.h>
#include <QTimer>
#include <QDebug>
#include <QPainter>


class Food : public QObject , public Board

{

    int   currentFrame;
    QTimer *spriteTimer;
    QPixmap sprite;

public:
    Food();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

     QRectF boundingRect() const;

    void nextFrame();
};

#endif // FOOD_H
