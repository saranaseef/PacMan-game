#include "coin.h"

Coin::Coin()
{
    currentFrame = 0;   // Sets the coordinates of the current frame of the sprite
    spriteImage = new QPixmap("./images/coin.png"); // Load the sprite image QPixmap
    *spriteImage = spriteImage->scaled(300,50);

    coinTimer = new QTimer();   // Create a timer for sprite animation
    this->setPixmap(*spriteImage);
    connect(coinTimer, &QTimer::timeout, this, &Coin::nextFrame);
    coinTimer->start(125);

}
QRectF Coin::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,0, *spriteImage, currentFrame, 0, 50,50);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Coin::nextFrame()
{

    currentFrame += 50;
        if (currentFrame >= 300 )
            currentFrame = 0;
    this->update(0,0,50,50);
}
