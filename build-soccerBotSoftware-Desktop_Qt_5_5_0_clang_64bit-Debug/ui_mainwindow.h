/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart_as_Host;
    QAction *actionStart_as_Player;
    QWidget *centralWidget;
    QTabWidget *mainTabs;
    QWidget *tb_game;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_startMatch;
    QPushButton *btn_ForceMatchStart;
    QPushButton *btn_stopMatch;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *gb_game_redTeam;
    QWidget *layoutWidget2;
    QVBoxLayout *redTeamVert;
    QGroupBox *gb_game_player1;
    QSplitter *splitter;
    QLabel *txt_game_p1_robcom;
    QLabel *txt_game_p1_joystick;
    QGroupBox *gb_game_player2;
    QSplitter *splitter_2;
    QLabel *txt_game_p2_robcom;
    QLabel *txt_game_p2_joystick;
    QGroupBox *gb_game_player3;
    QSplitter *splitter_3;
    QLabel *txt_game_p3_robcom;
    QLabel *txt_game_p3_joystick;
    QGroupBox *gb_game_blueTeam;
    QWidget *layoutWidget3;
    QVBoxLayout *blueTeamVert;
    QGroupBox *gb_game_player4;
    QSplitter *splitter_4;
    QLabel *txt_game_p4_robcom;
    QLabel *txt_game_p4_joystick;
    QGroupBox *gb_game_player5;
    QSplitter *splitter_5;
    QLabel *txt_game_p5_robcom;
    QLabel *txt_game_p5_joystick;
    QGroupBox *gb_game_player6;
    QSplitter *splitter_6;
    QLabel *txt_game_p6_robcom;
    QLabel *txt_game_p6_joystick;
    QWidget *tb_p1;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QToolButton *toolButton;
    QWidget *tb_p2;
    QWidget *tb_p3;
    QWidget *tb_p4;
    QWidget *tb_p5;
    QWidget *tb_p6;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(600, 470);
        MainWindow->setMinimumSize(QSize(600, 470));
        MainWindow->setMaximumSize(QSize(600, 470));
        QFont font;
        font.setKerning(true);
        MainWindow->setFont(font);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionStart_as_Host = new QAction(MainWindow);
        actionStart_as_Host->setObjectName(QStringLiteral("actionStart_as_Host"));
        actionStart_as_Player = new QAction(MainWindow);
        actionStart_as_Player->setObjectName(QStringLiteral("actionStart_as_Player"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mainTabs = new QTabWidget(centralWidget);
        mainTabs->setObjectName(QStringLiteral("mainTabs"));
        mainTabs->setGeometry(QRect(10, 10, 571, 401));
        tb_game = new QWidget();
        tb_game->setObjectName(QStringLiteral("tb_game"));
        layoutWidget = new QWidget(tb_game);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 340, 239, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btn_startMatch = new QPushButton(layoutWidget);
        btn_startMatch->setObjectName(QStringLiteral("btn_startMatch"));
        btn_startMatch->setEnabled(false);

        horizontalLayout->addWidget(btn_startMatch);

        btn_ForceMatchStart = new QPushButton(layoutWidget);
        btn_ForceMatchStart->setObjectName(QStringLiteral("btn_ForceMatchStart"));

        horizontalLayout->addWidget(btn_ForceMatchStart);

        btn_stopMatch = new QPushButton(layoutWidget);
        btn_stopMatch->setObjectName(QStringLiteral("btn_stopMatch"));
        btn_stopMatch->setEnabled(false);

        horizontalLayout->addWidget(btn_stopMatch);

        layoutWidget1 = new QWidget(tb_game);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 528, 322));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        gb_game_redTeam = new QGroupBox(layoutWidget1);
        gb_game_redTeam->setObjectName(QStringLiteral("gb_game_redTeam"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gb_game_redTeam->sizePolicy().hasHeightForWidth());
        gb_game_redTeam->setSizePolicy(sizePolicy);
        gb_game_redTeam->setMinimumSize(QSize(260, 320));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        gb_game_redTeam->setFont(font1);
        layoutWidget2 = new QWidget(gb_game_redTeam);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 30, 241, 281));
        redTeamVert = new QVBoxLayout(layoutWidget2);
        redTeamVert->setSpacing(6);
        redTeamVert->setContentsMargins(11, 11, 11, 11);
        redTeamVert->setObjectName(QStringLiteral("redTeamVert"));
        redTeamVert->setContentsMargins(0, 0, 0, 0);
        gb_game_player1 = new QGroupBox(layoutWidget2);
        gb_game_player1->setObjectName(QStringLiteral("gb_game_player1"));
        gb_game_player1->setEnabled(true);
        sizePolicy.setHeightForWidth(gb_game_player1->sizePolicy().hasHeightForWidth());
        gb_game_player1->setSizePolicy(sizePolicy);
        splitter = new QSplitter(gb_game_player1);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(10, 20, 222, 50));
        splitter->setMinimumSize(QSize(200, 0));
        QFont font2;
        font2.setStyleStrategy(QFont::PreferDefault);
        splitter->setFont(font2);
        splitter->setOrientation(Qt::Vertical);
        txt_game_p1_robcom = new QLabel(splitter);
        txt_game_p1_robcom->setObjectName(QStringLiteral("txt_game_p1_robcom"));
        QFont font3;
        font3.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        txt_game_p1_robcom->setFont(font3);
        txt_game_p1_robcom->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p1_robcom->setFrameShape(QFrame::Box);
        txt_game_p1_robcom->setAlignment(Qt::AlignCenter);
        splitter->addWidget(txt_game_p1_robcom);
        txt_game_p1_joystick = new QLabel(splitter);
        txt_game_p1_joystick->setObjectName(QStringLiteral("txt_game_p1_joystick"));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setWeight(75);
        txt_game_p1_joystick->setFont(font4);
        txt_game_p1_joystick->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p1_joystick->setFrameShape(QFrame::Box);
        txt_game_p1_joystick->setAlignment(Qt::AlignCenter);
        splitter->addWidget(txt_game_p1_joystick);

        redTeamVert->addWidget(gb_game_player1);

        gb_game_player2 = new QGroupBox(layoutWidget2);
        gb_game_player2->setObjectName(QStringLiteral("gb_game_player2"));
        gb_game_player2->setEnabled(true);
        sizePolicy.setHeightForWidth(gb_game_player2->sizePolicy().hasHeightForWidth());
        gb_game_player2->setSizePolicy(sizePolicy);
        splitter_2 = new QSplitter(gb_game_player2);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(10, 20, 222, 50));
        splitter_2->setMinimumSize(QSize(200, 0));
        splitter_2->setFont(font2);
        splitter_2->setOrientation(Qt::Vertical);
        txt_game_p2_robcom = new QLabel(splitter_2);
        txt_game_p2_robcom->setObjectName(QStringLiteral("txt_game_p2_robcom"));
        txt_game_p2_robcom->setFont(font3);
        txt_game_p2_robcom->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p2_robcom->setFrameShape(QFrame::Box);
        txt_game_p2_robcom->setAlignment(Qt::AlignCenter);
        splitter_2->addWidget(txt_game_p2_robcom);
        txt_game_p2_joystick = new QLabel(splitter_2);
        txt_game_p2_joystick->setObjectName(QStringLiteral("txt_game_p2_joystick"));
        txt_game_p2_joystick->setFont(font4);
        txt_game_p2_joystick->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p2_joystick->setFrameShape(QFrame::Box);
        txt_game_p2_joystick->setAlignment(Qt::AlignCenter);
        splitter_2->addWidget(txt_game_p2_joystick);

        redTeamVert->addWidget(gb_game_player2);

        gb_game_player3 = new QGroupBox(layoutWidget2);
        gb_game_player3->setObjectName(QStringLiteral("gb_game_player3"));
        gb_game_player3->setEnabled(true);
        sizePolicy.setHeightForWidth(gb_game_player3->sizePolicy().hasHeightForWidth());
        gb_game_player3->setSizePolicy(sizePolicy);
        splitter_3 = new QSplitter(gb_game_player3);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setGeometry(QRect(10, 30, 222, 50));
        splitter_3->setMinimumSize(QSize(200, 0));
        splitter_3->setFont(font2);
        splitter_3->setOrientation(Qt::Vertical);
        txt_game_p3_robcom = new QLabel(splitter_3);
        txt_game_p3_robcom->setObjectName(QStringLiteral("txt_game_p3_robcom"));
        txt_game_p3_robcom->setFont(font3);
        txt_game_p3_robcom->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p3_robcom->setFrameShape(QFrame::Box);
        txt_game_p3_robcom->setAlignment(Qt::AlignCenter);
        splitter_3->addWidget(txt_game_p3_robcom);
        txt_game_p3_joystick = new QLabel(splitter_3);
        txt_game_p3_joystick->setObjectName(QStringLiteral("txt_game_p3_joystick"));
        txt_game_p3_joystick->setFont(font4);
        txt_game_p3_joystick->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p3_joystick->setFrameShape(QFrame::Box);
        txt_game_p3_joystick->setAlignment(Qt::AlignCenter);
        splitter_3->addWidget(txt_game_p3_joystick);

        redTeamVert->addWidget(gb_game_player3);


        horizontalLayout_2->addWidget(gb_game_redTeam);

        gb_game_blueTeam = new QGroupBox(layoutWidget1);
        gb_game_blueTeam->setObjectName(QStringLiteral("gb_game_blueTeam"));
        sizePolicy.setHeightForWidth(gb_game_blueTeam->sizePolicy().hasHeightForWidth());
        gb_game_blueTeam->setSizePolicy(sizePolicy);
        gb_game_blueTeam->setMinimumSize(QSize(260, 320));
        gb_game_blueTeam->setFont(font1);
        layoutWidget3 = new QWidget(gb_game_blueTeam);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 30, 241, 281));
        blueTeamVert = new QVBoxLayout(layoutWidget3);
        blueTeamVert->setSpacing(6);
        blueTeamVert->setContentsMargins(11, 11, 11, 11);
        blueTeamVert->setObjectName(QStringLiteral("blueTeamVert"));
        blueTeamVert->setContentsMargins(0, 0, 0, 0);
        gb_game_player4 = new QGroupBox(layoutWidget3);
        gb_game_player4->setObjectName(QStringLiteral("gb_game_player4"));
        sizePolicy.setHeightForWidth(gb_game_player4->sizePolicy().hasHeightForWidth());
        gb_game_player4->setSizePolicy(sizePolicy);
        splitter_4 = new QSplitter(gb_game_player4);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setGeometry(QRect(10, 20, 222, 50));
        splitter_4->setMinimumSize(QSize(200, 0));
        splitter_4->setFont(font2);
        splitter_4->setOrientation(Qt::Vertical);
        txt_game_p4_robcom = new QLabel(splitter_4);
        txt_game_p4_robcom->setObjectName(QStringLiteral("txt_game_p4_robcom"));
        txt_game_p4_robcom->setFont(font3);
        txt_game_p4_robcom->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p4_robcom->setFrameShape(QFrame::Box);
        txt_game_p4_robcom->setAlignment(Qt::AlignCenter);
        splitter_4->addWidget(txt_game_p4_robcom);
        txt_game_p4_joystick = new QLabel(splitter_4);
        txt_game_p4_joystick->setObjectName(QStringLiteral("txt_game_p4_joystick"));
        txt_game_p4_joystick->setFont(font4);
        txt_game_p4_joystick->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p4_joystick->setFrameShape(QFrame::Box);
        txt_game_p4_joystick->setAlignment(Qt::AlignCenter);
        splitter_4->addWidget(txt_game_p4_joystick);

        blueTeamVert->addWidget(gb_game_player4);

        gb_game_player5 = new QGroupBox(layoutWidget3);
        gb_game_player5->setObjectName(QStringLiteral("gb_game_player5"));
        sizePolicy.setHeightForWidth(gb_game_player5->sizePolicy().hasHeightForWidth());
        gb_game_player5->setSizePolicy(sizePolicy);
        splitter_5 = new QSplitter(gb_game_player5);
        splitter_5->setObjectName(QStringLiteral("splitter_5"));
        splitter_5->setGeometry(QRect(10, 20, 222, 50));
        splitter_5->setMinimumSize(QSize(200, 0));
        splitter_5->setFont(font2);
        splitter_5->setOrientation(Qt::Vertical);
        txt_game_p5_robcom = new QLabel(splitter_5);
        txt_game_p5_robcom->setObjectName(QStringLiteral("txt_game_p5_robcom"));
        txt_game_p5_robcom->setFont(font3);
        txt_game_p5_robcom->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p5_robcom->setFrameShape(QFrame::Box);
        txt_game_p5_robcom->setAlignment(Qt::AlignCenter);
        splitter_5->addWidget(txt_game_p5_robcom);
        txt_game_p5_joystick = new QLabel(splitter_5);
        txt_game_p5_joystick->setObjectName(QStringLiteral("txt_game_p5_joystick"));
        txt_game_p5_joystick->setFont(font4);
        txt_game_p5_joystick->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p5_joystick->setFrameShape(QFrame::Box);
        txt_game_p5_joystick->setAlignment(Qt::AlignCenter);
        splitter_5->addWidget(txt_game_p5_joystick);

        blueTeamVert->addWidget(gb_game_player5);

        gb_game_player6 = new QGroupBox(layoutWidget3);
        gb_game_player6->setObjectName(QStringLiteral("gb_game_player6"));
        sizePolicy.setHeightForWidth(gb_game_player6->sizePolicy().hasHeightForWidth());
        gb_game_player6->setSizePolicy(sizePolicy);
        splitter_6 = new QSplitter(gb_game_player6);
        splitter_6->setObjectName(QStringLiteral("splitter_6"));
        splitter_6->setGeometry(QRect(10, 30, 222, 50));
        splitter_6->setMinimumSize(QSize(200, 0));
        splitter_6->setFont(font2);
        splitter_6->setOrientation(Qt::Vertical);
        txt_game_p6_robcom = new QLabel(splitter_6);
        txt_game_p6_robcom->setObjectName(QStringLiteral("txt_game_p6_robcom"));
        txt_game_p6_robcom->setFont(font3);
        txt_game_p6_robcom->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p6_robcom->setFrameShape(QFrame::Box);
        txt_game_p6_robcom->setAlignment(Qt::AlignCenter);
        splitter_6->addWidget(txt_game_p6_robcom);
        txt_game_p6_joystick = new QLabel(splitter_6);
        txt_game_p6_joystick->setObjectName(QStringLiteral("txt_game_p6_joystick"));
        txt_game_p6_joystick->setFont(font4);
        txt_game_p6_joystick->setStyleSheet(QStringLiteral("background-color:rgba(255, 10, 10, 0.75);"));
        txt_game_p6_joystick->setFrameShape(QFrame::Box);
        txt_game_p6_joystick->setAlignment(Qt::AlignCenter);
        splitter_6->addWidget(txt_game_p6_joystick);

        blueTeamVert->addWidget(gb_game_player6);


        horizontalLayout_2->addWidget(gb_game_blueTeam);

        mainTabs->addTab(tb_game, QString());
        tb_p1 = new QWidget();
        tb_p1->setObjectName(QStringLiteral("tb_p1"));
        layoutWidget4 = new QWidget(tb_p1);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 10, 551, 361));
        verticalLayout = new QVBoxLayout(layoutWidget4);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        textBrowser = new QTextBrowser(layoutWidget4);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        comboBox = new QComboBox(layoutWidget4);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(180);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(comboBox);

        pushButton_2 = new QPushButton(layoutWidget4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        pushButton = new QPushButton(layoutWidget4);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);

        toolButton = new QToolButton(layoutWidget4);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout_3->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout_3);

        mainTabs->addTab(tb_p1, QString());
        tb_p2 = new QWidget();
        tb_p2->setObjectName(QStringLiteral("tb_p2"));
        mainTabs->addTab(tb_p2, QString());
        tb_p3 = new QWidget();
        tb_p3->setObjectName(QStringLiteral("tb_p3"));
        mainTabs->addTab(tb_p3, QString());
        tb_p4 = new QWidget();
        tb_p4->setObjectName(QStringLiteral("tb_p4"));
        mainTabs->addTab(tb_p4, QString());
        tb_p5 = new QWidget();
        tb_p5->setObjectName(QStringLiteral("tb_p5"));
        mainTabs->addTab(tb_p5, QString());
        tb_p6 = new QWidget();
        tb_p6->setObjectName(QStringLiteral("tb_p6"));
        mainTabs->addTab(tb_p6, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionStart_as_Host);
        menuMenu->addAction(actionStart_as_Player);

        retranslateUi(MainWindow);

        mainTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionStart_as_Host->setText(QApplication::translate("MainWindow", "Start as Host", 0));
        actionStart_as_Player->setText(QApplication::translate("MainWindow", "Start as Player", 0));
        btn_startMatch->setText(QApplication::translate("MainWindow", "Start Match", 0));
        btn_ForceMatchStart->setText(QApplication::translate("MainWindow", "Force Start", 0));
        btn_stopMatch->setText(QApplication::translate("MainWindow", "Stop Match", 0));
        gb_game_redTeam->setTitle(QApplication::translate("MainWindow", "Red Team", 0));
        gb_game_player1->setTitle(QApplication::translate("MainWindow", "Player 1", 0));
        txt_game_p1_robcom->setText(QApplication::translate("MainWindow", "Robot Communication", 0));
        txt_game_p1_joystick->setText(QApplication::translate("MainWindow", "Joystick", 0));
        gb_game_player2->setTitle(QApplication::translate("MainWindow", "Player 2", 0));
        txt_game_p2_robcom->setText(QApplication::translate("MainWindow", "Robot Communication", 0));
        txt_game_p2_joystick->setText(QApplication::translate("MainWindow", "Joystick", 0));
        gb_game_player3->setTitle(QApplication::translate("MainWindow", "Player 3", 0));
        txt_game_p3_robcom->setText(QApplication::translate("MainWindow", "Robot Communication", 0));
        txt_game_p3_joystick->setText(QApplication::translate("MainWindow", "Joystick", 0));
        gb_game_blueTeam->setTitle(QApplication::translate("MainWindow", "Blue Team", 0));
        gb_game_player4->setTitle(QApplication::translate("MainWindow", "Player 4", 0));
        txt_game_p4_robcom->setText(QApplication::translate("MainWindow", "Robot Communication", 0));
        txt_game_p4_joystick->setText(QApplication::translate("MainWindow", "Joystick", 0));
        gb_game_player5->setTitle(QApplication::translate("MainWindow", "Player 5", 0));
        txt_game_p5_robcom->setText(QApplication::translate("MainWindow", "Robot Communication", 0));
        txt_game_p5_joystick->setText(QApplication::translate("MainWindow", "Joystick", 0));
        gb_game_player6->setTitle(QApplication::translate("MainWindow", "Player 6", 0));
        txt_game_p6_robcom->setText(QApplication::translate("MainWindow", "Robot Communication", 0));
        txt_game_p6_joystick->setText(QApplication::translate("MainWindow", "Joystick", 0));
        mainTabs->setTabText(mainTabs->indexOf(tb_game), QApplication::translate("MainWindow", "Game", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Link Robot", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Link Controller", 0));
        toolButton->setText(QApplication::translate("MainWindow", "...", 0));
        mainTabs->setTabText(mainTabs->indexOf(tb_p1), QApplication::translate("MainWindow", "Player1", 0));
        mainTabs->setTabText(mainTabs->indexOf(tb_p2), QApplication::translate("MainWindow", "Player2", 0));
        mainTabs->setTabText(mainTabs->indexOf(tb_p3), QApplication::translate("MainWindow", "Player 3", 0));
        mainTabs->setTabText(mainTabs->indexOf(tb_p4), QApplication::translate("MainWindow", "Player 4", 0));
        mainTabs->setTabText(mainTabs->indexOf(tb_p5), QApplication::translate("MainWindow", "Player 5", 0));
        mainTabs->setTabText(mainTabs->indexOf(tb_p6), QApplication::translate("MainWindow", "Player 6", 0));
        menuMenu->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
