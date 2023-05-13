#include "mycustomgraphicsview.h"

myCustomGraphicsView::myCustomGraphicsView(Board ***boardmap , int **gridtonode, vector <pair<int,int> > &nodetogrid, int numofnode) : QGraphicsView()
{
    board = boardmap;



p1 = new Player();
p1->setPos((50 * 25), (50* 7));


c1 = new Coin();
c1->setPos(300,300);
e1 = new Enemy(p1, gridtonode,nodetogrid,numofnode);
e1->setPos(8 * 50, 50*8);

 penn = QPen(Qt::red);
penn.setWidth(6);
livestext = new QGraphicsTextItem();
numOfLives = new QGraphicsTextItem();
mode = new QGraphicsTextItem();
scoreText = new QGraphicsTextItem();
score = new QGraphicsTextItem();

scaleMeasure = 0.5;
scaleTimer = new QTimer();
textTimer = new QTimer();
foodTimer = new QTimer();
enemyTimer = new QTimer();
connect(foodTimer, &QTimer::timeout, this, &myCustomGraphicsView::updateFood);
connect(scaleTimer, &QTimer::timeout, this, &myCustomGraphicsView::scaleFirst);
connect(textTimer, &QTimer::timeout, this, &myCustomGraphicsView::updateText);
connect(enemyTimer, &QTimer::timeout, e1, &Enemy::updatePath);

healthBoard = new QGraphicsRectItem(800,20, 500,50 );
//connect(enemyTimer, &QTimer::timeout, e1, &Enemy::move(vector<pair<int,int>>));
enemyTimer->start(1000);

e1->movetimer->start(100);


//setting the texts that will appear to the user
livestext->setPos(50* 24, 0 );
// text.setHtml("<b> <u> <font face='Arial' color='white' size='3'>Lifes Remaning  </font></u></b>");
livestext->setDefaultTextColor(Qt::white);
livestext->setFont(QFont("Arial",9));
livestext->setPlainText("Remaining lives: ");
numOfLives->setPos(livestext->pos().x()+livestext->boundingRect().width() ,livestext->pos().y());
numOfLives->setDefaultTextColor(Qt::white);
numOfLives->setFont(QFont("Arial",9));
numOfLives->setPlainText(QString::number(p1->numOfLives));
mode->setPos(livestext->pos().x() - 380 ,livestext->pos().y());
mode->setDefaultTextColor(Qt::yellow);
mode->setFont(QFont("Arial",9));
mode->setPlainText("This is the normal mode ");
scoreText->setPos(numOfLives->pos().x()+ 200  ,numOfLives->pos().y());
scoreText->setDefaultTextColor(Qt::cyan);
scoreText->setFont(QFont("Arial",9));
scoreText->setPlainText("your Score: ");
score->setPos(scoreText->pos().x() + 100 , scoreText->pos().y());
score->setDefaultTextColor(Qt::cyan);
score->setFont(QFont("Arial",9));
score->setPlainText("your Score ");

        textTimer->start(500);
foodTimer->start(150);
}

void myCustomGraphicsView::updateText()
{
    numOfLives->setPlainText(QString::number(p1->numOfLives));
    if (p1->isPowerHolder)
        mode->setPlainText("This is the inivisible mode ");
    else
        mode->setPlainText("This is the normal mode ");
    if (p1->numOfLives <= 0 )
    {mode->setPlainText("You have lost!");

    enemyTimer->stop();
    foodTimer->stop();
    textTimer->stop();
    p1->isAllowedToMove = false;
    p1->state = p1->spritevertif;
    p1->update();
    p1->timer->start(150);

    }
if (p1->applesDel >= 4)
 mode->setPlainText("You have won!");
qDebug () << p1->score<<endl;

score->setPlainText(QString::number(p1->score));
}

void myCustomGraphicsView::updateFood()
{
if (p1->appleOneIsEaten  )
    board[10][3]->setVisible(false);
else board[10][3]->setVisible(true);
if (p1->appleTwoIsEaten )
    board[10][46]->setVisible(false);
else board[10][46]->setVisible(true);
 if (p1->appleThreeIsEaten  )
    board[3][46]->setVisible(false);
 else board[3][46]->setVisible(true);
 if (p1->appleFourIsEaten  )
    board[3][3]->setVisible(false);
 else board[3][3]->setVisible(true);
}

bool myCustomGraphicsView::isCollidingWithWall(char d)
{
    QList<QGraphicsItem*> items;
   switch (d) {
   case 'u':
       items =  scene()->collidingItems( p1->UR);
       break;
   case 'd':
       items =  scene()->collidingItems( p1->DR);
       break;
   case 'r':
        items =  scene()->collidingItems( p1->RR);
       break;
   case 'l':
       items =  scene()->collidingItems( p1->LR);
       break;

   }
   foreach(QGraphicsItem *item, items){




            if(typeid (*item) == typeid (Walls))
            {

                 return true;

            }
            else if (typeid (*item) == typeid (Enemy))
            {
               if (p1->isEatable){
               p1->setPos((50 * 25), (50* 7));
               p1->UR->setPos(pos().x(), pos().y());
               p1->DR->setPos(pos().x(), pos().y());
               p1->RR->setPos(pos().x(), pos().y());
               p1->LR->setPos(pos().x(), pos().y());
               p1->numOfLives--;
               p1-> isFoodHolder = false;

               p1-> appleOneIsEaten = false ;
               p1-> appleTwoIsEaten = false;
                p1->appleThreeIsEaten = false;
                p1->appleFourIsEaten = false;
               }

            }
            else if (typeid (*item) == typeid (Coin))
             {
                p1->score += 5;

                 item->setVisible(false);

             }
            else if (typeid (*item) == typeid(Home))
               {

                if ( p1->isFoodHolder)
                {
                    p1->score += 100;
                    p1->applesDel++;
                }

                    p1->isFoodHolder = false ;


            }
            else if (typeid (*item) == typeid(Food))

            {

               if (item->pos().y() >  500 )
                 {  if (item->pos().x() < 1000)
                    p1->appleOneIsEaten = true;
                  else  p1->appleTwoIsEaten = true;
               }
               else
               {
                   if (item->pos().x() < 1000)
                   p1->appleFourIsEaten = true;
                   else p1->appleThreeIsEaten = true;

               }

               p1->isFoodHolder = true ;

            }

            else if (typeid (*item) == typeid(Power))

            {
                p1->powerTimer->start(1000);
                p1->isEatable = false;
            p1->isPowerHolder = true;
              item->setVisible(false);
            }

   }
   return false;
}

void myCustomGraphicsView::scaleFirst()
{
    if(scaleMeasure >= 1)
        scaleTimer->stop();
    else scaleMeasure += 0.1;
    scale(1.1,1.1);

}

void myCustomGraphicsView::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
    {
       if (event->key() == Qt::Key_Up)
       {
            if (!isCollidingWithWall('u'))
            p1->move('u');
            this->ensureVisible(p1, 500 ,800);
       }
       else if (event->key() == Qt::Key_Down)
       {if (!isCollidingWithWall('d'))
               p1->move('d');;
            this->ensureVisible(p1, 500 ,800);

       }
       else if (event->key() == Qt::Key_Right)
       {

           if (!isCollidingWithWall('r'))
           p1->move('r');
           this->ensureVisible(p1, 500 ,800);

           }
       else if (event->key() == Qt::Key_Left)
       {
           if (!isCollidingWithWall('l'))
           p1->move('l');
            this->ensureVisible(p1, 500 ,800);
       }
       return;
    }
   else if (event->key() == Qt::Key_Up)
    {
         p1->setDirection('u');
         if (!isCollidingWithWall('u'))
         p1->move('u');
        this->ensureVisible(p1, 500 ,800);
        this->p1->update();
        p1->timer->start(40);
    }
    else if (event->key() == Qt::Key_Down)
    {
         p1->setDirection('d');
         if (!isCollidingWithWall('d'))
         p1->move('d');
        this->ensureVisible(p1, 500 ,800);
        this->p1->update();
        p1->timer->start(40);

    }
    else if (event->key() == Qt::Key_Right)
    {
          p1->setDirection('r');
          if (!isCollidingWithWall('r'))
          p1->move('r');
        this->ensureVisible(healthBoard);
        this->ensureVisible(p1, 500 ,800);
        this->p1->update();
        p1->timer->start(40);
    }
    else if (event->key() == Qt::Key_Left)
    {
         p1->setDirection('l');
         if (!isCollidingWithWall('l'))
         p1->move('l');
      this->ensureVisible(p1, 500 ,800);
        this->p1->update();
        p1->timer->start(40);
    }
    else if (event->key() == Qt::Key_I)
    {

       this->scale(0.9,0.9);
    }
    else if (event->key() == Qt::Key_O)
    {
       this->scale(1.1,1.1);
    }

}
void myCustomGraphicsView::keyReleaseEvent(QKeyEvent *event)
{

    if (event->isAutoRepeat())
          return;
     if (event->key() == Qt::Key_Up)
    {
       this->p1->currentFrame = 0;

       this->p1->update();
      // this->p1->timer->stop();
    }
    else if (event->key() == Qt::Key_Down)

     {
       QRectF rectD(p1->pos().x() + 20, (p1->pos().y() + p1->boundingRect().height()) -10 , p1->boundingRect().width() - 40, 5);
       QRectF rectU(p1->pos().x() + 10, p1->pos().y() ,p1->boundingRect().width() - 20, 5);
       QRectF rectL(p1->pos().x(), p1->pos().y() , 5 , p1->boundingRect().height() - 5);
       QRectF rectR((p1->pos().x() + p1->boundingRect().width()) - 5, p1->pos().y()  , 5 , p1->boundingRect().height() - 5);
       QRectF rectfff(p1->pos().x(), p1->pos().y(), p1->boundingRect().width(), p1->boundingRect().height() );

       this->p1->currentFrame = 0;

       this->p1->update();
      // this->p1->timer->stop();

    }
    else if (event->key() == Qt::Key_Right)
    {


         QList<QGraphicsItem*> items = scene()->collidingItems(p1);



        // scene()->addRect(p1->boundingRect());
         QRectF rect(p1->pos().x(), p1->pos().y(), p1->boundingRect().width(), p1->boundingRect().height());
         QRectF otherRect(c1->pos().x(), c1->pos().y(), c1->boundingRect().width(), c1->boundingRect().height());
       // scene()->addRect(rect);
        //scene()->addRect(otherRect);
            for (int i = 0 ; i < items.size(); i++)

                               qDebug() << typeid (*items[i]).name();


       this->p1->currentFrame = 0;

       this->p1->update();
      // this->p1->timer->stop();
    }
    else if (event->key() == Qt::Key_Left)
    {
       this->p1->currentFrame = 0;

       this->p1->update();
      // this->p1->timer->stop();
    }
}
