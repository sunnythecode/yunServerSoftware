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
    for(int i = 0;i<4;i++)
    {
        this->joyList.append(new JoyStickHandler());
        this->joyList.at(i)->initJoystick(i);

    }
    //connect menu bar buttons
    connect(ui->actionStart_as_Host,SIGNAL(triggered()),this,SLOT(check4Host()));
    connect(ui->actionStart_as_Player,SIGNAL(triggered()),this,SLOT(startClient()));


    connect(this->host,SIGNAL(clientAdded()),this,SLOT(updateClientList()));
    connect(this->host, SIGNAL(robotAdded()), this, SLOT(checkStartMatch()));



    /*Start test code
    connect(this->timer,SIGNAL(timeout()),this,SLOT(updateJoyVals()));
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

    this->host->getMasterList()->at(0)->setName("Swag1");
    this->host->getMasterList()->at(1)->setName("Swag2");
    this->host->getMasterList()->at(2)->setName("Swag3");
    this->host->getMasterList()->at(3)->setName("Swag4");
    this->host->getMasterList()->at(4)->setName("Swag5");
    this->host->getMasterList()->at(5)->setName("Swag6");

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
    connect(this->timer,SIGNAL(timeout()),this,SLOT(updateJoyVals()));

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
        connect(this->timer,SIGNAL(timeout()),this,SLOT(updateJoyVals()));
        this->timer->start();
        delete this->client;
    }
}
void MainWindow::updateClientList()
{
    QList<QComboBox *> comboBoxes =ui->mainTabs->findChildren<QComboBox*>(); //create list of combo boxes
    for(int i=0; i<comboBoxes.length(); i++)
    {
        if(comboBoxes[i]->objectName().endsWith("_cb"))
        {
            comboBoxes[i]->clear();
            comboBoxes[i]->addItems(this->host->getClientNames());
        }
    }
}

void MainWindow::checkStartMatch() {
        if (this->host->getRobots()->count() == 6)
            this->ui->btn_startMatch->setEnabled(true);
        else
            this->ui->btn_startMatch->setEnabled(false);
}

void MainWindow::on_btn_ForceMatchStart_clicked()
{
    //do stuff
}

void MainWindow::on_p1_linkCont_clicked()
{
    D_MSG("BITCH");
    int index = -1;
    QTime timeout = QTime::currentTime().addSecs(5);
    for(int i = 0;QTime::currentTime() < timeout ;i++)
    {
        if(i>=this->joyList.size())i=0;
        this->joyList.at(i)->updateJoystick();
        if(this->joyList.at(i)->readBttn(i).indvBttn.START)
        {
            index = i;
            break;
        }
    }
    if(index!=-1)
    {
        D_MSG("Controlled linked successfully");
        this->host->getMasterList()->at(ui->mainTabs->currentIndex()-1)->setJoyIndex(index);
    }
}

void MainWindow::on_p2_linkCont_clicked()
{
    int index = -1;
    QTime timeout = QTime::currentTime().addSecs(5);
    for(int i = 0;QTime::currentTime() > timeout ;i++)
    {
        if(i>this->joyList.size())i=0;
        this->joyList.at(i)->updateJoystick();
        if(this->joyList.at(i)->readBttn(i).indvBttn.START)
        {
            index = i;
            break;
        }
    }
    if(index!=-1)
    {
        this->host->getMasterList()->at(ui->mainTabs->currentIndex()-1)->setJoyIndex(index);
    }
}

void MainWindow::on_p3_linkCont_clicked()
{
    int index = -1;
    QTime timeout = QTime::currentTime().addSecs(5);
    for(int i = 0;QTime::currentTime() > timeout ;i++)
    {
        if(i>this->joyList.size())i=0;
        this->joyList.at(i)->updateJoystick();
        if(this->joyList.at(i)->readBttn(i).indvBttn.START)
        {
            index = i;
            break;
        }
    }
    if(index!=-1)
    {
        this->host->getMasterList()->at(ui->mainTabs->currentIndex()-1)->setJoyIndex(index);
    }
}

void MainWindow::on_p4_linkCont_clicked()
{
    int index = -1;
    QTime timeout = QTime::currentTime().addSecs(5);
    for(int i = 0;QTime::currentTime() > timeout ;i++)
    {
        if(i>this->joyList.size())i=0;
        this->joyList.at(i)->updateJoystick();
        if(this->joyList.at(i)->readBttn(i).indvBttn.START)
        {
            index = i;
            break;
        }
    }
    if(index!=-1)
    {
        this->host->getMasterList()->at(ui->mainTabs->currentIndex()-1)->setJoyIndex(index);
    }
}

void MainWindow::on_p5_linkCont_clicked()
{
    int index = -1;
    QTime timeout = QTime::currentTime().addSecs(5);
    for(int i = 0;QTime::currentTime() > timeout ;i++)
    {
        if(i>this->joyList.size())i=0;
        this->joyList.at(i)->updateJoystick();
        if(this->joyList.at(i)->readBttn(i).indvBttn.START)
        {
            index = i;
            break;
        }
    }
    if(index!=-1)
    {
        this->host->getMasterList()->at(ui->mainTabs->currentIndex()-1)->setJoyIndex(index);
    }
}

void MainWindow::on_p6_linkCont_clicked()
{
    int index = -1;
    QTime timeout = QTime::currentTime().addSecs(5);
    for(int i = 0;QTime::currentTime() > timeout ;i++)
    {
        if(i>this->joyList.size())i=0;
        this->joyList.at(i)->updateJoystick();
        if(this->joyList.at(i)->readBttn(i).indvBttn.START)
        {
            index = i;
            break;
        }
    }
    if(index!=-1)
    {
        this->host->getMasterList()->at(ui->mainTabs->currentIndex()-1)->setJoyIndex(index);
    }
}
void MainWindow::updateJoyVals()
{
    for(int i = 0;i<this->host->getMasterList()->size();i++)
    {
        int index = this->host->getMasterList()->at(i)->getJoyIndex();
        if(index!=-1)
        {
            this->joyList.at(index)->updateJoystick();
            JoystickData data;
            data.lX = this->joyList.at(index)->readAxis(0);
            data.lY = this->joyList.at(index)->readAxis(1);
            data.rX = this->joyList.at(index)->readAxis(2);
            data.rY = this->joyList.at(index)->readAxis(3);
            data.lT = this->joyList.at(index)->readAxis(4);
            data.rT = this->joyList.at(index)->readAxis(5);
            data.buttons = this->joyList.at(index)->readBttn(index);
            this->host->getMasterList()->at(i)->setJoystickData(data);
        }
    }
    this->host->sendRobotSync();
}

void MainWindow::on_btn_stopMatch_clicked()
{
    disconnect(this->timer,SIGNAL(timeout()),this,SLOT(updateJoyVals()));
}
