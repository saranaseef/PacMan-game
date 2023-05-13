#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <mycustomgraphicsview.h>
#include <walls.h>

#include <ground.h>
#include <enemy.h>
#include <coin.h>
#include <home.h>
#include <food.h>
#include <QMediaPlayer>

void initializeArrays(int**& boardArray, int**& Gridtonode, int& numNodes,
                      vector<pair<int,int>>& nodeToGrid, Board***& boardmap);
void initializeGraphics(myCustomGraphicsView& view, QGraphicsScene& scene);
void initializeImages(QPixmap& wall, QPixmap& wall2, QPixmap& wall3, QPixmap& wall4, QPixmap& wall5, QPixmap& wall6,
                      QPixmap& wall7, QPixmap& wall8,  QPixmap& player, QPixmap& home,
                      Board***& boardmap, QGraphicsScene& scene, int** boardArray);
void addToScene(QGraphicsScene& scene, myCustomGraphicsView& view);

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);



    // Needed Variables Declaration
    int **boardArray, **Gridtonode, numNodes;
    vector<pair<int,int>> nodeToGrid;
    Board*** boardmap;
    QPixmap wall, wall2, wall3, wall4, wall5, wall6, wall7, wall8, player, home;
    initializeArrays(boardArray, Gridtonode, numNodes, nodeToGrid, boardmap);
    myCustomGraphicsView view(boardmap, Gridtonode, nodeToGrid, numNodes);
    QGraphicsScene scene;

    initializeGraphics(view, scene);
    initializeImages(wall, wall2, wall3, wall4, wall5, wall6, wall7, wall8,
                     player, home, boardmap, scene, boardArray);
    addToScene(scene, view);

    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("./Theme.mp3"));
    music->setVolume(10);
    music->play();
    return a.exec();
}

void initializeArrays(int**& boardArray, int**& Gridtonode, int& numNodes,
                      vector<pair<int,int>>& nodeToGrid, Board***& boardmap) {
    boardArray = new int* [14];
    for (int i = 0; i < 14; ++i) boardArray[i] = new int[50];

    Gridtonode = new int* [14];
    for (int i = 0; i < 14; ++i) Gridtonode[i] = new int[50];

    numNodes = 0;

    QFile file("actual.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 50; j++) {
            stream >> boardArray[i][j];
            if (boardArray[i][j] > 0) {
                Gridtonode[i][j] = numNodes;
                nodeToGrid.push_back(make_pair(i, j));
                numNodes++;
            }
            else Gridtonode[i][j] = -1;
        }
    }

    boardmap = new Board **[14];
    for (int i = 0; i < 14; ++i) {
        boardmap[i] = new Board * [50];
        for (int j = 0; j < 50; ++j) {
            boardmap[i][j] = new Board();
        }
    }
}

void initializeImages(QPixmap& wall, QPixmap& wall2, QPixmap& wall3, QPixmap& wall4, QPixmap& wall5, QPixmap& wall6,
                      QPixmap& wall7, QPixmap& wall8,  QPixmap& player, QPixmap& home,
                      Board***& boardmap, QGraphicsScene& scene, int** boardArray) {
    wall = QPixmap("./images/Walls/p2.png");
    wall = wall.scaledToWidth(50); wall = wall.scaledToHeight(50);

    wall2 = QPixmap("./images/Walls/p3.png");
    wall2 = wall2.scaledToWidth(50); wall2 = wall2.scaledToHeight(50);

    wall3 = QPixmap("./images/Walls/p4.png");
    wall3 = wall3.scaledToWidth(50); wall3 = wall3.scaledToHeight(50);

    wall4 = QPixmap("./images/Walls/p5.png");
    wall4 = wall4.scaledToWidth(50); wall4 = wall4.scaledToHeight(50);

    wall5 = QPixmap("./images/Walls/p6.png");
    wall5 = wall5.scaledToWidth(50); wall5 = wall5.scaledToHeight(50);

    wall6 = QPixmap("./images/Walls/p7.png");
    wall6 = wall6.scaledToWidth(50); wall6 = wall6.scaledToHeight(50);

    wall7 = QPixmap("./images/Walls/p8.png");
    wall7 = wall7.scaledToWidth(50); wall7 = wall7.scaledToHeight(50);

    wall8 = QPixmap("./images/Walls/p9.png");
    wall8 = wall8.scaledToWidth(50); wall8 = wall8.scaledToHeight(50);

    player = QPixmap("./images/Ground/p1.png");
    player = player.scaledToWidth(50); player = player.scaledToHeight(50);

    home = QPixmap("./images/Ground/h.png");
    home = home.scaledToWidth(50); home = home.scaledToHeight(50);

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 50; j++) {
            switch (boardArray[i][j]) {
            case -1:
                boardmap[i][j] = new Walls(50, 50, wall);
                break;
            case -2:
                boardmap[i][j] = new Walls(50, 50, wall2);
                break;
            case -3:
                boardmap[i][j] = new Walls(50, 50, wall3);
                break;
            case -4:
                boardmap[i][j] = new Walls(50, 50, wall4);
                break;
            case -5:
                boardmap[i][j] = new Walls(50, 50, wall5);
                break;
            case -6:
                boardmap[i][j] = new Walls(50, 50, wall6);
                break;
            case -7:
                boardmap[i][j] = new Walls(50, 50, wall7);
                break;
            case -8:
                boardmap[i][j] = new Walls(50, 50, wall8);
                break;
            case 1:
                boardmap[i][j] = new Coin();
                break;
            case 2:
                boardmap[i][j] = new Home(50, 50, home);
                break;
            case 3:
                boardmap[i][j] = new Food();
                break;
            case 4:
                boardmap[i][j] = new Power();
                break;
            }
            if (i == 0 && j == 0)
                boardmap[i][j]->setPos(50, 50);
            else if (j != 0)
                boardmap[i][j]->setPos(boardmap[i][j - 1]->pos().x() + boardmap[i][j - 1]->boundingRect().width(), boardmap[i][0]->pos().y());
            else
                boardmap[i][j]->setPos(50, boardmap[i - 1][j]->pos().y() + boardmap[i - 1][j]->boundingRect().height());
            scene.addItem(boardmap[i][j]);
        }
    }
}


void initializeGraphics(myCustomGraphicsView& view, QGraphicsScene& scene) {
    view.setWindowTitle("PACMAN: The Ultimate Version");
    view.setFixedSize(1500, 850);
    view.setBackgroundBrush(QBrush(Qt::black));
    QRectF rect = scene.sceneRect();
    rect.setRect(-50, -50, 25000, 700);
    view.verticalScrollBar()->setSliderPosition(0);
    view.horizontalScrollBar()->setSliderPosition(0);
    view.setScene(&scene);
}

void addToScene(QGraphicsScene& scene, myCustomGraphicsView& view) {
    Coin cc;
    cc.setPos(400, 400);

    scene.addItem(view.e1);
    scene.addItem(view.c1);
    scene.addItem(&cc);
    scene.addItem(view.p1);
    scene.addItem(view.healthBoard);
    scene.addItem(view.livestext);
    scene.addItem(view.numOfLives);
    scene.addItem(view.mode);
    scene.addItem(view.scoreText);
    scene.addItem(view.score);
    view.show();
}
