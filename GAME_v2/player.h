#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <walls.h>

#include <coin.h>
#include <home.h>
#include <food.h>


using namespace std;
class Player : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
    QPixmap spritehori, spriteverti,spritehoric, spritevertic, spritehorif, spritevertif, state;


    bool isPowerHolder , isEatable, isFoodHolder, isAllowedToMove,
    appleOneIsEaten, appleTwoIsEaten, appleThreeIsEaten,  appleFourIsEaten;


    char direction;
    int numOfLives, score, applesDel;



    QGraphicsRectItem  * UR, *DR, *RR, *LR ;

    int speed;

    int currentFrame , powerTimeriteirator;

    QTimer *timer, *powerTimer;

    Player();
    void setDirection(char);
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
      void move(char d);
      QRectF boundingRect() const;
      void powerTimerincrement();



     void nextFrame();

};

#endif // PLAYER_H
