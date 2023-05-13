#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPainter>
#include <board.h>
class Coin: public QObject , public Board
{


public:
    int currentFrame;
    QPixmap *spriteImage;
    QTimer *coinTimer;


    Coin();
    void nextFrame();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
  // In this QPixmap object will be placed sprite

};

#endif // COIN_H
