#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    host = new Host();
    this->timer = new QTimer();
    this->timer->setInterval(1000);

    connect(ui->actionStart_as_Host,SIGNAL(triggered()),this,SLOT(check4Host()));
    connect(ui->actionStart_as_Player,SIGNAL(triggered()),this,SLOT(startClient()));
    connect(this->host,SIGNAL(clientAdded()),this,SLOT(updateClientList()));
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
