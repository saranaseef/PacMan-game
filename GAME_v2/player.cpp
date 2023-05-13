#include "player.h"

Player::Player()
{
    speed = 10;
    currentFrame = 0;

    spritehori =  QPixmap("./images/sprite/shh.png");
    spriteverti =  QPixmap("./images/sprite/svv.png");
    spritehoric =  QPixmap("./images/sprite/shc.png");
    spritevertic =  QPixmap("./images/sprite/svc.png");
    spritehorif =  QPixmap("./images/sprite/shf.png");
    spritevertif =  QPixmap("./images/sprite/svf.png");


     direction = 'r';
     spritehori = spritehori.scaled(280,40);
     spriteverti = spriteverti.scaled(280,40);
     spritehoric = spritehoric.scaled(280,40);
     spritevertic= spritevertic.scaled(280,40);
     spritehorif = spritehorif.scaled(280,40);
     spritevertif= spritevertif.scaled(280,40);

     state = spritehori;
     setPixmap(state);

     UR = new QGraphicsRectItem(pos().x() +20, pos().y(), 10, 0);
     DR = new QGraphicsRectItem(pos().x() +20, pos().y() + 40, 10, 0);
     RR = new QGraphicsRectItem(pos().x() + 40, pos().y()+ 20,0 , 10);
     LR = new QGraphicsRectItem(pos().x()  , pos().y()+20,10, 0);
isPowerHolder = false;
isFoodHolder = false;
           numOfLives = 4;
        timer = new QTimer();
        powerTimer = new QTimer();
        connect(timer, &QTimer::timeout, this, &Player::nextFrame);

        connect(powerTimer, &QTimer::timeout, this, &Player::powerTimerincrement);

appleOneIsEaten = false;
appleTwoIsEaten = false;
appleThreeIsEaten = false;
appleFourIsEaten = false;
isEatable = true;

isAllowedToMove = true;
score = 0;
powerTimeriteirator = 0;
applesDel = 0;

}

void Player::setDirection(char d)
{
    switch (d) {
    case 'u' :
    {
        if (isPowerHolder)
            state = spritevertic;
       else if (isFoodHolder)
       state = spritevertif;
        else
             state = spriteverti;
         setTransform(QTransform());
        direction = 'u';
            break;
    }
    case 'd' :
    {if (isPowerHolder)
            state = spritevertic;
       else if (isFoodHolder)
       state = spritevertif;
        else
             state = spriteverti;

       setTransform(QTransform(1, 0, 0, -1, 0, boundingRect().height()));
        direction = 'd';
            break;
    }
    case 'r' :
    {
        if (isPowerHolder)
           state = spritehoric;
        else if (isFoodHolder)
               state = spritehorif;
       else
           state = spritehori;

            direction = 'r';
     setTransform(QTransform());
     break;
    }
    case 'l' :
    {
        if (isPowerHolder)
           state = spritehoric;
        else if (isFoodHolder)
               state = spritehorif;
       else
           state = spritehori;

            direction = 'l';
     setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
     break;
    }
    }
}
QRectF Player::boundingRect() const
{
    return QRectF(0,0,40,40);
}

void Player::powerTimerincrement()
{
    powerTimeriteirator += 5;
    if (powerTimeriteirator >= 50)
    {
        powerTimer->stop(); powerTimeriteirator = 0; isEatable = true;
      isPowerHolder = false;
    }

}


void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{

    painter->drawPixmap(0,0, state,currentFrame, 0, 40,40);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
void Player::nextFrame()
{

    currentFrame += 40;
        if (currentFrame >= 280 )
            currentFrame = 0;
    this->update(this->pos().x(), this->pos().y(),40,40);
        qDebug() << this->pos().x();
}
void Player::move(char d)
{
    if (isAllowedToMove){
// this 40 in the add is the dimension of the player it is only added in the down and right move
    if (d == 'u'   )
    {
        setPos(x() , y()-speed);
        qDebug() << (this->x() ) << "," << (this->y()  );
    }
    else if (d == 'd'  )
    {
        setPos(x() , y() + speed);

        qDebug() << (this->x() ) << "," << (this->y()  );

    }
    else if (d == 'r'   )
    {
    setPos(x() +speed , y());

    qDebug() << (this->x() ) << "," << (this->y()  );



    }
    else if (d == 'l'    )
    {
        setPos(x() -speed, y());

        qDebug() << (this->x() ) << "," << (this->y()  );
    }
  UR->setPos(pos().x(), pos().y());
  DR->setPos(pos().x(), pos().y());
  RR->setPos(pos().x(), pos().y());
  LR->setPos(pos().x(), pos().y());
}
}



