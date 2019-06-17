#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include <QInputDialog>
#include <QListWidget>
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

    pixmap.fill(Qt::black);                         // reuse pixmap for color button icon
    icon.addPixmap(pixmap);
    ui->colorButton->setIcon(icon);

    ui->listWidget->addItem("default generation");              // add default generation
    ui->listWidget->setCurrentItem(ui->listWidget->item(0));    // selection flags at designer
    ui->listWidget->currentItem()->setIcon(icon);

    pixmap.fill(Qt::gray);                          // reuse for background color
    icon.addPixmap(pixmap);
    ui->backgroundColor->setIcon(icon);

    // connect signals
    connect(ui->startButton, SIGNAL(clicked()), game, SLOT(startGame()));
    connect(ui->startButton, SIGNAL(clicked(bool)), ui->deleteItemButton, SLOT(setDisabled(bool)));
    connect(ui->nextButton, SIGNAL(clicked(bool)), ui->deleteItemButton, SLOT(setDisabled(bool)));
    connect(ui->nextButton, SIGNAL(clicked()), game, SLOT(nextGeneration()));
    connect(ui->stopButton, SIGNAL(clicked()), game, SLOT(stopGame()));
    connect(ui->clearButton, SIGNAL(clicked()), game, SLOT(clear()));
    connect(ui->iterInterval, SIGNAL(valueChanged(int)), game, SLOT(setInterval(int)));
    connect(ui->cellsControl, SIGNAL(valueChanged(int)), game, SLOT(setCellNumber(int)));
    connect(game, SIGNAL(environmentChanged(bool)),ui->cellsControl, SLOT(setDisabled(bool)));
    connect(game, SIGNAL(gameEnds(bool)),ui->cellsControl, SLOT(setEnabled(bool)));
    connect(game, SIGNAL(gameEnds(bool)),ui->deleteItemButton, SLOT(setEnabled(bool)));
    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));
    connect(ui->backgroundColor, SIGNAL(clicked()), this, SLOT(setBackgroundColor()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));
    connect(ui->addItemButton, SIGNAL(clicked()), this, SLOT(addNewGeneration()));
    connect(ui->renameItemButton, SIGNAL(clicked()), this, SLOT(renameGeneration()));
    connect(ui->deleteItemButton, SIGNAL(clicked()), this, SLOT(deleteGeneration()));
    connect(ui->listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(setGenerationHints()));

    ui->gameLayout->addWidget(game);                            // and add new widget
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::saveGame()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save current game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game *.life Files (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    file.write((QString::number(game->cellNumber())+"\n").toUtf8());              //write num cells
    file.write(game->dump().toUtf8());                                            //write dump of map
    file.write((QString::number(ui->listWidget->count())+"\n").toUtf8());         //write number of generations
    for(int i=0; i<ui->listWidget->count(); i++)                                  //for each gen
    {  
        file.write((QString::number(game->generationColor[i].red())+" "+          //write colors of generations
                    QString::number(game->generationColor[i].green())+" "+
                    QString::number(game->generationColor[i].blue())+" ").toUtf8());
        file.write((ui->listWidget->item(i)->text()+"\n").toUtf8());              //write names of generations
    }

    QString buf ="";
    QColor color = game->getBackgroundColor();                                    //write background color
    buf = QString::number(color.red())+" "+
          QString::number(color.green())+" "+
          QString::number(color.blue())+"\n";
    file.write(buf.toUtf8());
    buf.clear();

    buf = QString::number(ui->iterInterval->value())+"\n";                        //write interval
    file.write(buf.toUtf8());
    file.close();
}

void MainWindow::loadGame()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open saved game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game Of Life File (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    //read and set number of cells
    int sv;
    in >> sv;
    ui->cellsControl->setValue(sv);

    //read and set map this size
    const int constSize = sv*sv;
    int *dump = new int[constSize];
    for(int k=0; k != constSize; k++) {
        in >> dump[k];
    }
    game->setDump(dump);
    delete[] dump;

    int numOfGenerations;                           //read and set number of colors
    in >> numOfGenerations;

    ui->listWidget->clear();                        //clear all previous data from listWidget
    game->generationColor.clear();                  //clear vector of colors

    //read and set names of generations and rgb colors in loop
    int r,g,b;                                      // RGB color
    for(int i=0; i<numOfGenerations; i++)
    {
        in >> r >> g >> b;                          // read rgb of generation
        QColor color(r,g,b);                        // create such color
        game->generationColor.push_back(color);     // push color into vector of colors

        QString genName = in.readLine();            // read name of generation
        genName.remove(0, 1);                       // remove first ' '
        ui->listWidget->addItem(genName);           // add new generation of readed name

        QPixmap icon(16,16);                        // create pixmap obj
        icon.fill(color);                           // fill it with such color
        ui->listWidget->item(i)->setIcon(QIcon(icon));// set it's color icon
    }

    game->setMasterColor(QColor(r,g,b));            // set last color as master
    ui->listWidget->setCurrentItem(ui->listWidget->item(ui->listWidget->count()-1));  //set last readed item as current
    QPixmap icon(16, 16);                           // icon on the color button
    icon.fill(game->getMasterColor());              // fill with new color
    ui->colorButton->setIcon( QIcon(icon) );        // set icon for button

    //read and set rgb background
    in >> r >> g >> b;                              // read background color
    //set backgroung color with hints
    QColor color(r,g,b);
    game->setBackgroundColor(color);                //set new background color at game class
    QColor invertedBackgroundColor = game->invertBackgroundColor();
    ui->universeSize->setStyleSheet(QString("color: %1").arg(invertedBackgroundColor.name()));      //set stylesheets for labels and groupboxes
    ui->interval->setStyleSheet(QString("color: %1").arg(invertedBackgroundColor.name()));
    ui->generationsGroupBox->setStyleSheet(QString("color: %1").arg(invertedBackgroundColor.name()));

    QPalette p(ui->centralWidget->palette());       //create object of palette class
    p.setColor(QPalette::Background, color);        //set new color on palette
    ui->centralWidget->setAutoFillBackground(true); //set autofill background
    ui->centralWidget->setPalette(p);               //set new palette on widget

    icon.fill(color);
    ui->backgroundColor->setIcon(QIcon(icon));      //set new icon for backgroundColor button

    //read and set interval
    in >> r;                                 // r will be interval number
    ui->iterInterval->setValue(r);
    game->setInterval(r);
    file.close();
    emit game->environmentChanged(true);     //lock universe size
}

void MainWindow::selectMasterColor()
{
    QColor color = QColorDialog::getColor(game->getMasterColor(), this, tr("Select color of cells generations"));
    if(!color.isValid())
        return;

    for(int i = 0; i < game->generationColor.size(); i++)
    {
        if(color == game->generationColor[i])
        {
            messageBoxWarningExec("Warning", "Such generation with this color exists\nChoose new!");
            return;
        }
    }

    game->changeCellsOfGenColor(game->convertQColorToInt(game->generationColor.at(ui->listWidget->currentRow())), game->convertQColorToInt(color));   //replace prev color with new choosen color
    game->generationColor.remove(ui->listWidget->currentRow());         // remove prev color
    game->generationColor.insert(ui->listWidget->currentRow(), color);  // set new color to vector
    game->setMasterColor(color);                                        // set new master
    QPixmap pixmap(16, 16);                                   // change icon
    pixmap.fill(color);
    QIcon icon(pixmap);                              // create icon
    ui->colorButton->setIcon(icon);                  // set icon on color button
    ui->listWidget->currentItem()->setIcon(icon);    // and also set icon in listWidget
}

void MainWindow::setBackgroundColor()
{
    QColor color = QColorDialog::getColor(game->getMasterColor(), this, tr("Select Background Color"));
    if(!color.isValid())
       return;

    game->setBackgroundColor(color);                //set new background color at game class
    QColor invertedBackgroundColor = game->invertBackgroundColor();
    ui->universeSize->setStyleSheet(QString("color: %1").arg(invertedBackgroundColor.name()));
    ui->interval->setStyleSheet(QString("color: %1").arg(invertedBackgroundColor.name()));
    ui->generationsGroupBox->setStyleSheet(QString("color: %1").arg(invertedBackgroundColor.name()));

    QPalette p(ui->centralWidget->palette());       //create object of palette class
    p.setColor(QPalette::Background, color);        //set new color on palette
    ui->centralWidget->setAutoFillBackground(true); //set autofill background
    ui->centralWidget->setPalette(p);               //set new palette on widget

    QPixmap icon(16, 16);                           //change icon
    icon.fill(color);
    ui->backgroundColor->setIcon(QIcon(icon));
}

void MainWindow::addNewGeneration()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add generation!\n"),
                                         tr("New generation name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (!ok) return;                                                                //if it's not ok
    if(text.isEmpty())                                                              //it cannot be empty string
    {
        messageBoxWarningExec("Warning", "Please, name generation!");
        return;
    }

    for(int i = 0; i < ui->listWidget->count();i++)                                   //search in listview for such generations
    {
        if(ui->listWidget->item(i)->text() == text)
        {
            messageBoxWarningExec("Warning", "Such generation exists!");
            return;
        }
    }

    QColor color;                                                                   //now choose color for generation
    while(1)
    {
        bool isColorValid = true;
        color = QColorDialog::getColor(game->getMasterColor(), this, "Select color for such generation");
        if(!color.isValid())
        {
            messageBoxWarningExec("Warning", "Color is not valid! Try again!");
            continue;
        }

        for(int i = 0; i < game->generationColor.size(); i++)                                   //search in listview for such generations
        {
            if(color == game->generationColor.at(i))
            {
                messageBoxWarningExec("Warning", "Such color exists!\nYou can't have TWO same colors at one time!\nChoose new color!");
                isColorValid = false;
                break;
            }
        }

        if(isColorValid) break;
    }

    ui->listWidget->addItem(text);                                                    //add new item
    ui->listWidget->setCurrentItem(ui->listWidget->item(ui->listWidget->count()-1));  //set new current

    QPixmap pixmap(16, 16);                                                           //create pixmap for item icon
    pixmap.fill(color);
    QIcon icon(pixmap);                                                               //fill pixmap with color
    ui->listWidget->currentItem()->setIcon(icon);                                     //set new icon of black color
    ui->colorButton->setIcon(icon);
    game->setMasterColor(color);                                                      //set new master color
    game->generationColor.push_back(color);                                           //color by default push into vector
}

void MainWindow::renameGeneration()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Rename generation!\n"),
                                         tr("New generation name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (!ok) return;
    if(text.isEmpty())
    {
        messageBoxWarningExec("Warning", "Name connot be empty string!");
        return;
    }

    for(int i = 0; i<ui->listWidget->count();i++)
    {
        if(ui->listWidget->currentItem()->text() == text)
        {
            messageBoxWarningExec("Warning", "Such generation exists!");
            return;
        }
    }

    ui->listWidget->currentItem()->setText(text);     //change generation name
}

void MainWindow::deleteGeneration()
{
    if(ui->listWidget->count() == 1)
    {
        messageBoxWarningExec("Warning", "You cannot delete last generation!");
        return;
    } else
    {
        game->deleteMembersOfGeneration(game->convertQColorToInt(game->generationColor[ui->listWidget->currentRow()])); //remove all members of generation
        game->generationColor.remove(ui->listWidget->currentRow());                      //remove color from vector
        if(ui->listWidget->currentRow() == 0)
        {
            ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
            delete ui->listWidget->takeItem(0);
            return;
        }
        delete ui->listWidget->takeItem(ui->listWidget->currentRow());                                                             //delete from list of gui
    }
}

void MainWindow::setGenerationHints()
{
    game->setMasterColor(game->generationColor[ui->listWidget->currentRow()]) ; //set new current color
    QIcon icon(ui->listWidget->currentItem()->icon());                              //get icon from listWidget item
    ui->colorButton->setIcon(icon);                                                 //set new cell button color
}

void MainWindow::messageBoxWarningExec(const QString& title, const QString& message)
{
    QMessageBox info(QMessageBox::Icon::Warning,
                     title,
                     message,
                     QMessageBox::StandardButton::Cancel,
                     this);
    info.exec();
}






