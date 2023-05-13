#include "enemy.h"

Enemy::Enemy(Player * pp, int ** board, vector<pair<int, int>> & grid, int numnodesss) {
    pe = pp;
    currentFrame = 0;
    eh =  QPixmap("./images/sprite/eh.png");
    evu =  QPixmap("./images/sprite/evu.png");
    evd =  QPixmap("./images/sprite/evd.png");

    eh = eh.scaled(120,40);
    evu = evu.scaled(120,40);
    evd = evd.scaled(120,40);
    state = eh;
    setPixmap(state);

    rows = 14; columns = 50; speed = 10;
    boardData = board;
    nodeToGrid = grid;
    numNodes = numnodesss;

    movetimer = new QTimer();

    connect(movetimer, &QTimer::timeout, this, &Enemy::changePos);
    connect(movetimer, &QTimer::timeout, this, &Enemy::nextFrame);

}

Enemy::Enemy()
{}

vector<pair<int,int>> Enemy::findPath(pair<int,int> start, pair<int,int> end,
                   int rows, int columns) {
    // initialize adjacency list
    vector<vector<int>> adj(numNodes);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (boardData[i][j] != -1) {
            if (boardData[i - 1][j] != -1)
                adj[boardData[i][j]].push_back(boardData[i - 1][j]);
             if (boardData[i + 1][j] != -1)
                adj[boardData[i][j]].push_back(boardData[i + 1][j]);
             if (boardData[i][j - 1] != -1)
                adj[boardData[i][j]].push_back(boardData[i][j - 1]);
             if (boardData[i][j + 1] != -1)
                adj[boardData[i][j]].push_back(boardData[i][j + 1]);
        }
    priority_queue<pair<int,int>> q; // first is the negative of the cost, second is the node
    vector<bool> visited(numNodes, 0);
    vector<pair<int,int>> path(numNodes, {1e9,-1}); // first is the cost, second is the previous

    int node = boardData[start.first][start.second];
    int nodeFinal = boardData[end.first][end.second];
    // Dijkstra's
    path[node].first = 0;
    q.push({ 0, node });
    while (!q.empty()) {
        int a = q.top().second; q.pop();
        if (visited[a]) continue;
        visited[a] = true;
        for (auto u : adj[a]) if (!visited[u]){
            if (path[a].first + 1 < path[u].first) {
                path[u].first = path[a].first + 1;
                path[u].second = a;
                q.push({ -1 * path[u].first, u });
            }
        }
    }

    vector<int> patho;
    patho.push_back(nodeFinal);
    int previous = path[nodeFinal].second;
    while (previous != node) {
        patho.push_back(previous);
        if (previous != -1) previous = path[previous].second;
        else return {};
    }
    reverse(patho.begin(), patho.end());

    int pathSize = patho.size();
    vector<pair<int,int>> finalPath(pathSize);
    for (int i = 0; i < pathSize; i++) finalPath[i] = nodeToGrid[patho[i]];
    return finalPath;
}

void Enemy::updatePath() {
    index = 0;
    start.first = (int)(pos().y() /50.0) - 1;
    start.second = (int)(pos().x()/ 50.0) - 1;
    end.first = (int)((pe->pos().y() + 20.0) / 50.0) - 1;
    end.second = (int)((pe->pos().x() +20.0 ) / 50.0)  - 1;

    if (end == make_pair(6,24) || end == make_pair(7,24)
            || end == make_pair(6,25) || end == make_pair(7,25))
        return;
    path = findPath(start,end,rows,columns);
}

void Enemy::nextFrame() {
    currentFrame = (currentFrame + 40 >= 120 ? 0 : currentFrame + 40);
    this->update(0,0,40,40);
}

void Enemy::changePos() {
    pair<int,int> enemyPos = make_pair((int)((pos().y() + 20.0)/50.0) -1,(int)((pos().x() + 20.0)/50.0) -1 );
    pair<int,int> playerPos = make_pair((int)((pe->pos().y() + 20) / 50.0) -1,  (int)((pe->pos().x() +20 ) / 50.0)  - 1);
    if (enemyPos == playerPos && pe->isEatable) {
        if (pe->numOfLives <= 1) {
            pe->numOfLives = 0;
            movetimer->stop();
            return;
        }
        pe->setPos((50 * 25), (50* 7));
        pe->UR->setPos(pos().x(), pos().y());
        pe->DR->setPos(pos().x(), pos().y());
        pe->RR->setPos(pos().x(), pos().y());
        pe->LR->setPos(pos().x(), pos().y());
        pe->numOfLives--;
        pe->isFoodHolder = false;

        pe-> appleOneIsEaten = false;
        pe-> appleTwoIsEaten = false;
        pe->appleThreeIsEaten = false;
        pe->appleFourIsEaten = false;
    }
    if (!path.empty()) index = (index) % path.size();
    if (!path.empty()) {
        pair<double, double> from = { pos().x(), pos().y() };
        pair<double, double> to = {(path[index].second + 1) * 50, (path[index].first + 1) * 50};
        if (from.first < to.first) moveWithDir('r');
        else if (from.first > to.first) moveWithDir('l');
        else if (from.second < to.second) moveWithDir('d');
        else if (from.second > to.second) moveWithDir('u');

        if (from == to) index++;
    }
}


void Enemy::moveWithDir(char dir) {
    switch (dir) {
    case 'u':
        state = evu;
        setPos(x() , y() - speed);
        break;
    case 'd':
        state = evd;
        setPos(x() , y() + speed);
        break;
    case 'r':
        state = eh;
        setTransform(QTransform());
        setPos(x() + speed , y());
        break;
    case 'l':
        state = eh;
         setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        setPos(x() - speed, y());
        break;
    }
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, state,currentFrame, 0, 40,40);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Enemy::boundingRect() const {
      return QRectF(0,0,40,40);
}

