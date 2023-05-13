#include "power.h"

Power::Power()
{
    currentFrame = 0;
    sprite = QPixmap("./images/power.png");
   sprite = sprite.scaled(400,50);

    spriteTimer = new QTimer();
    setPixmap(sprite);
    connect(spriteTimer, &QTimer::timeout, this, &Power::nextFrame);
    spriteTimer->start(150);

}

void Power::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite,currentFrame, 0, 50,50);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Power::boundingRect() const
{
    return QRectF(0,0,50,50);

}

void Power::nextFrame()
{
    currentFrame += 50;
        if (currentFrame >= 250 )
            currentFrame = 0;
    this->update(0, 0,50,50);
        qDebug() << this->pos().x();
}
