#include <QDebug>
#include <QColor>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(new GameWidget(this))
{
    ui->setupUi(this);

    QPixmap pixmap(16, 16);                         //create pixmap
    QIcon icon;                                     //create icon object

    pixmap.load(":/images/next-button", ".jpg");    // load it and use for next button
    icon.addPixmap(pixmap);
    ui->nextButton->setIcon(icon);                  // and set

    // connect signals
    connect(ui->startButton, SIGNAL(clicked()), game, SLOT(startGame()));
    connect(ui->nextButton, SIGNAL(clicked()), game, SLOT(nextGeneration()));
    connect(ui->stopButton, SIGNAL(clicked()), game, SLOT(stopGame()));
    connect(ui->clearButton, SIGNAL(clicked()), game, SLOT(clear()));



    ui->gameLayout->addWidget(game);                            // and add new widget
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}




