#ifndef MYCUSTOMGRAPHICSVIEW_H
#define MYCUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QEvent>
#include <QScrollBar>
#include <QtDebug>
#include "player.h"
#include <QAbstractScrollArea>
#include <coin.h>
#include <QObject>
#include <enemy.h>
#include <string>
#include <power.h>

class myCustomGraphicsView :   public QGraphicsView
{
      Q_OBJECT

public:
     Player *p1;
     Coin *c1;

     Enemy *e1;
     QPen penn;
     QRectF rectU;
     QTimer *scaleTimer, *textTimer, *foodTimer, *enemyTimer;
     QGraphicsRectItem * healthBoard;
     Board *** board;
     float scaleMeasure;
QGraphicsTextItem *livestext, *numOfLives, *mode, *scoreText, *score;
     myCustomGraphicsView(Board ***boardmap,int **gridtonode, vector <pair<int,int> > &nodetogrid, int numofnode);
     void updateText();
     void updateFood();
     void updatePlayer();
     bool isCollidingWithWall(char );



public slots :
    void scaleFirst();
    void keyPressEvent(QKeyEvent* event);

     void keyReleaseEvent(QKeyEvent *event);

};

#endif // MYCUSTOMGRAPHICSVIEW_H
