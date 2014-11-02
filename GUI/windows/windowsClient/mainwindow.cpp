

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);
    //initialize player stack
    this->playerStack.isConnected=false;
    this->playerStack.nextPlayer =NULL;

    ui->setupUi(this);
    clearPlayerCont(&(this->playerStack));
    connect(timer1, SIGNAL(timeout()), this, SLOT(updateJoyVals()));
    connect(timer2, SIGNAL(timeout()),this, SLOT(updateJoyGUI()));

    timer1->start(3);
    timer2->start(100);
    this->debug("test");

    //setup Player 1
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::updateValGraph()
{
        char data[255];
        XINPUT_STATE player1;
        int port =0;
        while(!XInputGetState(port++,&player1) && port<15);
        if(port<15)
            sprintf(data, "LY:%6d RY:%6d bttn1:%6d", player1.Gamepad.sThumbLY, player1.Gamepad.sThumbRY, player1.Gamepad.wButtons);
        else
            sprintf(data, "CNF");
}
*/

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
    *threadRes = "127.0.0.1";

    ipPos = parameter.toInt();
    //startup and get local IP
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
    }
    else
    {
        if( gethostname ( name, sizeof(name)) == 0)
        {
            if((hostinfo = gethostbyname(name)) != NULL)
            {
               int nCount = 0;
               while(hostinfo->h_addr_list[nCount])
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


    subNet.S_un.S_addr = inet_addr(ip); //convert to data struct
    subNet.S_un.S_un_b.s_b4=ipPos; //change last bit of ip

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

        // Connect to server.
        iResult = ::connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
        }
        else
        {
            *threadRes = QString::fromUtf8(inet_ntoa(subNet));
        }
        closesocket(ConnectSocket); //reset socket for next iteration
        ConnectSocket = INVALID_SOCKET;
        freeaddrinfo(result);
    }
    emit resultReady(*threadRes);
}

void MainWindow::pushPlayerStack(struct player *stack)
{
    while(stack->nextPlayer) stack = stack->nextPlayer;
    stack->nextPlayer =(struct player *) malloc(sizeof(struct player));
    stack->nextPlayer->isConnected =false;
    stack->nextPlayer->nextPlayer = NULL;
    clearPlayerCont(stack->nextPlayer);
}

void MainWindow::popPlayerStack(struct player *stack)
{
    struct player *mover = stack;
    if(stack->nextPlayer)
    {
        while(mover->nextPlayer)
        {
            stack = mover;
            mover = mover->nextPlayer;
        }
        stack->nextPlayer = NULL;
        free(mover);
    }
}

void MainWindow::deletePlayer(struct player *stack, struct player *del)
{
   while(stack != del && stack->nextPlayer)
       stack = stack->nextPlayer;
   if(stack->nextPlayer == del)
   {
       stack->nextPlayer = del->nextPlayer;
       free(del);
   }
}

void MainWindow::on_clientList_itemClicked(QListWidgetItem *item)
{
    ui->ipBox->setText(item->text());
}

void MainWindow::on_Scan4robot_clicked()
{
    if(!workerThread.isRunning())
    {
    this->debug("Clicked");
    netMap *scanThread = new netMap;
    scanThread->moveToThread(&workerThread);
    connect(scanThread, SIGNAL(finished()), scanThread, SLOT(deleteLater()));
    connect(this, SIGNAL(scanNet(QString)), scanThread, SLOT(scanIps(QString)));
    connect(scanThread, SIGNAL(resultReady(QString)), this ,SLOT(handleResIP(QString)));
    this->currIp = 0;

    workerThread.start();
    emit this->scanNet(QString::number(this->currIp));
    }
    else
    {
        this->debug("running");
    }
}

void MainWindow::deletePlayer(struct player *stack, int playerNum)
{
    struct player *mover = stack;
    while(mover->playerNum != playerNum && mover->nextPlayer)
    {
        stack = mover;
        mover = mover->nextPlayer;
    }
    if(mover->playerNum == playerNum)
    {
        stack->nextPlayer = mover->nextPlayer;
        free(mover);
    }
}


void MainWindow::on_connect2robot_clicked()
{
    ui->clientList->addItem(ui->ipBox->text());
}

void MainWindow::on_cancelButton_clicked()
{
    this->currIp=255;
    workerThread.exit();

}
void MainWindow::handleResIP(const QString &res)
{
    this->debug("Scanned IP " + QString::number(this->currIp));
    ui->scanProg->setValue(this->currIp);
    if(res!="127.0.0.1")
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
    struct player *mover = &(this->playerStack);
    do{
        if(mover->isReady)
        {
            int err = XInputGetState(mover->joy_fd, &(mover->controller));
            if(err == ERROR_DEVICE_NOT_CONNECTED)
            {

                clearPlayerCont(mover);
            }
        }
    }while(mover->nextPlayer);
}
void MainWindow::clearPlayerCont(struct player *play)
{
   debug("Controller DC'ED");
   play->isReady=false;
   play->joy_fd = -1;
}

void MainWindow::updateJoyGUI()
{
    if(ui->player1->isVisible())
    {
        ui->p1_val_leftX->display(this->playerStack.controller.Gamepad.sThumbLX);
        ui->p1_val_leftY->display(this->playerStack.controller.Gamepad.sThumbLY);
        ui->p1_val_rightX->display(this->playerStack.controller.Gamepad.sThumbRX);
        ui->p1_val_rightY->display(this->playerStack.controller.Gamepad.sThumbRY);
        ui->p1_val_but->setText(QString::number(this->playerStack.controller.Gamepad.wButtons));
    }

}


void MainWindow::on_p1_conCont_clicked()
{
    bool contConn[16];
    bool contFound = false;
    struct player *mover = &(this->playerStack);
    memset(contConn,0, sizeof(contConn));
    while(mover->nextPlayer)
    {
        if(mover->joy_fd <16 && mover->joy_fd>=0)
            contConn[mover->joy_fd] = true;
    }
    for(int i=0; i<16 && !contFound; i++)
    {
        int error=XInputGetState(i,&(playerStack.controller));
        if(error==ERROR_SUCCESS && !contConn[i])
        {
                debug("Connect Successful");
                playerStack.joy_fd=i;
                contFound=true;
                playerStack.isReady=true;
        }
    }
}
