#ifndef ENEMY_H
#define ENEMY_H
#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <player.h>
#include <QDebug>

using namespace std;
class Enemy :public QObject , public QGraphicsPixmapItem {
     Q_OBJECT
public:
    QPixmap state, eh , evu, evd;
    int currentFrame;

    Player *pe;
    Enemy(Player * pp , int **, vector<pair<int, int>> &, int );
    Enemy();
    QTimer *movetimer;

    pair<int,int> start;
    pair<int,int> end;
    int** boardData;
    vector<pair<int,int>> nodeToGrid;
    vector<pair<int,int>> path;
    int numNodes, rows, columns, index, speed;
    void changePos();
    vector<pair<int,int>> findPath(pair<int,int> start, pair<int,int> end, int rows, int columns);
    void moveWithDir(char dir);
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
     QRectF boundingRect() const;

public slots :
    void updatePath();

     void nextFrame();
};
#endif // ENEMY_H
