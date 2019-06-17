#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QListWidgetItem>
#include "gamewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void selectMasterColor();
    void saveGame();
    void loadGame();

private slots:
    void setBackgroundColor();
    void addNewGeneration();
    void renameGeneration();
    void deleteGeneration();
    void setGenerationHints();

private:
    void messageBoxWarningExec(const QString&, const QString&);
    Ui::MainWindow *ui;
    GameWidget* game;
};

#endif // MAINWINDOW_H
