#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    void deleteMembersOfGeneration(int);
    int convertQColorToInt(const QColor&) const;  //convertation functions
    QColor convertIntToQColor(const int&) const;
    QVector<QColor> generationColor;        //all colors
    ~GameWidget();

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void countSellAndUpdateIt(const int&, const int&, const bool);

signals:
    //when one of the cell has been changed,emit this signal to lock the universeSize
    void environmentChanged(bool ok);
    //when game is over or clear is called,emit it to unlock the universeSize
    void gameEnds(bool ok);

public slots:
    void startGame();  // start
    void nextGeneration();
    void stopGame(); // finish
    void clear();   // clear

    void setCellNumber(const int &s); // set number of the cells in one row
    void setInterval(int msec); // set interval between generations
    void setBackgroundColor(const QColor&);
public:
    void changeCellsOfGenColor(const int, const int);

    QColor invertBackgroundColor() const;

    int cellNumber() const; // number of the cells in one row

    int interval() const; // interval between generations

    QColor getMasterColor() const; // color of the cells
    void setMasterColor(const QColor&); // set color of the cells

    QColor getBackgroundColor() const;

    QString dump() const; // dump of current universe
    void setDump(int *&data); // set current universe from it's dump

private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void newGeneration();

private:
    int widthMargins, heightMargins;                           //margins of gamewidget
    int gridSize;
    int prevSelectedCellX, prevSelectedCellY;
    QColor m_masterColor;
    QColor m_backgroundColor;
    QTimer* timer;
    int* universe; // current map(contains color or -1)
    int* next;     // next map
    int universeSize;
    void givePowerAndExtractColors(int&, int&, int&, int&, const int&, const int&); //gives power to cell and count its color
    int isAlive(int k, int j); // return true if universe[k][j] accept rules
    void resetUniverse();      // reset the size of universe
    int extractRed(const int&);// extract functions
    int extractGreen(const int&);
    int extractBlue(const int&);
    void countMargins();
};

#endif // GAMEWIDGET_H
