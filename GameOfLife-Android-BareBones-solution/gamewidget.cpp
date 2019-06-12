#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    universe(nullptr),
    next(nullptr),
    universeSize(50)
{
    timer->setInterval(500);                             //set default timer interval
    prevSelectedCellX = -1;
    prevSelectedCellY = -1;
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
    resetUniverse();                                     //set current and next universes and fill them
}

GameWidget::~GameWidget()
{
    delete [] universe;
    delete [] next;
}

void GameWidget::startGame()
{
    timer->start();
}

void GameWidget::nextGeneration()
{
    newGeneration();
}

void GameWidget::stopGame()
{
    timer->stop();
}

void GameWidget::clear()
{
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            universe[k*universeSize + j] = 0;
        }
    }
    update();
}

void GameWidget::resetUniverse()
{
    delete [] universe;
    delete [] next;
    universe = new bool[(universeSize + 2) * (universeSize + 2)];
    next = new bool[(universeSize + 2) * (universeSize + 2)];
    memset(universe, 0, sizeof(bool) * static_cast<unsigned int>(universeSize + 2) * static_cast<unsigned int>(universeSize + 2));
    memset(next, 0, sizeof(bool) * static_cast<unsigned int>(universeSize + 2) * static_cast<unsigned int>(universeSize + 2));
    countMargins();                                                     //always after resizing change margins
}

void GameWidget::countMargins()
{
    int w = width();
    int h = height();

    if(w < h)
    {
        gridSize = w / universeSize * universeSize;
    } else
    {
        gridSize = h / universeSize * universeSize;
    }
    widthMargins = (w - gridSize) / 2;
    heightMargins = (h - gridSize) / 2;
}

int GameWidget::isAlive(int k, int j)
{
    int power = 0;             //power red green blue
                                                    //give some power to cell and extract colors
    if(universe[(k+1)*universeSize + j] != 0) power++;
    if(universe[(k-1)*universeSize + j] != 0) power++;
    if(universe[k*universeSize + (j+1)] != 0) power++;
    if(universe[k*universeSize + (j-1)] != 0) power++;
    if(universe[(k+1)*universeSize + (j-1)] != 0) power++;;
    if(universe[(k-1)*universeSize + (j+1)] != 0) power++;
    if(universe[(k-1)*universeSize + (j-1)] != 0) power++;
    if(universe[(k+1)*universeSize +  (j+1)] != 0) power++;
    if (((universe[k*universeSize + j] != 0) && (power == 2)) || (power == 3)) {
        return 1;
    } else
    return 0;
}

void GameWidget::newGeneration()
{
    int notChanged=0;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            next[k*universeSize + j] = isAlive(k, j);
            if(next[k*universeSize + j] == universe[k*universeSize + j])
                notChanged++;
        }
    }
    if(notChanged == universeSize*universeSize) {
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
        stopGame();
        return;
    }
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            universe[k*universeSize + j] = next[k*universeSize + j];
        }
    }
    update();
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::resizeEvent(QResizeEvent *)
{
    countMargins();
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    int w = width();
    int h = height();
    if (x < w - gridSize - widthMargins ||
            y < h - gridSize - heightMargins ||
            x >= w - widthMargins - 1 ||
            y >= h - heightMargins - 1) return;           //to avoid the free clickeng processing
    countSellAndUpdateIt(x, y, false);
}

void GameWidget::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    int w = width();
    int h = height();

    if (x < w - gridSize - widthMargins ||
            y < h - gridSize - heightMargins ||
            x >= w - widthMargins - 1 ||
            y >= h - heightMargins - 1) return;           //to avoid the free clickeng processing
    countSellAndUpdateIt(x, y, true);
}

void GameWidget::countSellAndUpdateIt(const int& x,const int& y, const bool isMove)
{
    int cellWidthAndHeight = gridSize / universeSize;
    int k = (y - heightMargins) / cellWidthAndHeight + 1;
    int j = (x - widthMargins) / cellWidthAndHeight + 1;

    bool currentColorInt = 1;
    if(!isMove)                     //if button was pressed
    {
        if(universe[k*universeSize + j] != currentColorInt)
            universe [k*universeSize + j] = currentColorInt;
        else
            universe [k*universeSize + j] = 0;
    }
    else                            //if button was pressed and moved
    {
        if(prevSelectedCellX != j || prevSelectedCellY != k)
        {
            if(universe[k*universeSize + j] != currentColorInt)
                universe [k*universeSize + j] = currentColorInt;
            else
                universe [k*universeSize + j] = 0;
            prevSelectedCellX = j;
            prevSelectedCellY = k;
        }
    }
    update();
}

void GameWidget::paintGrid(QPainter &p)
{
    QRect borders(widthMargins, heightMargins , gridSize, gridSize);  // set borders of the universe
    p.setPen(Qt::black);

    int cellWidthAndHeight = gridSize / universeSize;
    int x1 = width() - widthMargins - gridSize;
    int y1 = height() - heightMargins - gridSize;
    int x2 = x1 + gridSize;
    int y2 = y1 + gridSize;

    for(int i = 1; i < universeSize; i++)
    {
        p.drawLine(x1 + i * cellWidthAndHeight, y1, x1 + i * cellWidthAndHeight, y2);       //draw grid lines
        p.drawLine(x1, y1 + i * cellWidthAndHeight, x2, y1 + i * cellWidthAndHeight);
    }

    p.drawRect(borders);                                                //draw borders of universe
}

void GameWidget::paintUniverse(QPainter &p)
{
    int cellWidthAndHeight = gridSize / universeSize;
    int x1 = width() - widthMargins - gridSize;
    int y1 = height() - heightMargins - gridSize;

    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            if(universe[k*universeSize + j] != 0) {                          // if there is any sense to paint it
                int left = x1 + cellWidthAndHeight*(j-1);                    // margin from left
                int top  = y1 + cellWidthAndHeight*(k-1);                    // margin from top
                QRect r(left, top, cellWidthAndHeight, cellWidthAndHeight);
                p.fillRect(r, QBrush(Qt::black));                            // fill cell with brush of main color
            }
        }
    }
}
