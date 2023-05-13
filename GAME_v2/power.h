#ifndef POWER_H
#define POWER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <board.h>
class Power : public QObject , public Board
{
    int   currentFrame;
    QTimer *spriteTimer;
    QPixmap sprite;
public:
    Power();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

     QRectF boundingRect() const;

    void nextFrame();
};

#endif // POWER_H
