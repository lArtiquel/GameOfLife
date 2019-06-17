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
    m_masterColor = Qt::black;                           //set default color
    m_backgroundColor = Qt::gray;                        //set default background
    timer->setInterval(300);                             //set default timer interval
    generationColor.push_back(m_masterColor);            //set first color black by default
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
            universe[k*universeSize + j] = -1;
        }
    }
    gameEnds(true);
    update();
}

QColor GameWidget::invertBackgroundColor() const
{
    QColor color;
    int h = (m_backgroundColor.hue() + 180) % 360;
    int s = 255 - m_backgroundColor.saturation();
    int v = 255 - m_backgroundColor.value();

    color.setHsv(h, s, v);
    return color;
}

int GameWidget::cellNumber() const
{
    return universeSize;
}

void GameWidget::setCellNumber(const int &s)
{
    universeSize = s;
    resetUniverse();
    update();
}

void GameWidget::resetUniverse()
{
    delete [] universe;
    delete [] next;
    universe = new int[(universeSize + 2) * (universeSize + 2)];
    next = new int[(universeSize + 2) * (universeSize + 2)];
    memset(universe, -1, sizeof(int) * static_cast<unsigned int>(universeSize + 2) * static_cast<unsigned int>(universeSize + 2));
    memset(next, -1, sizeof(int) * static_cast<unsigned int>(universeSize + 2) * static_cast<unsigned int>(universeSize + 2));
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

QString GameWidget::dump() const
{
    QString master = "";
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            master += QString::number(universe[k*universeSize+j], 10) + ' ';
        }
        master.append("\n");
    }
    return master;
}

void GameWidget::setDump(int *&data)
{
    for(int k = 1; k <= universeSize; k++)
        for(int j = 1; j <= universeSize; j++)
            universe[k*universeSize + j] = data[(k-1)*universeSize + j-1];
    update();
}

int GameWidget::interval() const
{
    return timer->interval();
}

void GameWidget::setInterval(int msec)
{
    timer->setInterval(msec);
}

void GameWidget::givePowerAndExtractColors(int& power, int& red, int& green, int& blue, const int& k, const int& j)
{
    power++;
    red += extractRed(universe[k*universeSize + j]);
    green += extractGreen(universe[k*universeSize + j]);
    blue += extractBlue(universe[k*universeSize + j]);
}

int GameWidget::isAlive(int k, int j)
{
    int power = 0, r = 0, g = 0, b = 0;             //power red green blue
                                                    //give some power to cell and extract colors
    if(universe[(k+1)*universeSize + j] != -1) givePowerAndExtractColors(power, r, g, b, k + 1, j);
    if(universe[(k-1)*universeSize + j] != -1) givePowerAndExtractColors(power, r, g, b, k - 1, j);
    if(universe[k*universeSize + (j+1)] != -1) givePowerAndExtractColors(power, r, g, b, k, j + 1);
    if(universe[k*universeSize + (j-1)] != -1) givePowerAndExtractColors(power, r, g, b, k, j - 1);
    if(universe[(k+1)*universeSize + (j-1)] != -1) givePowerAndExtractColors(power, r, g, b, k + 1, j - 1);
    if(universe[(k-1)*universeSize + (j+1)] != -1) givePowerAndExtractColors(power, r, g, b, k - 1, j + 1);
    if(universe[(k-1)*universeSize + (j-1)] != -1) givePowerAndExtractColors(power, r, g, b, k - 1, j - 1);
    if(universe[(k+1)*universeSize +  (j+1)] != -1) givePowerAndExtractColors(power, r, g, b, k + 1, j + 1);
    if (((universe[k*universeSize + j] != -1) && (power == 2)) || (power == 3))
    {
        r = r / power;          //count average color from relatives
        g = g / power;
        b = b / power;
        QColor color(r, g, b);
        return convertQColorToInt(color);
    }
    return -1;
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
        gameEnds(true);
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
    emit environmentChanged(true);                                       //to block universe size
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

    int currentColorInt = convertQColorToInt(m_masterColor);
    if(!isMove)                     //if button was pressed
    {
        if(universe[k*universeSize + j] != currentColorInt)
            universe [k*universeSize + j] = currentColorInt;
        else
            universe [k*universeSize + j] = -1;
    }
    else                            //if button was pressed and moved
    {
        if(prevSelectedCellX != j || prevSelectedCellY != k)
        {
            if(universe[k*universeSize + j] != currentColorInt)
                universe [k*universeSize + j] = currentColorInt;
            else
                universe [k*universeSize + j] = -1;
            prevSelectedCellX = j;
            prevSelectedCellY = k;
        }
    }
    update();
}

void GameWidget::paintGrid(QPainter &p)
{
    QRect borders(widthMargins, heightMargins , gridSize, gridSize);  // set borders of the universe
    QColor gridColor = invertBackgroundColor();                                   // color of the grid
    p.setPen(gridColor);

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
            if(universe[k*universeSize + j] != -1) {                    // if there is any sense to paint it
                int left = x1 + cellWidthAndHeight*(j-1);                    // margin from left
                int top  = y1 + cellWidthAndHeight*(k-1);                    // margin from top
                QRect r(left, top, cellWidthAndHeight, cellWidthAndHeight);
                p.fillRect(r, QBrush(convertIntToQColor(universe[k*universeSize + j]))); // fill cell with brush of main color
            }
        }
    }
}

QColor GameWidget::getMasterColor() const
{
    return m_masterColor;
}

void GameWidget::setMasterColor(const QColor &color)
{
    m_masterColor = color;
    update();
}

QColor GameWidget::getBackgroundColor() const
{
    return m_backgroundColor;
}

void GameWidget::setBackgroundColor(const QColor& backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

void GameWidget::changeCellsOfGenColor(const int prevColor, const int newColor)
{
    for(int k = 1; k <= universeSize; k++)
        for(int j = 1; j <= universeSize; j++)
            if(universe[k*universeSize + j] == prevColor)
                universe[k*universeSize + j] = newColor;
}

void GameWidget::deleteMembersOfGeneration(int color)
{
    for(int k=1; k <= universeSize; k++)
        for(int j=1; j <= universeSize; j++)
            if(universe[k*universeSize + j] == color)
                universe[k*universeSize + j] = -1;
}

int GameWidget::convertQColorToInt(const QColor &color) const
{
    return ((color.red() & 0xff) << 16) + ((color.green() & 0xff) << 8) + (color.blue() & 0xff);
}

QColor GameWidget::convertIntToQColor(const int &rgb) const
{
    int red = 0, green = 0, blue = 0;
    red = (rgb >> 16) & 0xff;
    green = (rgb >> 8) & 0xff;
    blue = rgb & 0xff;
    QColor color(red, green, blue);
    return color;
}

int GameWidget::extractRed(const int& color)
{
   return (color >> 16) & 0xff;
}

int GameWidget::extractGreen(const int& color)
{
   return (color >> 8) & 0xff;
}

int GameWidget::extractBlue(const int& color)
{
   return color & 0xff;
}


