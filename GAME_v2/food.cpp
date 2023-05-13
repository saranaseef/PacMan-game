#include "food.h"


Food::Food( )
{
    currentFrame = 0;
    sprite = QPixmap("./images/food.png");
   sprite = sprite.scaled(250,50);

    spriteTimer = new QTimer();
    setPixmap(sprite);
    connect(spriteTimer, &QTimer::timeout, this, &Food::nextFrame);
    spriteTimer->start(150);


}
QRectF Food::boundingRect() const
{
    return QRectF(0,0,50,50);

}
void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite,currentFrame, 0, 50,50);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}



void Food::nextFrame() {
    currentFrame += 50;
        if (currentFrame >= 250 )
            currentFrame = 0;
    this->update(0,0,50,50);
        qDebug() << this->pos().x();
}

