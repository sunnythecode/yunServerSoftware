#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    host = new Host();
    this->timer = new QTimer();
    this->timer->setInterval(50);

    connect(ui->actionStart_as_Host,SIGNAL(triggered()),this,SLOT(check4Host()));
    connect(ui->actionStart_as_Player,SIGNAL(triggered()),this,SLOT(startClient()));
    connect(this->host,SIGNAL(clientAdded()),this,SLOT(updateClientList()));
    ///*Start test code
    connect(this->timer,SIGNAL(timeout()),this->host,SLOT(sendRobotSync()));
    ConnectedRobot rob1;
    rob1.addr = QHostAddress("192.10.0.1");
    rob1.name = "Swag1";
    rob1.port = 69;
    ConnectedRobot rob2;
    rob2.addr = QHostAddress("192.10.0.2");
    rob2.name = "Swag2";
    rob2.port = 69;
    ConnectedRobot rob3;
    rob3.addr = QHostAddress("192.10.0.3");
    rob3.name = "Swag3";
    rob3.port = 69;
    ConnectedRobot rob4;
    rob4.addr = QHostAddress("192.10.0.4");
    rob4.name = "Swag4";
    rob4.port = 69;
    ConnectedRobot rob5;
    rob5.addr = QHostAddress("192.10.0.5");
    rob5.name = "Swag5";
    rob5.port = 69;
    ConnectedRobot rob6;
    rob6.addr = QHostAddress("192.10.0.6");
    rob6.name = "Swag6";
    rob6.port = 69;
    this->host->getRobots()->append(rob1);
    this->host->getRobots()->append(rob2);
    this->host->getRobots()->append(rob3);
    this->host->getRobots()->append(rob4);
    this->host->getRobots()->append(rob5);
    this->host->getRobots()->append(rob6);

    this->host->getMasterList()->getNames()[0]="Swag1";
    this->host->getMasterList()->getNames()[1]="Swag2";
    this->host->getMasterList()->getNames()[2]="Swag3";
    this->host->getMasterList()->getNames()[3]="Swag4";
    this->host->getMasterList()->getNames()[4]="Swag5";
    this->host->getMasterList()->getNames()[5]="Swag6";

    this->timer->start();
    //*/

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startClient()
{
    this->client = new Client();

    //disable menu buttons after a selection
    this->ui->actionStart_as_Host->setEnabled(false);
    this->ui->actionStart_as_Player->setEnabled(false);
}
void MainWindow::check4Host()
{
    //check that a host doesn't already exist
    this->client = new Client();

    //disable menu buttons after a selection
    this->ui->actionStart_as_Host->setEnabled(false);
    this->ui->actionStart_as_Player->setEnabled(false);

    //wait for 5 seconds then check if a host beacon came in
    QTimer::singleShot(5000, this, SLOT(startHost()));
}

void MainWindow::startHost()
{
    if(this->client->isConnected())
    {
        //Host was found!
        delete this->client;

        //re-enable menu buttons
        this->ui->actionStart_as_Host->setEnabled(true);
        this->ui->actionStart_as_Player->setEnabled(true);
    }
    else
    {
        //no other host is available so we will start up as the host
        connect(this->timer,SIGNAL(timeout()),host,SLOT(sendBroadcast()));
        this->timer->start();
        delete this->client;
    }
}
void MainWindow::updateClientList()
{
    this->ui->comboBox->clear();
    this->ui->comboBox->addItems(this->host->getClientNames());
}

void MainWindow::on_btn_ForceMatchStart_clicked()
{
    //do stuff
}
