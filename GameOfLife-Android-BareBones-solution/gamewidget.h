#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void countSellAndUpdateIt(const int&, const int&, const bool);

public slots:
    void startGame();  // start
    void nextGeneration();
    void stopGame(); // finish
    void clear();   // clear

private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void newGeneration();

private:
    int widthMargins, heightMargins;                           //margins of gamewidget
    int gridSize;
    int prevSelectedCellX, prevSelectedCellY;
    QTimer* timer;
    bool* universe; // current map(contains color or -1)
    bool* next;     // next map
    int universeSize;
    int isAlive(int k, int j); // return true if universe[k][j] accept rules
    void resetUniverse();      // reset the size of universe
    void countMargins();
};

#endif // GAMEWIDGET_H
