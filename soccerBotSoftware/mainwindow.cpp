#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpBroadcast = new Host();
    timer = new QTimer();
    timer->setInterval(1000);

    connect(ui->actionStart_as_Host,SIGNAL(triggered()),timer,SLOT(start()));
    connect(timer,SIGNAL(timeout()),udpBroadcast,SLOT(sendBroadcast()));
    connect(ui->actionStart_as_Player,SIGNAL(triggered()),this,SLOT(startClient()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startClient()
{
    client = new Client();
}
