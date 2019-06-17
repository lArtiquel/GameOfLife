/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *mainLayout;
    QVBoxLayout *gameLayout;
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
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        gameLayout = new QVBoxLayout();
        gameLayout->setSpacing(6);
        gameLayout->setObjectName(QStringLiteral("gameLayout"));

        mainLayout->addLayout(gameLayout);

        controlLayout = new QHBoxLayout();
        controlLayout->setSpacing(6);
        controlLayout->setObjectName(QStringLiteral("controlLayout"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setMinimumSize(QSize(0, 0));
        startButton->setMaximumSize(QSize(85, 32));

        controlLayout->addWidget(startButton);

        nextButton = new QPushButton(centralWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        nextButton->setMinimumSize(QSize(32, 32));
        nextButton->setMaximumSize(QSize(32, 32));

        controlLayout->addWidget(nextButton);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setMinimumSize(QSize(0, 0));
        stopButton->setMaximumSize(QSize(85, 32));

        controlLayout->addWidget(stopButton);

        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setMinimumSize(QSize(0, 0));
        clearButton->setMaximumSize(QSize(85, 32));

        controlLayout->addWidget(clearButton);


        mainLayout->addLayout(controlLayout);

        mainLayout->setStretch(0, 1);

        verticalLayout_2->addLayout(mainLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Conway's Game of Life", nullptr));
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
