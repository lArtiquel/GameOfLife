/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *mainLayout;
    QVBoxLayout *gameLayout;
    QVBoxLayout *setLayout;
    QSpacerItem *verticalSpacer;
    QLabel *universeSize;
    QSpinBox *cellsControl;
    QLabel *interval;
    QSpinBox *iterInterval;
    QHBoxLayout *fileLayout;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QGroupBox *generationsGroupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QVBoxLayout *generationButtonsLayout;
    QPushButton *addItemButton;
    QPushButton *renameItemButton;
    QPushButton *colorButton;
    QPushButton *deleteItemButton;
    QPushButton *backgroundColor;
    QHBoxLayout *controlLayout;
    QPushButton *startButton;
    QPushButton *nextButton;
    QPushButton *stopButton;
    QPushButton *clearButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(810, 500);
        MainWindow->setMinimumSize(QSize(810, 500));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setSizeIncrement(QSize(0, 0));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setMaximumSize(QSize(111111, 111111));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        mainLayout = new QHBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        gameLayout = new QVBoxLayout();
        gameLayout->setSpacing(6);
        gameLayout->setObjectName(QStringLiteral("gameLayout"));

        mainLayout->addLayout(gameLayout);

        setLayout = new QVBoxLayout();
        setLayout->setSpacing(6);
        setLayout->setObjectName(QStringLiteral("setLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        setLayout->addItem(verticalSpacer);

        universeSize = new QLabel(centralWidget);
        universeSize->setObjectName(QStringLiteral("universeSize"));

        setLayout->addWidget(universeSize);

        cellsControl = new QSpinBox(centralWidget);
        cellsControl->setObjectName(QStringLiteral("cellsControl"));
        cellsControl->setMinimum(10);
        cellsControl->setMaximum(400);
        cellsControl->setValue(50);

        setLayout->addWidget(cellsControl);

        interval = new QLabel(centralWidget);
        interval->setObjectName(QStringLiteral("interval"));

        setLayout->addWidget(interval);

        iterInterval = new QSpinBox(centralWidget);
        iterInterval->setObjectName(QStringLiteral("iterInterval"));
        iterInterval->setMinimum(50);
        iterInterval->setMaximum(100000);
        iterInterval->setSingleStep(10);
        iterInterval->setValue(300);

        setLayout->addWidget(iterInterval);

        fileLayout = new QHBoxLayout();
        fileLayout->setSpacing(6);
        fileLayout->setObjectName(QStringLiteral("fileLayout"));
        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QStringLiteral("loadButton"));

        fileLayout->addWidget(loadButton);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        fileLayout->addWidget(saveButton);


        setLayout->addLayout(fileLayout);

        generationsGroupBox = new QGroupBox(centralWidget);
        generationsGroupBox->setObjectName(QStringLiteral("generationsGroupBox"));
        generationsGroupBox->setMinimumSize(QSize(0, 180));
        generationsGroupBox->setMaximumSize(QSize(111111, 180));
        gridLayout = new QGridLayout(generationsGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        listWidget = new QListWidget(generationsGroupBox);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMinimumSize(QSize(180, 0));
        listWidget->setMaximumSize(QSize(180, 16777215));
        listWidget->setFrameShape(QFrame::StyledPanel);
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

        horizontalLayout->addWidget(listWidget);

        generationButtonsLayout = new QVBoxLayout();
        generationButtonsLayout->setSpacing(6);
        generationButtonsLayout->setObjectName(QStringLiteral("generationButtonsLayout"));
        generationButtonsLayout->setContentsMargins(5, -1, -1, -1);
        addItemButton = new QPushButton(generationsGroupBox);
        addItemButton->setObjectName(QStringLiteral("addItemButton"));
        addItemButton->setMinimumSize(QSize(90, 0));
        addItemButton->setMaximumSize(QSize(90, 16777215));

        generationButtonsLayout->addWidget(addItemButton);

        renameItemButton = new QPushButton(generationsGroupBox);
        renameItemButton->setObjectName(QStringLiteral("renameItemButton"));
        renameItemButton->setMinimumSize(QSize(90, 0));
        renameItemButton->setMaximumSize(QSize(90, 16777215));

        generationButtonsLayout->addWidget(renameItemButton);

        colorButton = new QPushButton(generationsGroupBox);
        colorButton->setObjectName(QStringLiteral("colorButton"));
        colorButton->setMaximumSize(QSize(90, 16777215));

        generationButtonsLayout->addWidget(colorButton);

        deleteItemButton = new QPushButton(generationsGroupBox);
        deleteItemButton->setObjectName(QStringLiteral("deleteItemButton"));
        deleteItemButton->setMinimumSize(QSize(90, 0));
        deleteItemButton->setMaximumSize(QSize(90, 16777215));

        generationButtonsLayout->addWidget(deleteItemButton);


        horizontalLayout->addLayout(generationButtonsLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        setLayout->addWidget(generationsGroupBox);

        backgroundColor = new QPushButton(centralWidget);
        backgroundColor->setObjectName(QStringLiteral("backgroundColor"));

        setLayout->addWidget(backgroundColor);

        controlLayout = new QHBoxLayout();
        controlLayout->setSpacing(6);
        controlLayout->setObjectName(QStringLiteral("controlLayout"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setMinimumSize(QSize(85, 32));
        startButton->setMaximumSize(QSize(85, 32));

        controlLayout->addWidget(startButton);

        nextButton = new QPushButton(centralWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        nextButton->setMinimumSize(QSize(32, 32));
        nextButton->setMaximumSize(QSize(32, 32));

        controlLayout->addWidget(nextButton);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setMinimumSize(QSize(85, 32));
        stopButton->setMaximumSize(QSize(85, 32));

        controlLayout->addWidget(stopButton);

        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setMinimumSize(QSize(85, 32));
        clearButton->setMaximumSize(QSize(85, 32));

        controlLayout->addWidget(clearButton);


        setLayout->addLayout(controlLayout);


        mainLayout->addLayout(setLayout);

        mainLayout->setStretch(0, 1);

        gridLayout_2->addLayout(mainLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Conway's Game of Life", nullptr));
        universeSize->setText(QApplication::translate("MainWindow", "Universe Size", nullptr));
        cellsControl->setSuffix(QApplication::translate("MainWindow", " cells", nullptr));
        interval->setText(QApplication::translate("MainWindow", "Generation interval (in msec)", nullptr));
        iterInterval->setSuffix(QApplication::translate("MainWindow", " ms", nullptr));
        loadButton->setText(QApplication::translate("MainWindow", "Load", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "Save", nullptr));
        generationsGroupBox->setTitle(QApplication::translate("MainWindow", "Generations", nullptr));
        addItemButton->setText(QApplication::translate("MainWindow", "Add new", nullptr));
        renameItemButton->setText(QApplication::translate("MainWindow", "Rename", nullptr));
        colorButton->setText(QApplication::translate("MainWindow", "Color", nullptr));
        deleteItemButton->setText(QApplication::translate("MainWindow", "Delete current", nullptr));
        backgroundColor->setText(QApplication::translate("MainWindow", "Select background color", nullptr));
        startButton->setText(QApplication::translate("MainWindow", "Start", nullptr));
        nextButton->setText(QString());
        stopButton->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
