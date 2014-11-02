/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *player1;
    QFrame *line;
    QLabel *p1_lab_rob;
    QLabel *p1_lab_cont;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *p1_lab_rightX;
    QLabel *lab_rightY;
    QVBoxLayout *verticalLayout_7;
    QLCDNumber *p1_val_rightX;
    QLCDNumber *p1_val_rightY;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *p1_lab_but;
    QLabel *p1_val_but;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *p1_lab_leftX;
    QLabel *p1_lab_leftY;
    QVBoxLayout *verticalLayout_5;
    QLCDNumber *p1_val_leftX;
    QLCDNumber *p1_val_leftY;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *p1_lab_ipAdd;
    QLabel *p1_val_ipAdd;
    QHBoxLayout *horizontalLayout_6;
    QLabel *p1_lab_robStat;
    QLabel *p1_val_robStat;
    QHBoxLayout *horizontalLayout_7;
    QLabel *p1_lab_robMod;
    QLabel *p1_val_robMod;
    QHBoxLayout *horizontalLayout_8;
    QLabel *p1_lab_teamCol;
    QLabel *p1_val_teamCol;
    QPushButton *p1_conCont;
    QWidget *tab_2;
    QListWidget *debugList;
    QProgressBar *scanProg;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QListWidget *clientList;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *ipBox;
    QPushButton *connect2robot;
    QPushButton *Scan4robot;
    QPushButton *cancelButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(720, 588);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(20, 360, 671, 171));
        player1 = new QWidget();
        player1->setObjectName(QStringLiteral("player1"));
        line = new QFrame(player1);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(240, 0, 91, 161));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        p1_lab_rob = new QLabel(player1);
        p1_lab_rob->setObjectName(QStringLiteral("p1_lab_rob"));
        p1_lab_rob->setGeometry(QRect(120, 0, 61, 21));
        QFont font;
        font.setPointSize(18);
        p1_lab_rob->setFont(font);
        p1_lab_cont = new QLabel(player1);
        p1_lab_cont->setObjectName(QStringLiteral("p1_lab_cont"));
        p1_lab_cont->setGeometry(QRect(400, 0, 101, 21));
        p1_lab_cont->setFont(font);
        layoutWidget_2 = new QWidget(player1);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(500, 40, 164, 56));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        p1_lab_rightX = new QLabel(layoutWidget_2);
        p1_lab_rightX->setObjectName(QStringLiteral("p1_lab_rightX"));

        verticalLayout_6->addWidget(p1_lab_rightX);

        lab_rightY = new QLabel(layoutWidget_2);
        lab_rightY->setObjectName(QStringLiteral("lab_rightY"));

        verticalLayout_6->addWidget(lab_rightY);


        horizontalLayout_3->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        p1_val_rightX = new QLCDNumber(layoutWidget_2);
        p1_val_rightX->setObjectName(QStringLiteral("p1_val_rightX"));
        p1_val_rightX->setDigitCount(6);

        verticalLayout_7->addWidget(p1_val_rightX);

        p1_val_rightY = new QLCDNumber(layoutWidget_2);
        p1_val_rightY->setObjectName(QStringLiteral("p1_val_rightY"));
        p1_val_rightY->setDigitCount(6);

        verticalLayout_7->addWidget(p1_val_rightY);


        horizontalLayout_3->addLayout(verticalLayout_7);

        layoutWidget = new QWidget(player1);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(570, 120, 86, 15));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        p1_lab_but = new QLabel(layoutWidget);
        p1_lab_but->setObjectName(QStringLiteral("p1_lab_but"));

        horizontalLayout_5->addWidget(p1_lab_but);

        p1_val_but = new QLabel(layoutWidget);
        p1_val_but->setObjectName(QStringLiteral("p1_val_but"));

        horizontalLayout_5->addWidget(p1_val_but);

        layoutWidget1 = new QWidget(player1);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(300, 40, 156, 56));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        p1_lab_leftX = new QLabel(layoutWidget1);
        p1_lab_leftX->setObjectName(QStringLiteral("p1_lab_leftX"));

        verticalLayout_3->addWidget(p1_lab_leftX);

        p1_lab_leftY = new QLabel(layoutWidget1);
        p1_lab_leftY->setObjectName(QStringLiteral("p1_lab_leftY"));

        verticalLayout_3->addWidget(p1_lab_leftY);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        p1_val_leftX = new QLCDNumber(layoutWidget1);
        p1_val_leftX->setObjectName(QStringLiteral("p1_val_leftX"));
        p1_val_leftX->setDigitCount(6);
        p1_val_leftX->setProperty("value", QVariant(5));

        verticalLayout_5->addWidget(p1_val_leftX);

        p1_val_leftY = new QLCDNumber(layoutWidget1);
        p1_val_leftY->setObjectName(QStringLiteral("p1_val_leftY"));
        p1_val_leftY->setDigitCount(6);

        verticalLayout_5->addWidget(p1_val_leftY);


        horizontalLayout_2->addLayout(verticalLayout_5);

        layoutWidget2 = new QWidget(player1);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 30, 156, 108));
        verticalLayout_4 = new QVBoxLayout(layoutWidget2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        p1_lab_ipAdd = new QLabel(layoutWidget2);
        p1_lab_ipAdd->setObjectName(QStringLiteral("p1_lab_ipAdd"));
        p1_lab_ipAdd->setMinimumSize(QSize(80, 20));
        p1_lab_ipAdd->setMaximumSize(QSize(80, 20));

        horizontalLayout_4->addWidget(p1_lab_ipAdd);

        p1_val_ipAdd = new QLabel(layoutWidget2);
        p1_val_ipAdd->setObjectName(QStringLiteral("p1_val_ipAdd"));

        horizontalLayout_4->addWidget(p1_val_ipAdd);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        p1_lab_robStat = new QLabel(layoutWidget2);
        p1_lab_robStat->setObjectName(QStringLiteral("p1_lab_robStat"));
        p1_lab_robStat->setMinimumSize(QSize(80, 20));
        p1_lab_robStat->setMaximumSize(QSize(80, 20));

        horizontalLayout_6->addWidget(p1_lab_robStat);

        p1_val_robStat = new QLabel(layoutWidget2);
        p1_val_robStat->setObjectName(QStringLiteral("p1_val_robStat"));

        horizontalLayout_6->addWidget(p1_val_robStat);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        p1_lab_robMod = new QLabel(layoutWidget2);
        p1_lab_robMod->setObjectName(QStringLiteral("p1_lab_robMod"));
        p1_lab_robMod->setMinimumSize(QSize(80, 20));
        p1_lab_robMod->setMaximumSize(QSize(80, 20));

        horizontalLayout_7->addWidget(p1_lab_robMod);

        p1_val_robMod = new QLabel(layoutWidget2);
        p1_val_robMod->setObjectName(QStringLiteral("p1_val_robMod"));

        horizontalLayout_7->addWidget(p1_val_robMod);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        p1_lab_teamCol = new QLabel(layoutWidget2);
        p1_lab_teamCol->setObjectName(QStringLiteral("p1_lab_teamCol"));
        p1_lab_teamCol->setMinimumSize(QSize(80, 20));
        p1_lab_teamCol->setMaximumSize(QSize(80, 20));

        horizontalLayout_8->addWidget(p1_lab_teamCol);

        p1_val_teamCol = new QLabel(layoutWidget2);
        p1_val_teamCol->setObjectName(QStringLiteral("p1_val_teamCol"));

        horizontalLayout_8->addWidget(p1_val_teamCol);


        verticalLayout_4->addLayout(horizontalLayout_8);

        p1_conCont = new QPushButton(player1);
        p1_conCont->setObjectName(QStringLiteral("p1_conCont"));
        p1_conCont->setGeometry(QRect(310, 110, 101, 23));
        tabWidget->addTab(player1, QString());
        layoutWidget->raise();
        line->raise();
        p1_lab_rob->raise();
        p1_lab_cont->raise();
        layoutWidget_2->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        p1_conCont->raise();
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        debugList = new QListWidget(tab_2);
        debugList->setObjectName(QStringLiteral("debugList"));
        debugList->setGeometry(QRect(0, 0, 581, 131));
        tabWidget->addTab(tab_2, QString());
        scanProg = new QProgressBar(centralWidget);
        scanProg->setObjectName(QStringLiteral("scanProg"));
        scanProg->setGeometry(QRect(220, 330, 118, 23));
        scanProg->setMaximum(255);
        scanProg->setValue(0);
        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 10, 331, 311));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        clientList = new QListWidget(layoutWidget3);
        clientList->setObjectName(QStringLiteral("clientList"));

        verticalLayout_2->addWidget(clientList);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ipBox = new QLineEdit(layoutWidget3);
        ipBox->setObjectName(QStringLiteral("ipBox"));

        horizontalLayout->addWidget(ipBox);

        connect2robot = new QPushButton(layoutWidget3);
        connect2robot->setObjectName(QStringLiteral("connect2robot"));

        horizontalLayout->addWidget(connect2robot);

        Scan4robot = new QPushButton(layoutWidget3);
        Scan4robot->setObjectName(QStringLiteral("Scan4robot"));

        horizontalLayout->addWidget(Scan4robot);

        cancelButton = new QPushButton(layoutWidget3);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        tabWidget->raise();
        scanProg->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        p1_lab_rob->setText(QApplication::translate("MainWindow", "Robot", 0));
        p1_lab_cont->setText(QApplication::translate("MainWindow", "Controller", 0));
        p1_lab_rightX->setText(QApplication::translate("MainWindow", "Right Stick: X-axis", 0));
        lab_rightY->setText(QApplication::translate("MainWindow", "Right Stick: Y-axis", 0));
        p1_lab_but->setText(QApplication::translate("MainWindow", "Button", 0));
        p1_val_but->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        p1_lab_leftX->setText(QApplication::translate("MainWindow", "Left Stick: X-axis", 0));
        p1_lab_leftY->setText(QApplication::translate("MainWindow", "Left Stick: Y-axis", 0));
        p1_lab_ipAdd->setText(QApplication::translate("MainWindow", "IP Address", 0));
        p1_val_ipAdd->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        p1_lab_robStat->setText(QApplication::translate("MainWindow", "Robot Status", 0));
        p1_val_robStat->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        p1_lab_robMod->setText(QApplication::translate("MainWindow", "Robot Mode", 0));
        p1_val_robMod->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        p1_lab_teamCol->setText(QApplication::translate("MainWindow", "Team Color", 0));
        p1_val_teamCol->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        p1_conCont->setText(QApplication::translate("MainWindow", "Link to Controller", 0));
        tabWidget->setTabText(tabWidget->indexOf(player1), QApplication::translate("MainWindow", "Player 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Debug", 0));
        connect2robot->setText(QApplication::translate("MainWindow", "connect", 0));
        Scan4robot->setText(QApplication::translate("MainWindow", "Scan for Robots", 0));
        cancelButton->setText(QApplication::translate("MainWindow", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
