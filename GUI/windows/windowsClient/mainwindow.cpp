#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);

    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    //initialize player stack
    for(int i =0; i<4;i++)
    {
        clearPlayerCont(&(this->playerStack[i])); //make sure player doesn't have a controller linked to them
        this->playerStack[i].isConnected=false;
        this->playerStack[i].joy_fd = UNNASSIGNED;
        this->playerStack[i].socket = INVALID_SOCKET;
        this->playerStack[i].isReady = false;

        //special case for last member of stack
        if(i<3)
            this->playerStack[i].nextPlayer=this->playerStack +i;
        else
            this->playerStack[i].nextPlayer= NULL;
    }




    //connect function timers and start them
    connect(timer1, SIGNAL(timeout()), this, SLOT(updateJoyVals()));  //update joystick values for all players with a connected joystick
    connect(timer2, SIGNAL(timeout()),this, SLOT(updateJoyGUI()));    //update gui if joystick is connected
    timer1->start(20);
    timer2->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void netMap::scanIps(const QString &parameter)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    hints;
    char name[255],*ip;
    IN_ADDR subNet;
    PHOSTENT hostinfo;
    int iResult,ipPos;
    static QString *threadRes = new QString();
    *threadRes = LOCAL_HOST;



    //startup and get local IP
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
    }
    else
    {
        if( gethostname ( name, sizeof(name)) == 0) //get local hostname
        {
            if((hostinfo = gethostbyname(name)) != NULL) //get IP by hostname
            {
               int nCount = 0;
               while(hostinfo->h_addr_list[nCount]) // if hostname is associated with more than 1 IP then select the last one
               {
                    ip = inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[nCount]);;
                    nCount++;
               }
            }
        }
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


    //change last bit of IP to match input paramater
    ipPos = parameter.toInt();
    subNet.S_un.S_addr = inet_addr(ip);
    subNet.S_un.S_un_b.s_b4=ipPos;

    //try to connect to IP
    iResult = getaddrinfo(inet_ntoa(subNet), DEFAULT_PORT, &hints, &result);
    if ( iResult == 0 )
    {
        // Create a SOCKET for connecting to server
        ConnectSocket = socket(result->ai_family, result->ai_socktype,
            result->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %d\n", WSAGetLastError());
            WSACleanup();
        }

        iResult = ::connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult != SOCKET_ERROR)
        {

            *threadRes = QString::fromUtf8(inet_ntoa(subNet));
        }
        closesocket(ConnectSocket); //reset socket for next iteration
        ConnectSocket = INVALID_SOCKET;
        freeaddrinfo(result);
    }
    emit resultReady(*threadRes);
}


void MainWindow::on_clientList_itemClicked(QListWidgetItem *item)
{
    ui->ipBox->setText(item->text());
}

void MainWindow::on_Scan4robot_clicked()
{
    if(!workerThread.isRunning()) //check that the thread isn't already running
    {
        debug("searching network for clients");

        //start search on new thread
        netMap *scanThread = new netMap;
        scanThread->moveToThread(&workerThread);
        connect(scanThread, SIGNAL(finished()), scanThread, SLOT(deleteLater()));
        connect(this, SIGNAL(scanNet(QString)), scanThread, SLOT(scanIps(QString)));
        connect(scanThread, SIGNAL(resultReady(QString)), this ,SLOT(handleResIP(QString)));

        this->currIp = 0;  //start search from ip 0
        workerThread.start();
        emit this->scanNet(QString::number(this->currIp));

        ui->Scan4robot->setText("Cancel");//change search button to cancel button
    }
    else //if the button is clicked and the thread is already working exit the thread and update the UI
    {
        this->debug("cancelled search, current thread will finish execution before being stoped");
        ui->Scan4robot->setText("Scan for Robots"); //change button back to search
        workerThread.exit(); //cancel thread
    }
}

void MainWindow::on_connect2robot_clicked()
{
    struct player *currPlayer = &(this->playerStack[ui->playerTabs->currentIndex()]);
    WSADATA wsaData;
    struct addrinfo hints;
    int iResult;
    int ipAlreadyTaken = -1;

    //check that the IP the user is trying to connect to isn't already asigned to another player
    for(int i=0; i<4 && ipAlreadyTaken == -1;i++)
    {
        if (ui->ipBox->text() == this->playerStack[i].address)
            ipAlreadyTaken =i;
    }

    if(currPlayer->socket == INVALID_SOCKET && ipAlreadyTaken == -1)
    {
        //startup
        iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

        ZeroMemory( &hints, sizeof(hints) );
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        iResult = getaddrinfo(ui->ipBox->text().toLocal8Bit(), DEFAULT_PORT, &hints, &(currPlayer->add_inf));
        if ( iResult == 0)
        {
            // Create a SOCKET for connecting to server
            currPlayer->socket = socket(currPlayer->add_inf->ai_family, currPlayer->add_inf->ai_socktype,currPlayer->add_inf->ai_protocol);
            if (currPlayer->socket == INVALID_SOCKET) {
                debug("socket failed with error: " + QString::number(WSAGetLastError()));
                WSACleanup();
            }

            //try to connect
            iResult = ::connect(currPlayer->socket, currPlayer->add_inf->ai_addr, (int)currPlayer->add_inf->ai_addrlen);
            if (iResult == SOCKET_ERROR)
            {
                debug("Connection failed to ip: " + ui->ipBox->text()+  " with error: " + QString::number(WSAGetLastError()));
                currPlayer->socket = INVALID_SOCKET;
                closesocket(currPlayer->socket);
            }
            else
            {
                //update player info and UI
                currPlayer->isConnected =true;
                currPlayer->address = ui->ipBox->text().toLocal8Bit();
                QList<QLabel *> visableLabel =ui->playerTabs->currentWidget()->findChildren<QLabel*>(); //create list of visable label widgets
                for(int i=0; i< visableLabel.length(); i++)
                {
                    if(visableLabel[i]->objectName().endsWith("val_ipAdd"))
                    {
                        visableLabel[i]->setText(ui->ipBox->text());
                    }
                    else if(visableLabel[i]->objectName().endsWith("val_robStat"))
                    {
                        visableLabel[i]->setText("Not Ready");
                    }
                    else if(visableLabel[i]->objectName().endsWith("val_robMod"))
                    {
                        visableLabel[i]->setText("Idle");
                    }
                    else if(visableLabel[i]->objectName().endsWith("val_teamCol"))
                    {
                        visableLabel[i]->setText("Red");
                        currPlayer->teamColor=RED;
                    }
                }
            }
            //NEED TO HANDLE CONNECTION ERRORS HERE!
        }
        else
        {
            freeaddrinfo(currPlayer->add_inf);
            debug("could not get address info, failed with error code: " + QString::number(WSAGetLastError()));
        }
    }
    else
    {
        if(ipAlreadyTaken == -1)
            debug("player's socket is alread linked to robot at ip: " + currPlayer->address);
        else
            debug("IP address already linked to player " + QString::number(ipAlreadyTaken+1));
    }
}

void MainWindow::handleResIP(const QString &res)
{
    //update UI with data from thread
    this->debug("Scanned IP " + QString::number(this->currIp));
    ui->scanProg->setValue(this->currIp);
    if(res!=LOCAL_HOST)
        ui->clientList->addItem(res);
    this->currIp++;
    if(currIp<=255)emit this->scanNet(QString::number(this->currIp));
}
void MainWindow::debug(const char* input)
{
    ui->debugList->addItem(input);
}
void MainWindow::debug(QString input)
{
    ui->debugList->addItem(input);
}
void MainWindow::updateJoyVals()
{
    for(int i=0; i<4;i++) //for each player
    {
        if(this->playerStack[i].joy_fd != UNNASSIGNED)
        {
            //update joystick state
            int err = XInputGetState(this->playerStack[i].joy_fd, &(this->playerStack[i].controller));
            if(err == ERROR_DEVICE_NOT_CONNECTED)
            {
                clearPlayerCont(&(this->playerStack[i]));
            }

            //if player's socket is connected to a robot push data across the network bridge to the robot
            if(this->playerStack[i].socket != INVALID_SOCKET)
            {
                QString outputBuff = "9!3";
                //packJoystick state into string by converting the 16 bit number into two char variables, first char is int15:8 second char is int7:0
                outputBuff.append(((char)(this->playerStack[i].controller.Gamepad.sThumbLX>>8)) + ((char)(this->playerStack[i].controller.Gamepad.sThumbLX&0xFF)));
                outputBuff.append(((char)(this->playerStack[i].controller.Gamepad.sThumbLY>>8)) + ((char)(this->playerStack[i].controller.Gamepad.sThumbLY&0xFF)));
                outputBuff.append(((char)(this->playerStack[i].controller.Gamepad.sThumbRX>>8)) + ((char)(this->playerStack[i].controller.Gamepad.sThumbRX&0xFF)));
                outputBuff.append(((char)(this->playerStack[i].controller.Gamepad.sThumbRY>>8)) + ((char)(this->playerStack[i].controller.Gamepad.sThumbLY&0xFF)));
                outputBuff.append(((char)(this->playerStack[i].controller.Gamepad.wButtons>>8)) + ((char)(this->playerStack[i].controller.Gamepad.wButtons&0xFF)));

                outputBuff[2] = outputBuff.length();//update datagram length
                send(this->playerStack[i].socket, outputBuff.toLocal8Bit(), outputBuff.length(), 0);
                //SHOULD HANDLE ERRORS HERE
            }
        }
    }
}
void MainWindow::clearPlayerCont(struct player *play)
{
   debug("Controller DC'ED");
   play->joy_fd = UNNASSIGNED;
}

void MainWindow::updateJoyGUI()
{

        QList<QLCDNumber *> visableLCD =ui->playerTabs->currentWidget()->findChildren<QLCDNumber *>(); //create list of visable LCD widgets
        QList<QLabel *> visableLabel =ui->playerTabs->currentWidget()->findChildren<QLabel*>(); //create list of visable label widgets
        for(int i =0; i<visableLCD.length(); i++) //update LCD data
        {
            if(visableLCD[i]->objectName().endsWith("val_leftX"))
            {
                visableLCD[i]->display(this->playerStack[ui->playerTabs->currentIndex()].controller.Gamepad.sThumbLX);
            }
            else if(visableLCD[i]->objectName().endsWith("val_leftY"))
            {
                visableLCD[i]->display(this->playerStack[ui->playerTabs->currentIndex()].controller.Gamepad.sThumbLY);
            }
            else if(visableLCD[i]->objectName().endsWith("val_rightX"))
            {
                visableLCD[i]->display(this->playerStack[ui->playerTabs->currentIndex()].controller.Gamepad.sThumbRX);
            }
            else if(visableLCD[i]->objectName().endsWith("val_rightY"))
            {
                visableLCD[i]->display(this->playerStack[ui->playerTabs->currentIndex()].controller.Gamepad.sThumbRY);
            }
            else
            {
                visableLCD[i]->display(0);
            }
        }
        for(int i=0; i<visableLabel.length(); i++) //display buttons pressed in 16bit binary
        {
            if(visableLabel[i]->objectName().endsWith("val_but"))
            {
                QString output = "0000000000000000";
                int buttons = this->playerStack[ui->playerTabs->currentIndex()].controller.Gamepad.wButtons;
                for(int j=0; j < 16; j++)
                {
                    if(buttons & 1<<j)
                        output[j] = '1';
                    else
                        output[j] = '0';
                }
                visableLabel[i]->setText(output);
            }
        }
}

bool MainWindow::bindJoystick(int playerNum)
{
    bool retVal = false;
    QList<QPushButton *> visablePButtons =ui->playerTabs->currentWidget()->findChildren<QPushButton *>();
    bool contConn[16];
    bool contFound = false;
    memset(contConn,0, sizeof(contConn));
    QList<QComboBox *> visableCombo =ui->playerTabs->currentWidget()->findChildren<QComboBox*>();
    QComboBox *currSel;

    for(int i=0; i<visableCombo.length();i++)  //find comboBox then save the user selected number
    {
        if(visableCombo[i]->objectName().endsWith("contSel"))
            currSel = visableCombo[i];
    }

    if(playerStack[playerNum].joy_fd == UNNASSIGNED) //check if player is already assigned a controller
    {
        if(currSel->currentText() == "any") //check if the user has specified a controller
        {
            for(int i=0; i<4;i++) //check which controllers are already assigned
            {
                if(this->playerStack[i].joy_fd != UNNASSIGNED)
                    contConn[this->playerStack[i].joy_fd] = true;
            }
            for(int i=0; i<16 && !contFound; i++) //look through controllers for a connected controller that isnt assigned
            {
                int error=XInputGetState(i,&(playerStack[playerNum].controller));
                if(error!=ERROR_DEVICE_NOT_CONNECTED && !contConn[i])
                {
                        debug("Successful connected player: " + QString::number(ui->playerTabs->currentIndex()+1)+ " to controller: " + QString::number(i));
                        playerStack[playerNum].joy_fd=i;
                        contFound=true;
                        visablePButtons[0]->setText("Unlink Controller");
                }
            }
        }
        else //connect to the user selected controller
        {
            int userSelection = currSel->currentIndex()-1;

            for(int i=0; i<4;i++) //check which controllers are already assigned
            {
                if(this->playerStack[i].joy_fd != UNNASSIGNED)
                    contConn[this->playerStack[i].joy_fd] = true;
            }
            int error=XInputGetState(userSelection,&(playerStack[playerNum].controller));
            if(error!=ERROR_DEVICE_NOT_CONNECTED && !contConn[userSelection])
            {
                    debug("Successful connected player " + QString::number(ui->playerTabs->currentIndex()+1)+ " to controller: " + QString::number(userSelection));
                    playerStack[playerNum].joy_fd=userSelection;
                    visablePButtons[0]->setText("Unlink Controller");
                    retVal = true;
            }
        }
        if(playerStack[playerNum].joy_fd == UNNASSIGNED)
        {
            debug("Could not find controller for player " + QString::number(ui->playerTabs->currentIndex()+1));
        }
    }
    else //player already has a controller assigned to them so we are going to unlink it from them
    {
        playerStack[playerNum].joy_fd = UNNASSIGNED;
        visablePButtons[0]->setText("Link Controller");
        debug("Unlinked controller from player " + QString::number(ui->playerTabs->currentIndex()+1));
    }
    return retVal;
}

void MainWindow::disConRobot(int playerNum)
{
    if(this->playerStack[playerNum].isConnected) //only run if player is already connected to a robot
    {
        this->playerStack[playerNum].address = "";
        this->playerStack[playerNum].isConnected=false;
        this->playerStack[playerNum].isReady = false;
        closesocket(this->playerStack[playerNum].socket);
        this->playerStack[playerNum].socket = INVALID_SOCKET;
        freeaddrinfo(this->playerStack[playerNum].add_inf);

        QList<QLabel *> visableLabel =ui->playerTabs->currentWidget()->findChildren<QLabel*>(); //create list of visable label widgets
        for(int i=0; i< visableLabel.length(); i++)
        {
            if(visableLabel[i]->objectName().endsWith("val_ipAdd"))
            {
                visableLabel[i]->setText("NONE");
            }
            else if(visableLabel[i]->objectName().endsWith("val_robStat"))
            {
                visableLabel[i]->setText("UNKNOWN");
            }
            else if(visableLabel[i]->objectName().endsWith("val_robMod"))
            {
                visableLabel[i]->setText("UNKNOWN");
            }
            else if(visableLabel[i]->objectName().endsWith("val_teamCol"))
            {
                visableLabel[i]->setText("UNKNOWN");
                this->playerStack[playerNum].teamColor=0;
            }
        }
    }
}
void MainWindow::toggleRobotReady()
{
    struct player *currPlayer = &(this->playerStack[ui->playerTabs->currentIndex()]);
    QList<QLabel *> visableLabel =ui->playerTabs->currentWidget()->findChildren<QLabel*>();
    QLabel *readyLabel;
    for(int i=0; i < visableLabel.length(); i++)
    {
        if(visableLabel[i]->objectName().endsWith("val_robStat"))
            readyLabel = visableLabel[i];
    }
    if(currPlayer->isConnected)
    {
        if(currPlayer->isReady)
        {
            currPlayer->isReady = false;
            readyLabel->setText("Not Ready");
        }
        else
        {
            currPlayer->isReady = true;
            readyLabel->setText("Ready");
        }
    }
}
void MainWindow::toggleRobotTeam(void)
{
    struct player *currPlayer = &(this->playerStack[ui->playerTabs->currentIndex()]);
    QList<QLabel *> visableLabel =ui->playerTabs->currentWidget()->findChildren<QLabel*>();
    QLabel *readyLabel;
    for(int i=0; i < visableLabel.length(); i++)
    {
        if(visableLabel[i]->objectName().endsWith("val_teamCol"))
            readyLabel = visableLabel[i];
    }
    if(currPlayer->isConnected)
    {
        if(currPlayer->teamColor == BLUE)
        {
            currPlayer->teamColor = RED;
            readyLabel->setText("RED");
        }
        else
        {
            currPlayer->teamColor = BLUE;
            readyLabel->setText("BLUE");
        }
    }
}

void MainWindow::on_p1_conCont_clicked()
{
    bindJoystick(ui->playerTabs->currentIndex());
}

void MainWindow::on_p2_conCont_clicked()
{
    bindJoystick(ui->playerTabs->currentIndex());
}

void MainWindow::on_p3_conCont_clicked()
{
     bindJoystick(ui->playerTabs->currentIndex());
}

void MainWindow::on_p4_conCont_clicked()
{
     bindJoystick(ui->playerTabs->currentIndex());
}

void MainWindow::on_p1_disCon_clicked()
{
    disConRobot(ui->playerTabs->currentIndex());
}

void MainWindow::on_p2_disCon_clicked()
{
    disConRobot(ui->playerTabs->currentIndex());
}

void MainWindow::on_p3_disCon_clicked()
{
    disConRobot(ui->playerTabs->currentIndex());
}

void MainWindow::on_p4_disCon_clicked()
{
    disConRobot(ui->playerTabs->currentIndex());
}

void MainWindow::on_p1_chng_stat_clicked()
{
    toggleRobotReady();
}

void MainWindow::on_p2_chng_stat_clicked()
{
    toggleRobotReady();
}

void MainWindow::on_p3_chng_stat_clicked()
{
    toggleRobotReady();
}

void MainWindow::on_p4_chng_stat_clicked()
{
    toggleRobotReady();
}

void MainWindow::on_p1_chng_team_clicked()
{
    toggleRobotTeam();
}

void MainWindow::on_p2_chng_team_clicked()
{
    toggleRobotTeam();
}

void MainWindow::on_p3_chng_team_clicked()
{
    toggleRobotTeam();
}

void MainWindow::on_p4_chng_team_clicked()
{
    toggleRobotTeam();
}
